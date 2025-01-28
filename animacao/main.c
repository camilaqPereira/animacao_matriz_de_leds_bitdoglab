
#include "main.h"


/* Definicao de constantes*/

const uint GPIO_BUTTON_A = 5;

const double LED_OFF = 0;
const double INTENSITY_20 = 0.2;
const double INTENSITY_50 = 0.5;
const double INTENSITY_80 = 0.8;
const double INTENSITY_100 = 1.0;

/*
*   @brief Funcao responsavel pela rotina de interrupcao do pushbutton A
*/
void handle_button_a_press(uint gpio, uint32_t events){
    printf("Interruption at %d pin. Entering boot mode", gpio);
    reset_usb_boot(0,0);
}


int main()
{

    PIO pio = pio0;
    char pressed_key = ' '; 

    /* Configuracao do clock*/
    if(set_sys_clock_khz(128000, false)){
        printf("Configuration of system clock completed!\n");
    }else{
        printf("Configuration of system clock failed\n");
        exit(-1);
    }

    /* Inicializacao de pinos*/
    stdio_init_all();
    
    buzzer_init();
    buzzer_setup_pwm(GPIO_BUZZER, BUZZER_FREQ);

    gpio_init(GPIO_BUTTON_A);
    gpio_set_dir(GPIO_BUTTON_A, GPIO_IN);
    gpio_pull_up(GPIO_BUTTON_A);

    keypad_init();

    /* Configuracao da PIO*/

    uint offset = pio_add_program(pio, &main_program);
    uint state_machine = pio_claim_unused_sm(pio, true);
    main_program_init(pio, state_machine, offset, GPIO_LED_MTX);

    /* Configurando interrupcao para o pushbutton A*/
    gpio_set_irq_enabled_with_callback(GPIO_BUTTON_A, GPIO_IRQ_EDGE_FALL, 1, &handle_button_a_press);

    while (true) {
        keypad_get_pressed_key(&pressed_key);
        //scanf("%c", &pressed_key); //PARA TESTE COM MONITOR SERIAL

        switch (pressed_key)
        {
        case '0':
            scroll_display_animation(pio, state_machine);
            break;
        case '1':
            cardiac_rate_matrix(pio, state_machine);
            break;
        case '2':
            vowels_animation(pio, state_machine);
            break;
        case '3':
            wave_animation(pio, state_machine);
            break;
        case '4':
            countdown_animation(pio, state_machine);
            break;
        case '5':
            break;
        case 'A':
            matrix_turn_all(pio, state_machine, LED_OFF, LED_OFF, LED_OFF);
            break;
        case 'B':
            matrix_turn_all(pio, state_machine, LED_OFF, LED_OFF, INTENSITY_100);
            break;
        case 'C':
            matrix_turn_all(pio, state_machine, INTENSITY_80, LED_OFF, LED_OFF);
            break;
        case 'D':
            matrix_turn_all(pio, state_machine, LED_OFF, INTENSITY_50, LED_OFF);
            break;
        case '#':
            matrix_turn_all(pio, state_machine, INTENSITY_20, INTENSITY_20, INTENSITY_20);
            break;
        case '*':
            reset_usb_boot(0,0);
            break;
        default:
            break;
        }

        sleep_ms(200);
    }
}
