#include "countdown.h"

double desenhos[4][NUM_PIXELS] = {
    {
        // mini 0
        0.0, 0.0, 0.0, 0.0, 0.0,  //
        0.0, 0.3, 0.3, 0.3, 0.0,  //
        0.0, 0.3, 0.0, 0.3, 0.0,  //
        0.0, 0.3, 0.3, 0.3, 0.0,  //
        0.0, 0.0, 0.0, 0.0, 0.0   //
    },
    {
        // ponto
        0.0, 0.0, 0.0, 0.0, 0.0,  //
        0.0, 0.0, 0.0, 0.0, 0.0,  //
        0.0, 0.0, 0.3, 0.0, 0.0,  //
        0.0, 0.0, 0.0, 0.0, 0.0,  //
        0.0, 0.0, 0.0, 0.0, 0.0   //
    },
    {
        // fogos pequenos
        0.0, 0.0, 0.0, 0.0, 0.0,  //
        0.0, 0.3, 0.0, 0.3, 0.0,  //
        0.0, 0.0, 0.3, 0.0, 0.0,  //
        0.0, 0.3, 0.0, 0.3, 0.0,  //
        0.0, 0.0, 0.0, 0.0, 0.0   //
    },
    {
        // fogos grandes
        0.3, 0.0, 0.0, 0.0, 0.3,  //
        0.0, 0.3, 0.0, 0.3, 0.0,  //
        0.0, 0.3, 0.3, 0.3, 0.0,  //
        0.0, 0.3, 0.0, 0.3, 0.0,  //
        0.3, 0.0, 0.0, 0.0, 0.3   //
    },
};

int desenhos_ordem[12][NUM_PIXELS] = {
    // numero 0
    {LED5, LED4, LED3, LED2, LED1, LED6, LED11, LED16, LED21, LED22, LED23,
     LED24, LED25, LED20, LED15, LED10},

    // numero 1
    {LED7, LED3, LED8, LED13, LED18, LED23, LED22, LED21, LED24, LED25},

    // numero 2
    {LED1, LED2, LED3, LED4, LED5, LED10, LED15, LED14, LED13, LED12, LED11,
     LED16, LED21, LED22, LED23, LED24, LED25},

    // numero 3
    {LED1, LED2, LED3, LED4, LED5, LED10, LED15, LED14, LED13, LED12, LED11,
     LED20, LED25, LED24, LED23, LED23, LED22, LED21},

    // numero 4
    {LED1, LED6, LED11, LED12, LED13, LED14, LED15, LED10, LED5, LED20, LED25},

    // numero 5
    {LED5, LED4, LED3, LED2, LED1, LED6, LED11, LED12, LED13, LED14, LED15,
     LED20, LED25, LED24, LED23, LED22, LED21},

    // numero 6
    {LED5, LED4, LED3, LED2, LED1, LED6, LED11, LED16, LED21, LED22, LED23,
     LED24, LED25, LED20, LED15, LED14, LED13, LED12},

    // numero 7
    {LED1, LED2, LED3, LED4, LED5, LED10, LED15, LED20, LED25},

    // numero 8
    {LED5, LED4, LED3, LED2, LED1, LED6, LED11, LED12, LED13, LED14, LED15,
     LED20, LED25, LED24, LED23, LED22, LED21, LED16, LED10},

    // numero 9
    {LED5, LED4, LED3, LED2, LED1, LED6, LED11, LED12, LED13, LED14, LED15,
     LED10, LED20, LED25, LED24, LED23, LED22, LED21}};

// rotina para definição da intensidade de cores do led
uint32_t matrix_rgb(double b, double r, double g) {
  unsigned char R, G, B;
  R = r * 255;
  G = g * 255;
  B = b * 255;
  return (G << 24) | (R << 16) | (B << 8);
}

// rotina para acionar a matrix de leds - ws2812b
void draw_matrix(PIO pio, uint sm, double* desenho, bool colorido) {
  uint32_t valor_led;
  for (int16_t i = 0; i < NUM_PIXELS; i++) {
    int index = 24 - i;
    double pixel = desenho[index];

    if (colorido) {
      if (index == 12) {
        valor_led = matrix_rgb(pixel, 0.0, 0.0);
      } else if ((index >= 6 && index <= 8) || index == 11 || index == 13 ||
                 (index >= 16 && index <= 18)) {
        valor_led = matrix_rgb(0.0, 0.0, pixel);
      } else {
        valor_led = matrix_rgb(0.0, pixel, 0.0);
      }
    } else {
      valor_led = matrix_rgb(pixel, 0.0, 0.0);
    }

    pio_sm_put_blocking(pio, sm, valor_led);
  }
}

void make_numbers(PIO pio, uint sm, int numero) {
  printf("Mostrando o número %i\n", numero);
  int* posicoes = desenhos_ordem[numero];
  double desenho[25] = {0.0};

  for (int i = 0; i < 25; i++) {
    int posicao = posicoes[i];
    if (posicao > 0 && posicao <= 25) {
      desenho[posicao - 1] = 0.3;
      draw_matrix(pio, sm, desenho, false);
      sleep_ms(NUMBERS_SLEEP);
    }
  }

  sleep_ms(ANIMATIONS_SLEEP);
}

void make_circles(PIO pio, uint sm) {
  desenha_na_matriz(pio, sm, desenhos[0], false);
  sleep_ms(ANIMATIONS_SLEEP);

  desenha_na_matriz(pio, sm, desenhos[1], false);
  sleep_ms(ANIMATIONS_SLEEP);
}

void make_firework(PIO pio, uint sm) {
  desenha_na_matriz(pio, sm, desenhos[2], true);
  sleep_ms(ANIMATIONS_SLEEP);

  desenha_na_matriz(pio, sm, desenhos[3], true);
  sleep_ms(ANIMATIONS_SLEEP);
}

void countdown_animation(PIO pio, uint sm) {
  while (true) {
    for (int i = 9; i >= 0; i--) {
      make_numbers(pio, sm, i);
    }
    make_circles(pio, sm);
    make_firework(pio, sm);
  }
}