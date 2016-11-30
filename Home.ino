

int statsCount = 0;
static void homeScreen() {
 // Serial.print("home\n");
  uiInputTick();
  switch (sprite) {
    case 0:
      printTama (frog, revFrog);
      break;
    case 1:
      printTama(fish, revFish);
      break;
    case 2:
      printTama(platy, revPlaty);
      break;
    case 3:
      printTama(joe, revJoe);
      break;
    case 4:
      printTama(alien, revAlien);
      break;
  }
  homeBackground();

  OrbitOledUpdate();
  delay(70);

  if (gameInputState.buttons[0].isRising)
  {
    pageMain = 1;

  }
  statsCount ++;
  if (statsCount % 100 == 0){
      stat.health -=1;
      stat.hunger -=3;
      stat.happiness -= 3;
      stat.hygiene -= 6;
    }

}

static void homeBackground() {
  OrbitOledMoveTo(64, 0);
  OrbitOledLineTo(64, 32);


}

