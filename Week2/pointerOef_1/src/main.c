#include <usart.h>
#define MAX 5
#define ZEVENVOUD 7

void printArray(int* array) {
  printf("Inhoud van array:\n");
  for (int i = 0; i < MAX; i++) {
    printf("Op adres: %p zit de waarde: %d\n", &array[i], array[i]);
  }
}

void vulArray(int* array) {
  for (int i = 0; i < MAX; i++) {
    array[i] = i * ZEVENVOUD;
  }
}

int main() {
  initUSART();

  int getallen[MAX] = {0};

  printArray(getallen);
  vulArray(getallen);
  printArray(getallen);

  return 0;
}