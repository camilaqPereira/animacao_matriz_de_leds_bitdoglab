#ifndef MAIN
#define MAIN


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
#include"animations/scroll_display.h"
#include "animations/heart_monitor.h"
#include "animations/wave.h"
#include "animations/countdown.h"

#include "main.pio.h"


/*Definicao de pinos*/

extern const double LED_OFF;
extern const double INTENSITY_20;
extern const double INTENSITY_50;
extern const double INTENSITY_80;
extern const double INTENSITY_100;


extern const uint GPIO_BUTTON_A;





#endif