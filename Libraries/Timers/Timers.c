#include <avr/io.h>

void initTimer(uint8_t timer, uint8_t mode, uint8_t interrupts) {
  // vul aan
if(timer == 0){

} else if(timer == 1){

} else if(timer == 2){
    if(mode == 0){
        TCCR2A |= _BV(WGM21);
    } else if(mode == 1){
        TCCR2A |= _BV(WGM20) | _BV(WGM21);
    }
    if(interrupts == 0 || interrupts == 2){
        TIMSK2 |= _BV(OCIE2A);
    }
    if(interrupts == 1 || interrupts == 2){
        TIMSK2 |= _BV(TOIE2);
    } 
}




}