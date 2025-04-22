#include <Servo.h>

Servo disp;
Servo base;
boolean dispense = false;
int baseDeg = 0;
int players = 3;
int degSegment = 360 / players;
const int trigPin = 12;  
const int echoPin = 13; 
float duration, distance; 

void setup() {
  disp.attach(6);
  base.attach(5);
  pinMode(trigPin, OUTPUT);  
  pinMode(echoPin, INPUT);  
  Serial.begin(9600); 
}

void loop() {
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2);  
  digitalWrite(trigPin, HIGH);  
  delayMicroseconds(10);  
  digitalWrite(trigPin, LOW); 

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.0343) / 2; 

  if (distance <= 2.0) {
    dispense = true;
    Serial.print("Distance: ");  
    Serial.println(distance);
  }  

  if (dispense) {
    for (int i = 0; i <= 270; i++) {
      disp.write(i);
      delay(1);  // small delay for servo to move
    }

    delay(100);  // hold position for a bit

    for (int i = 270; i >= 0; i--) {
      disp.write(i);
      delay(1);
    }

    delay(100);

    // Move the base to the next player
    baseDeg = (baseDeg + degSegment) % 360;  // wrap around if needed
    base.write(map(baseDeg, 0, 360, 0, 180));  // map 360 degrees to servo range

    delay(500);  // give time for base to rotate

    dispense = false;
  } 

  delay(100);
}
