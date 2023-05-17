#include <avr/io.h>

#define C1 32.7
#define CS1 34.6
#define F1 43.7
#define B1 61.7
#define C3 130.81 
#define C4 261.686
#define D4 293.724
#define E4 329.724
#define C5 523.250
#define D5 587.330
#define E5 659.250
#define F5 698.460
#define G5 783.990
#define A5 880.000
#define B5 987.770
#define C6 1046.500
#define C7 2093
#define B7 3951.1

void enableBuzzer();
void buzzerOn();
void buzzerOff();
void playTone(float frequency, uint32_t duration);