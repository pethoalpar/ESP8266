#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 5
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

char temperatureStr[5];

void setup() {
  Serial.begin(115200); 
  Serial.println("The board has started");

  sensors.begin();
}

void loop() {
  sensors.requestTemperatures();
  float temp1 = sensors.getTempCByIndex(0);
  dtostrf(temp1,2, 2, temperatureStr);

  Serial.println(temperatureStr);

  delay(500);
}
