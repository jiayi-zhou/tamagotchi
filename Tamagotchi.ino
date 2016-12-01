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
#include <time.h>
#include <string>
#include <stdint.h>


const uint32_t SwitchCount = 2;
const uint32_t ButtonCount = 4;
const uint32_t Switches[SwitchCount] = { PA_7, PA_6 };
const uint32_t Buttons[ButtonCount] = { PD_2, PE_0, PUSH1, PUSH2 };
const uint32_t Potentiometer = PE_3;
int pageEnter = 0;
int viewMenu = 1;

struct stats {
  int hunger;
  int health;
  int happiness;
  int hygiene;
} stat;

struct ButtonState
{
  bool state;
  bool isRising;
};


struct InputState {
  bool switches [SwitchCount];
  struct ButtonState buttons [ButtonCount];

} gameInputState;

void potentiometer();
void DeviceInit();
void WireInit();
int sprite;

void GameInit() {
  OrbitOledInit();
  OrbitOledClear();
  OrbitOledClearBuffer();
  OrbitOledSetFillPattern(OrbitOledGetStdPattern(iptnSolid));
  OrbitOledSetDrawMode(modOledSet);

  //  OrbitOledSetDrawColor('p');
  for (int i = 0; i < SwitchCount; ++i )
    pinMode(Switches[i], INPUT);
  for (int i = 0; i < ButtonCount; ++i )
    pinMode(Buttons[i], INPUT);

  pinMode(Buttons[2], INPUT_PULLUP);
}

static int pageMain = 0;

void setup() {
  Serial.begin(9600);
  WireInit();
  GameInit();
  sprite =  4;

  stat.hunger = 100;
  stat.health = 100;
  stat.happiness = 100 ;
  stat.hygiene = 100;

}

void loop() {

  switch (pageMain) {
    case 0:
      homeScreen();
      OrbitOledClearBuffer();
      break;
    case 1:
      menuPage();
      break;
    case 2:
      bopIt();
      break;
    case 3:
      death();
      break;
  }

}
