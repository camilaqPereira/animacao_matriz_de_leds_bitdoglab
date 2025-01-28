@ -0,0 +1,160 @@
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/pwm.h" // Biblioteca para PWM
#include "vogal.pio.h" // Arquivo .pio atualizado para a matriz

#define NUM_PIXELS 25 // Número de LEDs
#define OUT_PIN 7 // Pino de saída
#define BUZZER_PIN 21 // Pino do buzzer
#define BUZZER_FREQ 4000 // Frequência do buzzer em Hz

// Representação das letras A, E, I, O, U em matrizes
const int letter_frames[5][25] = {
    // Letra A
    { 0,  1,  1,  1,  0,
      1,  0,  0,  0,  1,
      1,  1,  1,  1,  1,
      1,  0,  0,  0,  1,
      1,  0,  0,  0,  1},

    // Letra E
    { 1,  1,  1,  1,  1,
      0,  0,  0,  0,  1,
      1,  1,  1,  1,  1,
      0,  0,  0,  0,  1,
      1,  1,  1,  1,  1},

    // Letra I
    { 0,  0,  1,  0,  0,
      0,  0,  1,  0,  0,
      0,  0,  1,  0,  0,
      0,  0,  1,  0,  0,
      0,  0,  1,  0,  0},

    // Letra O
    { 0,  1,  1,  1,  0,
      1,  0,  0,  0,  1,
      1,  0,  0,  0,  1,
      1,  0,  0,  0,  1,
      0,  1,  1,  1,  0},

    // Letra U
    { 1,  0,  0,  0,  1,
      1,  0,  0,  0,  1,
      1,  0,  0,  0,  1,
      1,  0,  0,  0,  1,
      0,  1,  1,  1,  0}
};

// Notas musicais: Dó, Ré, Mi, Fá, Sol, Lá, Si, Dó (escala simples)
const int melody[] = {262, 294, 330, 349, 392, 440, 494, 523}; // Notas C4 a C5
const int melody_duration[] = {300, 300, 300, 300, 300, 300, 300, 600}; // Durações em ms
const int melody_length = 8;

// Função para definir a intensidade de cores do LED
uint32_t matrix_rgb(double b, double r, double g) {
    unsigned char R = r * 255;
    unsigned char G = g * 255;
    unsigned char B = b * 255;
    return (G << 24) | (R << 16) | (B << 8);
}

// Função para acender LEDs gradualmente para formar uma letra
void render_letter(const int *letter, PIO pio, uint sm) {
    uint32_t frame[NUM_PIXELS] = {0}; // Estado atual dos LEDs

    for (int i = 0; i < NUM_PIXELS; i++) {
        if (letter[i]) {
            frame[i] = matrix_rgb(0.5, 0.0, 0.0); // Define o LED atual como azul
        }

        // Envia o estado atualizado para todos os LEDs
        for (int j = 0; j < NUM_PIXELS; j++) {
            pio_sm_put_blocking(pio, sm, frame[24 - j]);
        }
        sleep_ms(100); // Atraso para acender LED por LED
    }

    // Garante que a letra inteira permaneça visível após acender todos os LEDs
    for (int j = 0; j < NUM_PIXELS; j++) {
        pio_sm_put_blocking(pio, sm, frame[24 - j]);
    }
    sleep_ms(500); // Pausa após completar a letra
}

// Função para configurar o PWM no pino do buzzer
void setup_buzzer_pwm(uint pin, uint freq_hz) {
    gpio_set_function(pin, GPIO_FUNC_PWM); // Configura o pino como saída PWM
    uint slice_num = pwm_gpio_to_slice_num(pin); // Obtém o número do slice
    uint channel = pwm_gpio_to_channel(pin); // Obtém o canal PWM

    // Configura o clock do PWM
    uint32_t clock_div = clock_get_hz(clk_sys) / (freq_hz * 4096);
    pwm_set_clkdiv(slice_num, clock_div);

    // Ativa o PWM e define duty cycle como 0% inicialmente
    pwm_set_chan_level(slice_num, channel, 0);
    pwm_set_enabled(slice_num, true);
}

// Função para tocar o buzzer com PWM
void play_buzzer(int times, uint freq_hz, uint duration_ms) {
    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN); // Obtém o slice
    uint channel = pwm_gpio_to_channel(BUZZER_PIN); // Obtém o canal PWM

    for (int i = 0; i < times; i++) {
        pwm_set_chan_level(slice_num, channel, 2048); // Duty cycle 50% (som ligado)
        sleep_ms(duration_ms);
        pwm_set_chan_level(slice_num, channel, 0); // Duty cycle 0% (som desligado)
        sleep_ms(200); // Pausa entre os toques
    }
}

// Função para tocar uma melodia no buzzer
void play_melody() {
    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);
    uint channel = pwm_gpio_to_channel(BUZZER_PIN);

    for (int i = 0; i < melody_length; i++) {
        uint32_t clock_div = clock_get_hz(clk_sys) / (melody[i] * 4096);
        pwm_set_clkdiv(slice_num, clock_div);
        pwm_set_chan_level(slice_num, channel, 2867); // Duty cycle 70%
        sleep_ms(melody_duration[i]);
        pwm_set_chan_level(slice_num, channel, 0); // Desliga o som
        sleep_ms(150); // Pausa entre as notas
    }
}

int main() {
    PIO pio = pio0;
    uint32_t valor_led;

    // Configuração do clock e inicialização padrão
    bool ok = set_sys_clock_khz(128000, false);
    stdio_init_all();
    if (ok) printf("Clock configurado para %ld Hz\n", clock_get_hz(clk_sys));

    // Configuração do PIO
    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, OUT_PIN);

    // Configuração do pino do buzzer com PWM
    setup_buzzer_pwm(BUZZER_PIN, BUZZER_FREQ);

    while (true) {
        // Toca o buzzer duas vezes no início de cada repetição
        play_buzzer(2, BUZZER_FREQ, 200);

        // Exibe cada letra gradualmente
        for (int letter_idx = 0; letter_idx < 5; letter_idx++) {
            render_letter(letter_frames[letter_idx], pio, sm);
        }

        // Toca a escala simples "Dó, Ré, Mi, Fá, Sol, Lá, Si, Dó" no final da animação
        play_melody();
    }
}