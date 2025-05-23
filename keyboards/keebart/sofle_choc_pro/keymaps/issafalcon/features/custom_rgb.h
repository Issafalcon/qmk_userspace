#ifndef CUSTOM_RGB_H
#define CUSTOM_RGB_H

#include "action_layer.h"
#include "keymap_common.h"
#include "rgb_matrix.h"

uint8_t qwerty_keys[MATRIX_ROWS][MATRIX_COLS];

void set_rgb_on_mapped_layer_keys(uint8_t led_min, uint8_t led_max, uint8_t layer, rgb_t color);
#endif // !CUSTOM_RGB_H
