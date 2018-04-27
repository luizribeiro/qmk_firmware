#include "keyboards/winkeyless/bmini/bmini.h"
#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
#endif
#include "action_layer.h"
#include "quantum.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT( \
        KC_ESC, KC_FN0, KC_FN1, KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_MPRV,KC_MPLY,KC_MNXT,KC_MUTE,KC_VOLD,KC_VOLU,KC_FN3, KC_HOME,KC_END, \
        KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSPC,        KC_DEL, \
        KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSLS,        KC_FN2, \
        KC_CAPS,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_ENT,                 KC_PGUP,\
        KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,                KC_UP,  KC_PGDN,\
        KC_LCTL,KC_LALT,KC_LGUI,                KC_SPC,                                 KC_RGUI,KC_RALT,KC_RCTL,KC_LEFT,KC_DOWN,KC_RGHT \
    ),
};

enum macro_id {
    RGB_LEVEL_DOWN,
    RGB_LEVEL_UP,
    RGB_CHANGE,
    PRINT_SCREEN,
};

uint8_t current_level = 8;
uint8_t current_color = 0;

#ifdef RGBLIGHT_ENABLE
void rgblight_setrgb(uint8_t r, uint8_t g, uint8_t b);
#endif

uint8_t dim(uint8_t color, uint8_t opacity) {
    return ((uint16_t) color * opacity / 0xFF) & 0xFF;
}

void user_setrgb(uint8_t r, uint8_t g, uint8_t b) {
#ifdef RGBLIGHT_ENABLE
    uint8_t alpha = current_level * 0x11;
    rgblight_setrgb(dim(r, alpha), dim(g, alpha), dim(b, alpha));
#endif
}

void update_rgb_light(void) {
    switch (current_color) {
        case 1:
            user_setrgb(0x00, 0x00, 0xFF);
            break;
        case 2:
            user_setrgb(0x00, 0xFF, 0x00);
            break;
        default:
            user_setrgb(0xFF, 0x00, 0x00);
            break;
    }
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    keyevent_t event = record->event;

    switch (id) {
        case RGB_LEVEL_DOWN:
            if (event.pressed && current_level > 0) {
                current_level--;
            }
            update_rgb_light();
            break;
        case RGB_LEVEL_UP:
            if (event.pressed && current_level < 15) {
                current_level++;
            }
            update_rgb_light();
            break;
        case RGB_CHANGE:
            current_color = (current_color + 1) % 3;
            update_rgb_light();
            break;
        case PRINT_SCREEN:
            return (event.pressed
                    ? MACRO(D(LGUI), D(LSFT), T(S), U(LSFT), U(LGUI), END)
                    : MACRO(END));
    }

    return MACRO_NONE;
}

const uint16_t fn_actions[] PROGMEM = {
    [0] = ACTION_MACRO(RGB_LEVEL_DOWN),
    [1] = ACTION_MACRO(RGB_LEVEL_UP),
    [2] = ACTION_MACRO(RGB_CHANGE),
    [3] = ACTION_MACRO(PRINT_SCREEN),
};
