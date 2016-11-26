#include <stdbool.h>
struct ButtonState
{ 
  bool state;
  bool isRising;
};

static struct InputState{
  bool switches [2]; 
  struct ButtonState buttons [2];
  float potentiometer;
  }

struct GameState {
  int score;
  enum 
  }

void GameUIInit(){
  OrbitOledInit();
  OrbitOledClear();
  OrbitOledClearBuffer();
  OrbitOledSetFillPattern(OrbitOledGetStdPattern(iptnSolid));
  
  }
typedef enum Action 
