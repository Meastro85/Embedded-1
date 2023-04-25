#include <stdint.h>

void enableLed(int ledNumber);
void enableLeds(uint8_t ledBits);
void enableAllLeds(int aantalLeds);

void lightUpLed(int ledNumber);
void lightUpLeds(uint8_t ledBits);
void lightUpAllLeds(int aantalLeds);

void lightDownLed(int ledNumber);
void lightDownLeds(uint8_t ledBits);
void lightDownAllLeds(int aantalLeds);

void dimLed(int ledNumber,int percent,int duration);
void fadeInLed(int ledNumber, int duration);