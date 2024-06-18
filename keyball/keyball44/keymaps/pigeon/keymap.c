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
#define _WINDOWS 0
#define _MAC 1
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

// Keyboard Quantizer B用キー設定
// 左側のキーをRemap上で右側のキーとして配置する
#define AD_WO_L KC_F14
#define ADV_ID0 KC_F15
#define ADV_ID1 KC_F16
#define ADV_ID2 KC_F17
#define ADV_ID3 KC_F18
#define ADV_ID4 KC_F19
#define ADV_ID5 KC_F20
#define ADV_ID6 KC_F21
#define ADV_ID7 KC_F22
#define SEL_BLE KC_F23
#define SEL_USB KC_F24
#define DEL_ID0 KC_KP_0
#define DEL_ID1 KC_KP_1
#define DEL_ID2 KC_KP_2
#define DEL_ID3 KC_KP_3
#define DEL_ID4 KC_KP_4
#define DEL_ID5 KC_KP_5
#define DEL_ID6 KC_KP_6
#define DEL_ID7 KC_KP_7

#define M_TEAMS_REPEAT 10000

// キーコード定義
enum custom_keycodes {
	WINDOWS = KEYBALL_SAFE_RANGE,
	MAC,
	IMEON,
	IMEOFF,
	TGL_JIS,
	M_TEAMS,
	TGL_MS
};

bool imeOffOnly = false;
bool imeOnOnly = false;
bool isJisMode = true;

bool isRecording = false;
bool isTeamsOn = false;
bool isMouseOnly = false;
int teamsDelay = 0;
int pairingId = -1;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	// テンプレ
	// _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, 
	// _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, 
	// _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
	//                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______

	[_WINDOWS] = LAYOUT_universal(
		KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                   KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC,
		KC_LCTL, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                   KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_ENT ,
		KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                   KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_QUOT,
											DM_PLY1, KC_LGUI, KC_LALT, IMEOFF , KC_SPC , KC_RGUI, IMEON  , NOSPACE, NOSPACE, DELETED
	),

	[_MAC] = LAYOUT_universal(
		KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                   KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC,
		KC_LCTL, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                   KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_ENT ,
		KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                   KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_QUOT,
											DM_PLY1, KC_LALT, KC_LGUI, IMEOFF , KC_SPC , KC_RCTL, IMEON  , NOSPACE, NOSPACE, DELETED
	),

	[_LOWER] = LAYOUT_universal(
		KC_ESC , _______, KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                   KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_DEL , 
		_______, KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 ,                   KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , _______, 
		_______, KC_F11 , KC_F12 , _______, _______, _______,                   KC_MINS, KC_EQL , KC_LBRC, KC_RBRC, KC_BSLS, KC_GRV ,
											_______, _______, _______, _______, _______, _______, _______, _______, _______, TGL_MS
	),

	[_RAISE] = LAYOUT_universal(
		KC_ESC , _______, _______, _______, _______, _______,                   KC_HOME, PREVXLS, NEXTXLS,  KC_END, _______, KC_DEL , 
		_______,CPI_D100,SCRL_DVI,SCRL_DVD,CPI_I100,KBC_SAVE,                   KC_LEFT, KC_DOWN, KC_UP  ,KC_RIGHT, _______, _______, 
		_______, _______, _______, _______, _______, _______,                   KC_MINS, KC_EQL , KC_LBRC, KC_RBRC, KC_BSLS, KC_GRV ,
											DM_REC1, _______, _______, _______, _______, _______, _______, _______, _______, _______
	),

	[_ADJUST] = LAYOUT_universal(
		_______, _______, WINDOWS, _______, _______, _______,                   _______, SEL_USB, ADV_ID0, ADV_ID1, ADV_ID2, ADV_ID3, 
		_______, AD_WO_L, _______, _______, _______, _______,                   _______, TGL_JIS, ADV_ID4, ADV_ID5, ADV_ID6, ADV_ID7, 
		M_TEAMS, _______, _______, _______, _______, SEL_BLE,                   _______,     MAC, _______, _______, _______, _______, 
											_______, _______, _______, _______, _______, _______, _______, _______, _______, _______
	),
	[_MOUSE] = LAYOUT_universal(
		_______, _______, _______, _______, _______, _______,                   _______, PREVXLS, NEXTXLS, _______, _______, _______, 
		_______, _______, _______, _______, _______, _______,                   PREVTAB, KC_BTN1, KC_BTN2, NEXTTAB, _______, _______, 
		_______, _______, _______, _______, _______, _______,                   _______, KC_BTN3, SCRLTRG, _______, _______, _______, 
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
			if(isMouseOnly){
				keyball_set_scroll_mode(false);
				break;
			}
			set_auto_mouse_enable(true);
			keyball_set_scroll_mode(false);
			break;
	}

	return state;
}

#ifdef OLED_ENABLE

#include "lib/oledkit/oledkit.h"

static const char *format_4d(int8_t d) {
    static char buf[5] = {0}; // max width (4) + NUL (1)
    char        lead   = ' ';
    if (d < 0) {
        d    = -d;
        lead = '-';
    }
    buf[3] = (d % 10) + '0';
    d /= 10;
    if (d == 0) {
        buf[2] = lead;
        lead   = ' ';
    } else {
        buf[2] = (d % 10) + '0';
        d /= 10;
    }
    if (d == 0) {
        buf[1] = lead;
        lead   = ' ';
    } else {
        buf[1] = (d % 10) + '0';
        d /= 10;
    }
    buf[0] = lead;
    return buf;
}

void oledkit_render_info_user(void) {
	// keyball_oled_render_keyinfo();
	// keyball_oled_render_ballinfo();

    oled_write_P(PSTR("CPI:"), false);
    oled_write(format_4d(keyball_get_cpi()) + 1, false);
    oled_write_P(PSTR("00 "), false);

	switch(pairingId){
		case 0:
			oled_write_P(PSTR("BT0:Macbook"), false);
			break;

		case 1:
			oled_write_P(PSTR("BT1:iPadOld"), false);
			break;

		case 2:
			oled_write_P(PSTR("BT2:PC-K   "), false);
			break;

		case 3:
			oled_write_P(PSTR("BT3:iPhone "), false);
			break;

		case 4:
			oled_write_P(PSTR("BT4:iPad   "), false);
			break;

		case 5:
			oled_write_P(PSTR("BT5:Fold   "), false);
			break;

		case 6:
			oled_write_P(PSTR("BT6:WinPC  "), false);
			break;

		case 7:
			oled_write_P(PSTR("BT7:-      "), false);
			break;

		default:
		    oled_write_P(PSTR("USB:       "), false);
			break;
	}

	oled_write_P(PSTR("Layer:"), false);
	switch (get_highest_layer(layer_state | default_layer_state)) {
		case _MAC:
			oled_write_P(PSTR("Mac   "), false);
			break;
		case _WINDOWS:
			oled_write_P(PSTR("Win   "), false);
			break;
		case _LOWER:
			oled_write_P(PSTR("Lower "), false);
			break;
		case _RAISE:
			oled_write_P(PSTR("Raise "), false);
			break;
		case _ADJUST:
			oled_write_P(PSTR("Adjust"), false);
			break;
		case _MOUSE:
			oled_write_P(PSTR("Mouse "), false);
			break;
		case _SCROLL:
			oled_write_P(PSTR("Scroll"), false);
			break;
		default:
			oled_write_P(PSTR("Undef "), false);
			break;
	}

	oled_write_P(PSTR(" :"), false);

	if(isJisMode){
		oled_write_P(PSTR("JIS"), false);
	}else{
		oled_write_P(PSTR(" US"), false);
	}

	if(isRecording){
		oled_write_P(PSTR(" REC"), false);
	}else{
		oled_write_P(PSTR("    "), false);
	}

	if(isTeamsOn){
		oled_write_P(PSTR("--- ANTI SLEEP:ON ---"), false);
	}else{
		oled_write_P(PSTR("                     "), false);
	}
}
#endif

// マクロの記録を開始する時に起動されます。
void dynamic_macro_record_start_user(void){
	isRecording = true;
}

// マクロの記録を停止した時に起動されます。
void dynamic_macro_record_end_user(int8_t direction){
	isRecording = false;
}

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

//-------------------------------------------------------------
//
//  matrix_scan_user関数の中でフラグをチェックして必要なマクロを実行する。
//  この関数はQMKががキーの押下をチェックするたび実行される。
//

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
	if (isTeamsOn) {
		if (teamsDelay >= M_TEAMS_REPEAT) {
			// SEND_STRING("MCR");
			send_string_with_delay("MCR\b\b\b", 200);
			teamsDelay = 0;
		}
		// カウンタをカウントアップ
		teamsDelay++;
	}
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	bool result = false;
	// IMEキーの単押し判定用Switch
	switch (keycode) {
		case IMEOFF:
			imeOnOnly = false;
			break;
		case IMEON:
			imeOffOnly = false;
			break;
		default:
			imeOffOnly = false;
			imeOnOnly = false;
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
				imeOffOnly = true;
				layer_on(_LOWER);
				auto_mouse_layer_off();
				update_tri_layer(_LOWER, _RAISE, _ADJUST);
			} else {
				layer_off(_LOWER);
				auto_mouse_layer_off();
				update_tri_layer(_LOWER, _RAISE, _ADJUST);
		
				if (imeOffOnly) {
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
				imeOffOnly = false;
			}
			return false;
			break;

		case IMEON:
			if (record->event.pressed) {
				imeOnOnly = true;
				layer_on(_RAISE);
				auto_mouse_layer_off();
				update_tri_layer(_LOWER, _RAISE, _ADJUST);
			} else {
				layer_off(_RAISE);
				auto_mouse_layer_off();
				update_tri_layer(_LOWER, _RAISE, _ADJUST);
		
				if (imeOnOnly) {
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
				imeOnOnly = false;
			}
			return false;
			break;

		case TGL_JIS:
			if (record->event.pressed) {
				isJisMode = !isJisMode;
			}

			return false;
			break;
		case M_TEAMS:
			if (record->event.pressed) {
				isTeamsOn = !isTeamsOn;
				teamsDelay = 0;
			}

			return false;
			break;
		
		case TGL_MS:
			if (record->event.pressed) {
				if(isMouseOnly){
					isMouseOnly = false;
					set_auto_mouse_enable(true);
				}else{
					isMouseOnly = true;
					set_auto_mouse_enable(false);
					layer_on(_MOUSE);
				}
			}
			return false;

			break;

		case AD_WO_L:
			return true;

		case ADV_ID0:
			pairingId = 0;
			return true;

		case ADV_ID1:
			pairingId = 1;
			return true;

		case ADV_ID2:
			pairingId = 2;
			return true;

		case ADV_ID3:
			pairingId = 3;
			return true;

		case ADV_ID4:
			pairingId = 4;
			return true;

		case ADV_ID5:
			pairingId = 5;
			return true;

		case ADV_ID6:
			pairingId = 6;
			return true;

		case ADV_ID7:
			pairingId = 7;
			return true;

		case SEL_BLE:
			return true;

		case SEL_USB:
			pairingId = -1;
			return true;

		default:
			if(isJisMode){
				result = twpair_on_jis(keycode, record);
			}else{
				result = true;
			}
			break;
	}

	return result;
}
