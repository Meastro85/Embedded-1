#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/io.h>
#include <Leds.h>

int main(){
  enableLed(1);
  dimLed(1, 10, 10000);
  return 0;
}