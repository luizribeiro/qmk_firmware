#include "keyboards/winkeyless/bmini/bmini.h"
#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
#endif
#include "action_layer.h"
#include "quantum.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT( \
        KC_ESC, KC_FN3, KC_FN4, KC_FN5, KC_FN6, KC_NO,  KC_NO,  KC_MPRV,KC_MPLY,KC_MNXT,KC_MUTE,KC_VOLD,KC_VOLU,KC_FN7, KC_HOME,KC_END, \
        KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSPC,        KC_DEL, \
        KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSLS,        KC_FN1, \
        KC_FN2, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_ENT,                 KC_PGUP,\
        KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,                KC_UP,  KC_PGDN,\
        KC_FN0, KC_LALT,KC_LGUI,                KC_SPC,                                 KC_RGUI,KC_RALT,KC_RCTL,KC_LEFT,KC_DOWN,KC_RGHT \
    ),
    LAYOUT( \
        KC_NO,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_NO,  KC_NO,  KC_NO,  \
        KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_MPRV,KC_MPLY,KC_MNXT,KC_MUTE,KC_VOLD,KC_VOLU,KC_DEL,         KC_NO,  \
        KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_PGUP,KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,          KC_TRNS,\
        KC_FN1, KC_NO,  KC_NO,  KC_PGDN,KC_NO,  KC_NO,  KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,KC_NO,  KC_NO,  KC_NO,                  KC_NO,  \
        KC_TRNS,KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_TRNS,                KC_NO,  KC_NO,  \
        KC_TRNS,KC_TRNS,KC_TRNS,                KC_FN8,                                 KC_TRNS,KC_TRNS,KC_TRNS,KC_NO,  KC_NO,  KC_NO   \
    ),
    LAYOUT( \
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,\
        KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_END, KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_HOME,KC_NO,  KC_NO,  KC_NO,          KC_NO,  \
        KC_NO,  KC_BTN1,KC_MS_U,KC_BTN2,KC_NO,  KC_NO,  KC_NO,  KC_PGUP,KC_FN1, KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,          KC_TRNS,\
        KC_TRNS,KC_MS_L,KC_MS_D,KC_MS_R,KC_NO,  KC_NO,  KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,KC_NO,  KC_NO,  KC_NO,                  KC_TRNS,\
        KC_TRNS,KC_NO,  KC_DEL, KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_TRNS,                KC_TRNS,KC_TRNS,\
        KC_TRNS,KC_TRNS,KC_TRNS,                KC_NO,                                  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS \
    ),
};

enum macro_id {
    MAC_EXPOSE,
    MAC_LAUNCHPAD,
    MAC_PRINT_SCREEN,
    RGB_LEVEL_DOWN,
    RGB_LEVEL_UP,
    LAYER_2,
    KVM,
};

uint8_t current_level = 8;
uint8_t current_layer = 0;

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
    switch (current_layer) {
        case 1:
            user_setrgb(0xFF, 0x66, 0x00);
            break;
        case 2:
            user_setrgb(0x00, 0xFF, 0xFF);
            break;
        default:
            user_setrgb(0xFF, 0x00, 0x00);
            break;
    }
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    keyevent_t event = record->event;

    switch (id) {
        case LAYER_2:
            if (!event.pressed) {
                return MACRO(END);
            }
            if (IS_LAYER_ON(2)) {
                layer_off(2);
                return MACRO(D(LGUI), D(LSHIFT), D(LALT), D(LCTL), T(1),
                    U(LCTL), U(LALT), U(LSHIFT), U(LGUI), END);
            }
            layer_on(2);
            return MACRO(D(LGUI), D(LSHIFT), D(LALT), D(LCTL), T(2),
                U(LCTL), U(LALT), U(LSHIFT), U(LGUI), END);
        case MAC_EXPOSE:
            return (event.pressed
                    ? MACRO(D(LCTL), T(UP), U(LCTL), END)
                    : MACRO(END));
        case MAC_LAUNCHPAD:
            return (event.pressed
                    ? MACRO(D(LSHIFT), D(LCTL), T(L), U(LCTL), U(LSHIFT), END)
                    : MACRO(END));
        case MAC_PRINT_SCREEN:
            return (event.pressed
                    ? MACRO(D(LGUI), D(LSHIFT), T(4), U(LSHIFT), U(LGUI), END)
                    : MACRO(END));
        case KVM:
            return (event.pressed
                    ? MACRO(T(CAPS), T(CAPS), END)
                    : MACRO(END));
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
    }

    return MACRO_NONE;
}

const uint16_t fn_actions[] PROGMEM = {
    [0] = ACTION_LAYER_ONESHOT(1),
    [1] = ACTION_MACRO(LAYER_2),
    [2] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_ESC),
    [3] = ACTION_MACRO(RGB_LEVEL_DOWN),
    [4] = ACTION_MACRO(RGB_LEVEL_UP),
    [5] = ACTION_MACRO(MAC_EXPOSE),
    [6] = ACTION_MACRO(MAC_LAUNCHPAD),
    [7] = ACTION_MACRO(MAC_PRINT_SCREEN),
    [8] = ACTION_MACRO(KVM),
};

uint32_t layer_state_set_user(uint32_t state) {
    current_layer = biton32(state);
    update_rgb_light();

    return state;
}
