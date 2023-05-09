#define __DELAY_BACKWARD_COMPATIBLE__
#include <Buzzer.h>
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <usart.h>
#include <Buttons.h>

#define DURATIONSHORT 250
#define DURATIONMEDIUM 500
#define DURATIONLONG 1000

typedef struct{
  float frequency;
  uint16_t duration;
} NOTE;

typedef struct{
  char* name;
  NOTE** notes;
  uint16_t length;
} SONG ;

void playNote(NOTE* note) {
  if (note->frequency != 0) {
    playTone(note->frequency, note->duration);
  } else {
    _delay_ms(note->duration);
  }
}

SONG* generateSong(char* name, uint16_t length) {
  SONG* song = calloc(length, sizeof(SONG));
  song->length = length;
  song->name = malloc(sizeof(name) + 1);
  song->name = name;
  song->notes = calloc(length, sizeof(NOTE*));
  for (int i = 0; i < length; i++) {
    song->notes[i] = malloc(sizeof(NOTE));

    switch (rand() % 3){
      case 0: song->notes[i]->duration = DURATIONSHORT; break;
      case 1: song->notes[i]->duration = DURATIONMEDIUM; break;
      case 2: song->notes[i]->duration = DURATIONLONG; break;
    }
    uint32_t frequencies[] = {C5, D5, E5, F5, G5, A5, B5, C6};
    switch (rand() % 8){
      case 0: song->notes[i]->frequency = frequencies[0]; break;
      case 1: song->notes[i]->frequency = frequencies[1]; break;
      case 2: song->notes[i]->frequency = frequencies[2]; break;
      case 3: song->notes[i]->frequency = frequencies[3]; break;
      case 4: song->notes[i]->frequency = frequencies[4]; break;
      case 5: song->notes[i]->frequency = frequencies[5]; break;
      case 6: song->notes[i]->frequency = frequencies[6]; break;
      case 7: song->notes[i]->frequency = frequencies[7]; break;
    }

  }
  return song;
}

void playSong(SONG* song){
  for(int i = 0; i < song->length; i++){
    printf("Playing note: %f for duration %d\n", song->notes[i]->frequency, song->notes[i]->duration);
    playNote(song->notes[i]);
  }
}

int main() {

  enableBuzzer();
  initUSART();
  enableButton(0);
  int teller = 0;

  while (1) {

    teller++;
    if(buttonPushed(0) || buttonPushed(1) || buttonPushed(2)){
      srand(teller);
      SONG* song = generateSong("Kaas cappelo", 10);
      for(int i = 0; i < 2 ; i++){
        printf("Now playing: %s\n", song->name);
        playSong(song);
      }
      for(int i = 0; i < 10; i ++){
        free(song->notes[i]);
      }
      free(song);
    }

  }
  return 0;
}