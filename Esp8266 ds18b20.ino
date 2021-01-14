#include <SPI.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

char temperatureStr[5];

void setup()   
{                
   Serial.begin(9600);
  sensors.begin();
}

void loop() {

  sensors.requestTemperatures();
  float temp1 = sensors.getTempCByIndex(0);
  dtostrf(temp1,2, 2, temperatureStr);

  Serial.print(temp1);
  Serial.println("ºC");
  
  delay(1000);
 
}
