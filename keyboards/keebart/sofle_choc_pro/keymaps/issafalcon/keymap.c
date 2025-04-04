// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include "action.h"
#include "keycode_config.h"
#include "keycodes.h"
#include "modifiers.h"
#include "quantum_keycodes.h"
#include QMK_KEYBOARD_H
#include "keymap_uk.h"
#include "models/layers_enum.h"
#include "features/chordal_hold.h"
#include "features/encoder.h"

#define HOME_A LGUI_T(KC_A)
#define HOME_S LALT_T(KC_S)
#define HOME_D LSFT_T(KC_D)
#define HOME_F LCTL_T(KC_F)

#define HOME_H RCTL_T(KC_H)
#define HOME_J RSFT_T(KC_J)
#define HOME_K LALT_T(KC_K)
#define HOME_L RGUI_T(KC_L)

#define SPACE LT(_NAV, KC_SPC)
#define ENTER LT(_SYM, KC_ENT)
#define BSPC LT(_FUN, KC_BSPC)
#define TAB LT(_NUM, KC_TAB)
#define DEL LT(_FUN, KC_DEL)

#define R_BSPC LT(_NUM, KC_BSPC)

#define O_GUI OSM(MOD_LGUI)
#define O_SFT OSM(MOD_LSFT)
#define O_CTL OSM(MOD_LCTL)
#define O_LALT OSM(MOD_LALT)
#define O_RALT OSM(MOD_RALT)

#define CT_TAB LCTL(KC_TAB)
#define CT_SFT_TAB LCTL(LSFT(KC_TAB))

#define SFT_TAB LSFT(KC_TAB)

// clang-format off
enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_NAV,
    KC_SYM,
    KC_NMBR,
    KC_FUN,
    ALT_TAB,
    ALT_SFT_TAB,
    KC_SFT_TAB,
    KC_TMUX,
    NVIM_CA,
    NVIM_MARK
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌───────────────┬────────┬────────┬────────┬────────┬──────┐                                 ┌────────┬────────┬────────┬────────┬───┬──────┐
//    │      no       │   1    │   2    │   3    │   4    │  5   │                                 │   6    │   7    │   8    │   9    │ 0 │  no  │
//    ├───────────────┼────────┼────────┼────────┼────────┼──────┤                                 ├────────┼────────┼────────┼────────┼───┼──────┤
//    │      tab      │   q    │   w    │   e    │   r    │  t   │                                 │   y    │   u    │   i    │   o    │ p │ bspc │
//    ├───────────────┼────────┼────────┼────────┼────────┼──────┤                                 ├────────┼────────┼────────┼────────┼───┼──────┤
//    │      esc      │ HOME_A │ HOME_S │ HOME_D │ HOME_F │  g   │                                 │ HOME_H │ HOME_J │ HOME_K │ HOME_L │ ; │  `   │
//    ├───────────────┼────────┼────────┼────────┼────────┼──────┼──────┐                   ┌──────┼────────┼────────┼────────┼────────┼───┼──────┤
//    │ OSM(MOD_LSFT) │   z    │   x    │   c    │   v    │  b   │ mute │                   │ mply │   n    │   m    │   ,    │   .    │ / │  '   │
//    └───────────────┴────────┴────────┼────────┼────────┼──────┼──────┼───────┐   ┌───────┼──────┼────────┼────────┼────────┼────────┴───┴──────┘
//                                      │   no   │  lgui  │ tMUX │ TAB  │ SPACE │   │ ENTER │ BSPC │  DEL   │   no   │   no   │
//                                      └────────┴────────┴──────┴──────┴───────┘   └───────┴──────┴────────┴────────┴────────┘
[_QWERTY] = LAYOUT_split_4x6_5(
  XXXXXXX       , KC_1   , KC_2   , KC_3    , KC_4    , KC_5    ,                                         KC_6   , KC_7    , KC_8    , KC_9   , KC_0    , XXXXXXX,
  KC_TAB        , KC_Q   , KC_W   , KC_E    , KC_R    , KC_T    ,                                         KC_Y   , KC_U    , KC_I    , KC_O   , KC_P    , KC_BSPC,
  KC_ESC        , HOME_A , HOME_S , HOME_D  , HOME_F  , KC_G    ,                                         HOME_H , HOME_J  , HOME_K  , HOME_L , KC_SCLN , KC_GRV ,
  OSM(MOD_LSFT) , KC_Z   , KC_X   , KC_C    , KC_V    , KC_B    , KC_MUTE ,                     KC_MPLY , KC_N   , KC_M    , KC_COMM , KC_DOT , KC_SLSH , KC_QUOT,
                                    XXXXXXX , KC_LGUI , KC_TMUX , TAB     , SPACE ,     ENTER , BSPC    , DEL    , XXXXXXX , XXXXXXX
),

//    ┌─────────────┬──────┬───────┬────────┬───────┬────────┐                           ┌──────┬──────┬──────┬──────┬─────┬─────┐
//    │             │      │       │        │       │        │                           │      │      │      │      │     │     │
//    ├─────────────┼──────┼───────┼────────┼───────┼────────┤                           ├──────┼──────┼──────┼──────┼─────┼─────┤
//    │             │      │       │        │       │        │                           │      │      │ home │ end  │     │ f12 │
//    ├─────────────┼──────┼───────┼────────┼───────┼────────┤                           ├──────┼──────┼──────┼──────┼─────┼─────┤
//    │   ALT_TAB   │      │ O_GUI │ O_LALT │ O_SFT │ O_CTL  │                           │ left │ down │  up  │ rght │     │ f11 │
//    ├─────────────┼──────┼───────┼────────┼───────┼────────┼─────┐               ┌─────┼──────┼──────┼──────┼──────┼─────┼─────┤
//    │ ALT_SFT_TAB │ undo │  cut  │  copy  │ paste │ O_RALT │     │               │     │      │ pgdn │ pgup │      │     │ f10 │
//    └─────────────┴──────┴───────┼────────┼───────┼────────┼─────┼─────┐   ┌─────┼─────┼──────┼──────┼──────┼──────┴─────┴─────┘
//                                 │        │       │        │     │     │   │     │     │      │      │      │
//                                 └────────┴───────┴────────┴─────┴─────┘   └─────┴─────┴──────┴──────┴──────┘
[_NAV] = LAYOUT_split_4x6_5(
  _______     , _______ , _______ , _______ , _______  , _______ ,                                             _______ , _______ , _______ , _______  , _______ , _______,
  _______     , _______ , _______ , _______ , _______  , _______ ,                                             _______ , _______ , KC_HOME , KC_END   , _______ , KC_F12 ,
  ALT_TAB     , _______ , O_GUI   , O_LALT  , O_SFT    , O_CTL   ,                                             KC_LEFT , KC_DOWN , KC_UP   , KC_RIGHT , _______ , KC_F11 ,
  ALT_SFT_TAB , KC_UNDO , KC_CUT  , KC_COPY , KC_PASTE , O_RALT  , _______ ,                         _______ , _______ , KC_PGDN , KC_PGUP , _______  , _______ , KC_F10 ,
                                    _______ , _______  , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______
),

//    ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                           ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
//    │         │         │         │         │         │         │                           │         │         │         │         │         │         │
//    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                           ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
//    │         │ UK_QUOT │ UK_LABK │ UK_RABK │ UK_PND  │ UK_GRV  │                           │ UK_AMPR │ UK_UNDS │ UK_LBRC │ UK_RBRC │ UK_PERC │         │
//    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                           ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
//    │   tab   │ UK_EXLM │ UK_MINS │ UK_PLUS │ UK_EQL  │ UK_HASH │                           │ UK_PIPE │ UK_COLN │ UK_LPRN │ UK_RPRN │ UK_SCLN │ UK_DQUO │
//    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────┐               ┌─────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
//    │ SFT_TAB │ UK_CIRC │ UK_SLSH │ UK_ASTR │ UK_BSLS │  UK_AT  │     │               │     │ UK_TILD │ UK_DLR  │ UK_LCBR │ UK_RCBR │ UK_QUES │         │
//    └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┼─────┼─────┐   ┌─────┼─────┼─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
//                                  │         │         │         │     │     │   │     │     │         │         │         │
//                                  └─────────┴─────────┴─────────┴─────┴─────┘   └─────┴─────┴─────────┴─────────┴─────────┘
[_SYM] = LAYOUT_split_4x6_5(
  _______ , _______ , _______ , _______ , _______ , _______ ,                                             _______ , _______ , _______ , _______ , _______ , _______,
  _______ , UK_QUOT , UK_LABK , UK_RABK , UK_PND  , UK_GRV  ,                                             UK_AMPR , UK_UNDS , UK_LBRC , UK_RBRC , UK_PERC , _______,
  KC_TAB  , UK_EXLM , UK_MINS , UK_PLUS , UK_EQL  , UK_HASH ,                                             UK_PIPE , UK_COLN , UK_LPRN , UK_RPRN , UK_SCLN , UK_DQUO,
  SFT_TAB , UK_CIRC , UK_SLSH , UK_ASTR , UK_BSLS , UK_AT   , _______ ,                         _______ , UK_TILD , UK_DLR  , UK_LCBR , UK_RCBR , UK_QUES , _______,
                                _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______
),

//    ┌────────────┬─────┬───────┬────────┬───────┬────────┐                           ┌─────┬─────┬─────┬─────┬─────┬─────┐
//    │            │     │       │        │       │        │                           │     │     │     │     │     │     │
//    ├────────────┼─────┼───────┼────────┼───────┼────────┤                           ├─────┼─────┼─────┼─────┼─────┼─────┤
//    │            │     │       │        │       │        │                           │     │  7  │  8  │  9  │     │     │
//    ├────────────┼─────┼───────┼────────┼───────┼────────┤                           ├─────┼─────┼─────┼─────┼─────┼─────┤
//    │   CT_TAB   │     │ O_GUI │ O_LALT │ O_SFT │ O_CTL  │                           │     │  4  │  5  │  6  │  0  │     │
//    ├────────────┼─────┼───────┼────────┼───────┼────────┼─────┐               ┌─────┼─────┼─────┼─────┼─────┼─────┼─────┤
//    │ CT_SFT_TAB │     │       │        │       │ O_RALT │     │               │     │     │  1  │  2  │  3  │     │     │
//    └────────────┴─────┴───────┼────────┼───────┼────────┼─────┼─────┐   ┌─────┼─────┼─────┼─────┼─────┼─────┴─────┴─────┘
//                               │        │       │        │     │     │   │     │     │     │     │     │
//                               └────────┴───────┴────────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┘
[_NUM] = LAYOUT_split_4x6_5(
  _______    , _______ , _______ , _______ , _______ , _______ ,                                             _______ , _______ , _______ , _______ , _______ , _______,
  _______    , _______ , _______ , _______ , _______ , _______ ,                                             _______ , KC_7    , KC_8    , KC_9    , _______ , _______,
  CT_TAB     , _______ , O_GUI   , O_LALT  , O_SFT   , O_CTL   ,                                             _______ , KC_4    , KC_5    , KC_6    , KC_0    , _______,
  CT_SFT_TAB , _______ , _______ , _______ , _______ , O_RALT  , _______ ,                         _______ , _______ , KC_1    , KC_2    , KC_3    , _______ , _______,
                                   _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______
),

//    ┌─────┬─────────┬─────────┬─────────┬─────────┬─────────┐                           ┌─────────┬───────────┬─────────┬─────────┬─────────┬─────┐
//    │     │         │         │         │         │         │                           │         │           │         │         │         │     │
//    ├─────┼─────────┼─────────┼─────────┼─────────┼─────────┤                           ├─────────┼───────────┼─────────┼─────────┼─────────┼─────┤
//    │     │         │ LCTL(2) │ LCTL(3) │ LCTL(4) │ LCTL(5) │                           │ LCTL(6) │  LCTL(7)  │ LCTL(8) │ LCTL(9) │ LCTL(0) │     │
//    ├─────┼─────────┼─────────┼─────────┼─────────┼─────────┤                           ├─────────┼───────────┼─────────┼─────────┼─────────┼─────┤
//    │     │ NVIM_CA │ LALT(2) │ LALT(3) │ LALT(4) │ LALT(5) │                           │ LALT(6) │  LALT(7)  │ LALT(8) │ LALT(9) │ LALT(0) │     │
//    ├─────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────┐               ┌─────┼─────────┼───────────┼─────────┼─────────┼─────────┼─────┤
//    │     │         │         │         │         │         │     │               │     │         │ NVIM_MARK │         │         │         │     │
//    └─────┴─────────┴─────────┼─────────┼─────────┼─────────┼─────┼─────┐   ┌─────┼─────┼─────────┼───────────┼─────────┼─────────┴─────────┴─────┘
//                              │         │         │         │     │     │   │     │     │         │           │         │
//                              └─────────┴─────────┴─────────┴─────┴─────┘   └─────┴─────┴─────────┴───────────┴─────────┘
[_NVIM] = LAYOUT_split_4x6_5(
  _______ , _______ , _______    , _______    , _______    , _______    ,                                             _______    , _______    , _______    , _______    , _______    , _______,
  _______ , _______ , LCTL(KC_2) , LCTL(KC_3) , LCTL(KC_4) , LCTL(KC_5) ,                                             LCTL(KC_6) , LCTL(KC_7) , LCTL(KC_8) , LCTL(KC_9) , LCTL(KC_0) , _______,
  _______ , NVIM_CA , LALT(KC_2) , LALT(KC_3) , LALT(KC_4) , LALT(KC_5) ,                                             LALT(KC_6) , LALT(KC_7) , LALT(KC_8) , LALT(KC_9) , LALT(KC_0) , _______,
  _______ , _______ , _______    , _______    , _______    , _______    , _______ ,                         _______ , _______    , NVIM_MARK  , _______    , _______    , _______    , _______,
                                   _______    , _______    , _______    , _______ , _______ ,     _______ , _______ , _______    , _______    , _______
),

//    ┌─────────┬────────┬────────┬───────┬───────┬────────┐                           ┌─────┬─────┬─────┬─────┬─────┬─────┐
//    │         │        │        │       │       │        │                           │     │     │     │     │     │     │
//    ├─────────┼────────┼────────┼───────┼───────┼────────┤                           ├─────┼─────┼─────┼─────┼─────┼─────┤
//    │ QK_BOOT │ qWERTY │        │       │       │        │                           │     │ f7  │ f8  │ f9  │ f12 │ f15 │
//    ├─────────┼────────┼────────┼───────┼───────┼────────┤                           ├─────┼─────┼─────┼─────┼─────┼─────┤
//    │         │  lgui  │ O_LALT │ O_SFT │ O_CTL │ O_RALT │                           │     │ f4  │ f5  │ f6  │ f11 │ f14 │
//    ├─────────┼────────┼────────┼───────┼───────┼────────┼─────┐               ┌─────┼─────┼─────┼─────┼─────┼─────┼─────┤
//    │         │        │        │       │       │        │     │               │     │     │ f1  │ f2  │ f3  │ f10 │ f13 │
//    └─────────┴────────┴────────┼───────┼───────┼────────┼─────┼─────┐   ┌─────┼─────┼─────┼─────┼─────┼─────┴─────┴─────┘
//                                │       │       │        │     │     │   │     │     │     │     │     │
//                                └───────┴───────┴────────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┘
[_FUN] = LAYOUT_split_4x6_5(
  _______ , _______   , _______ , _______ , _______ , _______ ,                                             _______ , _______ , _______ , _______ , _______ , _______,
  QK_BOOT , KC_QWERTY , _______ , _______ , _______ , _______ ,                                             _______ , KC_F7   , KC_F8   , KC_F9   , KC_F12  , KC_F15 ,
  _______ , KC_LGUI   , O_LALT  , O_SFT   , O_CTL   , O_RALT  ,                                             _______ , KC_F4   , KC_F5   , KC_F6   , KC_F11  , KC_F14 ,
  _______ , _______   , _______ , _______ , _______ , _______ , _______ ,                         _______ , _______ , KC_F1   , KC_F2   , KC_F3   , KC_F10  , KC_F13 ,
                                  _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______
)
};

// clang-format on
void update_swapper(bool *active, uint16_t cmdish, uint16_t tabish, uint16_t trigger, uint16_t prv, bool *other_active, uint16_t keycode, keyrecord_t *record) {
    if (keycode == trigger && !*other_active) {
        if (record->event.pressed) {
            if (!*active) {
                *active = true;
                register_code(cmdish);
            }
            register_code(tabish);
        } else {
            unregister_code(tabish);
            // Don't unregister cmdish until some other key is hit or released.
        }
    } else if (keycode == prv && *active) {
        if (record->event.pressed) {
            register_code16(S(tabish));
        } else {
            unregister_code16(S(tabish));
        }
    } else if (*active) {
        // On non-ignored keyup, disable swapper
        unregister_code(cmdish);
        *active = false;
    }
}

bool alt_tab_active = false;
bool sft_grv_active = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // If console is enabled, it will print the matrix position and status of each
    // key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: "
            "%u, count: %u\n",
            keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif
    update_swapper(&alt_tab_active, KC_LALT, KC_TAB, ALT_TAB, ALT_SFT_TAB, &sft_grv_active, keycode, record);
    update_swapper(&sft_grv_active, KC_LALT, KC_GRV, ALT_SFT_TAB, ALT_TAB, &alt_tab_active, keycode, record);

    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case KC_NAV:
            if (record->event.pressed) {
                layer_on(_NAV);
            } else {
                layer_off(_NAV);
            }
            return false;
        case KC_SYM:
            if (record->event.pressed) {
                layer_on(_SYM);
            } else {
                layer_off(_SYM);
            }
            return false;
        case KC_NMBR:
            if (record->event.pressed) {
                layer_on(_NUM);
            } else {
                layer_off(_NUM);
            }
            return false;
        case KC_FUN:
            if (record->event.pressed) {
                layer_on(_FUN);
            } else {
                layer_off(_FUN);
            }
            return false;
        case KC_COPY:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_C);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_C);
            }
            return false;
        case KC_PASTE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_V);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_V);
            }
            return false;
        case KC_CUT:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_X);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_X);
            }
            return false;
            break;
        case KC_UNDO:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_Z);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_Z);
            }
            return false;
        case KC_TMUX:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_B);
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_B);
            }
            return false;
        case NVIM_CA:
            if (record->event.pressed) {
                tap_code(KC_SPC);
                tap_code(KC_C);
                tap_code(KC_A);
            }
        case NVIM_MARK:
            if (record->event.pressed) {
                tap_code(UK_BSLS);
                tap_code(KC_M);
            }
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _NAV, _SYM, _NVIM);
#ifdef CONSOLE_ENABLE
    uprintf("%d layer\n", state);
#endif
    return state;
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to next key.
            return true;
        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;
        default:
            return false; // Deactivate Caps Word.
    }
}
