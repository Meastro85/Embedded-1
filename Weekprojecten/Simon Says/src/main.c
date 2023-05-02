#define __DELAY_BACKWARD_COMPATIBLE__
#include <Buttons.h>
#include <Leds.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>
#include <usart.h>
#include <util/delay.h>

#define MAX_GAME_LENGTH 10
#define DELAY _delay_ms(500)

int startGame = 0;
int seed = 0;

ISR(PCINT1_vect) {
  if (buttonPushed(0)) {
    if (!startGame) startGame = 1;
  }
}

void generatePuzzle(uint8_t* leds) {
  for (int i = 0; i < MAX_GAME_LENGTH; i++) {
    leds[i] = (uint8_t)rand() % 3;
  }
}

void printPuzzle(uint8_t* leds, int length) {
  printf("[");
  for (int i = 0; i < MAX_GAME_LENGTH; i++) {
    printf("%d ", leds[i]);
  }
  printf("]\n");
}

int readInput(uint8_t* leds, int length) {
  int index = 0;
  while (index <= length) {
    if (buttonPushed(leds[index])) {
      printf("Je drukte op knop %d, juist!\n", leds[index] + 1);
      index++;
      DELAY;
    } else if (buttonPushed(0) && leds[index] != 0) {
      printf("Je drukte op knop %d, fout!\n", 1);
      return 1;
    } else if (buttonPushed(1) && leds[index] != 1) {
      printf("Je drukte op knop %d, fout!\n", 2);
      return 1;
    } else if (buttonPushed(2) && leds[index] != 2) {
      printf("Je drukte op knop %d, fout!\n", 3);
      return 1;
    }
  }
  return 0;
}

int playPuzzle(uint8_t* leds) {
  for (int i = 0; i < MAX_GAME_LENGTH; i++) {
    for (int j = 0; j <= i; j++) {
      flashLed(leds[j], 500);
      DELAY;
    }
    if (readInput(leds, i)) {
      printf("Fout, het juist patroon was ");
      printPuzzle(leds, i);
      return 0;
    } else {
      printf("Correct, we gaan naar level %d\n", i + 1);
    }
  }
  printf("Proficiat, je bent de Simon Master!\n");
  return 1;
}

int main() {
  initUSART();
  enableAllLeds();
  enableAllButtons();
  enableButtonInterrupt(0);
  lightDownAllLeds();
  sei();

  uint8_t leds[MAX_GAME_LENGTH];
  printf("Druk op knop 1 om het spel te starten\n");
  while (!startGame) {
    flashLed(3, 500);
    seed++;
  }

  srand(seed);
  cli();
  generatePuzzle(leds);
  playPuzzle(leds);
  return 0;
}