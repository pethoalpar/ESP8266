#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(-1);

long counter = 0; 

void setup()   
{                
  // initialize with the I2C addr 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  

  // Clear the buffer.
  display.clearDisplay();
  
}

void loop() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Temperature");
  display.display();
  display.setTextSize(2);
  display.setCursor(0,9);
  display.println(counter++);
  display.display();
  delay(1000);
  display.clearDisplay();
}