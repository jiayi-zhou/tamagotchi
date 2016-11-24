#include <FillPat.h>
#include <LaunchPad.h>
#include <OrbitBoosterPackDefs.h>
#include <OrbitOled.h>
#include <OrbitOledChar.h>
#include <OrbitOledGrph.h>
#include <stdlib.h>
#include <Wire.h>

void WireInit();
void GameInit() {
  OrbitOledInit();
  OrbitOledClear();
  OrbitOledClearBuffer();
  OrbitOledSetFillPattern(OrbitOledGetStdPattern(iptnSolid));
  OrbitOledSetDrawMode(modOledSet);
  //  OrbitOledSetDrawColor('p');
}

int count = 3;

static void printHello() {
  count++;
  OrbitOledMoveTo(count, 24);
  OrbitOledDrawString("Hello");
  if (count == 128) {
    count = 0;
  }

}
int xdirect = 0;
int ydirect = 0;
int jump = 0;

static void printFrog() {

  if (xpos == 128 - 16) {
    xdirect = 1;
  }
  if (xpos == 0) {
    xdirect = 0;
  }
  if (ypos == 10) {
    ydirect = 1;
  }
  if (ypos == 5) {
    ydirect = 0;
  }


  if((xpos/10)%2 == 0){
    if (ypos > 5 && ydirect == 1) {
      ypos--;
    } else if (ypos < 10 && ydirect == 0) {
      ypos++;
    }
  }else if((xpos/10)%2 == 1){
    ypos == 10;
  }

  if (xpos < 128 - 16 && xdirect == 0) {
    OrbitOledMoveTo(xpos++, ypos);
  }

  else {
    if (xpos > 0 && xdirect == 1) {
      OrbitOledMoveTo(xpos--, ypos);
    }
  }
  OrbitOledPutBmp(16, 17, frog);
  //jump++;
}

static void printFish() {
  OrbitOledMoveTo(24, 0);
  OrbitOledPutBmp(20, 19, fish);
}

void setup() {
  WireInit();
  GameInit();
  Serial.begin(9600);
  delay(100);



}

void loop() {
  printFrog();

  OrbitOledUpdate();
  //  printFish();
  // put your main code here, to run repeatedly:
  OrbitOledUpdate();
  delay(50);
  //  OrbitOledClear();
  Serial.print(ypos);
  Serial.print("\n");
  //Serial.print(jump);
  Serial.print("\n");
}

