// https://canvas.kdg.be/courses/38313/pages/projectideeen-2022-2023?module_item_id=794127
#define __DELAY_BACKWARD_COMPATIBLE__
#include <Buttons.h>
#include <Buzzer.h>
#include <Leds.h>
#include <Potentio.h>
#include <Timers.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <display.h>
#include <stdlib.h>
#include <usart.h>
#include <util/delay.h>

#define SKYPIECE 0
#define WALLPIECE 1
#define BOTTOMWALLPIECE 5
#define WINDOWPIECE 2
#define ROOFPIECE 3
#define DOORPIECE 4

uint8_t startGame = 0;
uint8_t timerCounter = 0;
uint8_t doMoveBlock = 0;
int** tileArray;
int direction;

typedef struct {
  uint8_t amountOfBlocks;
  uint8_t velocity;
} LEVEL;

typedef struct {
  uint8_t hp;
  int score;
} STATS;

LEVEL* level;
STATS* playerStats;

void initGame() {
  playerStats->hp = 4;
  playerStats->score = 0;
  level->velocity = 250;
  level->amountOfBlocks = 10;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
      if (j == 4) {
        if (rand() % 2 == 1) {
          tileArray[i][j] = BOTTOMWALLPIECE;
        } else {
          tileArray[i][j] = DOORPIECE;
        }
      } else {
        tileArray[i][j] = SKYPIECE;
      }
    }
  }
  lightUpAllLeds();
}

void sendTileArray() {
  printf("2DArray:[");
  for (int i = 0; i < 4; i++) {
    printf("[");
    for (int j = 0; j < 5; j++) {
      printf("%d", tileArray[i][j]);
      if (j != 4) {
        printf(", ");
      }
    }
    if (i != 3) {
      printf("], ");
    }
  }
  printf("]]$");
  _delay_ms(100);
}

void addBlock() {
  uint8_t random = rand() % 3;
  if (random == 0) {
    tileArray[0][0] = WALLPIECE;
  } else if (random == 1) {
    tileArray[0][0] = WINDOWPIECE;
  } else if (random == 2) {
    tileArray[0][0] = ROOFPIECE;
  }
  sendTileArray();
}

void moveBlock() {
  if (tileArray[0][0] > 0) {
    direction = 1;
  } else if (tileArray[3][0] > 0) {
    direction = -1;
  }

  for (int i = 0; i < 4; i++) {
    if (tileArray[i][0] > 0) {
      tileArray[i + direction][0] = tileArray[i][0];
      tileArray[i][0] = 0;
      sendTileArray();
      return;
    }
  }
}

void placeBlock() {
  for (int i = 0; i < 4; i++) {
    if (tileArray[i][0] > 0) {  // Check position of block in the first row
      if (tileArray[i][2] > 0) {
        for (int k = 0; k < 4; k++) {
          for (int l = 4; l > 1; l--) {
            tileArray[k][l] = tileArray[k][l - 1];
          }
        }
      }
      for (int j = 2; j < 5; j++) {
        if (tileArray[i][j] > 0 &&
            j != 2) {  // If any block in that column is > 0, place block and
                       // make new one.
          tileArray[i][j - 1] = tileArray[i][0];
          tileArray[i][0] = 0;
          addBlock();
          playerStats->score++;
          level->amountOfBlocks--;
          playTone(C6, 100);
          printf("Score: %d$$$", playerStats->score);
          return;
        }
        if(tileArray[i][4] == 0){
          tileArray[i][0] = 0;
          playerStats->hp--;
          level->amountOfBlocks--;
          addBlock();
          playTone(C5, 100);
          playTone(G5, 100);
          playTone(B5, 100);
          printf("HP: %d$", playerStats->hp);
          return;
        }
      }
    }
  }
}

ISR(PCINT1_vect) {
  if (buttonPushed(0)) {
    _delay_us(500);
    if (buttonPushed(0)) {
      startGame = 1;
    }
  }

  if (buttonPushed(1)) {
    _delay_us(500);
    if (buttonPushed(1)) {
      placeBlock();
      sendTileArray();
    }
  }
}

ISR(TIMER2_COMPA_vect) {
  timerCounter++;
  if ((timerCounter + 1) % level->velocity == 0) {
    moveBlock();
    timerCounter = 0;
  }
}

int main() {
  enableAllLeds();
  lightDownAllLeds();

  initUSART();
  initADC();
  initDisplay();
  enableAllButtons();
  enableAllButtonInterrupts();
  //enableBuzzer();
  initTimer(2, 0, 0);
  setOCRXA(2, 249);

  while (1) {
    sei();
    while (startGame == 0) {
      for (int i = 0; i < 4; i++) {
        lightUpLed(i);
        _delay_ms(200);
        lightDownLed(i);
      }
    }

    srand(readPotentio());
    // printf("STRING:STARTEND"); // Start game
    tileArray = malloc(4 * sizeof(int));
    for (int i = 0; i < 4; i++) {
      tileArray[i] = malloc(5 * sizeof(int));
    }
    playerStats = malloc(sizeof(playerStats));
    level = malloc(sizeof(level));

    initGame();
    sendTileArray();
    startTimer(2, 256);
    addBlock();
    while (playerStats->hp > 0) {
      writeNumber(playerStats->score);
      lightDownLed(playerStats->hp);
      if(level->amountOfBlocks == 0){
        level->amountOfBlocks = (rand() % 20) + 1;
        level->velocity = (rand() % 100) + 51;
      }
    }
    printf("stop$");
    cli();

    for (int i = 0; i < 4; i++) {
      free(tileArray[i]);
    }
    free(tileArray);
    startGame = 0;
  }
  return 0;
}