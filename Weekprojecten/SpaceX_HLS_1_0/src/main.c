#include <Buttons.h>
#include <Leds.h>
#include <Timers.h>
#include <avr/interrupt.h>
#include <display.h>
#include <stdlib.h>
#include <usart.h>
#include <util/delay.h>

#define VEELVOUD 250
#define STARTFUEL 1500
#define GRAVITY 1.662
#define LEDDELAY 100
#define LEDS 4

int timerCounter = 0;
uint8_t seconden;
double currentSpeed;
double distance;
uint16_t fuelReserve;
uint16_t burst = 0;

typedef struct {
  double distance;
  uint16_t burst;
  double currentSpeed;
  uint16_t fuelReserve;
} LOG;

LOG* logArray;

void showDashboard() {
  writeNumberAndWait(distance, 500);
  uint8_t activeLeds = fuelReserve / (STARTFUEL / LEDS);
  for (int i = 0; i < activeLeds; i++) {
    lightUpLed(i);
  }

  if (fuelReserve % (STARTFUEL / LEDS) > 0) {
    flashLed(activeLeds, fuelReserve % (STARTFUEL / LEDS));
    writeNumberAndWait(distance, 500);
  }

  for (int i = activeLeds; i < LEDS; i++) lightDownLed(i);
}


ISR(TIMER2_COMPA_vect) {
  timerCounter++;
  if ((timerCounter + 1) % VEELVOUD == 0) {
    seconden++;
    currentSpeed += GRAVITY - burst / 5;
    distance -= currentSpeed;
    fuelReserve -= burst;
    burst = 0;
    logArray[seconden].currentSpeed = currentSpeed;
    logArray[seconden].distance = distance;
    logArray[seconden].fuelReserve = fuelReserve;
  }
}

ISR(PCINT1_vect) {
  while (buttonPushed(1)) {
    writeNumberAndWait(distance, 200);
    burst += 5;
    printf("Burst: %d\n", burst);
  }
}

int main() {
  initUSART();
  initDisplay();

  enableAllLeds();
  lightUpAllLeds();

  initTimer(2, 0, 0);
  setOCRXA(2, 249);

  enableAllButtons();
  enableButtonInterrupt(1);

  while (1) {
    logArray = calloc(100, sizeof(LOG));
    writeString("STRT");
    distance = 9999;
    currentSpeed = 100;
    seconden = 0;
    fuelReserve = STARTFUEL;
    if (buttonPushed(0)) {
      _delay_us(500);
      if (buttonPushed(0)) {
        startTimer(2, 256);
        sei();
        while (distance > 3) {
          showDashboard();
        }
        cli();
        stopTimer(2);

        for(int i = 0; i < 100; i++){
          printf("LOG timestamp: %3d, Speed: %5s, Distance: %6s, Fuel reserve: %4d\n",i ,dtostrf(logArray[i].currentSpeed,4,2,""), dtostrf(logArray[i].distance,4,2,""), logArray[i].fuelReserve );
        }
        if (distance <= 3 && currentSpeed <= 5) {
          printf("Succesfully landed!\n");
          scrollingString("LANDED", 5000);
        } else {
          printf("Crashed!!!\n");
          scrollingString("CRASHED", 5000);
        }
      }
    }
    free(logArray);
  }
  return 0;
}