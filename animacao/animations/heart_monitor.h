#ifndef HEART_MONITOR_H
#define HEART_MONITOR_H

#include "pico/stdlib.h"
#include "hardware_management/buzzer.h"
#include "hardware_management/led_matrix.h"
#include "hardware/pio.h"
#include "hardware/pwm.h"


/* Definicao de constantes*/
#define HEART_MONITOR_FRAMES_SIZE 22
#define HEART_MONITOR_BIP_FREQ_HZ 1000
#define HEART_MONITOR_BIP_DURATION_MS 50


extern const const double frames[HEART_MONITOR_FRAMES_SIZE][MTX_NUM_LEDS];



void cardiac_rate_matrix(PIO pio, uint sm);

void heart_monitor_draw_matrix(PIO pio, uint sm, const double* desenho);

#endif