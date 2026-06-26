// Copyright 2025 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "quantum.h"

enum Layers {
    QWERTY,
    LOWER,
    RAISE,
    GAMING,
};

combo_t key_combos[] = {};

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
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,                   QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
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

static const char*
depad_str(const char* depad_str, char depad_char) {
    while (*depad_str == depad_char) ++depad_str;
    return depad_str;
}

static void
render_spacer(uint8_t char_length) {
    static const char PROGMEM spacer_char[] = { 8, 8, 8, 8, 8, 8, 8 };
    if (char_length > 5) {
        char_length = 5;
    }
    for (uint8_t i = 0; i < char_length; i++) {
        oled_write_raw_P(spacer_char, sizeof(spacer_char));
        oled_advance_char();
    }
}

static void
render_logo(void) {
    // Zig logo
    static const char PROGMEM raw_logo[] = {
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   128, 128, 192, 192, 96,  32,  16,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   255, 255, 255, 255, 15,  15,  7,   3,   9,   12,  14,  15,  143, 207, 239, 255, 255, 255, 127, 63,  31,
        15,  7,   3,   9,   12,  254, 255, 255, 255, 0,   0,   0,   0,   0,   7,   7,   7,   7,   7,   7,   135, 199,
        231, 247, 127, 63,  31,  15,  7,   0,   0,   255, 255, 255, 0,   0,   248, 252, 254, 15,  7,   7,   7,   7,
        7,   7,   7,   7,   15,  62,  60,  56,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   255, 255, 127,
        63,  144, 192, 224, 240, 248, 252, 254, 255, 255, 255, 247, 243, 241, 240, 240, 112, 48,  144, 192, 224, 240,
        240, 255, 255, 255, 255, 0,   0,   0,   0,   0,   224, 240, 248, 252, 254, 239, 231, 227, 225, 224, 224, 224,
        224, 224, 224, 0,   0,   255, 255, 255, 0,   0,   31,  63,  127, 240, 224, 224, 224, 225, 225, 225, 227, 227,
        243, 127, 63,  31,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   8,   4,   6,   3,   3,   1,   1,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

static const char*
layer_string(uint32_t layer) {
    char* layer_str;

    switch (layer) {
        case QWERTY:
            layer_str = "Base";
            break;
        case LOWER:
            layer_str = "Lower";
            break;
        case RAISE:
            layer_str = "Raise";
            break;
        case GAMING:
            layer_str = "Game";
            break;
        default:
            layer_str = "Undef";
            break;
    }

    return layer_str;
}

#define CUSTOM_WHITE 0, 0, rgb_matrix_get_val()
#define CUSTOM_RED 0, 255, rgb_matrix_get_val()
#define CUSTOM_CYAN 115, 255, rgb_matrix_get_val()
#define CUSTOM_BLUE 180, 255, rgb_matrix_get_val()

static void
init_rgb_matrix(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_enable_noeeprom();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(CUSTOM_RED);
#endif
}

void
keyboard_post_init_user(void) {
    init_rgb_matrix();
}

void
suspend_wakeup_init_user(void) {
    layer_state_set(QWERTY);
    init_rgb_matrix();
}

layer_state_t
layer_state_set_user(layer_state_t state) {
#ifdef RGB_MATRIX_ENABLE
    switch (get_highest_layer(state)) {
        case GAMING:
            rgb_matrix_sethsv_noeeprom(CUSTOM_BLUE);
            break;
        default:
            rgb_matrix_sethsv_noeeprom(CUSTOM_RED);
            break;
    }
#endif
    return state;
}

bool
process_detected_host_os_user(os_variant_t detected_os) {
    oled_set_cursor(0, 6);
    switch (detected_os) {
        case OS_MACOS:
            oled_write_ln("MacOS", false);
        case OS_IOS:
            oled_write_ln("Apple", false);
            break;
        case OS_WINDOWS:
            oled_write_ln("Win", false);
            break;
        case OS_LINUX:
            oled_write_ln("Linux", false);
            break;
        case OS_UNSURE:
            oled_write_ln("Unkno", false);
            break;
    }

    return false;
}

oled_rotation_t
oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return OLED_ROTATION_180;
}

static void
render_wpm(uint16_t wpm) {
    oled_set_cursor(0, 10);
    oled_write_ln(depad_str(get_u16_str(wpm, ' '), ' '), false);
}

static void
render_layer_state(layer_state_t state) {
    oled_set_cursor(0, 2);
    oled_write_ln(layer_string(state), false);
}

bool
oled_task_user(void) {
    static bool oled_init_done = false;

    if (!oled_init_done) {
        if (!is_keyboard_master()) {
            render_logo();
        } else {
            oled_set_cursor(0, 0);
            oled_write("Layer", false);
            render_spacer(5);

            oled_set_cursor(0, 4);
            oled_write_ln("OS", false);
            render_spacer(2);
            oled_advance_page(false);
            oled_write_ln("Wait", false);

            oled_set_cursor(0, 8);
            oled_write_ln("WPM", false);
            render_spacer(3);
            render_wpm(get_current_wpm());
        }

        oled_init_done = true;
    }

    if (is_keyboard_master()) {
        static layer_state_t last_layer = -1;
        const layer_state_t current_layer = get_highest_layer(layer_state);
        if (last_layer != current_layer) {
            last_layer = current_layer;
            render_layer_state(current_layer);
        }

        static uint16_t last_wpm = 0;
        const uint16_t current_wpm = get_current_wpm();
        if (last_wpm != current_wpm) {
            last_wpm = current_wpm;
            render_wpm(current_wpm);
        }
    }

    return false;
}
