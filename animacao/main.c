#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "pico/bootrom.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"


#include "hardware_management/buzzer.h"
#include "hardware_management/led_matrix.h"
#include "hardware_management/keypad.h"

#include "animations/vowels.h"

#include "main.pio.h"



/*Definicao de pinos*/

const uint GPIO_BUTTON_A = 5;
const uint GPIO_BUTTON_B = 6;



/* Definicao de fps*/
const uint32_t UPDATE_TIME_MS = 33; //ms

/*
*   @brief Funcao responsavel pela rotina de interrupcao do pushbutton A
*/
void handle_button_a_press(uint gpio, uint32_t events){
    printf("Interruption at %d pin. Entering boot mode", gpio);
    reset_usb_boot(0,0);
}


int main()
{
    //uint32_t target_mask = 0b111110000011111100000;
    //uint32_t target_dir_mask = 0b000000000010010000000;

    PIO pio = pio0; 

    /* Configuracao do clock*/
    if(set_sys_clock_khz(128000, false)){
        printf("Configuration of system clock completed!\n");
    }else{
        printf("COnfiguration of system clock failed\n");
        exit(-1);
    }

    /* Inicializacao de pinos*/
    stdio_init_all();
    
    buzzer_init();
    buzzer_setup_pwm(GPIO_BUZZER, BUZZER_FREQ);

    /* Configuracao da PIO*/

    uint offset = pio_add_program(pio, &main_program);
    uint state_machine = pio_claim_unused_sm(pio, true);
    main_program_init(pio, state_machine, offset, GPIO_LED_MTX);

    /*gpio_init_mask(target_mask);
    gpio_set_dir_masked(target_mask, target_dir_mask);


    */
    gpio_init(GPIO_BUTTON_A);
    gpio_set_dir(GPIO_BUTTON_A, GPIO_IN);
    gpio_pull_up(GPIO_BUTTON_A);

    gpio_set_irq_enabled_with_callback(GPIO_BUTTON_A, GPIO_IRQ_EDGE_FALL, 1, &handle_button_a_press);

    while (true) {
        printf("Begin animation!");
        vowels_animation(pio, state_machine);
        sleep_ms(500);
        
    }
}
