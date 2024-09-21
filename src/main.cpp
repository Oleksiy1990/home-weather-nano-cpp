#include <Arduino.h>

String response;
const char end_char{'\n'};
char buf[50];

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
}

void loop() {
  /*
  Serial.write("AT+GMR\r\n");
  Serial.flush();
  delay(200);
  response = Serial.readStringUntil(end_char);
  response.toCharArray(buf, 50);
  Serial.write(buf);
  Serial.write('\n');
  Serial.flush();
  delay(2000);
  */
  Serial.write("AT+UART_DEF=9600,8,1,0,0\r\n");
  Serial.flush();
  delay(200);
  //response = "";
 
  response = Serial.readStringUntil(end_char);
  response.toCharArray(buf, 50);
  Serial.write(buf);
  Serial.write('\n');
  Serial.flush();
  memset(buf,0,sizeof(buf));
  delay(2000);
  
  // put your main code here, to run repeatedly:
}
