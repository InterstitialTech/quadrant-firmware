#include "quadrant.h"

#define LED_THRESH 180

Quadrant myquad;

int values[4];
char serial_buf[21];

void setup() {

  myquad.begin();
  Serial.begin(115200);
  myquad.setLidarContinuous();
  digitalWrite(myquad.leds[0],LOW);
  digitalWrite(myquad.leds[1],LOW);
  digitalWrite(myquad.leds[2],LOW);
  digitalWrite(myquad.leds[3],LOW);

}

void loop() {

  //myquad.writeMidi(hi);

  int value;

  for(int i=0; i<4; i++){

    if(myquad.checkLidarContinuous(i)){

      value = myquad.readLidarContinuous(i);

      if (value < LED_THRESH) {
        digitalWrite(myquad.leds[i], HIGH);
      } else {
        digitalWrite(myquad.leds[i], LOW);
      }

      myquad.writeDac(i, value);

      values[i] = value;

    }
  }

  sprintf(serial_buf, "%d %d %d %d", values[0], values[1], values[2], values[3]);
  Serial.println(serial_buf);

}
