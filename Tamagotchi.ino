#include <FillPat.h>
#include <LaunchPad.h>
#include <OrbitBoosterPackDefs.h>
#include <OrbitOled.h>
#include <OrbitOledChar.h>
#include <OrbitOledGrph.h>
#include <stdlib.h>
#include <Wire.h>

void printFrog();
void printFish();

void WireInit();
void GameInit() {
  OrbitOledInit();
  OrbitOledClear();
  OrbitOledClearBuffer();
  OrbitOledSetFillPattern(OrbitOledGetStdPattern(iptnSolid));
  OrbitOledSetDrawMode(modOledSet);
  //  OrbitOledSetDrawColor('p');
}


void setup() {
  WireInit();
  GameInit();
  Serial.begin(9600);
  delay(100);



}

void loop() {
  printFrog();

  OrbitOledUpdate();
  //  printFish();
  // put your main code here, to run repeatedly:
  OrbitOledUpdate();
  delay(50);
  //  OrbitOledClear();
  
}

