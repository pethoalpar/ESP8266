double air_quality;

void setup()
{
  Serial.begin(9600);
  delay(10);

}

void loop()
{
   air_quality = ((analogRead(A0)/1024.0)*100.0);
  Serial.print("Air Quality: ");
  Serial.print(air_quality);
  Serial.println("  PPM");
  Serial.println();

  delay(2000);      
}
