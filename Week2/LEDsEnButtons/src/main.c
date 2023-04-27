#include <Leds.h>
#include <Buttons.h>
#include <avr/io.h>
#include <usart.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR(PCINT1_vect){
    if(buttonPushed(0)) if(isLedActive(0)) lightDownLed(0); else lightUpLed(0);
    if(buttonPushed(1)) if(isLedActive(1)) lightDownLed(1); else lightUpLed(1);
    if(buttonPushed(2)) if(isLedActive(2)) lightDownLed(2); else lightUpLed(2);
}

int main(){
    enableAllButtons();
    enableAllLeds();
    lightDownAllLeds();
    enableAllButtonInterrupts();
    sei();
    while(1){}
    return 0;
}