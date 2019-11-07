#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

char temperatureStr[5];

Adafruit_SSD1306 display(-1);

void setup()   
{                
  // initialize with the I2C addr 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  

  // Clear the buffer.
  display.clearDisplay();
  sensors.begin();
}

void loop() {

  sensors.requestTemperatures();
  float temp1 = sensors.getTempCByIndex(0);
  dtostrf(temp1,2, 2, temperatureStr);
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Temperature");
  display.display();
  display.setTextSize(2);
  display.setCursor(0,9);
  display.print(temperatureStr);
  display.println(" C");
  display.display();
  delay(1000);
  }
