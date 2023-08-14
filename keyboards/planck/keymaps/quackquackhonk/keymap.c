/* Copyright 2015-2021 Jack Humbert
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
#include "muse.h"


enum custom_layers {
  _COLEMAK,
  _QWERTY,
  _GAMING,
  _GAMING_NUMBERS,
  _NUMSYM,
  _FUNCTIONS,
  _TOGGLES,
};


enum planck_keycodes {
  COLEMAK = SAFE_RANGE,
  QWERTY,
  PLOVER,
  BACKLIT,
  EXT_PLV
};

#define NUMSYM MO(_NUMSYM)
#define FUNCS MO(_FUNCTIONS)
#define TOGGLES MO(_TOGGLES)
#define MEDIA MO(_MEDIA)
#define CTLESC LCTL_T(KC_ESC)
#define GAMING MO(_GAMING)
#define GAMNUM MO(_GAMING_NUMBERS)

const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &delete_key_override,
    NULL // Null terminate the array of overrides!
};

// rotary encoder!
uint8_t mod_state;
bool encoder_update_user(uint8_t index, bool clockwise) {
    mod_state = get_mods();
    // if hyper then brightness
    if (mod_state & MOD_MASK_CTRL) {
        if (clockwise) {
            tap_code(KC_TAB);
        } else {
            add_mods(MOD_MASK_SHIFT);
            tap_code(KC_TAB);
            set_mods(mod_state);
        }
    }
    else if (mod_state & MOD_MASK_ALT) {
      if (clockwise) {
        tap_code(KC_BRIU);
      } else {
        tap_code(KC_BRID);
      }
    }
    else if (mod_state & MOD_MASK_GUI) {
        if (clockwise) {
            add_mods(MOD_MASK_SHIFT);
            tap_code(KC_RIGHT);
            set_mods(mod_state);
        } else {
            add_mods(MOD_MASK_SHIFT);
            tap_code(KC_LEFT);
            set_mods(mod_state);
        }
    }
    else {
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    }
    return false;
}

// leader key definitions!
void leader_end_user(void) {
  // TEXT INPUTS (i)
  if (leader_sequence_two_keys(KC_I, KC_E)) {
    send_string("sahanatankala@gmail.com");
  }
  if (leader_sequence_three_keys(KC_I, KC_W, KC_E)) {
    send_string("i34866@verisk.com");
  }
  if (leader_sequence_three_keys(KC_I, KC_W, KC_N)) {
    send_string("i34866");
  }
  if (leader_sequence_two_keys(KC_I, KC_G)) {
    send_string("quackquackhonk");
  }
  if (leader_sequence_three_keys(KC_I, KC_S, KC_E)) {
    send_string("tankala.v@northeastern.edu");
  }
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
      // Keycodes that continue Caps Word, with shift applied.
      case KC_A ... KC_Z:
          add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
          return true;
      case KC_LSFT:
        send_char('_');
        return true;
      case KC_1 ... KC_0:
      case KC_BSPC:
      case KC_DEL:
      case KC_MINS:
      case KC_UNDS:
          return true;
      default:
          return false;  // Deactivate Caps Word.
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


    /* COLEMAK
    * ,-----------------------------------------------------------------------------------.
    * |  Tab |  Q   |  W   |  F   |  P   |  G   |  J   |  L   |  U   |  Y   |  ;   | Bksp |
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * | Esc/C|  A   |  R   |  S   |  T   |  D   |  H   |  N   |  E   |  I   |  O   |  '   |
    * |------+------+------+------+------+------|------+------+------+------+------+------|
    * | Tab  |  Z   |  X   |  C   |  V   |  B   |  K   |  M   |  ,   |  .   |  /   | Entr |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Lead | LCtl | LGUI | LAlt |  Num | LShft| Space| Func | RAlt | RGUI | Hypr |Toggle|
    * `-----------------------------------------------------------------------------------'
    */
    [_COLEMAK] = LAYOUT_planck_grid(KC_MPLY , KC_Q   , KC_W   , KC_F   , KC_P    , KC_B   , KC_J   , KC_L , KC_U   , KC_Y   , KC_SCLN, KC_BSPC,
                                    CTLESC  , KC_A   , KC_R   , KC_S   , KC_T    , KC_G   , KC_M   , KC_N , KC_E   , KC_I   , KC_O   , KC_QUOT,
                                    KC_TAB  , KC_X   , KC_C   , KC_D   , KC_V    , KC_Z   , KC_K   , KC_H , KC_COMM, KC_DOT , KC_SLSH, KC_ENTER,
                                    QK_LEAD, KC_LCTL, KC_LGUI, KC_LALT, NUMSYM, KC_LSFT , KC_SPC, FUNCS, KC_RALT, KC_MEH , KC_HYPR, TOGGLES),

    /* QWERTY
    * ,-----------------------------------------------------------------------------------.
    * | Mute |  Q   |  W   |  E   |  R   |  T   |  Y   |  U   |  I   |  O   |  P   | Bksp |
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * | Esc/C|  A   |  S   |  D   |  F   |  G   |  H   |  J   |  K   |  L   |  ;   |  '   |
    * |------+------+------+------+------+------|------+------+------+------+------+------|
    * | Tab  |  Z   |  X   |  C   |  V   |  B   |  N   |  M   |  ,   |  .   |  /   | Enter|
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Med  | Ctrl | LGUI | Alt  |  Num |    Space    | Func | Alt  | RGUI | Ctrl |Toggle|
    * `-----------------------------------------------------------------------------------'
    */
    [_QWERTY] = LAYOUT_planck_grid(KC_MPLY, KC_Q   , KC_W   , KC_E   , KC_R    , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC,
                                  CTLESC  , KC_A   , KC_S   , KC_D   , KC_F    , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
                                  KC_TAB  , KC_Z   , KC_X   , KC_C   , KC_V    , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_ENTER,
                                  QK_LEAD , KC_LCTL, KC_LGUI, KC_LALT, NUMSYM, KC_LSFT  , KC_SPC , FUNCS  , KC_RALT, KC_MEH , KC_HYPR, TOGGLES),

    /* GAMING
    * ,-----------------------------------------------------------------------------------.
    * | Mute |  Q   |  W   |  E   |  R   |  T   |  Y   |  U   |  I   |  O   |  p   | Bksp |
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * | Esc  |  A   |  S   |  D   |  F   |  G   |  H   |  J   |  K   |  L   |  ;   |  '   |
    * |------+------+------+------+------+------|------+------+------+------+------+------|
    * | Tab  |  Z   |  X   |  C   |  V   |  B   |  N   |  M   |  ,   |  .   |  /   | Entr |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Func | LCtl | LAlt | LShft| Space|GamNum| Func |      |      |      |      |Toggle|
    * `-----------------------------------------------------------------------------------'
    */
    [_GAMING] = LAYOUT_planck_grid(KC_MPLY , KC_Q   , KC_W   , KC_E   , KC_R    , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC,
                                   CTLESC  , KC_A   , KC_S   , KC_D   , KC_F    , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
                                   KC_TAB  , KC_Z   , KC_X   , KC_C   , KC_V    , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_ENTER,
                                   FUNCS   , KC_GRV , KC_F13 , KC_LALT, GAMNUM  , KC_SPC , KC_LSFT,XXXXXXX, XXXXXXX, XXXXXXX, QK_LEAD, TOGGLES),

    /* Gaming Numbers
    * ,-----------------------------------------------------------------------------------.
    * |      |      |      |      |      |      |      |      |      |      |      |      |
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * |  1   |  2   |  3   |  4   |  5   |      |      |      |      |      |      |      |
    * |------+------+------+------+------+------|------+------+------+------+------+------|
    * |  6   |  7   |  8   |  9   |  0   |      |      |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             |      |      |      |      |      |
    * `-----------------------------------------------------------------------------------'
    */
    [_GAMING_NUMBERS] = LAYOUT_planck_grid(KC_F14 , KC_F15 , KC_F16 , KC_F17 , KC_F18 , KC_F19 , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                           KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                           KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),

    /* Functions
    * ,-----------------------------------------------------------------------------------.
    * |      |  F1  |  F2  |  F3  |  F4  | PrtSc| Home | PgDn | PgUp | End  |      |      |
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * |      |  F5  |  F6  |  F7  |  F8  |Insert| Left | Down |  Up  | Right|MisCtl|      |
    * |------+------+------+------+------+------|------+------+------+------+------+------|
    * |CapsW |  F9  |  F10 |  F11 |  F12 |  F13 |  F14 | F15  | F16  | F17  |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             |      |      |      |      |      |
    * `-----------------------------------------------------------------------------------'
    */
    [_FUNCTIONS] = LAYOUT_planck_grid(_______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_PSCR, KC_HOME, KC_PGDN, KC_PGUP, KC_END , XXXXXXX, _______,
                                      _______, KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_INS , KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_MCTL, _______,
                                      CW_TOGG, KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_F13 , KC_F14 , KC_F15 , KC_F16 , KC_F17 , XXXXXXX, _______,
                                      XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX),
    /* Numbers
    * ,-----------------------------------------------------------------------------------.
    * |      |  !   |  @   |  #   |  $   |  [   |  ]   |  1   |  2   |  3   |  =   |      |
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * |  ~   |  %   |  ^   |  &   |  _   |  (   |  )   |  4   |  5   |  6   |  *   |  /   |
    * |------+------+------+------+------+------|------+------+------+------+------+------|
    * |  `   |      | \    |  |   |      |  {   |  }   |  7   |  8   |  9   |  -   |  +   |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |    Space    |  0   |  .   |  ,   |      |      |
    * `-----------------------------------------------------------------------------------'
    */
    [_NUMSYM] = LAYOUT_planck_grid(XXXXXXX, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_LBRC, KC_RBRC, KC_1   , KC_2   , KC_3   , KC_EQL , _______,
                                   KC_TILD, KC_PERC, KC_CIRC, KC_AMPR, KC_UNDS, KC_LPRN, KC_RPRN, KC_4   , KC_5   , KC_6   , KC_ASTR, KC_SLSH,
                                   KC_GRV , XXXXXXX, KC_BSLS, KC_PIPE, XXXXXXX, KC_LCBR, KC_RCBR, KC_7   , KC_8   , KC_9   , KC_MINS, KC_PLUS,
                                   _______, _______, _______, _______, _______, _______, _______, KC_0   , KC_DOT , KC_COMM, _______, _______),

    /* Toggles
    * ,-----------------------------------------------------------------------------------.
    * |      | Qwer | Cole |Gaming|      |      |      |      |      |      |      |      |
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * | Caps |      |      |      |      |      | MAC  |      |      |      |      |      |
    * |------+------+------+------+------+------|------+------+------+------+------+------|
    * |      |      |      |      |      |      |      |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             |      |      |      |      |      |
    * `-----------------------------------------------------------------------------------'
    */
    [_TOGGLES] = LAYOUT_planck_grid(XXXXXXX, DF(_QWERTY), DF(_COLEMAK), DF(_GAMING), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                    KC_CAPS, XXXXXXX    , XXXXXXX,      XXXXXXX    , XXXXXXX, XXXXXXX, CG_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                    XXXXXXX, XXXXXXX    , XXXXXXX,      XXXXXXX    , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                    XXXXXXX, XXXXXXX    , XXXXXXX,      XXXXXXX    , _______, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),
};

