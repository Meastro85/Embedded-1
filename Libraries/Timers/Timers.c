#include <avr/io.h>
#include <avr/interrupt.h>

void initTimer0(){
    // Wave Form -> FAST PWM
    TCCR0A |= _BV(WGM00) | _BV(WGM01);

    // PreScaler -> factor is 1024, dus 64µs
    TCCR0B |= _BV(CS02) | _BV(CS00);

    // Interrupts
    TIMSK0 |= _BV(TOIE0); // overflow interrupt enablen
    TIMSK0 |= _BV(OCIE0A); // OCRA interrupt enablen

}

void initTimer1(){
    // Wave Form -> FAST PWM
    TCCR1A |= _BV(WGM10) | _BV(WGM11);

    // PreScaler -> factor is 1024, dus 64µs
    TCCR1B |= _BV(CS12) | _BV(CS10);

    // Interrupts
    TIMSK1 |= _BV(TOIE1); // overflow interrupt enablen
    TIMSK1 |= _BV(OCIE1A); // OCRA interrupt enablen

}

void initTimer2(){
    // Wave Form -> FAST PWM
    TCCR2A |= _BV(WGM20) | _BV(WGM21);

    // PreScaler -> factor is 1024, dus 64µs
    TCCR2B |= _BV(CS22) | _BV(CS20);

    // Interrupts
    TIMSK2 |= _BV(TOIE2); // overflow interrupt enablen
    TIMSK2 |= _BV(OCIE2A); // OCRA interrupt enablen

}

void setOCR0A(int* value){
    OCR0A = value;
}

void setOCR1A(int* value){
    OCR1A = value;
}

void setOCR2A(int* value){
    OCR2A = value;
}
