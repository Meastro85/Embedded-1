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
  for(int i = 0; i < 10; i++){
    leds[i] = (uint8_t) rand() % 3;
  }
}

void printPuzzle(uint8_t* leds){
  printf("[");
  for(int i = 0; i < 10; i++){
    printf("%d ", leds[i]);
  }
  printf("]");
}

int readInput(){

}

int playPuzzle(uint8_t* leds){
  for(int i = 0; i < 10; i++){
     flashLed(leds[i],500);
  }
}

int main(){

  initUSART();
  enableAllLeds();
  enableAllButtons();
  enableAllButtonInterrupts();
  lightDownAllLeds();
  sei();

  uint8_t leds[10];

  while(!startGame){
    flashLed(3,500);
    seed++;
  }

  srand(seed);
  cli();
  generatePuzzle(leds);
  printPuzzle(leds);

  return 0;
}