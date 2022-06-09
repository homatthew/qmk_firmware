/* Copyright 2021 Brandon Lewi
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */

#include QMK_KEYBOARD_H

/**

((((([\w\d,\(\)]+))|[\w\d]+), ){6})
((((([\w\d,\(\)]+))|[\w\d]+), ){6})((((([\w\d,\(\)]+))|[\w\d]+), ){6})((((([\w\d,\(\)]+))|[\w\d]+), ){6})((((([\w\d,\(\)]+))|[\w\d]+), ){6})((((([\w\d,\(\)]+))|[\w\d]+), ){6})((((([\w\d,\(\)]+))|[\w\d]+), ){6})((((([\w\d,\(\)]+))|[\w\d]+), ){6})((((([\w\d,\(\)]+))|[\w\d]+), ){1})((((([\w\d,\(\)]+))|[\w\d]+), ){5})((((([\w\d,\(\)]+))|[\w\d]+)\)){1})

(\[\d\] = LAYOUT\()((((([\w\d,\(\)]+))|[\w\d]+), ){6})((((([\w\d,\(\)]+))|[\w\d]+), ){6})((((([\w\d,\(\)]+))|[\w\d]+), ){6})((((([\w\d,\(\)]+))|[\w\d]+), ){6})((((([\w\d,\(\)]+))|[\w\d]+), ){6})((((([\w\d,\(\)]+))|[\w\d]+), ){6})((((([\w\d,\(\)]+))|[\w\d]+), ){6})((((([\w\d,\(\)]+))|[\w\d]+), ){1})((((([\w\d,\(\)]+))|[\w\d]+), ){5})((((([\w\d,\(\)]+))|[\w\d]+)\)){1})
$1\n$2\t\t\t\t\t\t\t\t$7\n$12\t\t\t\t\t\t\t\t$17\n$22\t\t\t\t\t\t\t\t\t$27\n$32\t\t\t\t\t\t\t\t$37\t\t\t\t\t\t\t\t$42$47

 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [0] = LAYOUT(
          KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, 								                                              KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
          LCTL_T(KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, 								                                      KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
          KC_LSFT, LT(3,KC_Z), KC_X, KC_C, KC_V, KC_B, 									                                      KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, LT(2,KC_UP),
          KC_LGUI, KC_LALT, MO(2), KC_LCTL, KC_BSPC, KC_LSFT, 								          KC_MPLY, 		   				LT(1,KC_SPC), KC_ENT, KC_LGUI, KC_LEFT, KC_DOWN, KC_RGHT),
        [1] = LAYOUT(
          KC_ESC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 									                              KC_TRNS, KC_LBRC, KC_RBRC, KC_MINS, KC_EQL, KC_DEL,
          KC_TRNS, KC_1, KC_2, KC_3, KC_4, KC_5, 									                             								KC_6, KC_7, KC_8, KC_9, KC_0, KC_GRV,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 									                           	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSLS, KC_TRNS,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 								        KC_MPLY, 							KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
        [2] = LAYOUT(
          KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, 								                                          KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 								                              KC_TRNS, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 									                            KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 								        KC_MPLY,							KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
        [3] = LAYOUT(
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 								                              KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 								                              KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_TRNS, KC_GRV,
          KC_TRNS, KC_TRNS, MACRO_0, MACRO_1, MACRO_2, MACRO_3, 									                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSLS, KC_TRNS,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 								        MACRO_4,							KC_ENT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case MACRO_0:
                SEND_STRING("hello world");
                return false;
            case MACRO_1:
                SEND_STRING(SS_DOWN(X_LCTL)SS_DOWN(X_LALT)SS_TAP(X_BSLS)SS_UP(X_LALT)SS_UP(X_LCTL));
                return false;
            case MACRO_2:
                SEND_STRING(SS_DOWN(X_LCTL)SS_TAP(X_B)SS_UP(X_LCTL));
                return false;
            case MACRO_3:
                SEND_STRING(SS_DOWN(X_LALT)SS_TAP(X_F7)SS_UP(X_LALT));
                return false;
            case MACRO_4:
                reset_keyboard();
                return false;
        }
    }

    return true;
};


// OLED and Encoder function is located in the ristretto.c File
