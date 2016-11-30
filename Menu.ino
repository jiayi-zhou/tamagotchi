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

int viewMenu = 1;
float value = 0;
int menu[5] = {0};
int pageNum;


static enum pages {
  Feeding = 1,
  Cleaning = 2,
  Medicine = 3,
  Stats = 4,
  Games = 5,
} currentMenuPage;

struct menuState {
  struct ButtonState buttons [2];
} gameMenuState;

static void feedingPage() {
  uiInputTick();


  OrbitOledDrawString("Pick a food.");
  if (gameInputState.buttons[1].isRising) {

  }
  if (gameInputState.buttons[0].isRising)
  {
    OrbitOledClearBuffer();
    OrbitOledClear();
    pageMain = 0;
    viewMenu = 1;
  }
   
}
/*
  static void pageInputTick() {
  for (int i = 0; i < ButtonCount; ++i )
  {
    // Only look for Rising Edge Signals.
    bool previousState = gameMenuState.buttons[i].state;
    gameMenuState.buttons[i].state = digitalRead(Buttons[i]);
    gameMenuState.buttons[i].isRising = (!previousState && gameMenuState.buttons[i].state);
  }
  }*/

static void cleaningPage() {

  OrbitOledMoveTo(0, 0);
  OrbitOledDrawString("Shake to clean!!");
  tamaDoingThings (frog );

  if (gameInputState.buttons[0].isRising)
  {
    OrbitOledClearBuffer();
    OrbitOledClear();
    pageMain = 0;
   // viewMenu = 1;
  }

}

static void medicinePage() {
  uiInputTick();

  OrbitOledMoveTo(0, 0);
  OrbitOledDrawString("Give medicine!!!");
  if (gameInputState.buttons[0].isRising)
  {

    OrbitOledClearBuffer();
    OrbitOledClear();
    pageMain = 0;
     viewMenu = 1;
  }
}

static void statsPage() {
  uiInputTick();

  OrbitOledMoveTo(0, 0);
  OrbitOledDrawString("Stats go here.");
  if (gameInputState.buttons[0].isRising)
  {

    OrbitOledClearBuffer();
    OrbitOledClear();
    pageMain = 0;
     viewMenu = 1;
  }
}

static void gamesPage() {
  uiInputTick();

  OrbitOledMoveTo(0, 0);
  OrbitOledDrawString("Choose a game!");
  if (gameInputState.buttons[0].isRising)
  {

    OrbitOledClearBuffer();
    OrbitOledClear();
    pageMain = 0;
     viewMenu = 1;
  }
}


void menuPage() {

  Serial.print("menu\n");
   uiInputTick();
 if (viewMenu == 1) {
    OrbitOledMoveTo(0, 24);
    OrbitOledDrawString("Menu: ");

    value = analogRead(Potentiometer);
    int menuSize = sizeof(menu) / sizeof(int);
    for (int i = 0; i <  sizeof(menu) / sizeof(int); i++) {
      menu[i] = (4095 / menuSize) * (i);

    }

    if (value >= menu[0] && value < menu[1]) {
      OrbitOledDrawString("Feed  ");

      currentMenuPage = Feeding;
    }
    else if (value >= menu[1] && value < menu[2]) {
      OrbitOledDrawString("Clean  ");

      currentMenuPage = Cleaning;
    }
    else if (value >= menu[2] && value < menu[3]) {
      OrbitOledDrawString("Health");
      currentMenuPage = Medicine;
    }
    else if (value >= menu[3] && value < menu[4]) {
      OrbitOledDrawString("Games  ");
      currentMenuPage = Games;
    }
    else if (value >= menu[4] && value <= 4095) {
      OrbitOledDrawString("Stats   ");
      currentMenuPage = Stats;
    }

   
    if (gameInputState.buttons[1].isRising) {
      pageEnter = 1;
      Serial.print(pageEnter);
      viewMenu = 0;
      selectionScreen(currentMenuPage, pageEnter);
    }
  }
  OrbitOledUpdate();

  if (gameInputState.buttons[0].isRising)
  {
    OrbitOledClear();
    pageMain = 0;
    viewMenu =1;
  }

}

void selectionScreen(int pageNumber, int pageEnter) {
  OrbitOledClearBuffer();
  OrbitOledUpdate();
  uiInputTick();
  switch (pageNumber) {
    case Feeding:
      OrbitOledMoveTo(0, 0);
      feedingPage();
      break;

    case Cleaning:
      cleaningPage();
      break;

    case Medicine:
      medicinePage();
      break;

    case Stats:
      statsPage();
      break;

    case Games:
      gamesPage();
      break;

  }

  OrbitOledUpdate();
}
