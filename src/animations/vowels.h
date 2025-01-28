#ifndef VOWELS_H
#define VOWELS_h

#include "hardware/pio.h"
#include "hardware_management/buzzer.h"
#include "hardware_management/led_matrix.h"

/* Definicao de constantes*/

/*Representacao das letras A, E, I, O, U em matrizes */
extern const int letter_frames[5][25];

void vowels_render_letter(const int *letter, PIO pio, uint sm);

void vowels_animation(PIO pio, uint state_machine);

#endif