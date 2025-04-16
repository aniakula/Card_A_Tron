#include <Servo.h>

Servo disp;


void setup() {
  disp.attach(6);

}

void loop() {
  for(int i = 0; i < 360; i+=60){
    disp.write(i);
  }

  

  for(int i = 360; i >= -180; i-=3){
    disp.write(i);
    delay(15);
  }

}
