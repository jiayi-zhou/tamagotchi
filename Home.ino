char unhappy [] = {
  0x00, 0x20, 0x14, 0x10, 0x10, 0x14, 0x20, 0x00,
};

char  clean [] = {
  0x00, 0x65, 0x52, 0x68, 0x7C, 0x70, 0x6A, 0x04,
};

char health [] = {
  0x00, 0x18, 0x18, 0x7E, 0x7E, 0x18, 0x18, 0x00,
};


char fork [] = {
  0x00, 0x0E, 0x18, 0xFE, 0x18, 0x0E, 0x00, 0x00,
};

char angel [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x44, 0x2A, 0x2A, 0x2A, 0x2A, 0x44, 0x80, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x18, 0x20, 0x41, 0x84, 0x84, 0x41, 0x20, 0x18, 0x07,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

int statsCount = 0;
void homeScreen() {
  Serial.print("home\n");
  uiInputTick();
  printTama(tamaForw, tamaBack);
  homeBackground();
  OrbitOledMoveTo(65, 0);
  OrbitOledDrawString("Tama:");
   OrbitOledMoveTo(65, 10);
   OrbitOledDrawString(tamaName);
  if (stat.health < 20) {
    OrbitOledMoveTo(66, 24);
    OrbitOledPutBmp(8, 8, health);
  }

  if (stat.happiness < 20) {
    OrbitOledMoveTo(80, 24);
    OrbitOledPutBmp(8, 8, unhappy);
  }
  if (stat.hunger < 20) {
    OrbitOledMoveTo(95, 24);
    OrbitOledPutBmp(8, 8, fork);
  }
  if (stat.hygiene < 20) {
    OrbitOledMoveTo(110, 24);
    OrbitOledPutBmp(8, 8, clean);
  }
  OrbitOledUpdate();
  delay(70);

  if (gameInputState.buttons[0].isRising)
  {
    pageMain = 1;

  }
  statsCount ++;
  if (statsCount % 100 == 0) {
    if (stat.health - 1 > 0) {
      stat.health -= 1;
    }else stat.health = 0;
    if (stat.hunger - 3 > 0) {
      stat.hunger -= 3;
    }else stat.hunger = 0;
    if (stat.happiness - 5 > 0) {
      stat.happiness -= 5;
    }else stat.happiness = 0;
    if (stat.hygiene - 7 > 0) {
      stat.hygiene -= 7;
    }else stat.hygiene = 0;
  }

  if (stat.health <=0 || stat.hunger <= 0){
    pageMain = 3;}

}

static void homeBackground() {
  OrbitOledMoveTo(64, 0);
  OrbitOledLineTo(64, 32);
}

void death (){
   OrbitOledMoveTo(24,0);
   OrbitOledDrawString ("RIP, ");
   OrbitOledDrawString(tamaName);
  OrbitOledMoveTo(56, 8);

  OrbitOledPutBmp(18, 18, angel);
  OrbitOledUpdate();

  delay (10000);
  pageMain = 0;
  setup();
  pageMain =5;
  }

