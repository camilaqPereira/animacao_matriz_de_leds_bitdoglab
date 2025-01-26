#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"

#define NUM_LEDS 25 // Matriz 
#define ROWS 5
#define COLS 5
#define PIN_BASE 0  // GPIO inicial para os LEDs
#define FPS 10      // Quadros por segundo das animações

// Mapeamento do teclado matricial
const char keypad_map[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Pinos do teclado matricial 4x4
const uint8_t row_pins[4] = {17, 16, 18, 19};  // Pinos das linhas do teclado
const uint8_t col_pins[4] = {20, 4, 9, 8};     // Pinos das colunas do teclado

void init_leds() {
    for (int i = 0; i < NUM_LEDS; i++) {
        gpio_init(PIN_BASE + i);
        gpio_set_dir(PIN_BASE + i, GPIO_OUT);
    }
}

void set_led(int row, int col, bool state) {
    int led = row * COLS + col;
    gpio_put(PIN_BASE + led, state);
}

void clear_leds() {
    for (int i = 0; i < NUM_LEDS; i++) {
        gpio_put(PIN_BASE + i, false);
    }
}

void show_frame(bool frame[ROWS][COLS]) {
    clear_leds();
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            set_led(row, col, frame[row][col]);
        }
    }
    sleep_ms(1000 / FPS);
}

void animation_0() {
    bool frames[5][ROWS][COLS] = {
        {{1, 0, 0, 0, 1}, {0, 1, 0, 1, 0}, {0, 0, 1, 0, 0}, {0, 1, 0, 1, 0}, {1, 0, 0, 0, 1}},
        {{0, 1, 0, 1, 0}, {1, 0, 1, 0, 1}, {0, 1, 0, 1, 0}, {1, 0, 1, 0, 1}, {0, 1, 0, 1, 0}},
        {{0, 0, 1, 0, 0}, {0, 1, 0, 1, 0}, {1, 0, 0, 0, 1}, {0, 1, 0, 1, 0}, {0, 0, 1, 0, 0}},
        {{0, 1, 0, 1, 0}, {1, 0, 1, 0, 1}, {0, 1, 0, 1, 0}, {1, 0, 1, 0, 1}, {0, 1, 0, 1, 0}},
        {{1, 0, 0, 0, 1}, {0, 1, 0, 1, 0}, {0, 0, 1, 0, 0}, {0, 1, 0, 1, 0}, {1, 0, 0, 0, 1}}
    };

    for (int i = 0; i < 5; i++) {
        show_frame(frames[i]);
    }
}

// Outras animações (1-9) podem ser adicionadas seguindo o mesmo formato
void play_animation(char key) {
    switch (key) {
        case '0':
            animation_0();
            break;
        // case '1': animation_1(); break;
        // case '2': animation_2(); break;
        // ...
        default:
            break;
    }
}

void init_keypad() {
    for (int i = 0; i < 4; i++) {
        gpio_init(row_pins[i]);
        gpio_set_dir(row_pins[i], GPIO_OUT);
        gpio_put(row_pins[i], true);

        gpio_init(col_pins[i]);
        gpio_set_dir(col_pins[i], GPIO_IN);
        gpio_pull_up(col_pins[i]);
    }
}

char read_keypad() {
    for (int row = 0; row < 4; row++) {
        gpio_put(row_pins[row], false);

        for (int col = 0; col < 4; col++) {
            if (!gpio_get(col_pins[col])) {
                gpio_put(row_pins[row], true);
                return keypad_map[row][col];
            }
        }

        gpio_put(row_pins[row], true);
    }
    return '\0'; // Nenhuma tecla pressionada
}

int main() {
    stdio_init_all();
    init_leds();
    init_keypad();

    while (true) {
        char key = read_keypad();
        if (key != '\0') {
            printf("Tecla pressionada: %c\n", key);
            play_animation(key);
        }
        sleep_ms(100);  // Pequena pausa para evitar múltiplas leituras da mesma tecla
    }
