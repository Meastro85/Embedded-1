#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>
#include <Leds.h>
#include <usart.h>
#include <string.h>

#define MAX_NUMBER_OF_LEDS 4
#define KORT 1000
#define LANG 3000

char characterList[36] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9'};
char morseList[36][5] = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-",
"-.--","--..","-----",".----","..---","...--","....-",".....","-....","--...","---..","----."};
char morseCode[5];

// Methode om de Delay terug te geven afhangende van het gekregen teken
int morseDelay(char morse){
  if(morse == '.'){ return KORT;} 
  else if(morse == '-') {return LANG;}
  else { return 0;}
};

// Methode voor het 'LED-Dansje'
void blinkingLeds(){
  for(int i = 0; i < MAX_NUMBER_OF_LEDS; i++){
    lightUpLed(i);
    _delay_ms(200);
    lightDownLed(i);
  }
}

// Methode om de Leds juist te laten branden afhangend van het gekreken karakter
void showMorse(char morse[],char character){
  for(int k = 0; k < strlen(morse); k++){
      if(morse[k] == '.' || morse[k] == '-'){
        lightUpAllLeds();
        _delay_ms(morseDelay(morse[k]));
        lightDownAllLeds();
        _delay_ms(1000);
      }
    }
    _delay_ms(5000);
    printf("Het karakter was: %c \n", character);
}

// Methode om een string te tonen als morse code
void showMorseString(char string[]){
  int charLoc;
  for(int i = 0; i < strlen(string); i++){
    for(int j = 0; j < strlen(characterList); j++){
      if (string[i] == characterList[j])
      {
        charLoc = j;
      }
    }
    showMorse(morseList[charLoc], characterList[charLoc]);
    printf("%c",characterList[charLoc]);
  }
  printf("De string is: ");
  for(int i = 0; i < strlen(string); i++){
    printf("%c",string[i]);
  }
  printf("\n");
}

int main(){

  initUSART();
  printf("Het programma is gestart\n");

  enableAllLeds();

  lightUpAllLeds();

  for(int i = 0; i < MAX_NUMBER_OF_LEDS; i++){
    _delay_ms(1000);
    lightDownLed(i);
  }

  srand(time(NULL));

  showMorseString("KAAS");

  for(int i = 0; i < 10; i++){
    int random = rand() % 36;
    char character = characterList[random];
    for(int j = 0; j < sizeof(morseList[random]); j++){
      morseCode[j] = morseList[random][j];
    }
  showMorse(morseCode, character);
  }

  for(int i = 0; i < 2; i++) blinkingLeds();

  lightUpAllLeds();
  _delay_ms(1000);
  lightDownAllLeds();

  printf("Het programma is gestopt\n");
  return 0;
}