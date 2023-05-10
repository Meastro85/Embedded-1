#include <avr/io.h>

#define TIMERS {TCCR0A, TCCR1A, TCCR2A}
#define TIMERSB {TCCR0B, TCCR1B, TCCR2B}
#define TIMERINTERRUPTS {TIMSK0, TIMSK1, TIMSK2}
#define OCRXA {OCR0A, OCR1A, OCR2A}

void initTimer(uint8_t timer, uint8_t mode, uint8_t interrupts) {
    switch(mode){
        case 0: TIMERS(timer) |= _BV(WGM01); break; //CSC Mode
        case 1: TIMERS(timer) |= _BV(WGM00) | _BV(WGM21); break; //Fast PWM Mode
    }
    switch(interrupts){
        case 0: TIMERINTERRUPTS(timer) |= _BV(OCIE0A); break; // OCRxA Interrupt
        case 1: TIMERINTERRUPTS(timer) |= _BV(TOIE0); break; // Top Value Interrupt
        case 2: TIMERINTERRUPTS(timer) |= _BV(OCIE0A); TIMERINTERRUPTS(timer) |= _BV(TOIE0); break; // Beide interrupts
    }
}

void startTimer(uint8_t timer, uint8_t factor) {
    switch(timer){
        case 0: switch(factor){
            case 1: TIMERSB(0) |= _BV(CS00); break;
            case 8: TIMERSB(0) |= _BV(CS01); break;
            case 64: TIMERSB(0) |= _BV(CS01) | _BV(CS00); break;
            case 256: TIMERSB(0) |= _BV(CS02); break;
            case 1024: TIMERSB(0) |= _BV(CS02) | _BV(CS00); break; 
        }; break;
        case 1: switch(factor){
            case 1: TIMERSB(1) |= _BV(CS10); break;
            case 8: TIMERSB(1) |= _BV(CS11); break;
            case 64: TIMERSB(1) |= _BV(CS11) | _BV(CS10); break;
            case 256: TIMERSB(1) |= _BV(CS12); break;
            case 1024: TIMERSB(1) |= _BV(CS12) | _BV(CS10); break; 
        }; break;
        case 2: switch(factor){
            case 1: TIMERSB(2) |= _BV(CS20); break;
            case 8: TIMERSB(2) |= _BV(CS21); break;
            case 64: TIMERSB(2) |= _BV(CS22); break;
            case 128: TIMERSB(2) |= _BV(CS22) | _BV(CS20); break;
            case 256: TIMERSB(2) |= _BV(CS22) | _BV(CS21); break;
            case 1024: TIMERSB(2) |= _BV(CS22) | _BV(CS21) | _BV(CS20); break;
        } break;
    }
}

void stopTimer(uint8_t timer) {
  TIMERSB(timer) &= ~(_BV(CS02) | _BV(CS01) | _BV(CS00));
}

void setOCRXA(uint8_t timer, int value){
    OCRXA(timer) = value;
}
