#ifndef SNAKE_H
#define SNAKE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"

#include "hardware_management/led_matrix.h"


#define SNAKE_NUM_FRAMES 28

extern const double snake_frames[SNAKE_NUM_FRAMES][MTX_NUM_LEDS];

void snake_animation(PIO pio, uint sm);

#endif