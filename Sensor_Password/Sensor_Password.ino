#include<Wire.h>

const int sensor = A0;
const int PIRSensor = 11;

const int ledR = A1;
const int ledY = A2;
const int ledB = A3;

const int changeButton = 12;
const int selectButton = 13;

int selectNum[2] = {};
int selectCount = 0;

int password[2] = {1,2};
bool unlocked = false;

int segPins[]={2,3,4,5,6,7,8,9};
byte digits[10][8]={
  {0,0,0,0,0,0,1,1},
  {1,0,0,1,1,1,1,1},
  {0,0,1,0,0,1,0,1},
  {0,0,0,0,1,1,0,1},
  {1,0,0,1,1,0,0,1},
  {0,1,0,0,1,0,0,1},
  {0,1,0,0,0,0,0,1},
  {0,0,0,1,1,0,1,1},
  {0,0,0,0,0,0,0,1},
  {0,0,0,0,1,0,0,1}
};

int countNum=0;

int sensorVal=0;

int benchmarkLight = 20;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  pinMode(changeButton, INPUT);
  pinMode(selectButton, INPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledY, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(PIRSensor, INPUT);
  for (int i = 0; i < 8; i++)  pinMode(segPins[i], OUTPUT);
}

void loop() {
  if(digitalRead(changeButton) == HIGH && digitalRead(selectButton) == LOW){
    countNum++;
    countNum %= 10;
    delay(250);
  }

  else if(digitalRead(changeButton) == LOW && digitalRead(selectButton) == HIGH){
    if (selectCount<2){
      selectNum[selectCount] = countNum;
      selectCount++;
      countNum = 0;
      delay(400);
    }
  }

  for (int i = 0; i < 8; i++)   digitalWrite(segPins[i], digits[countNum][i]);

  if (selectCount == 1)    digitalWrite(ledY, HIGH);
  else    digitalWrite(ledY, LOW);

  if (selectCount == 2){
      if ((selectNum[0] == password[0]) && (selectNum[1] == password[1]))   unlocked = true;
      else unlocked = false;

      selectCount = 0;
  }

  sensorVal = analogRead(sensor);
Serial.println(sensorVal);

  if (unlocked){
    digitalWrite(ledB, HIGH);
    digitalWrite(ledR, LOW);
  } else{
      digitalWrite(ledB, LOW);
      digitalWrite(ledR, HIGH);
    }
  Serial.println(sensorVal);
  if (!unlocked && (benchmarkLight > sensorVal) && digitalRead(PIRSensor) == HIGH){
    Wire.beginTransmission(4);
    Wire.write(1); 
    Wire.endTransmission();
  } else{
      Wire.beginTransmission(4);
      Wire.write(0); 
      Wire.endTransmission();
    }
    
}
