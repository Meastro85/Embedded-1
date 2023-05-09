#define __DELAY_BACKWARD_COMPATIBLE__
#include <Buttons.h>
#include <Potentio.h>
#include <avr/interrupt.h>
#include <display.h>
#include <stdint.h>
#include <stdlib.h>
#include <usart.h>
#include <util/delay.h>

#define STARTAANTAL 21
#define MAXAANTAL 3

int playerTurn;
int setup = 1;
int currentAantal;
int playerZet = MAXAANTAL;
int computerZet = 0;
int teller;
int* moves;
char* turns;

int startGame() {
  cli();
  while (!buttonPushed(0)) {
    int seed = ((double)readPotentio() / 1023 * 9999);
    writeNumber(seed);
    srand(seed);
  }
  currentAantal = STARTAANTAL;
  sei();
  return 1;
}

void initGame(int player) {
  while (setup) {
    writeNumberToSegment(2, (STARTAANTAL / 10) % 10);
    writeNumberToSegment(3, STARTAANTAL % 10);
    switch (player) {
      case 0:
        writeCharToSegment(1, 'C');
        playerTurn = 0;
        break;
      case 1:
        writeCharToSegment(1, 'P');
        writeNumberToSegment(0, MAXAANTAL);
        playerTurn = 1;
        break;
    }
  }
}

int computerMove() {
  int move = (currentAantal - 1) % (MAXAANTAL + 1);
  if (move == 0) {
    while (move == 0) {
      move = rand() % 4;
    }
    return move;
  } else {
    return move;
  }
}

void writeOnHeap(int turn){
  if(turn == 0){
    moves[teller] = computerZet;
    turns[teller++] = 'C';
  } else {
    moves[teller] = playerZet;
    turns[teller++] = 'P';
  }
}

void progressGame() {
  while (currentAantal > 1) {
    writeNumberToSegment(2, (currentAantal / 10) % 10);
    writeNumberToSegment(3, currentAantal % 10);
    switch (playerTurn) {
      case 0:
        writeCharToSegment(1, 'C');
        if (computerZet == 0) {
          writeCharToSegment(0, ' ');
        } else {
          writeNumberToSegment(0, computerZet);
        }
        break;
      case 1:
        writeCharToSegment(1, 'P');
        writeNumberToSegment(0, playerZet);
        break;
    }
  }
  int lucifers = STARTAANTAL;
  for(int i = 0; i < teller; i++){
    lucifers -= moves[i];
    printf("Op beurt %d speelde %s en nam hij %d lucifers, er blijven %d lucifers over.\n", i + 1, (turns[i] == 'C') ? "Computer" : "Speler", moves[i], lucifers);
  }
  if(playerTurn){
    writeStringAndWait("CWON",5000);
  } else {
    writeStringAndWait("PWON",5000);
  }
}

ISR(PCINT1_vect) {
  if (playerTurn) {
    if (buttonPushed(0) && playerZet > 1) {
      _delay_us(500);
      if (buttonPushed(0)) {
        playerZet--;
      }
    }
    if (buttonPushed(2) && playerZet < 3) {
      _delay_us(500);
      if (buttonPushed(2)) {
        playerZet++;
      }
    }
    if (buttonPushed(1)) {
      _delay_us(500);
      if (buttonPushed(1)) {
        currentAantal -= playerZet;
        writeOnHeap(1);
        playerTurn = 0;
      }
    }
  } else {
    if (buttonPushed(1)) {
      _delay_us(500);
      {
        if (buttonPushed(1) && computerZet == 0) {
          computerZet = computerMove();
          setup = 0;
        } else if (buttonPushed(1) && computerZet != 0) {
          currentAantal -= computerZet;
          writeOnHeap(0);
          playerTurn = 1;
          computerZet = 0;
        }
      }
    }
  }
}

int main() {
  enableAllButtons();
  initDisplay();
  initADC();
  initUSART();
  enableAllButtonInterrupts();
  moves = calloc(21, sizeof(int));
  turns = calloc(21, sizeof(char));

  while (1) {
    teller = 0;
    if (startGame()) {
      initGame(rand() % 2);
      progressGame();
      free(moves);
      free(turns);
    }
  }
  return 0;
}