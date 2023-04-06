/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"

// レイヤー定義
#define _MAC 0
#define _WINDOWS 1
#define _LOWER 2
#define _RAISE 3
#define _ADJUST 4
#define _MOUSE 5
#define _SCROLL 6

// 長いキーをマクロに
#define SCRLTRG LT(_SCROLL,KC_BTN3)
#define NOSPACE _______
#define DELETED _______
#define NEXTTAB LCTL(KC_TAB)
#define PREVTAB LCTL(LSFT(KC_TAB))
#define NEXTXLS LCTL(KC_PGDN)
#define PREVXLS LCTL(KC_PGUP)

// キーコード定義
enum custom_keycodes {
  MAC = KEYBALL_SAFE_RANGE,
  WINDOWS,
  IMEON,
  IMEOFF,
  TGL_JIS
};

bool ime_off_only = false;
bool ime_on_only = false;
bool jis_mode = false;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // テンプレ
  // _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, 
  // _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, 
  // _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
  //                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______


  [_MAC] = LAYOUT_universal(
    KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                   KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC,
    KC_LCTL, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                   KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_ENT ,
    KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                   KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_QUOT,
                      DELETED, DELETED, KC_LALT, IMEOFF , KC_SPC , KC_RGUI, IMEON  , NOSPACE, NOSPACE, KC_DOT
  ),

  [_WINDOWS] = LAYOUT_universal(
    KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                   KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC,
    KC_LCTL, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                   KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_ENT ,
    KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                   KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_QUOT,
                      DELETED, DELETED, KC_LGUI, IMEOFF , KC_SPC , KC_RALT, IMEON  , NOSPACE, NOSPACE, DELETED
  ),

  [_LOWER] = LAYOUT_universal(
    KC_ESC , _______, KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                   KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_DEL , 
    _______, KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 ,                   KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , _______, 
    _______, KC_F11 , KC_F12 , _______, _______, _______,                   KC_MINS, KC_EQL , KC_LBRC, KC_RBRC, KC_BSLS, KC_GRV ,
                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [_RAISE] = LAYOUT_universal(
    KC_ESC , _______, _______, _______, _______, _______,                   KC_HOME, KC_PGDN, KC_PGUP,  KC_END, _______, KC_DEL , 
    _______,CPI_D100,SCRL_DVI,SCRL_DVD,CPI_I100, _______,                   KC_LEFT, KC_DOWN, KC_UP  ,KC_RIGHT, _______, _______, 
    _______, _______, _______, _______, _______, _______,                   KC_MINS, KC_EQL , KC_LBRC, KC_RBRC, KC_BSLS, KC_GRV ,
                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [_ADJUST] = LAYOUT_universal(
    _______, _______, WINDOWS, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______,                   _______, TGL_JIS, _______, _______, _______, _______, 
   KBC_SAVE, _______, _______, _______, _______, _______,                   _______,     MAC, _______, _______, _______, _______, 
                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
  [_MOUSE] = LAYOUT_universal(
    _______, _______, _______, _______, _______, _______,                   _______, PREVXLS, NEXTXLS, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______,                   PREVTAB, KC_BTN1, KC_BTN2, NEXTTAB, _______, _______, 
    _______, _______, _______, _______, _______, _______,                   KC_BTN4, KC_BTN3, SCRLTRG, KC_BTN5, _______, _______, 
                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [_SCROLL] = LAYOUT_universal(
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, 
                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3

    // keyball_set_scroll_mode(get_highest_layer(state) == 3);

    switch(get_highest_layer(remove_auto_mouse_layer(state, true))) {
        case _SCROLL:
            // Auto enable scroll mode when the highest layer is 3
            state = remove_auto_mouse_layer(state, false);
            set_auto_mouse_enable(false);
            keyball_set_scroll_mode(true);
            break;
        default:
            set_auto_mouse_enable(true);
            keyball_set_scroll_mode(false);
            break;
    }

    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    
    oled_write_P(PSTR("Layer:"), false);
    oled_write(get_u8_str(get_highest_layer(layer_state), ' '), false);

    if(get_highest_layer(default_layer_state) == _WINDOWS){
      oled_write_P(PSTR("   Mode: Win"), false);
    }else{
      oled_write_P(PSTR("   Mode: Mac"), false);
    }
}
#endif

/* Copyright 2018-2020 eswai <@eswai>
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

/*
  OSで日本語キーボード(logical bit pairing)と設定/認識されているキーボードで、
  USキーキャップの文字、記号(typewriter pairing)を正しく出力する。
  例: Shift + 2 で @ を入力する
  変換された文字はキーリピートが無効です。
*/

// #include QMK_KEYBOARD_H
#include "keymap_japanese.h"

const uint16_t us2jis[][2] = {
  {KC_LPRN, JP_LPRN},
  {KC_RPRN, JP_RPRN},
  {KC_AT,   JP_AT},
  {KC_LBRC, JP_LBRC},
  {KC_RBRC, JP_RBRC},
  {KC_LCBR, JP_LCBR},
  {KC_RCBR, JP_RCBR},
  {KC_MINS, JP_MINS},
  {KC_EQL,  JP_EQL},
  {KC_BSLS, JP_BSLS},
  {KC_SCLN, JP_SCLN},
  {KC_QUOT, JP_QUOT},
  {KC_GRV,  JP_GRV},
  {KC_PLUS, JP_PLUS},
  {KC_COLN, JP_COLN},
  {KC_UNDS, JP_UNDS},
  {KC_PIPE, JP_PIPE},
  {KC_DQT,  JP_DQUO},
  {KC_ASTR, JP_ASTR},
  {KC_TILD, JP_TILD},
  {KC_AMPR, JP_AMPR},
  {KC_CIRC, JP_CIRC},
};

bool twpair_on_jis(uint16_t keycode, keyrecord_t *record) {
  if (!record->event.pressed) return true;

  uint16_t skeycode; // シフトビットを反映したキーコード
  bool lshifted = keyboard_report->mods & MOD_BIT(KC_LSFT); // シフトキーの状態
  bool rshifted = keyboard_report->mods & MOD_BIT(KC_RSFT);
  bool shifted = lshifted | rshifted;

  if (shifted) {
    skeycode = QK_LSFT | keycode;
  } else {
    skeycode = keycode;
  }

  for (int i = 0; i < sizeof(us2jis) / sizeof(us2jis[0]); i++) {
    if (us2jis[i][0] == skeycode) {
      unregister_code(KC_LSFT);
      unregister_code(KC_RSFT);
      if ((us2jis[i][1] & QK_LSFT) == QK_LSFT || (us2jis[i][1] & QK_RSFT) == QK_RSFT) {
        register_code(KC_LSFT);
        tap_code(us2jis[i][1]);
        unregister_code(KC_LSFT);
      } else {
        tap_code(us2jis[i][1]);
      }
      if (lshifted) register_code(KC_LSFT);
      if (rshifted) register_code(KC_RSFT);
      return false;
    }
  }

  return true;
}

void pointing_device_init_user(void) {
    // set_auto_mouse_layer(<mouse_layer>); // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
    set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool result = false;
  // IMEキーの単押し判定用Switch
  switch (keycode) {
    case IMEOFF:
      ime_on_only = false;
      break;
    case IMEON:
      ime_off_only = false;
      break;
    default:
      ime_off_only = false;
      ime_on_only = false;
      break;
  }
  switch (keycode) {
    case MAC:
      if (record->event.pressed) {
        default_layer_set(1UL<<_MAC);
      }
      return false;
      break;
    case WINDOWS:
      if (record->event.pressed) {
        default_layer_set(1UL<<_WINDOWS);
      }
      return false;
      break;
    case IMEOFF:
      if (record->event.pressed) {
        ime_off_only = true;
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
    
        if (ime_off_only) {
          switch (get_highest_layer(default_layer_state)) {
            case _WINDOWS:
              tap_code(KC_INT5);
              break;
            case _MAC: 
              tap_code(KC_LNG2);
              break;
            default:
              break;
          }
        }
        ime_off_only = false;
      }
      return false;
      break;
    case IMEON:
      if (record->event.pressed) {
        ime_on_only = true;
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
    
        if (ime_on_only) {
          switch (get_highest_layer(default_layer_state)) {
            case _WINDOWS:
              tap_code(KC_INT4);
              break;
            case _MAC: 
              tap_code(KC_LNG1);
              break;
            default:
              break;
          }
        }
        ime_on_only = false;
      }
      return false;
      break;
    case TGL_JIS:
      if (record->event.pressed) {
        jis_mode = !jis_mode;
      }

      return false;
      break;
    default:
      if(jis_mode){
        result = twpair_on_jis(keycode, record);
      }else{
        result = true;
      }
      break;
  }

  return result;
}
