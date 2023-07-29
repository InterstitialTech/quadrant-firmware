#include "quadrant.h"

int datas[4];
Quadrant myquad;

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
  for(int x=0;x<4;x++){
    if(myquad.checkLidarContinuous(x)){
      datas[x] = myquad.readLidarContinuous(x);
      myquad.writeDac(x, datas[x]);
      if(x==2){
      }
    }
  }

}
