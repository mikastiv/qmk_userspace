// Copyright 2025 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum Layers {
    QWERTY,
    LOWER,
    RAISE,
    GAMING,
};

#define LOW MO(LOWER)
#define RSE MO(RAISE)
#define TO_GAME TO(GAMING)
#define TO_QWER TO(QWERTY)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[QWERTY] = LAYOUT(
   KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,
   KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
  KC_LALT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC, KC_RBRC,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
                             KC_LALT, KC_LGUI,     LOW, KC_LSFT,  KC_SPC,     RSE,  KC_ENT, KC_RGUI
),

[LOWER] = LAYOUT(
  _______,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_TILD, XXXXXXX, _______,
  _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                   KC_MINS,  KC_EQL, KC_LPRN, KC_RPRN, KC_PIPE,  KC_GRV,
  _______,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______, _______, KC_UNDS, KC_PLUS,   KC_LT,   KC_GT, KC_BSLS, XXXXXXX,
                             _______, _______, XXXXXXX, _______, _______, XXXXXXX, _______, _______
),


[RAISE] = LAYOUT(
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   _______, _______, _______, _______, _______, _______,
  _______,  KC_F1,    KC_F2,   KC_F3,   KC_F4, XXXXXXX,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______,
  _______,  KC_F5,    KC_F6,   KC_F7,   KC_F8, XXXXXXX,                   KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX, XXXXXXX,
  _______,  KC_F9,   KC_F10,  KC_F11,  KC_F12, XXXXXXX, _______, _______, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, XXXXXXX, TO_GAME,
                             _______, _______, XXXXXXX, _______, _______, XXXXXXX, _______, _______
),

[GAMING] = LAYOUT(
   KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,
   KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
  KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC, KC_RBRC,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, TO_QWER,
                             KC_LALT, KC_LGUI, XXXXXXX,  KC_SPC,  KC_SPC, XXXXXXX,  KC_ENT, KC_RGUI
)
};

// clang-format on


#define CUSTOM_WHITE 0, 0, rgb_matrix_get_val()
#define CUSTOM_RED   0, 255, rgb_matrix_get_val()
#define CUSTOM_BLUE  170, 255, rgb_matrix_get_val()

static void init_rgb_matrix(void) {
#ifdef CONVERTER_ENABLED
    rgb_matrix_enable_noeeprom();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(CUSTOM_WHITE);
#endif
}

void keyboard_post_init_user(void) {
    init_rgb_matrix();
}

void suspend_wakeup_init_user(void) {
    layer_state_set(QWERTY);
    init_rgb_matrix();
}


layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef CONVERTER_ENABLED
    switch(get_highest_layer(state)) {
        case GAMING:
            rgb_matrix_sethsv_noeeprom(CUSTOM_RED);
            break;
        default:
            rgb_matrix_sethsv_noeeprom(CUSTOM_WHITE);
            break;
    }
#endif
    return state;
}
