#include QMK_KEYBOARD_H

enum custom_keycodes {
    PUSH_TO_TALK = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_4x4(
        KC_7, KC_8,   KC_9,      KC__VOLUP,
        KC_4, KC_5,   KC_6,      KC__VOLDOWN,
        KC_1, KC_2,   KC_3,      KC_V,
        KC_0, KC_ENT, KC_BSPACE, PUSH_TO_TALK
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t ptt_timer;

    switch (keycode) {
    case PUSH_TO_TALK:
        if (record->event.pressed) {
            SEND_STRING("m");
            ptt_timer = timer_read();
        } else {
            if (timer_elapsed(ptt_timer) > 150) {
              SEND_STRING("m");
            }
        }
        break;
    }
    return true;
};
