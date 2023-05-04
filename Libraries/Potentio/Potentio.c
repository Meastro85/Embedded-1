#include <avr/io.h>

void initADC(){
    ADMUX |= (1<<REFS0);
    ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
    ADCSRA |= (1<<ADEN);
}

uint16_t readPotentio(){
    ADCSRA |= (1<<ADSC);
    loop_until_bit_is_clear(ADCSRA,ADSC);
    return ADC;
}