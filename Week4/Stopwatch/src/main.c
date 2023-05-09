#include <Buttons.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "display.h"
#include "usart.h"

#define VEELVOUD 250

// globale variabelen
// plaats hier je globale variabelen

int counter = 0;
int seconden = 0;
int minuten = 0;

void initTimer() {
  // vul aan
  TCCR2A |= _BV(WGM21);
  TIMSK2 |= _BV(OCIE2A);
  sei();
  OCR2A = 249;
}

void startTimer() {
  // vul aan
  TCCR2B |= _BV(CS22) | _BV(CS21);
}

void stopTimer() {
  // vul aan
  TCCR2B &= ~(_BV(CS22) | _BV(CS21));
}

void tick() {
  seconden++;
  if (seconden == 60) {
    minuten++;
    seconden = 0;
  }
  printf("Er zijn %d minuten en %d seconden voorbij gegaan\n", minuten,
         seconden);
}

void writeTimeAndWait(uint8_t minuten, uint8_t seconden, int delay) {
  // Vul aan
  for (int i = 0; i < delay / 20; i++) {
    writeNumberToSegment(0, (minuten / 10) % 10);
    _delay_ms(5);
    writeNumberToSegment(1, minuten % 10);
    _delay_ms(5);
    writeNumberToSegment(2, (seconden / 10) % 10);
    _delay_ms(5);
    writeNumberToSegment(3, seconden % 10);
    _delay_ms(5);
  }
}

// Deze ISR loopt elke 4ms
ISR(TIMER2_COMPA_vect) {
  counter++;
  if ((counter + 1) % VEELVOUD == 0) {
    tick();
  }
}

ISR(PCINT1_vect) {
  if (buttonPushed(0)) {
    _delay_us(500);
    if (buttonPushed(0)) startTimer();
  }
  if (buttonPushed(1)) {
    _delay_us(500);
    if (buttonPushed(1)) stopTimer();
  }
  if (buttonPushed(2)) {
    _delay_us(500);
    if (buttonPushed(2)) {
      seconden = 0;
      minuten = 0;
    }
  }
}

int main() {
  initUSART();
  initDisplay();
  initTimer();
  enableAllButtons();
  enableAllButtonInterrupts();

  printf("Start de stopwatch met S1, stop met S2, en reset met S3\n");

  while (1) {
    writeTimeAndWait(minuten, seconden, 1000);
    // vergeet je timer niet te initialiseren en te starten
    // denk ook aan sei()
  }

  return 0;
}
