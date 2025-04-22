#define BLYNK_TEMPLATE_ID "TMPL2HzEyj8qE"
#define BLYNK_TEMPLATE_NAME "DealATron"
#define BLYNK_AUTH_TOKEN "mv-cxMZtvhhN5sMGBZ1x40mXmtvn8AM0"

#include <Servo.h>
#include <SPI.h>
#include <WiFiS3.h>
#include <BlynkSimpleWifi.h>

char ssid[] = "esesyno";
char pass[] = "eniacpenn";

Servo disp;
Servo base;
boolean dispense = false;
int baseDeg = 0;
int players = 3;
int degSegment = 360 / players;
int remainingCards = 54;

const int trigPin = 12;
const int echoPin = 13;
float duration, distance;

BlynkTimer timer;



void sendSensorData() {
  Blynk.virtualWrite(V0, players);
  Blynk.virtualWrite(V1, remainingCards);
}

// Update number of players
BLYNK_WRITE(V2) {
  players = param.asInt();
  degSegment = 360 / players;
  Blynk.virtualWrite(V0, players);
}


BLYNK_WRITE(V3) {
  if (param.asInt() == 1) {
    remainingCards = 54;
    Blynk.virtualWrite(V1, remainingCards);
  }
}

void setup() {
  disp.attach(6);
  base.attach(5);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(1000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();

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
      delay(1);
    }

    delay(100);

    for (int i = 270; i >= 0; i--) {
      disp.write(i);
      delay(1);
    }

    delay(100);

    baseDeg = (baseDeg + degSegment) % 360;
    base.write(map(baseDeg, 0, 360, 0, 180));

    if (remainingCards > 0) {
      remainingCards--;
      Blynk.virtualWrite(V1, remainingCards);
    }

    delay(500);
    dispense = false;
  }

  delay(100);
}
