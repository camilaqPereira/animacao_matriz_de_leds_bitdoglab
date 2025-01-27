
#include "led_matrix.h"

/* Definicao de constantes*/
const uint GPIO_LED_MTX = 7;

uint32_t matrix_rgb(double b, double r, double g) {
    unsigned char R = r * 255;
    unsigned char G = g * 255;
    unsigned char B = b * 255;
    return (G << 24) | (R << 16) | (B << 8);
}





