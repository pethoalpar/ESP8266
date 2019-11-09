#include <SPI.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>


FirebaseData firebaseData;
FirebaseJson json;

const char* ssid     = "SSID";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "Wi-Fi Password";

const long utcOffsetInSeconds = 3600 * 2;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", utcOffsetInSeconds);

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

char temperatureStr[5];
void setup()
{
  Firebase.begin("https://your project id.firebaseio.com", "secret key from firebase");
  Firebase.reconnectWiFi(true);
  Firebase.setMaxRetry(firebaseData, 3);
  Firebase.setMaxErrorQueue(firebaseData, 30);
  Firebase.enableClassicRequest(firebaseData, true);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
  }

  sensors.begin();
  WiFi.begin(ssid, password);             // Connect to the network
  digitalWrite(LED_BUILTIN, LOW);
  timeClient.begin();
}

void loop() {

  sensors.requestTemperatures();
  float temp1 = sensors.getTempCByIndex(0);
  dtostrf(temp1, 2, 2, temperatureStr);

  if (WiFi.status() == WL_CONNECTED) {
    json.clear();
    json.add("device", "espBedroom");
    timeClient.update();
    //display.println(WiFi.localIP());
    json.add("epochTime", (double)timeClient.getEpochTime());
    json.add("formatedTime", timeClient.getFormattedTime());
    json.add("temp", (double)temp1);
    Firebase.pushJSON(firebaseData, "Bedroom/Temp", json);
  }


  delay(1000 * 60 * 2);
}
