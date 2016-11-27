#include <stdbool.h>
#include <string.h>

static enum menuPages{
  Feeding = 1,
  Cleaning = 2,
  Medicine = 3,
  Stats = 4,
  Games = 5
} gameUiPage;

static void feedingPage(){
 OrbitOledMoveTo(0,0);
 OrbitOledDrawString("Food!");
}


