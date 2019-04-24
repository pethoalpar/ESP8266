//declare the pins used by the module 
const int echoPin = D5; 
const int trigPin = D3;
//declare 2 variables which help us later to calculate the distance 

long duration; 
double distance;

void setup() {  //start the serial communication with the computer at 115200 bits/s  
  Serial.begin(115200); 
  Serial.println("The board has started");
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
}

void loop() {  //set the trigPin to LOW in order to prepare for the next reading  
  digitalWrite(trigPin, LOW);

  //delay for 2 microseconds  
  delayMicroseconds(2);
  //generate an ultrasound for 10 microseconds then turn off the transmitter  
  digitalWrite(trigPin, HIGH);  
  delayMicroseconds(10);  
  digitalWrite(trigPin, LOW);
  //reads the echoPin, returns the sound wave travel time in microseconds  
  duration = pulseIn(echoPin, HIGH);
  //using the formula shown in the guide, calculate the distance  
  distance = duration*0.034/2;
  //print the distance in Serial Monitor  
  Serial.print("Distance: ");  
  Serial.print(distance);  
  Serial.println(" cm"); 
  }
