#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "hardware/adc.h"
#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "pico/bootrom.h"
#include "pico/stdlib.h"

// arquivo .pio
#include "pio_matrix.pio.h"

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

// configurações da PIO
PIO pio = pio0;
bool ok;
uint16_t i;
double r = 0.0, b = 0.0, g = 0.0;
uint offset;
uint sm;

// vetor para criar imagem na matriz de led - 1
double desenhos[9][NUM_PIXELS] = {
    // Frame 1: Batimento normal
    {0.0, 0.0, 0.0, 0.0, 0.3, 0.0, 0.0, 0.0, 0.3, 0.0, 0.0, 0.0, 0.0, 0.3, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
    
    // Frame 2: Descanso (sem batimento)
    {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
    
    // Frame 3: Batimento forte
    {0.0, 0.0, 0.0, 0.3, 0.3, 0.0, 0.3, 0.3, 0.3, 0.0, 0.3, 0.0, 0.0, 0.3, 0.3, 0.0, 0.3, 0.3, 0.0, 0.0, 0.3, 0.0, 0.0, 0.0, 0.0},
    
    // Frame 4: Batimento fraco
    {0.0, 0.0, 0.0, 0.0, 0.1, 0.0, 0.0, 0.0, 0.1, 0.0, 0.0, 0.0, 0.0, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.0, 0.0, 0.0, 0.0},
    
    // Frame 5: Batimento médio
    {0.0, 0.0, 0.3, 0.3, 0.3, 0.0, 0.0, 0.3, 0.3, 0.0, 0.0, 0.3, 0.3, 0.0, 0.3, 0.0, 0.3, 0.3, 0.0, 0.3, 0.0, 0.3, 0.0, 0.0, 0.0},
    
    // Frame 6: Batimento com intervalo maior (menor frequência)
    {0.0, 0.0, 0.0, 0.3, 0.0, 0.0, 0.0, 0.3, 0.0, 0.0, 0.3, 0.0, 0.0, 0.3, 0.0, 0.0, 0.3, 0.0, 0.0, 0.0, 0.3, 0.0, 0.0, 0.0, 0.0},
    
    // Frame 7: Batimento acelerado
    {0.0, 0.0, 0.3, 0.3, 0.3, 0.3, 0.0, 0.3, 0.0, 0.3, 0.3, 0.3, 0.0, 0.3, 0.3, 0.3, 0.0, 0.3, 0.3, 0.0, 0.3, 0.3, 0.0, 0.3, 0.0},
    
    // Frame 8: Batimento com picos alternados
    {0.0, 0.3, 0.0, 0.0, 0.0, 0.3, 0.0, 0.0, 0.0, 0.3, 0.0, 0.0, 0.0, 0.3, 0.0, 0.0, 0.0, 0.3, 0.0, 0.0, 0.0, 0.3, 0.0, 0.0, 0.0}

        {
        // ponto
        0.0, 0.0, 0.0, 0.0, 0.0,  //
        0.0, 0.0, 0.0, 0.0, 0.0,  //
        0.0, 0.0, 0.3, 0.0, 0.0,  //
        0.0, 0.0, 0.0, 0.0, 0.0,  //
        0.0, 0.0, 0.0, 0.0, 0.0   //
    }
};

// função para exibir a sequência de batimentos
void exibe_monitor_cardiaco() {
  while (true) {
    for (int i = 0; i < 9; i++) {  // Exibe todos os 8 frames
      desenha_na_matriz(desenhos[i], true);
      sleep_ms(500);  // Intervalo entre os frames
    }
  }
}


int batimentos_frames[9][NUM_PIXELS] = {
    // Frame 1 (Batimento forte)
    {LED5, LED4, LED3, LED2, LED1, LED6, LED11, LED16, LED21, LED22, LED23, LED24, LED25, LED20, LED15, LED10},
    
    // Frame 2 (Batimento fraco)
    {LED7, LED3, LED8, LED13, LED18, LED23, LED22, LED21, LED24, LED25},
    
    // Frame 3 (Batimento forte)
    {LED1, LED2, LED3, LED4, LED5, LED10, LED15, LED14, LED13, LED12, LED11, LED16, LED21, LED22, LED23, LED24, LED25},
    
    // Frame 4 (Batimento fraco)
    {LED1, LED2, LED3, LED4, LED5, LED10, LED15, LED14, LED13, LED12, LED11, LED16, LED21, LED22},
    
    // Frame 5 (Sem pulso)
    {LED5, LED4, LED3, LED2, LED1, LED6, LED11, LED16, LED21, LED22, LED23},
    
    // Frame 6 (Batimento fraco)
    {LED1, LED6, LED11, LED12, LED13, LED14, LED15, LED10, LED5, LED20, LED25},
    
    // Frame 7 (Batimento forte)
    {LED5, LED4, LED3, LED2, LED1, LED6, LED11, LED12, LED13, LED14, LED15, LED20, LED25, LED24},
    
    // Frame 8 (Sem pulso)
    {LED5, LED4, LED3, LED2, LED1, LED6, LED11, LED16, LED21, LED22},
    
    // Frame 9 (Batimento forte)
    {LED5, LED4, LED3, LED2, LED1, LED6, LED11, LED12, LED13, LED14, LED15, LED10, LED20, LED25, LED24, LED23}
};

// rotina para definição da intensidade de cores do led
uint32_t matrix_rgb(double b, double r, double g) {
  unsigned char R, G, B;
  R = r * 255;
  G = g * 255;
  B = b * 255;
  return (G << 24) | (R << 16) | (B << 8);
}

// rotina para acionar a matrix de leds - ws2812b
void desenha_na_matriz(double* desenho, bool colorido) {
  uint32_t valor_led;
  for (int16_t i = 0; i < NUM_PIXELS; i++) {
    int index = 24 - i;
    double pixel = desenho[index];

    if (colorido) {
      if (index == 12) {
        valor_led = matrix_rgb(pixel, r = 0.0, g = 0.0);
      } else if ((index >= 6 && index <= 8) || index == 11 || index == 13 ||
                 (index >= 16 && index <= 18)) {
        valor_led = matrix_rgb(b = 0.0, r = 0.0, pixel);
      } else {
        valor_led = matrix_rgb(b = 0.0, pixel, g = 0.0);
      }
    } else {
      valor_led = matrix_rgb(pixel, r = 0.0, g = 0.0);
    }

    pio_sm_put_blocking(pio, sm, valor_led);
  }
}

// Função para desenhar os batimentos na matriz de LEDs
void desenha_batimento(int frame) {
    // A função 'desenha_na_matriz' pode ser implementada de acordo com a necessidade
    // Para simular os batimentos com os frames definidos
    desenha_na_matriz(batimentos_frames[frame], true);
}

// Função principal para simular os batimentos
void simula_batimento() {
    // Exibe os frames de batimento cardíaco em sequência
    for (int i = 0; i < 9; i++) {
        desenha_batimento(i);
        sleep_ms(300); // Tempo de exibição de cada frame
    }
}



// função principal
int main() {
  // coloca a frequência de clock para 128 MHz, facilitando a divisão pelo clock
  ok = set_sys_clock_khz(128000, false);

  // Inicializa todos os códigos stdio padrão que estão ligados ao binário.
  stdio_init_all();

  // configurações da PIO
  uint offset = pio_add_program(pio, &pio_matrix_program);
  uint sm = pio_claim_unused_sm(pio, true);
  pio_matrix_program_init(pio, sm, offset, OUT_PIN);

  while (true) {
    // Simula os batimentos cardíacos
    exibe_monitor_cardiaco();
    simula_batimento();
  }
}
