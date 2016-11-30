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

void lose (int score) {
OrbitOledClearBuffer();
  OrbitOledMoveTo(0, 0);
  OrbitOledDrawString("Score: ");
  OrbitOledDrawChar('0' + activeGame.score);
   OrbitOledUpdate();
   Serial.print("lose");
  delay (10000);
}

int timeLim = 1000;

void btnPress(int b) {
  Serial.print("should print\n");
  OrbitOledMoveTo(0, 0);
  OrbitOledDrawString("Press Btn ");
  OrbitOledDrawChar('1' + b);
  OrbitOledUpdate();
  for(int i = 0; i < timeLim; i++){
    if(gameInputState.buttons[b].isRising){
      OrbitOledClear();
      OrbitOledMoveTo(0, 0);
      OrbitOledDrawString("Hell ya, you pressed it!!");
      OrbitOledUpdate();
      delay(1);
      break;
      
    }
    else if(!(gameInputState.buttons[b].isRising)){
      Serial.print(i);
      Serial.print("\n");

      OrbitOledClearBuffer();
//      break;
     // OrbitOledClear();
    }
  }
  //return 0;
  Serial.print(activeGame.score);
  Serial.print("\n");
}

void shakeDetect() {
  
  Serial.print("should print\n");
  OrbitOledMoveTo(0, 0);
  OrbitOledDrawString("Shake");
  OrbitOledUpdate();
  int timeLim = 0;
  while(timeLim < 5000){
    if (ShakeIsShaking()){
       OrbitOledMoveTo(0, 10);
      activeGame.score ++;
      Serial.print(activeGame.score);
      OrbitOledUpdate();
    }
    delay (1);
    timeLim ++;
  }


  if  ( timeLim >= 5000){
    lose (activeGame.score);}
}


void bopIt() {
  //  activeGame.playerCommand = (enum Command)(rand() % 5);
  uiInputTick();
  activeGame.playerCommand = (enum Command)1;
  switch (activeGame.playerCommand) {
    case Shake: {
        shakeDetect();

        break;
      }
    case PressBTN3:
      { 
        btnPress (1);
        break;
      }
    case PressBTN4: {
        btnPress (3);
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


