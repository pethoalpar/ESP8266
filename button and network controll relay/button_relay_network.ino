#include <dummy.h>
#include <ESP8266WiFi.h>

const char* ssid     = "Your wifi name";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "YOUR wifi password";

int outpin = 0;
int button = 16;
int buttonState = 0;
int ledState = 0;

WiFiServer server(18980);

void setup() {
  pinMode(outpin, OUTPUT);
  pinMode(button, INPUT);
  Serial.begin(9600);

  WiFi.begin(ssid, password); 
  IPAddress ip(192,168,1,3);   
  IPAddress gateway(192,168,1,1);   
  IPAddress subnet(255,255,255,0);   
  WiFi.config(ip, gateway, subnet);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print(".");
  }
  Serial.println("Wifi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
 
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if(!client){
    buttonState=digitalRead(button); 
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
  }

  while (client.connected()){
    if (client.available()){
      String request = client.readStringUntil('\r');
      Serial.println(request);
      client.println("HTTP/1.1 200 OK"); //

      client.println("Content-Type: text/html");
      client.println("Success");
      client.flush();
      Serial.println(request);
      if(request.indexOf("/ON") > -1){
        digitalWrite(outpin, LOW); // Turn LED ON
        ledState = 0;
      }
      if(request.indexOf("/OFF") >-1){
        digitalWrite(outpin, HIGH); // Turn LED OFF
        ledState = 1;
      }
    }else{
      buttonState=digitalRead(button); 
      if (buttonState == 1){
        if(ledState == 0) {
          digitalWrite(outpin, HIGH); 
          ledState = 1;
        }else{
          digitalWrite(outpin, LOW); 
          ledState = 0;
        }
        delay(2000);
      }  
    }
  }
}