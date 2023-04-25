#include <stdint.h>

// Enable functions
void enableLed(int ledNumber);
void enableLeds(uint8_t ledBits);
void enableAllLeds();

// Light up functions
void lightUpLed(int ledNumber);
void lightUpLeds(uint8_t ledBits);
void lightUpAllLeds();

// Light down functions
void lightDownLed(int ledNumber);
void lightDownLeds(uint8_t ledBits);
void lightDownAllLeds();

// Utility functions
void dimLed(int ledNumber, int percent, int duration);
void fadeInLed(int ledNumber, int duration);
void fadeOutLed(int ledNumber, int duration);
void flashLed(int ledNumber, int duration);