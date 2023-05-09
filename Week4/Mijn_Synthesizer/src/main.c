#include <display.h>
#include <Buzzer.h>
#include <Buttons.h>
#include <Potentio.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int playing = 0;

ISR(PCINT1_vect){
  if(buttonPushed(0) || buttonPushed(1) || buttonPushed(2)){
    _delay_us(500);
    if(buttonPushed(0) || buttonPushed(1) || buttonPushed(2)) playing = !playing;
  }
}

int main(){

  initADC();
  initDisplay();
  enableAllButtons();
  enableAllButtonInterrupts();
  enableBuzzer();
  sei();

  while(1){
    int freq;
    if(playing){
      playTone(freq, 500);
    } else {
      freq = readPotentio();
    }
    writeNumber(freq);
  }


  return 0;
}
