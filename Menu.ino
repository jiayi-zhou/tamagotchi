#include <stdbool.h>
#include <string.h>

static enum pages{
  Feeding = 1,
  Cleaning = 2,
  Medicine = 3,
  Stats = 4,
  Games = 5
} currentMenuPage;

struct menuState{
  struct ButtonState buttons [2];
}gameMenuState;

static void feedingPage(){
//   ;
   OrbitOledDrawString("Pick a food.");
   if(gameInputState.buttons[1].isRising){
    
  }
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

void selectionScreen(int pageNumber, int pageEnter){
  switch(pageNumber){
    case Feeding:
      OrbitOledMoveTo(0,0);
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

void openMenu(){
  
}

