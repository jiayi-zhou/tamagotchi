#include <stdint.h>
#include <stdbool.h>

#include  "LaunchPad.h"
#include  "OrbitBoosterPackDefs.h"

#include  "OrbitOled.h"
#include  "OrbitOledGrph.h"
#include  "OrbitOledChar.h"
#include  "FillPat.h"

#include  "delay.h"

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

void bopuiInputTick() {
  for (int i = 0; i < ButtonCount; ++i )
  {
    // Only look for Rising Edge Signals.
    bool previousState = gameInputState.buttons[i].state;
    gameInputState.buttons[i].state = digitalRead(Buttons[i]);
    gameInputState.buttons[i].isRising = (!previousState && gameInputState.buttons[i].state);
  }
}

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

void lose (int score) {
OrbitOledClearBuffer();
  OrbitOledMoveTo(0, 0);
  OrbitOledDrawString("Score: ");
  OrbitOledDrawChar('0' + activeGame.score);
   OrbitOledUpdate();
   Serial.print ("lose");
  delay (10000);
}
int pass = 0;
void btnPress(int b) {
  bopuiInputTick();
  Serial.print("should print\n");
  OrbitOledMoveTo(0, 0);
  OrbitOledDrawString("Press Btn ");
  OrbitOledDrawChar('1' + b);
  OrbitOledUpdate();
  int timeLim = 0;
  while(timeLim < 5000 && pass == 0){
    if (gameInputState.buttons[b].isRising) {
      //  OrbitOledClear();
      OrbitOledMoveTo(0, 10);
      OrbitOledDrawString("Pressed ");
      activeGame.score ++;
      Serial.print(activeGame.score);
      OrbitOledUpdate();
      pass = 1;     
    }
    delay (1);
    timeLim ++;
  }


  if  ( timeLim >= 5000 && pass == 0){
    lose (activeGame.score);}
}

void shakeDetect() {
  
  Serial.print("should print\n");
  OrbitOledMoveTo(0, 0);
  OrbitOledDrawString("Shake");
  OrbitOledUpdate();
  int timeLim = 0;
  while(timeLim < 5000 && pass == 0){
    if (ShakeIsShaking()){
       OrbitOledMoveTo(0, 10);
      activeGame.score ++;
      Serial.print(activeGame.score);
      OrbitOledUpdate();
      pass = 1; 
    }
    delay (1);
    timeLim ++;
  }


  if  ( timeLim >= 5000 && pass == 0){
    lose (activeGame.score);}
}


void bopIt() {
  //  activeGame.playerCommand = (enum Command)(rand() % 5);

  activeGame.playerCommand = (enum Command)0;
  switch (activeGame.playerCommand) {
    case Shake: {
        shakeDetect();

        break;
      }
    case PressBTN1:
      { pass = 0;
        btnPress (0);
        break;
      }
    case PressBTN2: {
        pass = 0;
        btnPress (1);
        break;
      }
    case Switch1: {
        OrbitOledMoveTo(0, 0);
        OrbitOledDrawString("Switch1");
        break;
      }
    case Switch2: {
        OrbitOledMoveTo(0, 0);
        OrbitOledDrawString("Switch2");
        break;
      }
  }
  //OrbitOledClearBuffer();
  OrbitOledUpdate();
  //delay(1000);

  //OrbitOledClear();
}


