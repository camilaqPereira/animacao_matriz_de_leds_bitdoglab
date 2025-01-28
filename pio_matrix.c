#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "hardware/adc.h"
#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "pico/bootrom.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define BUZZER_PIN 15

// arquivo .pio
#include "pio_matrix.pio.h"

// número de LEDs
#define NUM_PIXELS 25

// pino de saída
#define OUT_PIN 7

#define FRAMES_SIZE 22

// configurações da PIO
PIO pio = pio0;
bool ok;
uint16_t i;
double r = 0.0, b = 0.0, g = 0.0;
uint offset;
uint sm;

// vetor para criar imagem na matriz de led - 1
double frames[FRAMES_SIZE][NUM_PIXELS] = {

    // Frame 1
    {0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.3, 0.3, 0.3, 0.3, 0.3,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0},

    // Frame 2
    {0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.3, 0.0, 0.0, 0.0, 0.0,  //
     0.3, 0.3, 0.3, 0.3, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0},

    // Frame 3
    {0.0, 0.0, 0.0, 0.0, 0.3,  //
     0.0, 0.3, 0.0, 0.0, 0.0,  //
     0.3, 0.3, 0.3, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0},

    // Frame 4
    {0.0, 0.0, 0.0, 0.3, 0.0,  //
     0.3, 0.0, 0.3, 0.0, 0.0,  //
     0.3, 0.3, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0},

    // Frame 5
    {0.0, 0.0, 0.3, 0.0, 0.0,  //
     0.0, 0.3, 0.0, 0.3, 0.0,  //
     0.3, 0.0, 0.0, 0.0, 0.3,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0},

    // Frame 6
    {0.0, 0.3, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.3, 0.0, 0.3,  //
     0.0, 0.0, 0.0, 0.3, 0.0,  //
     0.3, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0},

    // Frame 7
    {0.3, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.3, 0.0,  //
     0.0, 0.0, 0.3, 0.0, 0.3,  //
     0.0, 0.3, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0},

    // Frame 8
    {0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.3, 0.0, 0.0, 0.0, 0.3,  //
     0.0, 0.3, 0.0, 0.3, 0.0,  //
     0.0, 0.0, 0.3, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0},

    // Frame 9
    {0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.3, 0.0, 0.0,  //
     0.0, 0.3, 0.0, 0.3, 0.3,  //
     0.0, 0.0, 0.0, 0.0, 0.3,  //
     0.0, 0.0, 0.0, 0.0, 0.0},

    // Frame 10
    {0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.3, 0.0,  //
     0.3, 0.0, 0.3, 0.3, 0.3,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0},

    // Frame 11
    {0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.3,  //
     0.0, 0.3, 0.3, 0.3, 0.3,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0},

    // Frame 12
    {0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.3, 0.3, 0.3, 0.3, 0.3,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0},

    // Frame 13
    {0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.3, 0.0, 0.0, 0.0, 0.0,  //
     0.3, 0.3, 0.3, 0.3, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0},

    // Frame 14
    {0.0, 0.0, 0.0, 0.0, 0.3,  //
     0.0, 0.3, 0.0, 0.0, 0.0,  //
     0.3, 0.3, 0.3, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0},

    // Frame 15
    {0.0, 0.0, 0.0, 0.3, 0.0,  //
     0.3, 0.0, 0.3, 0.0, 0.0,  //
     0.3, 0.3, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0},

    // Frame 16
    {0.0, 0.0, 0.3, 0.0, 0.0,  //
     0.0, 0.3, 0.0, 0.3, 0.0,  //
     0.3, 0.0, 0.0, 0.0, 0.3,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0},

    // Frame 17
    {0.0, 0.3, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.3, 0.0, 0.3,  //
     0.0, 0.0, 0.0, 0.3, 0.0,  //
     0.3, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0},

    // Frame 18
    {0.3, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.3, 0.0,  //
     0.0, 0.0, 0.3, 0.0, 0.3,  //
     0.0, 0.3, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0},

    // Frame 19
    {0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.3, 0.0, 0.0, 0.0, 0.3,  //
     0.0, 0.3, 0.0, 0.3, 0.0,  //
     0.0, 0.0, 0.3, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0},

    // Frame 20
    {0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.3, 0.0, 0.0,  //
     0.0, 0.3, 0.0, 0.3, 0.3,  //
     0.0, 0.0, 0.0, 0.0, 0.3,  //
     0.0, 0.0, 0.0, 0.0, 0.0},

    // Frame 21
    {0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.3, 0.0,  //
     0.3, 0.0, 0.3, 0.3, 0.3,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0},

    // Frame 22
    {0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.3,  //
     0.0, 0.3, 0.3, 0.3, 0.3,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0},

};

// função para exibir a sequência de batimentos
void cardiac_rate_matrix() {
  while (true) {
    for (int i = 0; i < FRAMES_SIZE; i++) {  // Exibe todos os 22 frames
      drawn_matrix(frames[i]);
      sleep_ms(50);  // Intervalo entre os frames
    }
  }
}

void bip_heart_monitor(uint slice_num, uint frequency, uint duration_ms) {
    pwm_set_clkdiv(slice_num, 125.0f); // Configura o divisor de clock para 125
    pwm_set_wrap(slice_num, 1000000 / frequency); // Define o período do PWM
    pwm_set_chan_level(slice_num, PWM_CHAN_A, (1000000 / frequency) / 2); // Define o duty cycle para 50%
    pwm_set_enabled(slice_num, true); // Habilita o PWM
    sleep_ms(duration_ms); // Aguarda pelo tempo de duração
    pwm_set_enabled(slice_num, false); // Desabilita o PWM
    sleep_ms(50); // Pausa de 500 ms
}

// rotina para definição da intensidade de cores do led
uint32_t matrix_rgb(double b, double r, double g) {
  unsigned char R, G, B;
  R = r * 255;
  G = g * 255;
  B = b * 255;
  return (G << 24) | (R << 16) | (B << 8);
}

// rotina para acionar a matrix de leds - ws2812b
void drawn_matrix(double* desenho) {
  uint32_t valor_led;
  for (int16_t i = 0; i < NUM_PIXELS; i++) {
    int index = 24 - i;
    double pixel = desenho[index];

    valor_led = matrix_rgb(b = 0.0, pixel, g = 0.0);

    pio_sm_put_blocking(pio, sm, valor_led);
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

  //configuração do buzzer
  gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM); // Configura o pino do buzzer para a função PWM
  uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN); // Obtém o número do slice PWM associado ao pino

  while (true) {
    // Simula os batimentos cardíacos
    cardiac_rate_matrix();
    bip_heart_monitor(slice_num, 1000, 50); // Toca um tom de 1000 Hz por 500 ms

  }
}