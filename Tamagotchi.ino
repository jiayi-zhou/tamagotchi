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
const uint32_t SwitchCount = 2;
const uint32_t ButtonCount = 2;
const uint32_t Switches[SwitchCount] = { PA_7, PA_6 };
const uint32_t Buttons[ButtonCount] = { PD_2, PE_0 };
int pageEnter = 0;

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
  for(int i = 0; i < SwitchCount; ++i )
    pinMode(Switches[i], INPUT);
  for(int i = 0; i < ButtonCount; ++i )
    pinMode(Buttons[i], INPUT);
}

void DeviceInit();
void OrbitSetOled();
void bopIt();

void setup() {
  Serial.begin(9600);
 WireInit();
GameInit();
  
  

}

void loop() {
bopIt();
// homeScreen();

  //printFish();
  
  // put your main code here, to run repeatedly:

    
}
