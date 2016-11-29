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


const uint32_t Potentiometer = PE_3;
float value = 0;
int menu[5] = {0};
int pageNum;

void potentiometer(){
  uiInputTick();

  OrbitOledMoveTo(68, 18);

  value = analogRead(Potentiometer);
  int menuSize = sizeof(menu)/sizeof(int);
  for(int i = 0; i <  sizeof(menu)/sizeof(int); i++){
    menu[i] = (4095/menuSize) * (i);
    
  }
  
  if(value >= menu[0] && value < menu[1]){
    OrbitOledDrawString("Feed  ");

        currentMenuPage = Feeding;
  }
  else if(value >= menu[1] && value < menu[2]){
    OrbitOledDrawString("Clean  ");

    currentMenuPage = Cleaning;
  }
  else if(value >= menu[2] && value < menu[3]){
    OrbitOledDrawString("Health");
    currentMenuPage = Medicine;
  }
  else if(value >= menu[3] && value < menu[4]){
    OrbitOledDrawString("Games  ");
    currentMenuPage = Games;
  }
  else if(value >= menu[4] && value <= 4095){
    OrbitOledDrawString("Stats   ");
    currentMenuPage = Stats;
  }
  
  while(gameMenuState.buttons[1].isRising){
    pageEnter = 1;
    Serial.print(pageEnter);
    OrbitOledClearBuffer();
   // OrbitOledClear();
    selectionScreen(currentMenuPage, pageEnter);
  }
  Serial.print(value);
  Serial.print("\n");

}
static void uiInputTick(){
  for(int i = 0; i < ButtonCount; ++i )
  {
    // Only look for Rising Edge Signals.
    bool previousState = gameMenuState.buttons[i].state;
    gameMenuState.buttons[i].state = digitalRead(Buttons[i]);
    gameMenuState.buttons[i].isRising = (!previousState && gameMenuState.buttons[i].state);
  }
}

