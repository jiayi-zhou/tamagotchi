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
  PressBTN2 = 1,
   PressBTN3 = 2,
  PressBTN4 = 3,
  Switch1 = 4,
  Switch2 = 5,
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


int timeLim = 1300, timeTaken = 0, levelClear;

void lose () {
  OrbitOledClearBuffer();
  OrbitOledMoveTo(0, 0);
  OrbitOledDrawString("Game Over!");
  OrbitOledMoveTo(0, 10);
    OrbitOledDrawString("Score: ");

  String strScore = String(activeGame.score);
  char score[1024];
  strcpy(score, strScore.c_str());


  OrbitOledDrawString(score);
  OrbitOledUpdate();
  Serial.print("lose");
  delay (10000);


  pageMain = 0;
}

bool shaking ;
void shakeDetect() {

  ShakeTick();


  if (ShakeIsShaking()) {
    levelClear = 1;
    shaking = true;
    delay (100);

  }
}

void btnPress(int b) {
  uiInputTick();
  if (gameInputState.buttons[b].isRising) {
    OrbitOledClearBuffer();
    OrbitOledUpdate();
    levelClear = 1;
    activeGame.score++;
    Serial.print(activeGame.score);
    Serial.print("\n");
  }
}

void bopIt() {
 activeGame.playerCommand = (enum Command)(rand() % 6);
  uiInputTick();
  levelClear = 0;


  //activeGame.playerCommand = (enum Command)2;
  switch (activeGame.playerCommand) {
    case Shake: {
        Serial.print("should print\n");
        OrbitOledMoveTo(0, 0);
        OrbitOledClearBuffer();
        OrbitOledDrawString("Shake");
        OrbitOledUpdate();

        while (timeTaken < timeLim && levelClear == 0 && shaking == false) {
          ShakeInit();
          shakeDetect();
          delay (1);
          timeTaken ++;
        }

        if (shaking) {
          activeGame.score++;
          Serial.print(activeGame.score);
          Serial.print("\n");

          shaking = false;
        }
        if (timeTaken >= timeLim )
        { Serial.print("lose");
          lose ();
        }
        if (levelClear == 1) {
          timeTaken = 0;
        }
        break;
      }
    case PressBTN2:

      {
        OrbitOledMoveTo(0, 0);
        OrbitOledDrawString("Press Btn 2");
        OrbitOledUpdate();
        while (timeTaken < timeLim && levelClear == 0) {
          btnPress (1);
          delay (1);
          timeTaken ++;
        }

        if (timeTaken >= timeLim )
        { Serial.print("lose");
          lose ();
        }
        if (levelClear == 1) {
          timeTaken = 0;
        }
        break;
      }
      case PressBTN3:

      {
        OrbitOledMoveTo(0, 0);
        OrbitOledDrawString("Press Btn 3");
        OrbitOledUpdate();
        while (timeTaken < timeLim && levelClear == 0) {
          btnPress (2);
          delay (1);
          timeTaken ++;
        }

        if (timeTaken >= timeLim )
        { Serial.print("lose");
          lose ();
        }
        if (levelClear == 1) {
          timeTaken = 0;
        }
        break;
      }
    case PressBTN4:
      {
        OrbitOledMoveTo(0, 0);
        OrbitOledDrawString("Press Btn 4");
        OrbitOledUpdate();
        while (timeTaken < timeLim && levelClear == 0) {
          btnPress (3);
          delay (1);
          timeTaken ++;
        }

        if (timeTaken >= timeLim )
        { Serial.print("lose");
          lose ();
        }
        if (levelClear == 1) {
          timeTaken = 0;
        }
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




