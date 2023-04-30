#include <Leds.h>
#include <Buttons.h>
#include <avr/io.h>
#include <usart.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR(PCINT1_vect){
    if(buttonPushed(0)) flipLed(0);
    if(buttonPushed(1)) flipLed(1);
    if(buttonPushed(2)) flipLed(2);
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