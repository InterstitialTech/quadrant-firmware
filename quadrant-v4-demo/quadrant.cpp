

#include <Arduino.h>
#include <Wire.h>
#include <MIDI.h>
#include "quadrant.h"

Quadrant::Quadrant(){
}

void Quadrant::begin(){
  //MIDI setup
  //using Transport = MIDI_NAMESPACE::SerialMIDI<SoftwareSerial>;
  //Transport serialMIDI(_midi);
  //MIDI_NAMESPACE::MidiInterface<Transport> MIDI((Transport&)serialMIDI);
  //MIDI.begin();
  _midi.begin(31250);

  //DAC setup
  Wire1.setSDA(6);
  Wire1.setSCL(7);
  Wire1.begin();

  //lidar pin setup
  pinMode(SHT_LOX0, OUTPUT);
  pinMode(SHT_LOX1, OUTPUT);
  pinMode(SHT_LOX2, OUTPUT);
  pinMode(SHT_LOX3, OUTPUT);
 
  digitalWrite(SHT_LOX0, LOW);
  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);

  //led setup 
  pinMode(LED0, OUTPUT); 
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  //lidar setup

  _disableLidars();
  delay(100);
  setLidarId(0);
  setLidarId(1);
  setLidarId(2);
  setLidarId(3);
  // setLidarId(_lidar[1], _lidarAddress[1]);
  // setLidarId(_lidar[2], _lidarAddress[2]);
  // setLidarId(_lidar[3], _lidarAddress[3]);

}

void Quadrant::writeDac(uint8_t dac, int dacData){
  if (dacData > 1023){ //limit dacData to 1023
    dacData = 1023;
  }
  Wire1.beginTransmission(byte(0x58));
  Wire1.write(_dacAddress[dac]);
  Wire1.write(dacData>>2);
  Wire1.write((dacData&0x03)<<6);
  Wire1.endTransmission();
 }

 void Quadrant::writeMidi(uint8_t midiData){
  _midi.write(midiData);   
 }


void Quadrant::_disableLidars(){
  digitalWrite(SHT_LOX0, LOW);    
  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
}

int Quadrant::setLidarId( uint8_t lidarId, uint8_t id) {
  // activating LOX1 and resetting LOX2

  if(id==0){id=_lidarAddress[lidarId];}
 
  digitalWrite(_lidarEnable[lidarId], HIGH);
  delay(100);
  // initing LOX
  digitalWrite(leds[lidarId], HIGH);
  switch(lidarId){
  case 0: 
    if(!_lox0.begin(id)) {
      //Serial.print(F("Failed to boot VL53L0X "));
      //Serial.println(lidarId);
      digitalWrite(leds[lidarId], LOW);
      return 1;
    }
  case 1:
    if(!_lox1.begin(id)) {
      //Serial.print(F("Failed to boot VL53L0X "));
      //Serial.println(lidarId);
      digitalWrite(leds[lidarId], LOW);
      return 1;
    }
  case 2:
    if(!_lox2.begin(id)) {
      //Serial.print(F("Failed to boot VL53L0X "));
      //Serial.println(lidarId);
      digitalWrite(leds[lidarId], LOW);
      return 1;
    }

  case 3:
    if(!_lox3.begin(id)) {
      //Serial.print(F("Failed to boot VL53L0X "));
      //Serial.println(lidarId);
      digitalWrite(leds[lidarId], LOW);
      return 1;
    }
  }
  //Serial.print(lidarId);
  //Serial.println(" Configured");
  return 0;
}

void Quadrant::setLidarContinuous(uint8_t id){
  switch(id){
    case 0:
      _lox0.startRangeContinuous();
    case 1:
      _lox1.startRangeContinuous();
    case 2:
      _lox2.startRangeContinuous();
    case 3:
      _lox3.startRangeContinuous();
    case 4:
      _lox0.startRangeContinuous();
      _lox1.startRangeContinuous();
      _lox2.startRangeContinuous();
      _lox3.startRangeContinuous();
  }

}

int Quadrant::checkLidarContinuous(uint8_t id){
  switch(id){
    case 0:
      if(_lox0.isRangeComplete()){
        return 1;
      }else{
        return 0;
      }
    case 1:
      if(_lox1.isRangeComplete()){
        return 1;
      }else{
        return 0;
      }
    case 2:
      if(_lox2.isRangeComplete()){
        return 1;
      }else{
        return 0;
      }
    case 3:
      if(_lox3.isRangeComplete()){
        return 1;
      }else{
        return 0;
      }
    case 4:
      if(_lox0.isRangeComplete()&&
          _lox1.isRangeComplete()&&
          _lox2.isRangeComplete()&&
          _lox3.isRangeComplete()){
        return 1;
      }else{
        return 0;
      }
  }
  return 0;
}

int Quadrant::readLidarContinuous(uint8_t id){
  int temp=0;
  switch(id){
    case 0:
      //digitalWrite(leds[0], HIGH);
      temp = _lox0.readRange();
      //digitalWrite(leds[0], LOW);
      return(temp);
    case 1:
      //digitalWrite(leds[1], HIGH);
      temp = _lox1.readRange();
      //digitalWrite(leds[1], LOW);
      return(temp);
    case 2:
      //digitalWrite(leds[2], HIGH);
      temp = _lox2.readRange();
      //digitalWrite(leds[2], LOW);
      return(temp);
    case 3:
      //digitalWrite(leds[3], HIGH);
      temp = _lox3.readRange();
      //digitalWrite(leds[3], LOW);
      return(temp);
  }
  return 0;
}

int Quadrant::readLidar(uint8_t lidarId) {
  digitalWrite(leds[lidarId], HIGH);
  switch(lidarId){
    case 0:
      _lox0.rangingTest(&_measure[lidarId], false); // pass in 'true' to get debug data printout!
    case 1:
      _lox1.rangingTest(&_measure[lidarId], false); 
    case 2:
      _lox2.rangingTest(&_measure[lidarId], false); 
    case 3:
      _lox3.rangingTest(&_measure[lidarId], false); 
    case 4:
    digitalWrite(leds[0], HIGH);
      _lox0.rangingTest(&_measure[0], false); 
      digitalWrite(leds[0], LOW);
      digitalWrite(leds[1], HIGH);
      _lox1.rangingTest(&_measure[1], false); 
      digitalWrite(leds[1], LOW);
      digitalWrite(leds[2], HIGH);
      _lox2.rangingTest(&_measure[2], false); 
      digitalWrite(leds[2], LOW);
      digitalWrite(leds[3], HIGH);
      _lox3.rangingTest(&_measure[3], false);
      digitalWrite(leds[3], LOW); 
  }
  
  digitalWrite(leds[lidarId], LOW);

  // print sensor one reading
  //Serial.print(lidarId);
  //Serial.print(F(": "));
  if(_measure[lidarId].RangeStatus != 4) {     // if not out of range
    //Serial.print(_measure[lidarId].RangeMilliMeter);
  } else {
    //Serial.print(F("Out of range"));
  }
  
  return _measure[lidarId].RangeMilliMeter;
}

