#include <avr/io.h>

void initTimer(uint8_t timer, uint8_t mode, uint8_t interrupts) {
    switch(timer){
        case 0: switch(mode){
            case 0: TCCR0A |= _BV(WGM01); break;
            case 1: TCCR0A |= _BV(WGM00) | _BV(WGM01); break;
        }
        switch(interrupts){
            case 0: TIMSK0 |= _BV(OCIE0A); break;
            case 1: TIMSK0 |= _BV(TOIE0); break;
            case 2: TIMSK0 |= _BV(OCIE0A); TIMSK0 |= _BV(TOIE0); break;
        } break;
        case 1: switch(mode){
            case 0: TCCR1A |= _BV(WGM11); break;
            case 1: TCCR1A |= _BV(WGM10) | _BV(WGM11); break;
        }
        switch(interrupts){
            case 0: TIMSK1 |= _BV(OCIE1A); break;
            case 1: TIMSK1 |= _BV(TOIE1); break;
            case 2: TIMSK1 |= _BV(OCIE1A); TIMSK1 |= _BV(TOIE1); break;
        } break;
        case 2: switch(mode){
            case 0: TCCR2A |= _BV(WGM21); break;
            case 1: TCCR2A |= _BV(WGM20) | _BV(WGM21); break;
        }
        switch(interrupts){
            case 0: TIMSK2 |= _BV(OCIE2A); break;
            case 1: TIMSK2 |= _BV(TOIE2); break;
            case 2: TIMSK2 |= _BV(OCIE2A); TIMSK2 |= _BV(TOIE2); break;
        } break;
    }
}

void startTimer(uint8_t timer, int factor) {
    switch(timer){// https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf Pagina 87-110-131 voor factors
        case 0: switch(factor){// P87 (Zie Link)
            case 1: TCCR0B |= _BV(CS00); break;
            case 8: TCCR0B |= _BV(CS01); break;
            case 64: TCCR0B |= _BV(CS01) | _BV(CS00); break;
            case 256: TCCR0B |= _BV(CS02); break;
            case 1024: TCCR0B |= _BV(CS02) | _BV(CS00); break; 
        }; break;
        case 1: switch(factor){ // P110 (Zie Link)
            case 1: TCCR1B |= _BV(CS10); break;
            case 8: TCCR1B |= _BV(CS11); break;
            case 64: TCCR1B |= _BV(CS11) | _BV(CS10); break;
            case 256: TCCR1B |= _BV(CS12); break;
            case 1024: TCCR1B |= _BV(CS12) | _BV(CS10); break; 
        }; break;
        case 2: switch(factor){// P131 (Zie Link)
            case 1: TCCR2B |= _BV(CS20); break;
            case 8: TCCR2B |= _BV(CS21); break;
            case 64: TCCR2B |= _BV(CS22); break;
            case 128: TCCR2B |= _BV(CS22) | _BV(CS20); break;
            case 256: TCCR2B |= _BV(CS22) | _BV(CS21); break;
            case 1024: TCCR2B |= _BV(CS22) | _BV(CS21) | _BV(CS20); break;
        } break;
    }
}

void stopTimer(uint8_t timer) {
    switch(timer){
        case 0: TCCR0B &= ~(_BV(CS02) | _BV(CS01) | _BV(CS00)); break;
        case 1: TCCR1B &= ~(_BV(CS02) | _BV(CS01) | _BV(CS00)); break;
        case 2: TCCR2B &= ~(_BV(CS02) | _BV(CS01) | _BV(CS00)); break;
    }
}

void setOCRXA(uint8_t timer, long value){
    switch(timer){
        case 0: OCR0A = value; break;
        case 1: OCR1A = value; break;
        case 2: OCR2A = value; break;
    }
}
