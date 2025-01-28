#ifndef WAVE_H
#define WAVE_H


#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware_management/led_matrix.h"
#include "hardware_management/buzzer.h"

/* Declaracao de constantes*/

#define WAVE_FRAMES_SIZE 22

extern const double wave_frames[WAVE_FRAMES_SIZE][MTX_NUM_LEDS];


void wave_animation(PIO pio, uint sm);

void draw_matrix(PIO pio, uint sm, const double* desenho, int frame_index);



#endif