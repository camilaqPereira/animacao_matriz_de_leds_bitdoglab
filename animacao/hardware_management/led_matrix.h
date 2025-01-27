#ifndef LED_MATRIZ_H
#define LED_MATRIX_H


#include "pico/stdlib.h"

#define NUM_LEDS 25 //Total de leds na matriz

extern const uint GPIO_LED_MTX; // GPIO da matriz de leds


/*
*   @brief Função para definir a intensidade de cores do LED
*/
uint32_t matrix_rgb(double b, double r, double g);

#endif