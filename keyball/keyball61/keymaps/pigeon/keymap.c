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
#define _BASE 0
#define _LOWER 1
#define _RAISE 2
#define _MOUSE 3
#define _SCROLL 4

// 長いキーをマクロに
#define SCRLTRG LT(_SCROLL,KC_LNG2)
#define NOSPACE _______
#define PREVTAB LCTL(KC_TAB)
#define NEXTTAB LCTL(LSFT(KC_TAB))

// キーコード定義
enum custom_keycodes {
  MAC = KEYBALL_SAFE_RANGE,
  WINDOWS,
  IMEON,
  IMEOFF,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // テンプレ
  // _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, 
  // _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, 
  // _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, 
  // _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
  // _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ 

  [_BASE] = LAYOUT_universal(
    KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                   KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_DEL ,
    KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                   KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC,
    KC_LCTL, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                   KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_ENT ,
    KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_RBRC, KC_LBRC, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
    SCRLTRG, KC_LALT, _______, KC_LGUI, KC_LALT, IMEOFF , KC_SPC , KC_RGUI, IMEON  , NOSPACE, NOSPACE, NOSPACE, _______, SCRLTRG
  ),

  [_LOWER] = LAYOUT_universal(
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, 
    _______, _______, KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                   KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , _______, 
    _______, KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 ,                   KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , _______, 
    _______, KC_F11 , KC_F12 , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [_RAISE] = LAYOUT_universal(
   KBC_SAVE, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______,                   KC_HOME, KC_PGDN, KC_PGUP,  KC_END, _______, _______, 
    _______,CPI_D100,SCRL_DVI,SCRL_DVD,CPI_I100, _______,                   KC_LEFT, KC_DOWN, KC_UP  ,KC_RIGHT, _______, _______, 
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_EQL , KC_BSLS, KC_LBRC, KC_RBRC, KC_GRV ,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ 
  ),

  [_MOUSE] = LAYOUT_universal(
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______,                   PREVTAB, KC_BTN1, KC_BTN2, NEXTTAB, _______, _______, 
    _______, _______, _______, _______, _______, _______, _______, _______, KC_BTN4, KC_BTN3, SCRLTRG, KC_BTN5, _______, _______, 
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ 
  ),

  [_SCROLL] = LAYOUT_universal(
        MAC, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, 
    WINDOWS, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ 
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
}
#endif

void pointing_device_init_user(void) {
    // set_auto_mouse_layer(<mouse_layer>); // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
    set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
}

// 引数に渡されたレイヤーをデフォルトのレイヤーとする
void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool ime_off_only = false;
bool ime_on_only = false;
bool isWindows = false;

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
        isWindows = false;
        //persistent_default_layer_set(1UL<<_MAC);
        SEND_STRING("Mac Mode");
      }
      return false;
      break;
    case WINDOWS:
      if (record->event.pressed) {
        isWindows = true;
        //persistent_default_layer_set(1UL<<_WINDOWS);
        SEND_STRING("Windows Mode");
      }
      return false;
      break;
    case IMEOFF:
      if (record->event.pressed) {
        ime_off_only = true;
        layer_on(_LOWER);
        // update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        // update_tri_layer(_LOWER, _RAISE, _ADJUST);
    
        if (ime_off_only) {
          if(isWindows){
            register_code(KC_INT5);
            unregister_code(KC_INT5);
          }else{
            register_code(KC_LNG2);
            unregister_code(KC_LNG2);
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
        // update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        // update_tri_layer(_LOWER, _RAISE, _ADJUST);
    
        if (ime_on_only) {
          if(isWindows){
            register_code(KC_INT4);
            unregister_code(KC_INT4);
          }else{
            register_code(KC_LNG1);
            unregister_code(KC_LNG1);
          }
        }
        ime_on_only = false;
      }
      return false;
      break;
    default:
      result = true;
      break;
  }

  return result;
}
