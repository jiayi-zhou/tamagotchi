
int selectInt;
int charSelectState = 1;
int charSelection(){
  uiInputTick();
  if(charSelectState == 1){
    printSelection();
    selectInt = pickSelection();
  }
  if (gameInputState.buttons[1].isRising){
    OrbitOledClear();
    OrbitOledClearBuffer();
    charSelectState = 0;
    tamaInit(selectInt);
  }
  if(charSelectState == 0){
    pageMain = 0;
  }
  OrbitOledUpdate();
}

int pickSelection(){
  OrbitOledMoveTo(17,0);
  OrbitOledDrawString("Pick a Tama!");
    if (gameInputState.buttons[3].isRising && selectPos < 4) {
      selectPos++;
      OrbitOledClear();
    }
    if (gameInputState.buttons[2].isRising && selectPos > 0) {
      selectPos--;
      OrbitOledClear();
    }
    if(selectPos == 0){
      OrbitOledMoveTo(15, 26);
      OrbitOledPutBmp(16, 16, arrow);
    }
    else if(selectPos == 1){
      OrbitOledMoveTo(35, 26);
      OrbitOledPutBmp(16, 16, arrow);
    }
    else if(selectPos == 2){
      OrbitOledMoveTo(55, 26);
      OrbitOledPutBmp(16, 16, arrow);
    }
    else if(selectPos == 3){
      OrbitOledMoveTo(75, 26);
      OrbitOledPutBmp(16, 16, arrow);
    }
    else if(selectPos == 4){
      OrbitOledMoveTo(95, 26);
      OrbitOledPutBmp(16, 16, arrow);
    }
  return selectPos;
}
void printSelection() {
  OrbitOledMoveTo(15, 10);
  OrbitOledPutBmp(16, 16, frog);
  OrbitOledMoveTo(35, 10);
  OrbitOledPutBmp(16, 16, fish);
  OrbitOledMoveTo(55, 10);
  OrbitOledPutBmp(16, 16, alien);
  OrbitOledMoveTo(75, 10);
  OrbitOledPutBmp(16, 16, joe);
  OrbitOledMoveTo(95, 10);
  OrbitOledPutBmp(16, 16, platy);
}

