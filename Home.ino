
static void homeScreen(){
   printTama(frog);
   homeBackground();
   potentiometer();
   OrbitOledUpdate();
   delay(70);
}

static void homeBackground(){
  OrbitOledMoveTo(64, 0);
  OrbitOledLineTo(64, 32);
  OrbitOledMoveTo(68, 0);
}

