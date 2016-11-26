#include <FillPat.h>
#include <LaunchPad.h>
#include <OrbitBoosterPackDefs.h>
#include <OrbitOled.h>
#include <OrbitOledChar.h>
#include <OrbitOledGrph.h>
#include <stdlib.h>
#include <Wire.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>

void potentiometer();
void DeviceInit();
void WireInit();
void GameInit() {
  OrbitOledInit();
  OrbitOledClear();
  OrbitOledClearBuffer();
  OrbitOledSetFillPattern(OrbitOledGetStdPattern(iptnSolid));
  OrbitOledSetDrawMode(modOledSet);
  //  OrbitOledSetDrawColor('p');
}
void DeviceInit();
void OrbitSetOled();

void movement();
void printFrog();

void printFish();
void bopIt();
static void back(){
    OrbitOledMoveTo(64, 0);
    OrbitOledLineTo(64, 32);
    OrbitOledMoveTo(68, 0);
    OrbitOledDrawString("health");
    movement();
}
void setup() {
  Serial.begin(9600);
 WireInit();
GameInit();
 DeviceInit();
  
  

}

void loop() {
  bopIt();
  /*potentiometer();
 back();
 printFrog();

  //printFish();
  
  // put your main code here, to run repeatedly:
  OrbitOledUpdate();
      delay(70);

  OrbitOledClear();*/
    
}
