int timeLim = 1500, timeTaken = 0, levelClear;

typedef enum Command
{
  Shake = 0,
  PressBTN2 = 1,
  PressBTN3 = 2,
  PressBTN4 = 3,
  Switch1 = 4,
  Switch2 = 5,
} Command;

struct GameState {
  int score;
  bool isShaking;
  enum Command playerCommand;
} activeGame;


void GameUIInit() {
  gameInputState = { 0 };
  activeGame = { 0 };
  timeLim = 1500, timeTaken = 0, levelClear=0;

}



void lose () {
  OrbitOledClearBuffer();
  OrbitOledMoveTo(0, 0);
  OrbitOledDrawString("Game Over!");
  OrbitOledMoveTo(0, 10);
  OrbitOledDrawString("Score: ");
  String strScore = String(activeGame.score);
  char score[1024];
  strcpy(score, strScore.c_str());
  OrbitOledDrawString(score);
  OrbitOledUpdate();
  delay (5000);

  pageMain = 0;
  viewMenu = 1;
  GameUIInit();
}

bool shaking ;
void shakeDetect() {

  ShakeTick();

  if (ShakeIsShaking()) {
    levelClear = 1;
    shaking = true;
    delay (100);

  }
}

void btnPress(int b) {
  uiInputTick();
  if (gameInputState.buttons[b].isRising) {
    OrbitOledClearBuffer();
    OrbitOledUpdate();
    levelClear = 1;
    activeGame.score++;
  
  }
}


void switchChanged(int b, bool currentState) {
  uiInputTick();
  if (gameInputState.switches[b]!=currentState) {
    OrbitOledClearBuffer();
    OrbitOledUpdate();
    levelClear = 1;
    activeGame.score++;
  
  }
}

void bopIt() {
  activeGame.playerCommand = (enum Command)(rand() % 6);
  uiInputTick();
  levelClear = 0;
  stat.happiness++;

  switch (activeGame.playerCommand) {
    case Shake: {
        
        OrbitOledMoveTo(0, 0);
        OrbitOledClearBuffer();
        OrbitOledDrawString("Shake");
        OrbitOledUpdate();

        while (timeTaken < timeLim && levelClear == 0 && shaking == false) {
          ShakeInit();
          shakeDetect();
          delay (1);
          timeTaken ++;
        }

        if (shaking) {
          activeGame.score++;
          

          shaking = false;
        }
        if (timeTaken >= timeLim )
        { 
          lose ();
        }
        if (levelClear == 1) {
          timeTaken = 0;
        }
        break;
      }
    case PressBTN2:

      {
        OrbitOledMoveTo(0, 0);
        OrbitOledDrawString("Press Btn 2");
        OrbitOledUpdate();
        while (timeTaken < timeLim && levelClear == 0) {
          btnPress (1);
          delay (1);
          timeTaken ++;
        }

        if (timeTaken >= timeLim )
        { 
          lose ();
        }
        if (levelClear == 1) {
          timeTaken = 0;
        }
        break;
      }
    case PressBTN3:

      {
        OrbitOledMoveTo(0, 0);
        OrbitOledDrawString("Press Btn 3");
        OrbitOledUpdate();
        while (timeTaken < timeLim && levelClear == 0) {
          btnPress (2);
          delay (1);
          timeTaken ++;
        }

        if (timeTaken >= timeLim )
        { 
          lose ();
        }
        if (levelClear == 1) {
          timeTaken = 0;
        }
        break;
      }
    case PressBTN4:
      {
        OrbitOledMoveTo(0, 0);
        OrbitOledDrawString("Press Btn 4");
        OrbitOledUpdate();
        while (timeTaken < timeLim && levelClear == 0) {
          btnPress (3);
          delay (1);
          timeTaken ++;
        }

        if (timeTaken >= timeLim )
        {
          lose ();
        }
        if (levelClear == 1) {
          timeTaken = 0;
        }
        break;
      }

    case Switch1: {
      
        OrbitOledMoveTo(0, 0);
        OrbitOledDrawString("Change Switch 1");
        OrbitOledUpdate();
         int currentState = gameInputState.switches[0] ;
       
        while (timeTaken < timeLim && levelClear == 0) {
          switchChanged (0, currentState);
          delay (1);
          timeTaken ++;
        }

        if (timeTaken >= timeLim )
        { 
          lose ();
        }
        if (levelClear == 1) {
          timeTaken = 0;

          
        }
        break;
      }
    case Switch2: {
        OrbitOledMoveTo(0, 0);
        OrbitOledDrawString("Change Switch 2");
        OrbitOledUpdate();
         int currentState = gameInputState.switches[1] ;
         
        while (timeTaken < timeLim && levelClear == 0) {
          switchChanged (1, currentState);
          delay (1);
          timeTaken ++;
        }

        if (timeTaken >= timeLim )
        { 
          lose ();
        }
        if (levelClear == 1) {
          timeTaken = 0;          
        }
        break;
      }
  }
 
  OrbitOledUpdate();

}




