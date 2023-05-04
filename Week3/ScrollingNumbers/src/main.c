#define __DELAY_BACKWARD_COMPATIBLE__
#include <display.h>
#include <avr/io.h>
#include <util/delay.h>

int main(){
  initDisplay();
  while(1){
    for(int i = 1; i < 10; i++){
      int a = (i * 1000) + (((i+1) % 10) * 100) + (((i+2) % 10) * 10) + ((i+3) % 10);
      writeNumberAndWait(a,1000);
    }
  }

}