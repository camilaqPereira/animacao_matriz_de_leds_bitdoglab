#ifndef COUNTDOWN_H
#define COUNTDOWN_H


#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "hardware/pio.h"
#include "hardware/pwm.h"
#include "hardware_management/buzzer.h"
#include "hardware_management/led_matrix.h"
#include "pico/stdlib.h"

/* Definicao de constantes*/
#define COUNTDOWN_LED1 1
#define COUNTDOWN_LED2 2
#define COUNTDOWN_LED3 3
#define COUNTDOWN_LED4 4
#define COUNTDOWN_LED5 5
#define COUNTDOWN_LED6 10
#define COUNTDOWN_LED7 9
#define COUNTDOWN_LED8 8
#define COUNTDOWN_LED9 7
#define COUNTDOWN_LED10 6
#define COUNTDOWN_LED11 11
#define COUNTDOWN_LED12 12
#define COUNTDOWN_LED13 13
#define COUNTDOWN_LED14 14
#define COUNTDOWN_LED15 15
#define COUNTDOWN_LED16 20
#define COUNTDOWN_LED17 19
#define COUNTDOWN_LED18 18
#define COUNTDOWN_LED19 17
#define COUNTDOWN_LED20 16
#define COUNTDOWN_LED21 21
#define COUNTDOWN_LED22 22
#define COUNTDOWN_LED23 23
#define COUNTDOWN_LED24 24
#define COUNTDOWN_LED25 25

// tempo de espera entre as animacoes
#define COUNTDOWN_ANIMATIONS_SLEEP 200
#define COUNTDOWN_NUMBERS_SLEEP 40

void countdown_animation(PIO pio, uint sm);

#endif