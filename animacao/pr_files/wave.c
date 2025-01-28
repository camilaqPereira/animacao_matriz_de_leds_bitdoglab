#include <stdio.h>

#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "pico/bootrom.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define BUZZER_PIN 15

// arquivo .piooo
#include "pio_animacao.pio.h"

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
// Efeito de onda
double frames[FRAMES_SIZE][NUM_PIXELS] = {
    {0.3, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0},

    {0.0, 0.3, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0},

    {0.0, 0.0, 0.3, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0},

    {0.0, 0.0, 0.0, 0.3, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0},

    {0.0, 0.0, 0.0, 0.0, 0.3,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0},

    // Agora, retorna para a esquerda
    {0.0, 0.0, 0.0, 0.3, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0},

    {0.0, 0.0, 0.3, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0},

    {0.0, 0.3, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0},

    {0.3, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0,  //
     0.0, 0.0, 0.0, 0.0, 0.0},
};


// função para exibir as ondas
void wave_matrix(unit slice_num) {
  while (true) {
    for (int i = 0; i < FRAMES_SIZE; i++) {  // Exibe todos os frames
      drawn_matrix(frames[i]);
      sleep_ms(50);  // Intervalo entre os frames
    }
  }
}

void drawn_matrix(double* desenho, uint slice_num, int frame_index) {
  uint32_t valor_led;
  
  for (int16_t i = 0; i < NUM_PIXELS; i++) {
    int index = 24 - i;
    double pixel = desenho[index];

    valor_led = matrix_rgb(b = 0.0, pixel, g = 0.0);
    pio_sm_put_blocking(pio, sm, valor_led);
  }

  // Aciona o PWM no primeiro e último frame
  if (frame_index == 0 || frame_index == FRAMES_SIZE - 1) {
      pwm_set_clkdiv(slice_num, 125.0f);  // Configura o divisor de clock
      pwm_set_wrap(slice_num, 1000000 / 1000);  // Frequência de 1kHz
      pwm_set_chan_level(slice_num, PWM_CHAN_A, 500);  // Duty cycle de 50%
      pwm_set_enabled(slice_num, true);  // Ativa o PWM
  } else {
      pwm_set_enabled(slice_num, false);  // Desativa o PWM
  }
}

// rotina para definição da intensidade de cores do led
uint32_t matrix_rgb(double b, double r, double g) {
  unsigned char R, G, B;
  R = r * 255;
  G = g * 255;
  B = b * 255;
  return (G << 24) | (R << 16) | (B << 8);
}

int main() {
    // Configura o clock para 128 MHz
    bool ok = set_sys_clock_khz(128000, false);
    stdio_init_all();

    // Configuração da PIO para os LEDs
    uint offset = pio_add_program(pio0, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio0, true);
    pio_matrix_program_init(pio0, sm, offset, OUT_PIN);

    // Configuração do PWM para o buzzer
    gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);  // Configura o pino do buzzer para função PWM
    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);  // Obtém o slice PWM

    while (true) {
        wave_matrix(slice_num);  // Sincroniza a animação com o buzzer via PWM
    }
}