#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

// layers
#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

// custom keycodes
#define UNO RGUI(KC_LSFT) // super + shift (i3wm)
#define DUE RGUI(KC_LALT) // super + alt (i3wm)
#define TMUX LCTL(KC_B) // tmux prefix ctrl + b

#define CAPSYM LT(SYMB, KC_CAPS) // caps lock or hold for symbols layer
#define H_SYM LT(SYMB, KC_H) // H or hold for symbol layer
#define SC_MED LT(MDIA, KC_SCLN) // semicolon or hold for media layer

#define OSHFT OSM(MOD_LSFT) // One shot key shift

#define Z_CTRL CTL_T(KC_Z) // Z or hold for ctrl
#define SL_CTL CTL_T(KC_SLSH) // / or hold for ctrl

#define B_ALTGR ALGR_T(KC_B) // b or hold for alt_gr

// MACROS
enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  IPDB
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Esc    |   1  |   2  |   3  |   4  |   5  |  L2  |           |  L1  |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  | DUE  |           | UNO  |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Caps/L1|   A  |   S  |   D  |   F  |   G  |------|           |------| H/L1 |   J  |   K  |   L  |; / L2|   '    |
 * |--------+------+------+------+------+------| CTRL |           | Meta |------+------+------+------+------+--------|
 * | LShift |Z/Ctrl|   X  |   C  |   V  |ALGR/B|  + B |           |      |   N  |   M  |   ,  |   .  |//Ctrl|   =    |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      | Alt  | Left | Right|                                       |  Up  | Down |   [  |   ]  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        |  +   |  -   |       | PrScr| Insert |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Del   |Enter |
 *                                 |      |ace   | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_ESC,   KC_1,     KC_2,      KC_3,     KC_4,     KC_5,     TG(MDIA),
        KC_TAB,   KC_Q,     KC_W,      KC_E,     KC_R,     KC_T,     DUE,
        CAPSYM,   KC_A,     KC_S,      KC_D,     KC_F,     KC_G,
        OSHFT,    Z_CTRL,   KC_X,      KC_C,     KC_V,     B_ALTGR,  TMUX,
        _______,  _______,  KC_LALT,   KC_LEFT,  KC_RGHT,
                                                           KC_PPLS,  KC_PMNS,
                                                                     KC_HOME,
                                                 KC_SPC,   KC_BSPC,  KC_END,
        // right hand
        TG(SYMB), KC_6,     KC_7,      KC_8,     KC_9,     KC_0,     KC_MINS,
        UNO,      KC_Y,     KC_U,      KC_I,     KC_O,     KC_P,     KC_BSLS,
                  H_SYM,    KC_J,      KC_K,     KC_L,     SC_MED,   KC_QUOT,
        KC_LGUI,  KC_N,     KC_M,      KC_COMM,  KC_DOT,   SL_CTL,   KC_EQL,
                            KC_UP,     KC_DOWN,  KC_LBRC,  KC_RBRC,  _______,
        KC_PSCR,  KC_INS,
        KC_PGUP,
        KC_PGDN,  KC_DELT,  KC_ENT
    ),
/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |Version  |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   {  |   }  |   |  | ipdb |           |      |   -  |   7  |   8  |   9  |   *  |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | xxxxxxx |   #  |   $  |   (  |   )  |   `  |------|           |------| xxxx |   4  |   5  |   6  |   +  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | EPRM  |      |      |      |      |                                       |   0  |   0  |   .  |   =  |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[SYMB] = LAYOUT_ergodox(
       // left hand
       VRSN,     KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    _______,
       _______,  KC_EXLM,  KC_AT,    KC_LCBR,  KC_RCBR,  KC_PIPE,  IPDB,
       _______,  KC_HASH,  KC_DLR,   KC_LPRN,  KC_RPRN,  KC_GRV,
       _______,  KC_PERC,  KC_CIRC,  KC_LBRC,  KC_RBRC,  KC_TILD,  _______,
          EPRM,  _______,  _______,  _______,  _______,
                                                         _______,  _______,
                                                                   _______,
                                               _______,  _______,  _______,
       // right hand
       _______,  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,
       _______,  KC_MINS,  KC_7,     KC_8,     KC_9,     KC_ASTR,  KC_F12,
                 _______,  KC_4,     KC_5,     KC_6,     KC_PLUS,  _______,
       _______,  KC_AMPR,  KC_1,     KC_2,     KC_3,     KC_BSLS,  _______,
                           KC_0,     KC_0,     KC_DOT,   KC_EQL,   _______,
       _______,  _______,
       _______,
       _______,  _______,  _______
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |  Up  |      |      | VolUp  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      | Left | Down | Right| xxxx | Mute   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      | VolDn  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Left |Right |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |  Up  |       |      |      |      |
 *                                 | Lclk | Rclk |------|       |------| Play | Next |
 *                                 |      |      | down |       | Prew |      |      |
 *                                 `--------------------'       `--------------------'
 */
[MDIA] = LAYOUT_ergodox(
       _______,  _______,  _______,  _______,  _______,  _______,  _______,
       _______,  _______,  _______,  KC_MS_U,  _______,  _______,  _______,
       _______,  _______,  KC_MS_L,  KC_MS_D,  KC_MS_R,  _______,
       _______,  _______,  _______,  _______,  _______,  _______,  _______,
       _______,  _______,  _______,  _______,  _______,
	                                                KC_MS_WH_LEFT, KC_MS_WH_RIGHT,
                                                                   KC_MS_WH_UP,
                                               KC_BTN1,  KC_BTN2,  KC_MS_WH_DOWN,
    // right hand
       _______,  _______,  _______,  _______,  _______,  _______,  _______,
       _______,  _______,  _______,  KC_UP,    _______,  _______,  KC_VOLU,
                 _______,  KC_LEFT,  KC_DOWN,  KC_RGHT,  _______,  KC_MUTE,
       _______,  _______,  _______,  _______,  _______,  _______,  KC_VOLD,
                           _______,  _______,  _______,  _______,  _______,
       _______,  _______,
       _______,
       KC_MPRV,  KC_MPLY,  KC_MNXT
),
/* Keymap X: Empty layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        |      |      |       |      |        |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 |      |      |------|       |------|        |      |
 *                                 |      |      |      |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */
/* [EMPTY] = LAYOUT_ergodox( */
/*        _______, _______, _______, _______, _______, _______, _______, */
/*        _______, _______, _______, _______, _______, _______, _______, */
/*        _______, _______, _______, _______, _______, _______, */
/*        _______, _______, _______, _______, _______, _______, _______, */
/*        _______, _______, _______, _______, _______, */
/*                                                     _______, _______, */
/*                                                              _______, */
/*                                            _______, _______, _______, */
/*     // right hand */
/*        _______,  _______, _______, _______, _______, _______, _______, */
/*        _______,  _______, _______, _______, _______, _______, _______, */
/*                  _______, _______, _______, _______, _______, _______, */
/*        _______,  _______, _______, _______, _______, _______, _______, */
/*                           _______, _______, _______, _______, _______, */
/*        _______, _______, */
/*        _______, */
/*        _______, _______, _______ */
/* ), */
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
    case 0:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      break;
    case 1:
      if (record->event.pressed) { // For resetting EEPROM
        eeconfig_init();
      }
      break;
  }
  return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case IPDB:
      if (record->event.pressed) {
        SEND_STRING ("import ipdb; ipdb.set_trace()" SS_TAP(X_TAB));
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

};

// Runs whenever there is a layer state change.
uint32_t layer_state_set_user(uint32_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = biton32(state);
  switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #else
          rgblight_init();
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      default:
        break;
    }

  return state;
};
