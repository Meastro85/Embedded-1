#include <Buttons.h>
#include <Leds.h>
#include <Timers.h>
#include <avr/interrupt.h>
#include <display.h>
#include <usart.h>
#include <util/delay.h>
#include <stdlib.h>

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

typedef struct{
  double distance;
  uint16_t burst;
  double currentSpeed;
  uint16_t fuelReserve;
  uint8_t seconden;
} LOG;

LOG** logArray;

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

void writeLog() {
    logArray[seconden]->currentSpeed = currentSpeed;
    logArray[seconden]->distance = distance;
    logArray[seconden]->fuelReserve = fuelReserve;
    logArray[seconden]->seconden = seconden;
}

ISR(TIMER2_COMPA_vect) {
  if(logArray == NULL){
    logArray = calloc(250, sizeof(LOG));
  }
  timerCounter++;
  if ((timerCounter + 1) % VEELVOUD == 0) {
    seconden++;
    currentSpeed += GRAVITY - burst / 5;
    distance -= currentSpeed;
    fuelReserve -= burst;
    burst = 0;
    writeLog();
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

while(1){
  writeString("STRT");
  if(buttonPushed(0)){
    _delay_us(500);
    if(buttonPushed(0)){
      startTimer(2, 256);
      sei();
      distance = 9999;
      currentSpeed = 100;
      seconden = 0;
      fuelReserve = STARTFUEL;
  while (distance > 3) {
    showDashboard();
  }

  cli();
  stopTimer(2);

  for(int i = 0; i < sizeof(logArray)/sizeof(int); i++){
    printf("LOG Seconden %d:\n",logArray[i]->seconden);
    printf("Speed: %d\n", logArray[i]->currentSpeed);
    printf("Distance: %d\n", logArray[i]->distance);
    printf("Fuel reserve: %d\n", logArray[i]->fuelReserve);
  }
  if(distance <= 3 && currentSpeed <= 5){
    printf("Succesfully landed!\n");
    scrollingString("LANDED", 10000);
  } else {
    printf("Crashed!!!\n");
    scrollingString("CRASHED", 10000);
  }
    }
  }
}
  return 0;
}