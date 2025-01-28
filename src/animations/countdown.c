#include "countdown.h"

double desenhos[4][MTX_NUM_LEDS] = {
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

int desenhos_ordem[12][MTX_NUM_LEDS] = {
    // numero 0
    {COUNTDOWN_LED5, COUNTDOWN_LED4, COUNTDOWN_LED3, COUNTDOWN_LED2, COUNTDOWN_LED1, COUNTDOWN_LED6, COUNTDOWN_LED11, COUNTDOWN_LED16, COUNTDOWN_LED21, COUNTDOWN_LED22, COUNTDOWN_LED23,
     COUNTDOWN_LED24, COUNTDOWN_LED25, COUNTDOWN_LED20, COUNTDOWN_LED15, COUNTDOWN_LED10},

    // numero 1
    {COUNTDOWN_LED7, COUNTDOWN_LED3, COUNTDOWN_LED8, COUNTDOWN_LED13, COUNTDOWN_LED18, COUNTDOWN_LED23, COUNTDOWN_LED22, COUNTDOWN_LED21, COUNTDOWN_LED24, COUNTDOWN_LED25},

    // numero 2
    {COUNTDOWN_LED1, COUNTDOWN_LED2, COUNTDOWN_LED3, COUNTDOWN_LED4, COUNTDOWN_LED5, COUNTDOWN_LED10, COUNTDOWN_LED15, COUNTDOWN_LED14, COUNTDOWN_LED13, COUNTDOWN_LED12, COUNTDOWN_LED11,
     COUNTDOWN_LED16, COUNTDOWN_LED21, COUNTDOWN_LED22, COUNTDOWN_LED23, COUNTDOWN_LED24, COUNTDOWN_LED25},

    // numero 3
    {COUNTDOWN_LED1, COUNTDOWN_LED2, COUNTDOWN_LED3, COUNTDOWN_LED4, COUNTDOWN_LED5, COUNTDOWN_LED10, COUNTDOWN_LED15, COUNTDOWN_LED14, COUNTDOWN_LED13, COUNTDOWN_LED12, COUNTDOWN_LED11,
     COUNTDOWN_LED20, COUNTDOWN_LED25, COUNTDOWN_LED24, COUNTDOWN_LED23, COUNTDOWN_LED23, COUNTDOWN_LED22, COUNTDOWN_LED21},

    // numero 4
    {COUNTDOWN_LED1, COUNTDOWN_LED6, COUNTDOWN_LED11, COUNTDOWN_LED12, COUNTDOWN_LED13, COUNTDOWN_LED14, COUNTDOWN_LED15, COUNTDOWN_LED10, COUNTDOWN_LED5, COUNTDOWN_LED20, COUNTDOWN_LED25},

    // numero 5
    {COUNTDOWN_LED5, COUNTDOWN_LED4, COUNTDOWN_LED3, COUNTDOWN_LED2, COUNTDOWN_LED1, COUNTDOWN_LED6, COUNTDOWN_LED11, COUNTDOWN_LED12, COUNTDOWN_LED13, COUNTDOWN_LED14, COUNTDOWN_LED15,
     COUNTDOWN_LED20, COUNTDOWN_LED25, COUNTDOWN_LED24, COUNTDOWN_LED23, COUNTDOWN_LED22, COUNTDOWN_LED21},

    // numero 6
    {COUNTDOWN_LED5, COUNTDOWN_LED4, COUNTDOWN_LED3, COUNTDOWN_LED2, COUNTDOWN_LED1, COUNTDOWN_LED6, COUNTDOWN_LED11, COUNTDOWN_LED16, COUNTDOWN_LED21, COUNTDOWN_LED22, COUNTDOWN_LED23,
     COUNTDOWN_LED24, COUNTDOWN_LED25, COUNTDOWN_LED20, COUNTDOWN_LED15, COUNTDOWN_LED14, COUNTDOWN_LED13, COUNTDOWN_LED12},

    // numero 7
    {COUNTDOWN_LED1, COUNTDOWN_LED2, COUNTDOWN_LED3, COUNTDOWN_LED4, COUNTDOWN_LED5, COUNTDOWN_LED10, COUNTDOWN_LED15, COUNTDOWN_LED20, COUNTDOWN_LED25},

    // numero 8
    {COUNTDOWN_LED5, COUNTDOWN_LED4, COUNTDOWN_LED3, COUNTDOWN_LED2, COUNTDOWN_LED1, COUNTDOWN_LED6, COUNTDOWN_LED11, COUNTDOWN_LED12, COUNTDOWN_LED13, COUNTDOWN_LED14, COUNTDOWN_LED15,
     COUNTDOWN_LED20, COUNTDOWN_LED25, COUNTDOWN_LED24, COUNTDOWN_LED23, COUNTDOWN_LED22, COUNTDOWN_LED21, COUNTDOWN_LED16, COUNTDOWN_LED10},

    // numero 9
    {COUNTDOWN_LED5, COUNTDOWN_LED4, COUNTDOWN_LED3, COUNTDOWN_LED2, COUNTDOWN_LED1, COUNTDOWN_LED6, COUNTDOWN_LED11, COUNTDOWN_LED12, COUNTDOWN_LED13, COUNTDOWN_LED14, COUNTDOWN_LED15,
     COUNTDOWN_LED10, COUNTDOWN_LED20, COUNTDOWN_LED25, COUNTDOWN_LED24, COUNTDOWN_LED23, COUNTDOWN_LED22, COUNTDOWN_LED21}};


// rotina para acionar a matrix de leds - ws2812b
void countdown_draw_matrix(PIO pio, uint sm, double* desenho, bool colorido) {
  uint32_t valor_led;
  for (int16_t i = 0; i < MTX_NUM_LEDS; i++) {
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
      countdown_draw_matrix(pio, sm, desenho, false);
      sleep_ms(COUNTDOWN_NUMBERS_SLEEP);
    }
  }

  sleep_ms(COUNTDOWN_ANIMATIONS_SLEEP);
}

void make_circles(PIO pio, uint sm) {
  countdown_draw_matrix(pio, sm, desenhos[0], false);
  sleep_ms(COUNTDOWN_ANIMATIONS_SLEEP);

  countdown_draw_matrix(pio, sm, desenhos[1], false);
  sleep_ms(COUNTDOWN_ANIMATIONS_SLEEP);
}

void make_firework(PIO pio, uint sm) {
  countdown_draw_matrix(pio, sm, desenhos[2], true);
  sleep_ms(COUNTDOWN_ANIMATIONS_SLEEP);

  countdown_draw_matrix(pio, sm, desenhos[3], true);
  sleep_ms(COUNTDOWN_ANIMATIONS_SLEEP);
  buzzer_play(3, 1000, 250);
}

void countdown_animation(PIO pio, uint sm) {
  
  for (int i = 9; i >= 0; i--) {
    make_numbers(pio, sm, i);
  }
  make_circles(pio, sm);
  make_firework(pio, sm);
  
}