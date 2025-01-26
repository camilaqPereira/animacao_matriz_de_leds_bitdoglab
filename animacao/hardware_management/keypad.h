#ifndef KEYPAD_h
#define KEYPAD_H

#include <stdio.h>
#include "pico/stdlib.h"
/* Definicao de constantes*/


#define NUM_ROWS 4
#define NUM_COLUMNS 4

extern const uint rows_pins[NUM_ROWS];
extern const uint columns_pins[NUM_COLUMNS];

/* Mapeamento do teclado matricial*/
extern const char keypad_mapping[NUM_ROWS][NUM_COLUMNS];



/*
*   @brief Funcao para inicializacao dos pinos do teclado matricial
*/
void keypad_init();

/*
*   @brief Funcao para leitura do teclado matricial e deteccao do pressionamento de teclas
*   @param pressed_key ponteiro char para o retorno da tecla pressionada
*/

void keypad_get_pressed_key(char *pressed_key);



#endif