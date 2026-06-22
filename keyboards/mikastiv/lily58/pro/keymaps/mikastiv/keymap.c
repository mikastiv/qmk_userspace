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

static uint16_t current_keycode = 0xFF;

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

__attribute__((weak)) void
render_logo(void) {
    static const char PROGMEM mb_logo[] = {
        252, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 31,  31,  31,  31,  31,  255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 3,   3,   3,   3,   3,   3,   3,
        3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,
        3,   3,   3,   227, 227, 227, 3,   227, 227, 227, 3,   227, 227, 227, 3,   3,   3,   3,   3,   3,   3,   3,
        3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   7,   254, 252, 255, 255, 255, 255,
        255, 7,   7,   7,   7,   7,   255, 7,   7,   7,   7,   7,   255, 7,   7,   7,   7,   7,   255, 7,   7,   7,
        7,   7,   255, 7,   7,   7,   7,   7,   255, 255, 255, 4,   4,   4,   4,   4,   255, 7,   7,   7,   7,   7,
        255, 7,   7,   7,   7,   7,   255, 255, 255, 255, 255, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   224, 224, 224, 0,   238, 238, 238, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   255, 255, 255, 255, 255, 255, 255, 65,  65,  65,
        65,  65,  255, 255, 255, 255, 255, 255, 255, 65,  65,  65,  65,  65,  255, 255, 255, 255, 255, 255, 255, 65,
        65,  65,  65,  65,  255, 255, 255, 65,  65,  65,  65,  65,  255, 127, 127, 127, 127, 127, 255, 65,  65,  65,
        65,  65,  255, 255, 255, 255, 255, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   14,
        14,  14,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   255, 255, 63,  127, 255, 255, 255, 240, 240, 240, 240, 240, 255, 255,
        255, 255, 255, 255, 255, 240, 240, 240, 240, 240, 255, 255, 255, 255, 255, 255, 255, 240, 240, 240, 240, 240,
        255, 255, 255, 240, 240, 240, 240, 240, 255, 240, 240, 240, 240, 240, 255, 240, 240, 240, 240, 240, 255, 255,
        255, 255, 255, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192,
        192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 199, 199, 199, 192, 192,
        192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192,
        192, 192, 192, 224, 127, 63,
    };
    oled_write_raw_P(mb_logo, sizeof(mb_logo));
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
    oled_write("M:", false);
    oled_write_ln(depad_str(get_u16_str(last_mode, ' '), ' '), false);
}

static const char basic_codes_to_name[57] = { ' ', ' ',  ' ', ' ', 'a',  'b', 'c', 'd', 'e', 'f', 'g', 'h',
                                              'i', 'j',  'k', 'l', 'm',  'n', 'o', 'p', 'q', 'r', 's', 't',
                                              'u', 'v',  'w', 'x', 'y',  'z', '1', '2', '3', '4', '5', '6',
                                              '7', '8',  '9', '0', 'R',  'E', 'B', 'T', '_', '-', '=', '[',
                                              ']', '\\', '#', ';', '\'', '`', ',', '.', '/' };

static const char*
keycode_string(uint16_t keycode) {
    char* keycode_str;
    static char key;
    switch (keycode) {
        case 0 ... 56:
            key = pgm_read_byte(&basic_codes_to_name[keycode]);
            return &key;
        case KC_CAPS:
            keycode_str = "Caps";
            break;
        case KC_SCRL:
            keycode_str = "Scrl";
            break;
        case KC_PAUS:
            keycode_str = "Pause";
            break;
        case KC_DEL:
            keycode_str = "Del";
            break;
        case KC_NUM:
            keycode_str = "Num";
            break;
        case KC_MUTE:
            keycode_str = "Mute";
            break;
        case KC_VOLU:
            keycode_str = "VolUp";
            break;
        case KC_VOLD:
            keycode_str = "VolD";
            break;
        case KC_MNXT:
            keycode_str = "Next";
            break;
        case KC_MPRV:
            keycode_str = "Prev";
            break;
        case KC_MSTP:
            keycode_str = "Stop";
            break;
        case KC_MPLY:
            keycode_str = "Play";
            break;
        case QK_MODS ... QK_MODS_MAX:
            keycode_str = "MOD()";
            break;
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            keycode_str = "MT()";
            break;
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            keycode_str = "LT()";
            break;
        case QK_LAYER_MOD ... QK_LAYER_MOD_MAX:
            keycode_str = "LM()";
            break;
        case QK_TO ... QK_TO_MAX:
            keycode_str = "TO()";
            break;
        case QK_MOMENTARY ... QK_MOMENTARY_MAX:
            keycode_str = "MO()";
            break;
        case QK_DEF_LAYER ... QK_DEF_LAYER_MAX:
            keycode_str = "DF()";
            break;
        case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
            keycode_str = "TG()";
            break;
        case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_MOD_MAX:
            keycode_str = "1SHOT";
            break;
        case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
            keycode_str = "TT()";
            break;
        case QK_PERSISTENT_DEF_LAYER ... QK_PERSISTENT_DEF_LAYER_MAX:
            keycode_str = "PDF()";
            break;
        case QK_SWAP_HANDS ... QK_SWAP_HANDS_MAX:
            keycode_str = "SWAP";
            break;
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            keycode_str = "TD()";
            break;
        case QK_MAGIC ... QK_MAGIC_MAX:
            keycode_str = "Magic";
            break;
        case QK_MIDI ... QK_MIDI_MAX:
            keycode_str = "Midi";
            break;
        case QK_SEQUENCER ... QK_SEQUENCER_MAX:
            keycode_str = "Seq";
            break;
        case QK_JOYSTICK ... QK_JOYSTICK_MAX:
            keycode_str = "Joy";
            break;
        case QK_PROGRAMMABLE_BUTTON ... QK_PROGRAMMABLE_BUTTON_MAX:
            keycode_str = "Prog";
            break;
        case QK_AUDIO ... QK_AUDIO_MAX:
            keycode_str = "Audio";
            break;
        case QK_STENO ... QK_STENO_MAX:
            keycode_str = "Steno";
            break;
        case QK_MACRO ... QK_MACRO_MAX:
            keycode_str = "Macro";
            break;
        case QK_CONNECTION ... QK_CONNECTION_MAX:
            keycode_str = "Conn";
            break;
        case QK_LIGHTING ... QK_LIGHTING_MAX:
            keycode_str = "Light";
            break;
        case QK_QUANTUM ... QK_QUANTUM_MAX:
            keycode_str = "Quant";
            break;
        case QK_KB ... QK_KB_MAX:
            keycode_str = "KB";
            break;
        case QK_USER ... QK_USER_MAX:
            keycode_str = "USER";
            break;
        case QK_UNICODEMAP ... QK_UNICODEMAP_PAIR_MAX:
            keycode_str = "Uni";
            break;
        default:
            keycode_str = "Undef";
            break;
    }

    return keycode_str;
}

static const char*
layer_string(uint32_t layer) {
    char* layer_str;
    switch (layer) {
        case 0:
            layer_str = "Zero";
            break;
        case 1:
            layer_str = "One";
            break;
        case 2:
            layer_str = "Two";
            break;
        case 3:
            layer_str = "Three";
            break;
        case 4:
            layer_str = "Four";
            break;
        case 5:
            layer_str = "Five";
            break;
        case 6:
            layer_str = "Six";
            break;
        case 7:
            layer_str = "Seven";
            break;
        default:
            return get_u16_str(layer, ' ');
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
    oled_set_cursor(0, 2);
    oled_write_ln(layer_string(get_highest_layer(state)), false);
    return state;
}

bool
process_detected_host_os_user(os_variant_t detected_os) {
    oled_set_cursor(0, 10);
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

bool
process_record_user(uint16_t keycode, keyrecord_t* record) {
    current_keycode = keycode;
    return true;
};

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
            render_logo();
        } else {
            oled_set_cursor(0, 0);
            oled_write("Layer", false);
            render_spacer(5);
            oled_write_ln(layer_string(get_highest_layer(layer_state)), false);

            oled_set_cursor(0, 4);
            oled_write_ln("Key", false);
            render_spacer(3);
            oled_advance_page(false);
            oled_write_ln("None", false);

            oled_set_cursor(0, 8);
            oled_write_ln("OS", false);
            render_spacer(2);
            oled_advance_page(false);
            oled_write_ln("Wait", false);
        }

        oled_init_done = true;
    }

    static uint16_t last_keycode = 0xFF;
    static bool oled_slave_init_done = false;

    if (is_keyboard_master()) {
        if (last_keycode != current_keycode) {
            oled_set_cursor(0, 6);
            if (current_keycode < ARRAY_SIZE(basic_codes_to_name)) {
                oled_write_char(basic_codes_to_name[current_keycode], false);
                oled_advance_page(true);
            } else {
                oled_write_ln(keycode_string(current_keycode), false);
            }
            last_keycode = current_keycode;
        }
    } else {
        if (!oled_slave_init_done) {
            if (timer_elapsed32(0) > 5000) {
                oled_slave_init_done = true;
                oled_reinit_slave();
            }
        } else {
            static uint16_t last_wpm = 0;
            if (rgb_matrix_get_hue() != last_hue || rgb_matrix_get_sat() != last_sat ||
                rgb_matrix_get_val() != last_val || rgb_matrix_get_mode() != last_mode) {
                render_rgb_info();
            }
            if (last_wpm != get_current_wpm()) {
                last_wpm = get_current_wpm();
                oled_set_cursor(0, 2);
                oled_write_ln(depad_str(get_u16_str(last_wpm, ' '), ' '), false);
            }
        }
    }

    return false;
}
