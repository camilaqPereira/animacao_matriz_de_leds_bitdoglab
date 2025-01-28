#include "scroll_display.h"


/* Definicao de constantes*/

void rotate_left_by_one(uint64_t value[]) {
    for (size_t i = 0; i < MTX_NUM_ROWS; i++){
        value[i] = (value[i] << 1) | (value[i] >> (64 - 1));
        
    } 
}


void scroll_display_animation(PIO pio, uint state_machine){
    uint32_t led_value;
    double intensity;

    uint64_t scroll_display_frames[] = {
        0b1110100010100011101110111011101110111011101010,
        0b1000110110100010101000100010100100100010001010,
        0b1110101010111010101000100010100100111010001110,
        0b1000100010101011101000100011100100100010001010,
        0b1110100010111010101000111010100100111011101010,
    };
    
    int shift, aux;
    
    for (int frame = 0; frame < 46; frame++)
    {
        for (int i = 4; i >=0; i--){
            aux = 4;
            for (int j = 45; j > 40; j--){
                shift = (i & 1) ? j : j - aux;
                intensity = ((scroll_display_frames[i] >> shift) & 1)*0.1;
                led_value = matrix_rgb(intensity,intensity, 0.0);
                pio_sm_put_blocking(pio, state_machine, led_value);
                aux-=2;
            }
            
        }
        sleep_ms(150);
        rotate_left_by_one(scroll_display_frames);
    }
    



        
    
}