#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>
#include <Leds.h>

#define MAX_NUMBER_OF_LEDS 4

int main(){
  
  enableAllLeds();
  srand(0);


  while(1){
    int led = rand() % 4;
    lightUpLed(led);
    _delay_ms(100 + rand() % 900);
    lightDownLed(led);
  }

  return 0;
}