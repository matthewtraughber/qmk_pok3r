#include "vortex.h"

const uint16_t keymaps_default[][MATRIX_ROWS][MATRIX_COLS] = {
#if defined(KEYMAP_60_ANSI)
    [0] = LAYOUT_60_ansi(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        LT(1, KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  MO(1), KC_RGUI,   KC_RALT, TG(1)
    ),
    [1] = LAYOUT_60_ansi(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, KC_HOME, KC_PGUP, KC_UP,   KC_PGDN, KC_PSCR, _______, _______, _______,
        _______, KC_PAUSE, KC_VOLD, KC_VOLU, KC_MUTE, _______, KC_END, KC_LEFT, KC_DOWN, KC_RIGHT,_______,  _______, _______,
        _______, _______, _______, _______, _______, _______, _______,  _______, _______,  _______, _______,  _______,
        _______, _______, _______, KC_BSPC, _______, _______, _______, _______
    ),
#else
    #error "No Keymap!"
#endif
};
const uint16_t keymaps_default_size = sizeof(keymaps_default);
uint16_t keymaps[MAX_LAYERS][MATRIX_ROWS][MATRIX_COLS];

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    return MACRO_NONE;
};


void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}

void led_set_user(uint8_t usb_led) {

}