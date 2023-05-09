#include <Buttons.h>
#include <usart.h>
#include <string.h>
#include <stdlib.h>

int bytes = 0;
char string[] = "Ik mag niet praten in de les.";

void schrijfStrafOpHeap(char* zin){
    bytes += strlen(zin)+1*sizeof(char);
    strcpy(malloc(strlen(zin)+1*sizeof(char)), zin );
    printf("Op heap zijn nu %d bytes bezet.\n", bytes);
  }

int main() {
  initUSART();
  enableButton(0);

  while (1) {
    if (buttonPushed(0)) {
      printf("Op heap zijn nu %d bytes bezet.\n", bytes);
      for (int i = 0; i < 100; i++) {
        printf("%d: %s\n", i, string);
        schrijfStrafOpHeap(string);
      }
    }
  }
  return 0;
}