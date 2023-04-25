#include <string.h>
#include <usart.h>
#define MAX 7

void drukEersteLetters(char (*namen)[10]){
  printf("Eerste letter: ");
  for(int i = 0; i < MAX; i++){
    printf("%c",namen[i][0]);
  }
  printf("\n");
}

char* zoekKleinsteNaam(char (*namen)[10]){
  char* naam = namen[0];
  for(int i = 0; i < MAX; i++){
    if(strcmp(namen[i], *naam) < 0){
      naam = namen[i];
    }
  }
  return naam;
}

int main(){

  initUSART();

  char namen[MAX][10] = {"Noa","Job","Kyan","Presten","Axel","Mats","Zeno"};

  drukEersteLetters(namen);
  
  char* kleinste = zoekKleinsteNaam(namen);

  printf("Kleinste = %s\n",kleinste);

  return 0;
}