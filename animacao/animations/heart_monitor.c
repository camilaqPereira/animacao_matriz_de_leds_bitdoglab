# include "heart_monitor.h"




/* Definicao de constantes*/

const double heart_monitor_frames[HEART_MONITOR_FRAMES_SIZE][MTX_NUM_LEDS] = {

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
void cardiac_rate_matrix(PIO pio, uint sm) {
    for (int times = 0; times < 3; times++){
        for (int i = 0; i < HEART_MONITOR_FRAMES_SIZE; i++) {  // Exibe todos os 22 frames
        heart_monitor_draw_matrix(pio, sm, heart_monitor_frames[i]);
        sleep_ms(150);  // Intervalo entre os frames
        }
        buzzer_play(1, 1000, 50);
       
    }
    

}


void heart_monitor_draw_matrix(PIO pio, uint sm, const double* desenho){
    uint32_t valor_led;
    for (int16_t i = 0; i < MTX_NUM_LEDS; i++) {
        int index = 24 - i;
        double pixel = desenho[index];

        valor_led = matrix_rgb(0.0, pixel,0.0);

        pio_sm_put_blocking(pio, sm, valor_led);
    }
}

