#include <ESP8266WiFi.h>

const char* ssid     = "SSID";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "PASSWORD";

void setup() {
  WiFi.hostname("Esp8266_internet_checker");
  Serial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);
  WiFi.begin();
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED && i<10) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
}



void loop() {

  WiFiClient client;
  if (client.connect("www.google.com", 80))
  {
        //Serial.println("connected");
        digitalWrite(BUILTIN_LED,HIGH);
        client.stop();
        delay(2000);
     
    }
    else {
    digitalWrite(BUILTIN_LED,LOW);
    client.stop();
    delay(2000);
  }     
}
