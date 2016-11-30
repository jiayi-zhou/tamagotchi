struct ButtonState
{
  bool state;
  bool isRising;
};


static struct InputState {
  bool switches [2];
  struct ButtonState buttons [2];

} gameInputState;

static void homeScreen() {
  Serial.print("home\n");
  uiInputTick();
  printTama(frog, revFrog);
  homeBackground();

  //printTama(frog);
  //  homeBackground();
  //   potentiometer();
  
  OrbitOledUpdate();
  delay(70);

  if (gameInputState.buttons[0].isRising)
  {
    pageMain = 1;

  }

}

static void homeBackground() {
  OrbitOledMoveTo(64, 0);
  OrbitOledLineTo(64, 32);


}

