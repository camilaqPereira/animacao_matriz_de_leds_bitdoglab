#include "vowels.h"


/* Definicao de constantes*/

const int letter_frames[5][25] = {
    // Letra A
    { 0,  1,  1,  1,  0,
      1,  0,  0,  0,  1,
      1,  1,  1,  1,  1,
      1,  0,  0,  0,  1,
      1,  0,  0,  0,  1},

    // Letra E
    { 1,  1,  1,  1,  1,
      0,  0,  0,  0,  1,
      1,  1,  1,  1,  1,
      0,  0,  0,  0,  1,
      1,  1,  1,  1,  1},

    // Letra I
    { 0,  0,  1,  0,  0,
      0,  0,  1,  0,  0,
      0,  0,  1,  0,  0,
      0,  0,  1,  0,  0,
      0,  0,  1,  0,  0},

    // Letra O
    { 0,  1,  1,  1,  0,
      1,  0,  0,  0,  1,
      1,  0,  0,  0,  1,
      1,  0,  0,  0,  1,
      0,  1,  1,  1,  0},

    // Letra U
    { 1,  0,  0,  0,  1,
      1,  0,  0,  0,  1,
      1,  0,  0,  0,  1,
      1,  0,  0,  0,  1,
      0,  1,  1,  1,  0}
};

// Função para acender LEDs gradualmente para formar uma letra
void vowels_render_letter(const int *letter, PIO pio, uint sm) {
  uint32_t frame[NUM_LEDS] = {0}; // Estado atual dos LEDs

  for (int i = 0; i < NUM_LEDS; i++) {
      if (letter[i]) {
          frame[i] = matrix_rgb(0.5, 0.0, 0.0); // Define o LED atual como azul
      }

      // Envia o estado atualizado para todos os LEDs
      for (int j = 0; j < NUM_LEDS; j++) {
          pio_sm_put_blocking(pio, sm, frame[24 - j]);
      }
      sleep_ms(100); // Atraso para acender LED por LED
  }

  // Garante que a letra inteira permaneça visível após acender todos os LEDs
  for (int j = 0; j < NUM_LEDS; j++) {
      pio_sm_put_blocking(pio, sm, frame[24 - j]);
  }
  sleep_ms(500); // Pausa após completar a letra
}


void vowels_animation(PIO pio, uint state_machine){
  // Toca o buzzer duas vezes no início de cada repetição
  buzzer_play(2, BUZZER_FREQ, 200);

  // Exibe cada letra gradualmente
  for (int letter_idx = 0; letter_idx < 5; letter_idx++) {
    vowels_render_letter(letter_frames[letter_idx], pio, state_machine);
  }

  // Toca a escala simples "Dó, Ré, Mi, Fá, Sol, Lá, Si, Dó" no final da animação
  buzzer_play_melody();
}
