#include "encoder.h"

enum layers {
    _QWERTY = 0, // default layer
    _FUN,        // function layer
    _NAV,        // navigation layer
    _SYM,        // symbols layer
    _NUM,        // numbers layer
    _NVIM,       // nvim layer
};

// clang-format off
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {[_QWERTY] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT)}, [_NAV] = {ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)}, [_FUN] = {ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)}, [_SYM] = {ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)}, [_NUM] = {ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)}, [_NVIM] = {ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)}};
// clang-format on
