#include <stdbool.h>
#include <string.h>

static enum pages{
  Feeding = 1,
  Cleaning = 2,
  Medicine = 3,
  Stats = 4,
  Games = 5,
  Home = 0,
} currentMenuPage;

struct menuState{
  struct ButtonState buttons [2];
}gameMenuState;

static void feedingPage(){
 uiInputTick();

   OrbitOledDrawString("Pick a food.");
   if(gameInputState.buttons[1].isRising){
    
  }
}

static void pageInputTick(){
  for(int i = 0; i < ButtonCount; ++i )
  {
    // Only look for Rising Edge Signals.
    bool previousState = gameMenuState.buttons[i].state;
    gameMenuState.buttons[i].state = digitalRead(Buttons[i]);
    gameMenuState.buttons[i].isRising = (!previousState && gameMenuState.buttons[i].state);
  }
}

static void cleaningPage(){

 OrbitOledMoveTo(0,0);
 OrbitOledDrawString("Shake to clean!!");


 if(gameInputState.buttons[0].isRising)
  {
    Serial.print("pressed");
    OrbitOledClearBuffer();
    OrbitOledClear();
    currentMenuPage = Home;
  }
/*

 if(gameMenuState.buttons[0].isRising){
    OrbitOledClear();
    pageEnter = 1;
    Serial.print(pageEnter);
    OrbitOledClearBuffer();
    OrbitOledClear();
    
    selectionScreen(0, pageEnter);
  }*/
}

static void medicinePage(){
   uiInputTick();

 OrbitOledMoveTo(0,0);
 OrbitOledDrawString("Give medicine!!!");
}

static void statsPage(){
   uiInputTick();

 OrbitOledMoveTo(0,0);
 OrbitOledDrawString("Stats go here.");
}

static void gamesPage(){
   uiInputTick();

 OrbitOledMoveTo(0,0);
 OrbitOledDrawString("Choose a game!");
}

void selectionScreen(int pageNumber, int pageEnter){
 // pageInputTick();
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
    case Home:
     potentiometer();
      break;
  }
  
  OrbitOledUpdate();
}

void openMenu(){
  
}

