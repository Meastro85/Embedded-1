#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>
#include <Leds.h>

void enableLed(int ledNumber){
  if(ledNumber < 4){
    DDRB |= (1 << (PB2 + ledNumber));
  }
}

void enableLeds(uint8_t leds){
  leds &= 0b00001111;
  DDRB |= (leds << PB2);
}

void enableAllLeds(){
  for(int i = 0; i < 4; i++){
    enableLed(i);
  }
}



void lightUpLed(int ledNumber){
  if(ledNumber < 4){
    PORTB &= ~(1 << (PB2 + ledNumber));
  }
}

void lightUpLeds(uint8_t leds){
    leds &= 0b00001111;
    PORTB &= ~(leds << PB2);
}

void lightUpAllLeds(){
  for(int i = 0; i < 4; i++){
    lightUpLed(i);
  }
}



void lightDownLed(int ledNumber){
  if(ledNumber < 4){
    PORTB |= (1 << (PB2 + ledNumber));
  }
}

void lightDownLeds(uint8_t leds){
  leds &= 0b00001111;
  PORTB |= (leds << PB2);
}

void lightDownAllLeds(){
  for(int i = 0; i < 4; i++){
    lightDownLed(i);
  }
}



void dimLed(int ledNumber, int percent, int duration){
  for(int i = duration; i > 0; i -= 10){
    lightUpLed(ledNumber);
    _delay_ms(percent/10);
    lightDownLed(ledNumber);
    _delay_ms((100 - percent)/10);
  }
}

void fadeInLed(int ledNumber, int duration){
  for(int i = 1; i <= 100; i++){
    dimLed(ledNumber, i, duration/100);
  }
  lightUpLed(ledNumber);
}

void fadeOutLed(int ledNumber,int duration){
  for(int i = 100; i > 0; i--){
    dimLed(ledNumber, i, duration/100);
  }
  lightDownLed(ledNumber);
}

void flashLed(int ledNumber, int duration){
  lightUpLed(ledNumber);
  _delay_ms(duration);
  lightDownLed(ledNumber);
}

int isLedActive(int ledNumber){
  if(bit_is_clear(PINB, PB2 + ledNumber)){
    return 1;
  } else {
    return 0;
  }
}