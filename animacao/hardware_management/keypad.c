#include "keypad.h"

/* Definicao de constantes*/

const uint rows_pins[KEYPAD_NUM_ROWS] = {17, 16, 18, 19};
const uint columns_pins[KEYPAD_NUM_COLUMNS] = {20, 4, 9, 8};
const char keypad_mapping[KEYPAD_NUM_ROWS][KEYPAD_NUM_COLUMNS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

void keypad_init() {
    for (int i = 0; i < 4; i++) {
        // Configura os pinos das linhas como saída
        gpio_init(rows_pins[i]);
        gpio_set_dir(rows_pins[i], GPIO_OUT);
        gpio_put(rows_pins[i], 1); // Desativar linha

        // Configura os pinos das colunas como entrada 
        gpio_init(columns_pins[i]);
        gpio_set_dir(columns_pins[i], GPIO_IN);
        gpio_pull_up(columns_pins[i]);
    }
}

void keypad_get_pressed_key(char *pressed_key) {
    for (int row = 0; row < 4; row++) {
        gpio_put(rows_pins[row], 0); // Ativar linha
        for (int col = 0; col < 4; col++) {
            if (gpio_get(columns_pins[col]) == 0) { // Verifica se a coluna está ativa
                gpio_put(rows_pins[row], 1); // Desativar linha
                *pressed_key = keypad_mapping[row][col]; // Retorna a tecla pressionada
                return;
            }
        }
        gpio_put(rows_pins[row], 1); // Desativar linha
    }
    *pressed_key = ' ';
    // Nenhuma tecla pressionada
}



