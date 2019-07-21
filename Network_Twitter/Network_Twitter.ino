#include <Wire.h>
#include <Twitter.h>
#include <SPI.h>
#include <WiFi.h>

int locked = 0;

char ssid[] = "ollehEgg_419";  //연결할 무선 네트워크 이름을 입력해주세요.
char pass[] = "info10019";      //비밀번호를 입력해주세요.

Twitter twitter("3636103272-L5urY3iQPaSf3vBVU9oE8TvpyPa7CnU8xnKeHzY"); 

char msg[] = "For someone came to my house ! WTF!!";
int num =0;
void setup() {
  Serial.begin(9600);
  Wire.begin(4);                
  Wire.onReceive(receiveEvent); 
/*시작*/

  delay(1000);
  WiFi.begin(ssid, pass); 
  
  Serial.begin(9600);

  /*종료*/
}

void loop() {
   
   if(locked==1){
     delay(500);
     char tmp[10];
     sprintf(tmp," %d",num);
     char str[100];
     strcpy(str, msg);
     strcat(str, tmp);
    
     
     Serial.println("connecting ...");  //와이파이 연결후 메세지 보내기 시작 전에 확인
  
      if (twitter.post(str)) {           //메세지를 전송 확인
 
      int status = twitter.wait(&Serial);  //메세지 보내기가 끝난 후 트위터로부터 상태전달 받음
      if (status == 200) {                 //200을 전달받으면 
        Serial.println("OK.");             //성공된 것이므로 시리얼 모니터에 OK출력
      } else {                             //아닐 경우 실패 메세지와 전달받은 값 출력
        Serial.print("failed : code ");
        Serial.println(status);
      }
    } else {                              //연결부터 실패 했을 경우
      Serial.println("connection failed.");
    }
    locked=0;
    num++;
    delay(10000);
   }
}

void receiveEvent(int howMany)
{
  locked = Wire.read();    
  Serial.println(locked);        
}
