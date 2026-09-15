// Copyright 2026 Matthew Ho
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "bongo_cat.h"

enum layer_names {
    L_BASE,
    L_SYMBOLS,
    L_NAV,
    L_SYSTEM,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L_BASE] = LAYOUT(
        KC_TAB,          KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        LCTL_T(KC_ESC),  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT,         LT(3, KC_Z), KC_X, KC_C,   KC_V,    KC_B,                         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, LT(2, KC_UP),
        KC_LGUI,         KC_LALT, MO(2),   KC_LCTL, KC_BSPC, KC_LSFT,            KC_MPLY,  LT(1, KC_SPC), KC_ENT, KC_LGUI, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [L_SYMBOLS] = LAYOUT(
        KC_ESC,  _______, _______, _______, _______, _______,                        _______, KC_LBRC, KC_RBRC, KC_MINS, KC_EQL,  KC_DEL,
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
        _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, KC_BSLS, _______,
        _______, _______, _______, _______, _______, _______,              KC_MPLY,  _______, _______, _______, _______, _______, _______
    ),

    [L_NAV] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                          KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        _______, _______, _______, _______, _______, _______,                        KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,
        _______, _______, _______, _______, _______, _______,                        _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
        _______, _______, _______, _______, _______, _______,              KC_MPLY,  _______, _______, _______, _______, _______, _______
    ),

    [L_SYSTEM] = LAYOUT(
        QK_BOOT, KC_BRID, KC_BRIU, KC_MPRV, KC_MPLY, KC_MNXT,                        KC_MUTE, KC_VOLD, KC_VOLU, KC_PSCR, _______, _______,
        _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, KC_CAPS,
        _______, _______, MC_0,    MC_1,    MC_2,    MC_3,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,              KC_MUTE,  _______, _______, _______, _______, _______, _______
    ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [L_BASE]    = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [L_SYMBOLS] = {ENCODER_CCW_CW(KC_MPRV, KC_MNXT)},
    [L_NAV]     = {ENCODER_CCW_CW(KC_PGDN, KC_PGUP)},
    [L_SYSTEM]  = {ENCODER_CCW_CW(KC_BRID, KC_BRIU)},
};
#endif

#ifdef OLED_ENABLE

enum animation_state {
    ANIM_IDLE,
    ANIM_PREP,
    ANIM_TAP,
};

#define IDLE_WPM_MAX 40
#define TAP_WPM_MIN 60
#define FRAME_DURATION_MS 150

static uint32_t frame_timer;
static uint8_t  idle_frame;
static uint8_t  tap_frame;

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_0;
}

static enum animation_state animation_state_for_wpm(uint8_t wpm) {
    if (wpm <= IDLE_WPM_MAX) {
        return ANIM_IDLE;
    }
    if (wpm < TAP_WPM_MIN) {
        return ANIM_PREP;
    }
    return ANIM_TAP;
}

static void render_bongo_cat(uint8_t wpm) {
    if (timer_elapsed32(frame_timer) < FRAME_DURATION_MS) {
        return;
    }
    frame_timer = timer_read32();

    switch (animation_state_for_wpm(wpm)) {
        case ANIM_IDLE:
            oled_write_raw_P((const char *)bongo_idle[idle_frame], BONGO_FRAME_SIZE);
            idle_frame = (idle_frame + 1) % BONGO_IDLE_FRAME_COUNT;
            break;
        case ANIM_PREP:
            oled_write_raw_P((const char *)bongo_prep, BONGO_FRAME_SIZE);
            break;
        case ANIM_TAP:
            oled_write_raw_P((const char *)bongo_tap[tap_frame], BONGO_FRAME_SIZE);
            tap_frame = (tap_frame + 1) % BONGO_TAP_FRAME_COUNT;
            break;
    }
}

static void render_status(uint8_t wpm) {
    oled_set_cursor(0, 0);
    oled_write_P(PSTR("WPM:"), false);
    oled_write(get_u8_str(wpm, '0'), false);

    oled_set_cursor(0, 1);
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case L_BASE:
            oled_write_P(PSTR("BASE   "), false);
            break;
        case L_SYMBOLS:
            oled_write_P(PSTR("SYMBOLS"), false);
            break;
        case L_NAV:
            oled_write_P(PSTR("NAV    "), false);
            break;
        default:
            oled_write_P(PSTR("SYSTEM "), false);
            break;
    }

    oled_set_cursor(16, 0);
    oled_write_P(PSTR("I WUB"), false);
    oled_set_cursor(18, 2);
    oled_write_P(PSTR("YOU"), false);
    oled_set_cursor(16, 3);
    oled_write_P(PSTR("JULIA"), false);
    oled_set_cursor(0, 3);
    oled_write_P(PSTR("8.31.23"), false);
}

bool oled_task_user(void) {
    const uint8_t wpm = get_current_wpm();
    render_bongo_cat(wpm);
    render_status(wpm);
    return false;
}

#endif
