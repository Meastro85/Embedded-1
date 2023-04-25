#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/io.h>

#define MAX_NUMBER_OF_BUTTONS 3

void enableButton(int button) {
  if (button < MAX_NUMBER_OF_BUTTONS) {
    DDRC &= ~_BV(PC1 + button);
    PORTC |= _BV(PC1 + button);
  }
}

void enableAllButtons() {
  for (int i = 0; i < MAX_NUMBER_OF_BUTTONS; i++) {
    enableButton(i);
  }
}

int buttonPushed(int button) {
  if (bit_is_clear(PINC, PC1 + button)) {
    return 1;
  }
  return 0;
}

int buttonReleased(int button) { return !buttonPushed(button); }