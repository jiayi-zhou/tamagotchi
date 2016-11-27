#include <stdbool.h>
#include <string.h>

static enum pages{
  Feeding = 1,
  Cleaning = 2,
  Medicine = 3,
  Stats = 4,
  Games = 5
} currentMenuPage;
int pageEnter;

struct menuState{
  struct ButtonState buttons [2];
}gameMenuState;

static void feedingPage(){
 OrbitOledMoveTo(0,0);
 OrbitOledDrawString("Food!");
}

static void cleaningPage(){
 OrbitOledMoveTo(0,0);
 OrbitOledDrawString("Shake to clean!!");
}

static void medicinePage(){
 OrbitOledMoveTo(0,0);
 OrbitOledDrawString("Give medicine!!!");
}

static void statsPage(){
 OrbitOledMoveTo(0,0);
 OrbitOledDrawString("Stats go here.");
}

static void gamesPage(){
 OrbitOledMoveTo(0,0);
 OrbitOledDrawString("Choose a game!");
}

void selectionScreen(int pageNumber){
  switch(pageNumber){
    case Feeding:
      OrbitOledClear();
      while(pageEnter == 1){
        gamesPage();
      }
      break;
      
    case Cleaning:
      OrbitOledClear();
      while(pageEnter == 1){
        gamesPage();
      }
      break;
      
    case Medicine:
      OrbitOledClear();
      while(pageEnter == 1){
        gamesPage();
      }
      break;
      
    case Stats:
      OrbitOledClear();
      while(pageEnter == 1){
        gamesPage();
      }
      break;
      
    case Games:
      OrbitOledClear();
      while(pageEnter == 1){
        gamesPage();
      }
      break;
  }
  
  OrbitOledUpdate();
}

void openMenu(){
  
}

