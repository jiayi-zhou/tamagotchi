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
#include <string>
int viewMenu = 1;
float value = 0;
int menu[5] = {0};
int pageNum;
int changePage = 0;

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
  tamaFeeding(revPlaty, eatingPlaty);
  printBanana();
  if (gameInputState.buttons[1].isRising) {
    stat.hunger += 30;
    

  }

  if (gameInputState.buttons[0].isRising)
  {
    OrbitOledClearBuffer();
    OrbitOledClear();
    pageMain = 0;
    viewMenu = 1;
    changePage = 0;
  }
  OrbitOledUpdate();

}


void cleaningPage() {
  ShakeTick();
  uiInputTick();
  bool shaking = false;
  
  switch (sprite) {
    case 0:
      tamaDoingThings (frog);
      break;
    case 1:
      tamaDoingThings(fish);
      break;
    case 2:
      tamaDoingThings(platy);
      break;
    case 3:
      tamaDoingThings(joe);
      break;
    case 4:
      tamaDoingThings(alien);
      break;
  }

  if (ShakeIsShaking()) {
    Serial.print("shake");
    shaking = true;
  }
  else if (shaking)
  {
    delay (1000);
    shaking = false;
    stat.hygiene += 100;
  }

  if (gameInputState.buttons[0].isRising)
  {
    OrbitOledClearBuffer();
    OrbitOledClear();
    pageMain = 0;
    viewMenu = 1;
    changePage = 0;
  }

  OrbitOledUpdate();

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
  String strHunger = String(stat.hunger);
  char hunger[1024];
  strcpy(hunger, strHunger.c_str());

  String strHealth = String(stat.health);
  char health[1024];
  strcpy(health, strHealth.c_str());

  String strHappiness = String(stat.happiness);
  char happiness[1024];
  strcpy(happiness, strHappiness.c_str());

  String strHygiene = String(stat.hygiene);
  char hygiene[1024];
  strcpy(hygiene, strHygiene.c_str());


  OrbitOledMoveTo(0, 0);
  OrbitOledDrawString("Hunger: ");
  OrbitOledDrawString(hunger);

  OrbitOledMoveTo(0, 8);
  OrbitOledDrawString("Health: ");
  OrbitOledDrawString(health);

  OrbitOledMoveTo(0, 16);
  OrbitOledDrawString("Happy: ");
  OrbitOledDrawString(happiness);

  OrbitOledMoveTo(0, 24);
  OrbitOledDrawString("Hygiene: ");
  OrbitOledDrawString(hygiene);
  OrbitOledUpdate();

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

  //Serial.print("menu\n");
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
      //  Serial.print(pageEnter);
      viewMenu = 0;
      selectionScreen(currentMenuPage, pageEnter);
    }
  }
  OrbitOledUpdate();

  if (gameInputState.buttons[0].isRising)
  {
    OrbitOledClear();
    pageMain = 0;
    viewMenu = 1;
    changePage = 0;
  }

}

void selectionScreen(int pageNumber, int pageEnter) {
  OrbitOledClearBuffer();
  OrbitOledUpdate();
  uiInputTick();
  changePage = 1;
  switch (pageNumber) {
    case Feeding:
      OrbitOledMoveTo(0, 0);
      OrbitOledDrawString("Pick a food.");
      
      while (changePage == 1) {
        feedingPage();

      }
      break;

    case Cleaning: 
    OrbitOledMoveTo(0, 0);
  OrbitOledDrawString("Shake to clean!!");
      while (changePage == 1) {
        cleaningPage();
      }
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
