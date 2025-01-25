#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"

// Definição de pinos para LEDs
#define LED_PIN_BASE 2
#define LED_COUNT 8

// Pinos do teclado matricial 4x4
const uint8_t row_pins[4] = {17, 16, 18, 19};  // Pinos das linhas do teclado
const uint8_t col_pins[4] = {20, 4, 9, 8};     // Pinos das colunas do teclado

// Mapeamento das teclas do teclado 4x4
const char keys[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Matriz de animação (quadrado, círculo, triângulo)
double desenho[3][5][5] = { 
    
    // Quadrado
    {1.0, 1.0, 1.0, 1.0, 1.0,
     1.0, 1.0, 1.0, 1.0, 1.0,
     1.0, 1.0, 1.0, 1.0, 1.0,
     1.0, 1.0, 1.0, 1.0, 1.0,
     1.0, 1.0, 1.0, 1.0, 1.0},
                         
    // Círculo
    {0.0, 1.0, 1.0, 1.0, 0.0,
     1.0, 0.0, 0.0, 0.0, 1.0, 
     1.0, 0.0, 0.0, 0.0, 1.0,
     1.0, 0.0, 0.0, 0.0, 1.0,
     0.0, 1.0, 1.0, 1.0, 0.0},

    // Triângulooo
    {0.0, 0.0, 1.0, 0.0, 0.0,
     0.0, 1.0, 1.0, 1.0, 0.0, 
     0.0, 1.0, 0.0, 1.0, 0.0,
     0.0, 1.0, 0.0, 0.0, 0.0,
     0.0, 0.0, 0.0, 0.0, 0.0}
};

// Funções para desenhar as formas no display (usando LEDs como exemplo)
void drawShape(double forma[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (forma[i][j] == 1.0) {
                gpio_put(LED_PIN_BASE + i + j, 1); // Acende o LED
            } else {
                gpio_put(LED_PIN_BASE + i + j, 0); // Apaga o LED
            }
        }
    }
}

// Função para ler o teclado matricial
char readKey() {
    for (int row = 0; row < 4; row++) {
        gpio_put(row_pins[row], 0);  // Ativa a linha (coloca o pino da linha em LOW)
        for (int col = 0; col < 4; col++) {
            if (gpio_get(col_pins[col]) == 0) {
                // Se uma tecla for pressionada, retorna o caractere correspondente
                return keys[row][col];
            }
        }
        gpio_put(row_pins[row], 1);  // Desativa a linha (coloca o pino da linha em HIGH)
    }
    return '\0';  // Retorna '\0' caso nenhuma tecla seja pressionada
}

int main() {
    // Inicializa os pinos de LEDs
    for (int i = 0; i < LED_COUNT; i++) {
        gpio_init(LED_PIN_BASE + i);
        gpio_set_dir(LED_PIN_BASE + i, GPIO_OUT);  // Configura os pinos dos LEDs como saída
        gpio_put(LED_PIN_BASE + i, 0);  // Inicializa os LEDs apagados
    }

    // Inicializa os pinos do teclado matricial
    for (int i = 0; i < 4; i++) {
        gpio_init(row_pins[i]);
        gpio_set_dir(row_pins[i], GPIO_OUT);  // Linhas como saída
        gpio_put(row_pins[i], 1);  // Mantém as linhas em HIGH

        gpio_init(col_pins[i]);
        gpio_set_dir(col_pins[i], GPIO_IN);  // Colunas como entrada
    }

    int step = 0;  // Controla a transição das formas
    while (true) {
        // Desenha as formas com base na variável 'step'
        if (step < 5) {
            drawShape(desenho[0]);  // Quadrado
        } else if (step < 10) {
            drawShape(desenho[1]);  // Círculo
        } else if (step < 15) {
            drawShape(desenho[2]);  // Triângulo
        }

        // Atraso para animação (100ms)
        sleep_ms(100);

        // Controla a transição suave de forma
        step++;
        if (step > 15) {
            step = 0;  // Reinicia a animação
        }

        // Ler tecla pressionada no teclado
        char key = readKey();
        if (key != '\0') {
            printf("Tecla pressionada: %c\n", key);
        }
    }

    return 0;
}
