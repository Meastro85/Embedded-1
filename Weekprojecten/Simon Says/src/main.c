#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/io.h>
#include <util/delay.h>
#include <Buttons.h>
#include <Leds.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <usart.h>

#define MAX_GAME_LENGTH 10
#define DELAY 500

int startGame = 0;
int seed = 0;

ISR(PCINT1_vect){
  if(buttonPushed(0)){
    if(!startGame) startGame = 1;
  }
}

void generatePuzzle(uint8_t* leds){
  for(int i = 0; i < MAX_GAME_LENGTH; i++){
    leds[i] = (uint8_t) rand() % 3;
  }
}

void printPuzzle(uint8_t* leds, int* length){
  printf("[");
  for(int i = 0; i < MAX_GAME_LENGTH; i++){
    printf("%d ", leds[i]);
  }
  printf("]\n");
}

int readInput(uint8_t* leds, int* length){
  while(1){
    for(int i = 0; i <= length; i++){
      if(!buttonPushed(leds[i])){
        printf("Je drukte op knop %d, fout!", leds[i]);
        return 0;
      } else{
        printf("Je drukte op knop %d, juist!", leds[i]);
      }
    }
    return 1;
  }
}

int playPuzzle(uint8_t* leds){
  for(int i = 0; i < MAX_GAME_LENGTH; i++){
    for(int j = 0; j <= i; j++){
      flashLed(leds[i],500);
      _delay_ms(DELAY);
    }
    if(!readInput(leds,i)){
      printf("Fout, het juist patroon was ");
      printPuzzle(leds, i);
      return 0;
    } else {
      printf("Correct, we gaan naar level", i + 1);
    }
  }
  printf("Proficiat, je bent de Simon Master!");
  return 1;
}

int main(){

  initUSART();
  enableAllLeds();
  enableAllButtons();
  enableButtonInterrupt(0);
  lightDownAllLeds();
  sei();

  uint8_t leds[MAX_GAME_LENGTH];

  printf("Druk op knop 1 om het spel te starten");
  while(!startGame){
    flashLed(3,500);
    seed++;
  }

  srand(seed);
  cli();
  generatePuzzle(leds);
  playPuzzle(leds);

  return 0;
}