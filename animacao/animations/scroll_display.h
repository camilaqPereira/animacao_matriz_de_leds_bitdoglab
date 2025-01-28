#ifndef SCROLL_DISPLAY
#define SCROLL_DISPLAY

#include "hardware/pio.h"
#include "hardware_management/led_matrix.h"

//extern const uint64_t scroll_display_frames[];


void rotate_left_by_one(uint64_t value[]);

void scroll_display_animation(PIO pio, uint state_machine);

#endif