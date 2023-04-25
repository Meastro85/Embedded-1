#define _DELAY_BACKWARDS_COMPATIBLE_
#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void enableLed(int ledNumber){
  DDRB |= (1 << (PB2 + ledNumber));
}

void enableLeds(uint8_t leds){
  leds &= 0b00001111;
  DDRB |= (leds << PB2);
}

void enableAllLeds(int leds){
  for(int i = 0; i < leds; i++){
    enableLed(i);
  }
}



void lightUpLed(int ledNumber){
  PORTB &= ~(1 << (PB2 + ledNumber));
}

void lightUpLeds(uint8_t leds){
    leds &= 0b00001111;
    PORTB &= ~(leds << PB2);
}

void lightUpAllLeds(int leds){
  for(int i = 0; i < leds; i++){
    lightUpLed(i);
  }
}



void lightDownLed(int ledNumber){
  PORTB |= (1 << (PB2 + ledNumber));
}

void lightDownLeds(uint8_t leds){
  leds &= 0b00001111;
  PORTB |= (leds << PB2);
}

void lightDownAllLeds(int leds){
  for(int i = 0; i < leds; i++){
    lightDownLed(i);
  }
}



void dimLed(int ledNumber, int percent, int duration){
    time_t startTime = clock();
    time_t endTime;
    enableLed(ledNumber);
    do{
      lightUpLed(ledNumber);
      _delay_(duration * (1 - (percent/100)));
      lightDownLed(ledNumber);
      _delay_ms(duration * (1 - (percent/100)));
    } while(endTime - startTime < duration);
}

void fadeInLed(int ledNumber, int duration){

}

void fadeOutLed(int ledNumber,int duration){

}