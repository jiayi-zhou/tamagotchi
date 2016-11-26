
#include <stdint.h>
#include <stdbool.h>

#include  "LaunchPad.h"
#include  "OrbitBoosterPackDefs.h"

#include  "OrbitOled.h"
#include  "OrbitOledGrph.h"
#include  "OrbitOledChar.h"
#include  "FillPat.h"

#include  "delay.h"

const uint32_t SwitchCount = 2;
const uint32_t ButtonCount = 2;
const uint32_t Switches[SwitchCount] = { PA_7, PA_6 };
const uint32_t Buttons[ButtonCount] = { PD_2, PE_0 };

struct ButtonState
{
  bool state;
  bool isRising;
};

typedef enum Command
{
  Shake = 0,
  PressBTN1 = 1,
  PressBTN2 = 2,
  Switch1 = 3,
  Switch2 = 4,
} Command;

struct InputState {
  bool switches [2];
  struct ButtonState buttons [2];

} gameInputState;

struct GameState {
  int score;
  bool isShaking;
  enum Command playerCommand;
} activeGame;

void GameUIInit() {
  OrbitOledInit();
  OrbitOledClear();
  OrbitOledClearBuffer();
  OrbitOledSetFillPattern(OrbitOledGetStdPattern(iptnSolid));
  gameInputState = { 0 };
  activeGame = { 0 };

  for (int i = 0; i < SwitchCount; ++i )
    pinMode(Switches[i], INPUT);
  for (int i = 0; i < ButtonCount; ++i )
    pinMode(Buttons[i], INPUT);
}

void bopIt() {
  activeGame.playerCommand = (enum Command)(rand() % 5);

  switch (activeGame.playerCommand) {
    case Shake:
      OrbitOledMoveTo(0, 0);
    OrbitOledDrawString("Shake");
      
      break;
    case PressBTN1:
       OrbitOledMoveTo(0, 0);
    OrbitOledDrawString("Press Btn1");
      
      break;
    case PressBTN2:
      OrbitOledMoveTo(0, 0);
    OrbitOledDrawString("Press Btn 2");
      
      break;
    case Switch1:
       OrbitOledMoveTo(0, 0);
    OrbitOledDrawString("Switch1");
     
      break;
    case Switch2:
       OrbitOledMoveTo(0, 0);
    OrbitOledDrawString("Switch2");
     
      break;
  }
  OrbitOledUpdate();
  delay(70);

  OrbitOledClear();
}

bool 

