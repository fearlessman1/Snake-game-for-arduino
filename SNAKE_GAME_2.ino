#include "arduino_secrets.h"

//Made by fearlessman
//Snake game with AI demo
//When AI reaches 20 score, The snake commits suicide and the demo restarts.
//If Q is pressed, the game enterrs in normal-playable mode
//If player die, or press R, the script returns to AI demo

#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

// ConfiguraciÃ³n general
#define MAX_LENGTH 96
#define WIN_SCORE 30
int snakeX[MAX_LENGTH], snakeY[MAX_LENGTH];
int snakeLength = 2;
int foodX, foodY;
int direction = 0;
int score = 0;
bool gameOver = false;
bool gameWon = false;
bool iaMode = true;
bool transitionActive = false;

unsigned long previousMillis = 0;
unsigned long blinkMillis = 0;
int gameSpeed = 250;       // velocidad modo jugable
int iaSpeed = 350;         // velocidad modo IA (ligeramente mÃ¡s rÃ¡pida)
bool foodBlinkState = true;

// ---- SETUP ----
void setup() {
  matrix.begin();
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  resetGame(true);
  Serial.println("Snake IA Demo Mode. Press 'Q' to play!");
}

// ---- LOOP ----
void loop() {
  unsigned long currentMillis = millis();

  if (!transitionActive) checkInput();

  int currentSpeed = iaMode ? iaSpeed : gameSpeed;
  if (currentMillis - previousMillis >= currentSpeed) {
    previousMillis = currentMillis;
    if (!gameOver) {
      if (iaMode) updateAI();
      else updateGame();
      drawGame();
    } else {
      showDeathX();          // X parpadeante
      showTransitionAnimation(); // animaciÃ³n de salida
      resetGame(true);           // volver a modo IA
    }
  }

  // Parpadeo de comida
  if (currentMillis - blinkMillis >= 700) {
    blinkMillis = currentMillis;
    foodBlinkState = !foodBlinkState;
  }
}

// ---- INPUT ----
void checkInput() {
  if (Serial.available() > 0) {
    char input = Serial.read();
    switch (input) {
      case 'w': if (direction != 1) direction = 3; break;
      case 's': if (direction != 3) direction = 1; break;
      case 'a': if (direction != 0) direction = 2; break;
      case 'd': if (direction != 2) direction = 0; break;
      case 'r': gameOver = true; break;
      case 'q': if (iaMode) startTransition(); break;
    }
  }
}

// ---- GAME UPDATE ----
void updateGame() {
  for (int i = snakeLength - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  switch (direction) {
    case 0: snakeX[0]++; break;
    case 1: snakeY[0]++; break;
    case 2: snakeX[0]--; break;
    case 3: snakeY[0]--; break;
  }

  // Bordes con wrap-around (entra por un lado, sale por el otro)
  if (snakeX[0] < 0) snakeX[0] = 11;
  if (snakeX[0] > 11) snakeX[0] = 0;
  if (snakeY[0] < 0) snakeY[0] = 7;
  if (snakeY[0] > 7) snakeY[0] = 0;

  // Comida
  if (snakeX[0] == foodX && snakeY[0] == foodY) {
    snakeLength++;
    score++;
    placeFood();
  }

  // ColisiÃ³n consigo misma
  for (int i = 1; i < snakeLength; i++) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      gameOver = true;
      return;
    }
  }
}

// ---- AI UPDATE (versiÃ³n estable) ----
void updateAI() {
  int dx = foodX - snakeX[0];
  int dy = foodY - snakeY[0];

  // DirecciÃ³n preferida hacia la comida
  int preferredDir;
  if (abs(dx) > abs(dy)) preferredDir = (dx > 0) ? 0 : 2;
  else preferredDir = (dy > 0) ? 1 : 3;

  // Calcular siguiente posiciÃ³n
  int nextX = snakeX[0];
  int nextY = snakeY[0];
  switch (preferredDir) {
    case 0: nextX++; break;
    case 1: nextY++; break;
    case 2: nextX--; break;
    case 3: nextY--; break;
  }

  // Wrap
  if (nextX < 0) nextX = 11;
  if (nextX > 11) nextX = 0;
  if (nextY < 0) nextY = 7;
  if (nextY > 7) nextY = 0;

  // Verificar si hay peligro (colisiÃ³n consigo misma)
  bool danger = false;
  for (int i = 0; i < snakeLength; i++) {
    if (snakeX[i] == nextX && snakeY[i] == nextY) {
      danger = true;
      break;
    }
  }

  // Buscar direcciÃ³n alternativa segura
  if (danger) {
    for (int alt = 0; alt < 4; alt++) {
      int testX = snakeX[0];
      int testY = snakeY[0];
      switch (alt) {
        case 0: testX++; break;
        case 1: testY++; break;
        case 2: testX--; break;
        case 3: testY--; break;
      }
      if (testX < 0) testX = 11;
      if (testX > 11) testX = 0;
      if (testY < 0) testY = 7;
      if (testY > 7) testY = 0;

      bool safe = true;
      for (int j = 0; j < snakeLength; j++) {
        if (snakeX[j] == testX && snakeY[j] == testY) {
          safe = false;
          break;
        }
      }
      if (safe) {
        preferredDir = alt;
        break;
      }
    }
  }

  direction = preferredDir;
  updateGame();

  if (score >= 20) {
    gameOver = true;
  }
}

// ---- DRAW GAME ----
void drawGame() {
  byte frame[8][12] = {0};

  // Cuerpo de la serpiente
  for (int i = 0; i < snakeLength; i++) {
    if (snakeX[i] >= 0 && snakeX[i] < 12 && snakeY[i] >= 0 && snakeY[i] < 8)
      frame[snakeY[i]][snakeX[i]] = 1;
  }

  // Comida (parpadeante)
  if (foodBlinkState) frame[foodY][foodX] = 1;

  matrix.renderBitmap(frame, 8, 12);
}

// ---- RESET ----
void resetGame(bool demoMode) {
  iaMode = demoMode;
  snakeLength = 2;
  direction = 0;
  snakeX[0] = 6; snakeY[0] = 4;
  score = 0;
  gameOver = false;
  placeFood();
}

// ---- PLACE FOOD ----
void placeFood() {
  bool valid;
  do {
    foodX = random(12);
    foodY = random(8);
    valid = true;
    for (int i = 0; i < snakeLength; i++) {
      if (foodX == snakeX[i] && foodY == snakeY[i]) valid = false;
    }
  } while (!valid);
}

// ---- TRANSICIÃN ----
void startTransition() {
  transitionActive = true;
  showTransitionAnimation();
  resetGame(false);
  transitionActive = false;
}

// ---- ANIMACIÃN DE BARRIDO ----
void showTransitionAnimation() {
  for (int col = 0; col < 12; col++) {
    byte frame[8][12] = {0};
    for (int y = 0; y < 8; y++)
      for (int x = 0; x <= col; x++)
        frame[y][x] = 1;
    matrix.renderBitmap(frame, 8, 12);
    delay(50);
  }
  for (int col = 11; col >= 0; col--) {
    byte frame[8][12] = {0};
    for (int y = 0; y < 8; y++)
      for (int x = 0; x <= col; x++)
        frame[y][x] = 1;
    matrix.renderBitmap(frame, 8, 12);
    delay(30);
  }
}

// ---- ANIMACIÃN DE MUERTE (X) ----
void showDeathX() {
  for (int i = 0; i < 5; i++) {
    byte frame[8][12] = {0};
    if (i % 2 == 0) {
      for (int j = 0; j < 8; j++) {
        int x1 = map(j, 0, 7, 0, 11);
        frame[j][x1] = 1;
        frame[j][11 - x1] = 1;
      }
    }
    matrix.renderBitmap(frame, 8, 12);
    delay(150);
  }
}
