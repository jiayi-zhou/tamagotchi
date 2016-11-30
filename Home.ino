static void homeScreen(){
   printTama(frog, revFrog);
   homeBackground();
   potentiometer();
   OrbitOledUpdate();
   delay(70);
   OrbitOledClearBuffer();
}

static void homeBackground(){
  OrbitOledMoveTo(64, 0);
  OrbitOledLineTo(64, 32);


}

