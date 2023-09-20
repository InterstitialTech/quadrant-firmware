/*
    Quadrant.h - Library for using Quadrant
    Created by Josh Muffin Gordonson, July 26 2023
    Released under the CERN OHL 2.0
*/
#ifndef Quadrant_h
#define Quadrant_h

#include "Arduino.h"
#include "Adafruit_VL53L0X.h"
#include <SoftwareSerial.h>

#define LOX0_ADDRESS 0x30
#define LOX1_ADDRESS 0x31
#define LOX2_ADDRESS 0x32
#define LOX3_ADDRESS 0x33

//led pins
#define LED0 0
#define LED3 12
#define LED2 18
#define LED1 23

// set the pins to shutdown
#define SHT_LOX0 1
#define SHT_LOX3 13
#define SHT_LOX2 19
#define SHT_LOX1 24



class Quadrant
{
    public:
        Quadrant();
        void begin();
        int readLidar(uint8_t id=4);
        int setLidarId(uint8_t lidarId, uint8_t id=0);
        void writeDac(uint8_t dac, int dacData);
        //void writeMidi(uint8_t midiData);
        void setLidarContinuous(uint8_t id=4);
        int checkLidarContinuous(uint8_t id=4);
        int readLidarContinuous(uint8_t id=4);
        const uint8_t leds[4]={LED0, LED1, LED2, LED3};
    private:
        void _disableLidars();
        //SerialPIO _midi=SerialPIO(11, SerialPIO::NOPIN);
        //Adafruit_VL53L0X _lidar[4]={_lox0, _lox1, _lox2, _lox3};
        Adafruit_VL53L0X _lox0= Adafruit_VL53L0X();
        Adafruit_VL53L0X _lox1= Adafruit_VL53L0X();
        Adafruit_VL53L0X _lox2= Adafruit_VL53L0X();
        Adafruit_VL53L0X _lox3= Adafruit_VL53L0X();
        VL53L0X_RangingMeasurementData_t _measure[4];
        VL53L0X_RangingMeasurementData_t _measure1;
        // VL53L0X_RangingMeasurementData_t _measure2;
        // VL53L0X_RangingMeasurementData_t _measure3;
        const uint8_t _dacAddress[4]={0x16,0x14,0x12,0x10};
        const uint8_t _lidarAddress[4]={LOX0_ADDRESS, LOX1_ADDRESS, LOX2_ADDRESS, LOX3_ADDRESS};
        const uint8_t _lidarEnable[4]={SHT_LOX0, SHT_LOX1, SHT_LOX2, SHT_LOX3};
  };

#endif
