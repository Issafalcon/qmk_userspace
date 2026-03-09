#include "custom_rgb.h"
#include <stdint.h>
#include <string.h>
#include "action_layer.h"
#include "color.h"
#include "models/layers_enum.h"
#include "rgb_matrix.h"
#include "split_util.h"
#include "transactions.h"
#include "qmk-vim/src/vim.h"
#include "qmk-vim/src/modes.h"

#define LED_MOON 26
#define LED_HEART 56

typedef struct {
    bool       enabled;
    vim_mode_t mode;
} vim_rgb_sync_t;

static vim_rgb_sync_t vim_rgb_state = {false, NORMAL_MODE};

static void vim_rgb_sync_handler(uint8_t in_size, const void *in_data, uint8_t out_size, void *out_data) {
    if (in_size == sizeof(vim_rgb_sync_t)) {
        memcpy(&vim_rgb_state, in_data, sizeof(vim_rgb_sync_t));
    }
}

void keyboard_post_init_user(void) {
    transaction_register_rpc(USER_VIM_SYNC, vim_rgb_sync_handler);
}

void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        static vim_rgb_sync_t last    = {false, NORMAL_MODE};
        vim_rgb_sync_t        current = {vim_mode_enabled(), get_vim_mode()};
        if (memcmp(&last, &current, sizeof(vim_rgb_sync_t)) != 0) {
            if (transaction_rpc_send(USER_VIM_SYNC, sizeof(vim_rgb_sync_t), &current)) {
                last = current;
            }
        }
        vim_rgb_state = current;
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (vim_rgb_state.enabled) {
        rgb_t color;
        switch (vim_rgb_state.mode) {
            case INSERT_MODE:
                color = (rgb_t){RGB_GREEN};
                break;
            case VISUAL_MODE:
            case VISUAL_LINE_MODE:
                color = (rgb_t){RGB_GOLDENROD};
                break;
            case NORMAL_MODE:
            default:
                color = (rgb_t){RGB_PURPLE};
                break;
        }
        rgb_matrix_set_color_all(color.r, color.g, color.b);
    } else {
        uint8_t layer     = get_highest_layer(layer_state);
        rgb_t   coral     = {RGB_CORAL};
        rgb_t   teal      = {RGB_TEAL};
        rgb_t   goldenrod = {RGB_GOLDENROD};
        rgb_t   orange    = {RGB_ORANGE};
        rgb_t   azure     = {RGB_AZURE};
        rgb_t   magenta   = {RGB_MAGENTA};

        switch (layer) {
            case _QWERTY:
                rgb_matrix_set_color(LED_MOON, RGB_WHITE);
                rgb_matrix_set_color(LED_HEART, RGB_WHITE);
                break;
            case _FUN:
                set_rgb_on_mapped_layer_keys(led_min, led_max, layer, azure);
                break;
            case _NAV:
                set_rgb_on_mapped_layer_keys(led_min, led_max, layer, coral);
                break;
            case _GAME:
                set_rgb_on_mapped_layer_keys(led_min, led_max, layer, magenta);
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
    }

    if (host_keyboard_led_state().caps_lock) {
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                if (keymap_key_to_keycode(_QWERTY, (keypos_t){col, row}) == KC_CAPS) {
                    uint8_t index = g_led_config.matrix_co[row][col];
                    if (index != NO_LED && index >= led_min && index < led_max) {
                        rgb_matrix_set_color(index, RGB_WHITE);
                    }
                }
            }
        }
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
