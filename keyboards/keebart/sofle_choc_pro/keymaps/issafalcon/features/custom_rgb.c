#include "custom_rgb.h"
#include <stdint.h>
#include "action_layer.h"
#include "models/layers_enum.h"
#include "rgb_matrix.h"

#define LED_MOON 26
#define LED_HEART 56

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer     = get_highest_layer(layer_state);
    rgb_t   coral     = {RGB_CORAL};
    rgb_t   purple    = {RGB_PURPLE};
    rgb_t   teal      = {RGB_TEAL};
    rgb_t   goldenrod = {RGB_GOLDENROD};
    rgb_t   orange    = {RGB_ORANGE};
    switch (layer) {
        case _QWERTY:
            rgb_matrix_set_color(LED_MOON, RGB_WHITE);
            rgb_matrix_set_color(LED_HEART, RGB_WHITE);
            break;
        case _NAV:
            set_rgb_on_mapped_layer_keys(led_min, led_max, layer, coral);
            break;
        case _GAME:
            set_rgb_on_mapped_layer_keys(led_min, led_max, layer, purple);
            break;
        case _SYM:
            set_rgb_on_mapped_layer_keys(led_min, led_max, layer, teal);
            break;
        case _NUM:
            set_rgb_on_mapped_layer_keys(led_min, led_max, layer, goldenrod);
            break;
        case _NVIM:
            set_rgb_on_mapped_layer_keys(led_min, led_max, layer, orange);
            break;
        default:
            break;
    }

    return true;
}

void set_rgb_on_mapped_layer_keys(uint8_t led_min, uint8_t led_max, uint8_t layer, rgb_t color) {
    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t index = g_led_config.matrix_co[row][col];

            if (index >= led_min && index < led_max && index != NO_LED && keymap_key_to_keycode(layer, (keypos_t){col, row}) > KC_TRNS) {
                rgb_matrix_set_color(index, color.r, color.g, color.b);
            } else if (index >= led_min && index < led_max && index != NO_LED) {
                rgb_matrix_set_color(index, 0, 0, 0);
            }
        }
    }
}
