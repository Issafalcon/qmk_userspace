#include "rgb_matrix.h"
#include <stdint.h>
#include "color.h"
#include "qmk-vim/src/vim.h"

uint8_t vim_keys[] = {
    KC_H, KC_J, KC_K, KC_L, KC_U, KC_I, KC_O, KC_Y, KC_BSPC, KC_TAB, KC_ENT, KC_SPC, KC_ESC, KC_F1,
};

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        for (uint8_t i = led_min; i < led_max; i++) {
            if (g_led_config.flags[i] & LED_FLAG_KEYLIGHT) {
                rgb_matrix_set_color(i, RGB_RED);
            }
        }
    }

    if (vim_mode_enabled()) {
        uint8_t layer = get_highest_layer(layer_state);

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                // Check if the keymap_key_to_keycode result is in the vim_keys array
                bool is_vim_key = false;
                for (uint8_t i = 0; i < sizeof(vim_keys); i++) {
                    if (keymap_key_to_keycode(layer, (keypos_t){col, row}) == vim_keys[i]) {
                        is_vim_key = true;
                        break;
                    }
                }
                if (index >= led_min && index < led_max && index != NO_LED && is_vim_key) {
                    rgb_matrix_set_color(index, RGB_PURPLE);
                }
            }
        }
    }

    return false;
}
