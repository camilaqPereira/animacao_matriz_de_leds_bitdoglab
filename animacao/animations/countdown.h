#ifndef COUNTDOWN
#define COUNTDOWN

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "hardware/pio.h"
#include "hardware/pwm.h"
#include "hardware_management/buzzer.h"
#include "hardware_management/led_matrix.h"
#include "pico/stdlib.h"

/* Definicao de constantes*/
#define LED1 1
#define LED2 2
#define LED3 3
#define LED4 4
#define LED5 5
#define LED6 10
#define LED7 9
#define LED8 8
#define LED9 7
#define LED10 6
#define LED11 11
#define LED12 12
#define LED13 13
#define LED14 14
#define LED15 15
#define LED16 20
#define LED17 19
#define LED18 18
#define LED19 17
#define LED20 16
#define LED21 21
#define LED22 22
#define LED23 23
#define LED24 24
#define LED25 25

// número de LEDs
#define NUM_PIXELS 25
// pino de saída
#define OUT_PIN 7
// tempo de espera entre as animacoes
#define ANIMATIONS_SLEEP 200
#define NUMBERS_SLEEP 40

void countdown_animation(PIO pio, uint sm);

#endif