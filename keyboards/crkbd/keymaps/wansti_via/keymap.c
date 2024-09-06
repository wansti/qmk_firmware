/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

#define ANIM_LUNA

#ifdef OLED_ENABLE

enum layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
};

static void render_logo(void)
{
#ifdef LOGO1
  static const char PROGMEM logo[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xe0, 0xe0, 0xf0, 0xf0, 
	0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xe0, 0xf0, 0xc8, 0xe4, 0x92, 0x49, 0x24, 0x92, 0x48, 0x24, 0x10, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xfe, 0xff, 0xff, 0xff, 0x0f, 0x07, 0x43, 0x23, 0x91, 
	0x49, 0x25, 0x93, 0x49, 0x27, 0x93, 0x4f, 0x2f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x23, 0x9f, 0x7f, 0x7f, 0xff, 0xfc, 0xf8, 0xf0, 0xf1, 0xe0, 
	0xe2, 0xe1, 0xe4, 0xe2, 0xf1, 0xf0, 0xf8, 0xfc, 0xff, 0x7f, 0x3f, 0x1f, 0x03, 0x00, 0x00, 0x00, 
	0x08, 0x20, 0x02, 0x48, 0x00, 0x92, 0x00, 0x24, 0x00, 0x09, 0x00, 0x02, 0x01, 0x01, 0x03, 0x03, 
	0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
#else
  static const char PROGMEM logo[] = {0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xb8, 0xbc, 0xbc, 0xbe, 0xbe, 0xbe, 0xff, 0xff, 0xff, 0x07, 
	0x03, 0xf1, 0xfd, 0xf3, 0x06, 0x0e, 0xfe, 0xfc, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 
	0xf0, 0xfe, 0xff, 0xff, 0xff, 0xbb, 0xbb, 0x0b, 0x83, 0xa3, 0xb1, 0x31, 0x3b, 0x3f, 0xfb, 0x9a, 
	0x00, 0x1b, 0x83, 0xa1, 0xb8, 0xba, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xff, 0xff, 0xff, 0xfe, 0xf0, 
	0x0f, 0x7f, 0xff, 0xff, 0xff, 0xbb, 0xbb, 0xb8, 0xb1, 0xa3, 0x8a, 0x9a, 0x9b, 0x98, 0x83, 0x1b, 
	0x8f, 0xeb, 0xb8, 0xb1, 0x33, 0x03, 0x8b, 0xbb, 0xbb, 0xbb, 0xbb, 0xff, 0xff, 0xff, 0x7f, 0x0f, 
	0x00, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x3f, 0x7f, 0x78, 0x60, 0xc8, 0xdf, 0xdf, 0xc4, 
	0xf0, 0xff, 0xff, 0xff, 0x7a, 0x7b, 0x7b, 0x3b, 0x3b, 0x1b, 0x0b, 0x07, 0x03, 0x01, 0x00, 0x00};
#endif

  oled_set_cursor(0,0);
  oled_write_raw_P(logo, sizeof(logo));
}

static void print_logo_narrow(void) {
    render_logo();

    oled_set_cursor(0, 5);
    switch (get_highest_layer(layer_state)) {
    case _RAISE:
        oled_write_P(PSTR("RAISE"), false);
        oled_set_cursor(0, 7);
        oled_write_P(PSTR("     "), false);
        oled_set_cursor(0, 8);
        oled_write_P(PSTR("     "), false);
        break;
    case _LOWER:
        oled_write_P(PSTR("LOWER"), false);
        oled_set_cursor(0, 7);
        oled_write_P(PSTR("-=`[]"), false);
        oled_set_cursor(0, 8);
        oled_write_P(PSTR("_+~{}"), false);
        break;
    case _ADJUST:
        oled_write_P(PSTR("MEDIA"), false);
        oled_set_cursor(0, 7);
        oled_write_P(PSTR("     "), false);
        oled_set_cursor(0, 8);
        oled_write_P(PSTR("     "), false);
        break;
    default: //  for any other layers, or the default layer
        oled_write_P(PSTR("     "), false);
        oled_set_cursor(0, 7);
        oled_write_P(PSTR("     "), false);
        oled_set_cursor(0, 8);
        oled_write_P(PSTR("     "), false);
        break;
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_set_cursor(0, 10);
    oled_write_P(led_state.caps_lock ? PSTR(" CAPS") : PSTR("     "), false);
    oled_set_cursor(0, 11);
    oled_write_P(led_state.num_lock ? PSTR(" NUM") : PSTR("    "), false);
    oled_set_cursor(0, 12);
    oled_write_P(led_state.scroll_lock ? PSTR(" SCRL") : PSTR("     "), false);

    /* wpm counter */
    uint8_t n = get_current_wpm();
    char    wpm_str[4];
    oled_set_cursor(0, 14);
    wpm_str[3] = '\0';
    wpm_str[2] = '0' + n % 10;
    wpm_str[1] = '0' + (n /= 10) % 10;
    wpm_str[0] = '0' + n / 10;
    oled_write(wpm_str, false);

    oled_set_cursor(0, 15);
    oled_write(" WPM", false);
}

#if defined ANIM_MUSIC_BARS

#define ANIM_INVERT false
#define ANIM_RENDER_WPM true
#define FAST_TYPE_WPM 40

#include "music-bars.c"

#elif defined ANIM_LUNA

#include "luna.c"

#else

oled_rotation_t oled_init_user(oled_rotation_t rotation)
{
  if (is_keyboard_master()) { return OLED_ROTATION_270; }
  return rotation;
}

bool oled_task_user(void)
{
  if (is_keyboard_master()) { print_logo_narrow(); }
  return false;
}

#endif
#endif


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LGUI,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL, TL_LOWR,  KC_SPC,     KC_ENT, TL_UPPR, KC_RALT
                                      //`--------------------------'  `--------------------------'

  ),

  [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LGUI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MINS, KC_EQL,  KC_GRV,KC_LBRC, KC_RBRC, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_UNDS, KC_PLUS, KC_TILD, KC_LCBR, KC_RCBR, KC_PIPE,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_CAPS, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LGUI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_INS,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_P1, KC_PGDN, KC_PGUP, KC_END, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, KC_F1,  KC_F2,   KC_F3,   KC_F4,   KC_F5,                         KC_F6,  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F12,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  )
};
