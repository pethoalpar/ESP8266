#include <dummy.h>

int outpin = 0;
int button = 16;
int buttonState = 0;
int ledState = 0;

void setup() {
  pinMode(outpin, OUTPUT);
  pinMode(button, INPUT);
  Serial.begin(9600);
}

void loop() {
   buttonState=digitalRead(button); 
   Serial.println(buttonState);
   if (buttonState == 1)
     {
      if(ledState == 0) {
        digitalWrite(outpin, HIGH); 
        ledState = 1;
      }else{
        digitalWrite(outpin, LOW); 
        ledState = 0;
      }
      delay(2000);
   }  
  delay(300);
}
