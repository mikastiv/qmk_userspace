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
render_small_mb_logo(void) {
    static const char PROGMEM small_mb_logo[] = {
        112, 112, 112, 0,   112, 112, 112, 0,   112, 112, 112, 0,   112, 112, 112, 0,   112, 112, 112, 0,   0,   119,
        119, 119, 0,   112, 112, 112, 0,   112, 112, 112, 119, 119, 119, 0,   0,   0,   0,   0,   119, 119, 119, 0,
        0,   0,   0,   0,   119, 119, 119, 0,   0,   119, 119, 119, 0,   112, 112, 112, 0,   119, 119, 119,
    };
    oled_write_raw_P(small_mb_logo, sizeof(small_mb_logo));
}

static uint8_t last_hue;
static uint8_t last_sat;
static uint8_t last_val;
static uint8_t last_mode;

static void
render_rgb_info(void) {
    last_hue = rgb_matrix_get_hue();
    last_sat = rgb_matrix_get_sat();
    last_val = rgb_matrix_get_val();
    last_mode = rgb_matrix_get_mode();
    oled_set_cursor(0, 6);
    oled_write("H:", false);
    oled_write(depad_str(get_u16_str(last_hue, ' '), ' '), false);
    oled_set_cursor(0, 7);
    oled_write("S:", false);
    oled_write_ln(depad_str(get_u16_str(last_sat, ' '), ' '), false);
    oled_set_cursor(0, 8);
    oled_write("V:", false);
    oled_write_ln(depad_str(get_u16_str(last_val, ' '), ' '), false);
    oled_set_cursor(0, 9);
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

static void
init_rgb_matrix(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_enable_noeeprom();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(CUSTOM_CYAN);
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
            rgb_matrix_sethsv_noeeprom(CUSTOM_RED);
            break;
        default:
            rgb_matrix_sethsv_noeeprom(CUSTOM_CYAN);
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

static void
oled_reinit_slave(void) {
    oled_init(OLED_ROTATION_270);
    oled_clear();
    oled_set_cursor(0, 0);
    oled_write_ln("WPM", false);
    render_spacer(3);
    oled_advance_page(false);
    oled_write_ln(depad_str(get_u16_str(get_current_wpm(), ' '), ' '), false);

    oled_set_cursor(0, 4);
    oled_write_ln("RGB", false);
    render_spacer(3);
    render_rgb_info();

    oled_set_cursor(0, 13);
    render_small_mb_logo();
}

bool
oled_task_user(void) {
    static bool oled_init_done = false;

    if (!oled_init_done) {
        if (!is_keyboard_master()) {
            oled_reinit_slave();
        } else {
            oled_set_cursor(0, 0);
            oled_write("Layer", false);
            render_spacer(5);
            oled_write_ln(layer_string(get_highest_layer(layer_state)), false);

            oled_set_cursor(0, 4);
            oled_write_ln("OS", false);
            render_spacer(2);
            oled_advance_page(false);
            oled_write_ln("Wait", false);
        }

        oled_init_done = true;
    }

    if (is_keyboard_master()) {
        oled_set_cursor(0, 2);
        oled_write_ln(layer_string(get_highest_layer(layer_state)), false);
    } else {
        static uint16_t last_wpm = 0;
        if (rgb_matrix_get_hue() != last_hue || rgb_matrix_get_sat() != last_sat || rgb_matrix_get_val() != last_val ||
            rgb_matrix_get_mode() != last_mode) {
            render_rgb_info();
        }
        if (last_wpm != get_current_wpm()) {
            last_wpm = get_current_wpm();
            oled_set_cursor(0, 2);
            oled_write_ln(depad_str(get_u16_str(last_wpm, ' '), ' '), false);
        }
    }

    return false;
}
