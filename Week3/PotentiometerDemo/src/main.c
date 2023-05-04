#include <util/delay.h>
#include <Potentio.h>
#include <usart.h>

int main(){
  initUSART();
  initADC();
  while(1){
    printf("Value: %d\n", readPotentio());
  }
}