#include <Buttons.h>
#include <Leds.h>
#include <usart.h>

int main() {
  initUSART();
  enableAllLeds();
  enableAllButtons();
  lightDownAllLeds();

  while (1) {
    for(int i = 0; i < 3; i++){
        if(buttonPushed(i)){
            lightDownAllLeds();
            printf("Button pushed: %d\n", i);
            flashLed(i, 100);
        }
    }
  }
  return 0;
}