#include <stdint.h>
#include <stdbool.h>

#include  "LaunchPad.h"
#include  "OrbitBoosterPackDefs.h"

#include  "OrbitOled.h"
#include  "OrbitOledGrph.h"
#include  "OrbitOledChar.h"
#include  "FillPat.h"

#include  "delay.h"


typedef enum Command
{
  Shake = 0,
  PressBTN3 = 1,
  PressBTN4 = 2,
  Switch1 = 3,
  Switch2 = 4,
} Command;

struct GameState {
  int score;
  bool isShaking;
  enum Command playerCommand;
} activeGame;


void GameUIInit() {
  gameInputState = { 0 };
  activeGame = { 0 };
}


int timeLim = 4000, timeTaken = 0, levelClear;

void btnPress(int b) {
  uiInputTick();
  if (gameInputState.buttons[b].isRising) {
    OrbitOledClearBuffer();
    OrbitOledMoveTo(0, 0);
    OrbitOledDrawString("Hell ya, you pressed it!!");
    OrbitOledUpdate();
    levelClear = 1;
    activeGame.score++;
    Serial.print(activeGame.score);
    Serial.print("\n");
  }
}

void bopIt() {
  //  activeGame.playerCommand = (enum Command)(rand() % 5);
  uiInputTick();
  levelClear = 0;
  

  activeGame.playerCommand = (enum Command)1;
  switch (activeGame.playerCommand) {
    case Shake: {
        //        shakeDetect();
        break;
      }
    case PressBTN3:

      {
        OrbitOledMoveTo(0, 0);
        OrbitOledDrawString("Press Btn 1");
        OrbitOledUpdate();
        while (timeTaken < timeLim && levelClear == 0) {
          btnPress (1);
          timeTaken ++;
        }

        if (timeTaken >= timeLim )
        {Serial.print("lose");}
        if (levelClear ==1){
        timeTaken =0;
        }
        break;
      }
    case PressBTN4: {
        btnPress (4);
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


