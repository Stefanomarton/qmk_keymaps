// Copyright 2023 Jason Hazel (@jasonhazel)
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H

enum custom_keycodes {
    DRAG_SCROLL = SAFE_RANGE,
};

bool set_scrolling = false;

// Modify these values to adjust the scrolling speed
#define SCROLL_DIVISOR_H 4.0
#define SCROLL_DIVISOR_V 4.0

// Variables to store accumulated scroll values
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

// Function to handle mouse reports and perform drag scrolling
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    // Check if drag scrolling is active
    if (set_scrolling) {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        scroll_accumulated_h += (float)mouse_report.x / SCROLL_DIVISOR_H;
        scroll_accumulated_v += (float)mouse_report.y / SCROLL_DIVISOR_V;

        // Assign integer parts of accumulated scroll values to the mouse report
        mouse_report.h = (int8_t)scroll_accumulated_h;
        mouse_report.v = (int8_t)scroll_accumulated_v;

        // Update accumulated scroll values by subtracting the integer parts
        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        // Clear the X and Y values of the mouse report
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}

// Function to handle key events and enable/disable drag scrolling
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DRAG_SCROLL:
            // Toggle set_scrolling when DRAG_SCROLL key is pressed or released
            set_scrolling = record->event.pressed;
            break;
        default:
            break;
    }
    return true;
}

// Function to handle layer changes and disable drag scrolling when not in AUTO_MOUSE_DEFAULT_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    // Disable set_scrolling if the current layer is not the AUTO_MOUSE_DEFAULT_LAYER
    if (get_highest_layer(state) != AUTO_MOUSE_DEFAULT_LAYER) {
        set_scrolling = false;
    }
    return state;
}

enum layers {
  _ALPHA,
  _SYMBOL,
  _SYMBOL2,
  _NUMBER,
  _NAVIGATION,
  LAYER_LENGTH
};


enum tapdances {
  TD_QESC,
  TD_SBKT,
  TD_CBKT,
  TD_PARN,
  TD_LTGT,
  /* TD_ATAB, */
  TAPDANCE_LENGTH
};

enum combos {
  /* COMBO_NAVIGATION, */
  /* COMBO_LENGTH, */
  JK,
  KL,
  GF,
  FD,
  ALT,
  CAPS,
  CHWS
};

// begin tapdances
#define KC_QESC     TD(TD_QESC)
#define KC_SBKT     TD(TD_SBKT)
#define KC_CBKT     TD(TD_CBKT)
#define KC_PARN     TD(TD_PARN)
#define KC_LTGT     TD(TD_LTGT)
/* #define KC_ATAB     TD(TD_ATAB) */

#define KC_GUIM     LGUI_T(KC_M)
#define KC_GUIV     LGUI_T(KC_V)

#define KC_ALTS     LALT_T(KC_S)
#define KC_ALTL     LALT_T(KC_L)

#define KC_CTLD     LCTL_T(KC_D)
#define KC_CTLK     RCTL_T(KC_K)

#define KC_SFTQ     LSFT_T(KC_QUOTE)
#define KC_SFTZ     LSFT_T(KC_Z)

#define KC_SENT     LSFT_T(KC_ENT)
#define KC_SDEL     LSFT_T(KC_DEL)

// oneshots
#define KC_OSFT   OSM(MOD_LSFT)
#define KC_OALT   OSM(MOD_LALT)

// layer changing
#define KC_ONUM   LT(_NUMBER, KC_BSPC)
#define KC_OSYM   LT(_SYMBOL, KC_TAB)
#define KC_OSYM2  LT(_SYMBOL2, KC_ESC)

// cleaner keys
#define KC_PLS S(KC_EQL)

/* uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) { */
/*     switch(keycode) { */
/*         case KC_GUIX: */
/*         case KC_ALTC: */
/*             return TAPPING_TERM * 2; */
/*         default: */
/*             return TAPPING_TERM; */
/*     } */
/* } */

const uint16_t PROGMEM jk_combo[] = {KC_J, RCTL_T(KC_K), COMBO_END};
const uint16_t PROGMEM kl_combo[] = {RCTL_T(KC_K), LALT_T(KC_L), COMBO_END};
/* const uint16_t PROGMEM alt_combo[] = {KC_OSYM, KC_ONUM, COMBO_END}; */
const uint16_t PROGMEM gf_combo[] = {KC_G, LGUI_T(KC_F), COMBO_END};
const uint16_t PROGMEM fd_combo[] = {LGUI_T(KC_F), LCTL_T(KC_D), COMBO_END};
const uint16_t PROGMEM caps_combo[] = {LT(3,KC_ESC), LT(1,KC_BSPC), COMBO_END};
const uint16_t PROGMEM chws_combo[] = {LT(3,KC_ESC), LT(4,KC_SPC), COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [KL] = COMBO(kl_combo, KC_SCLN),
  [JK] = COMBO(jk_combo, KC_COLN),
  [GF] = COMBO(gf_combo, KC_CIRC),
  [FD] = COMBO(fd_combo, S(KC_MINS)),
  [CAPS] = COMBO(caps_combo, CW_TOGG),
  [CHWS] = COMBO(chws_combo, OSL(3)),
};

/* uint16_t get_combo_term(uint16_t index, combo_t *combo) { */
/*   switch(index) { */
/*     case ALT:// extending the combo term here helps reduce sticky layers some more. */
/*       return 250; */
/*   } */
/*       return COMBO_TERM; */
/* } */

/* uint16_t COMBO_LEN = COMBO_LENGTH; */

/* const uint16_t PROGMEM combo_navigation[] = { KC_OSYM, KC_ONUM, COMBO_END }; */
/* combo_t key_combos[] = { */
/*   [COMBO_NAVIGATION]        = COMBO(combo_navigation, OSL(_NAVIGATION)), */
/* }; */


// tapdances
tap_dance_action_t tap_dance_actions[] = {
    [TD_QESC]   = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC),
    [TD_SBKT]   = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
    [TD_CBKT]   = ACTION_TAP_DANCE_DOUBLE(KC_LCBR, KC_RCBR),
    [TD_PARN]   = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_RPRN),
    [TD_LTGT]   = ACTION_TAP_DANCE_DOUBLE(KC_LABK, KC_RABK),
    /* [TD_ATAB]   = ACTION_TAP_DANCE_DOUBLE(KC_TAB, (OSM(MOD_ALT))) */
};
// end tapdances

// begin layers
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ALPHA] = LAYOUT_split_3x5_3(
    KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,             KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,
    KC_A,       KC_ALTS,    KC_CTLD,    KC_F,      KC_G,             KC_H,       KC_J,       KC_CTLK,     KC_ALTL,   KC_SLSH,
    KC_SFTZ,    KC_X,       KC_C,       KC_GUIV,    KC_B,             KC_N,       KC_GUIM,    KC_COMM,    KC_DOT,  KC_SFTQ,
                            KC_SPC,     KC_OSYM2,     KC_SDEL,         KC_SENT,     KC_ONUM,    KC_OSYM
  ),     
  [_SYMBOL] = LAYOUT_split_3x5_3(
    KC_F1,      KC_F2,       KC_F3,      KC_F4,      KC_F5,           KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,
    KC_EXLM,    KC_AT,       KC_HASH,    KC_DLR,     KC_PERC,         KC_AMPR,    KC_CIRC,    KC_ASTR,    KC_TILD,    KC_BSLS,
    KC_F11,     KC_F12,      KC_F13,     KC_F14,     KC_F15,          KC_F16,     KC_F17,     KC_F18,     KC_F19,     KC_F20,
                             KC_SPC,     KC_ESC,     KC_SDEL,          KC_SENT,     KC_ONUM,    KC_TAB
  ),
  [_SYMBOL2] = LAYOUT_split_3x5_3(
    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,          KC_NO,      KC_NO,      KC_NO,    KC_NO,    KC_NO,
    KC_NO,      S(KC_LBRC), KC_PLS,    S(KC_RBRC), KC_NO,          KC_NO,      KC_LPRN,    KC_MINS,  KC_RPRN,    KC_NO,
    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,          KC_NO,      KC_LBRC,    KC_NO,    KC_LBRC,    KC_NO,
                            KC_SPC,     KC_ESC,     KC_SDEL,        KC_SENT,   KC_EQL,      KC_OSYM
  ),
  [_NUMBER] = LAYOUT_split_3x5_3(
    KC_NO,      KC_7,       KC_8,       KC_9,      KC_NO,            KC_NO,      KC_NO,      KC_HOME,      KC_NO,      KC_NO,
    KC_END,     KC_4,       KC_5,       KC_6,      KC_NO,            KC_NO,      KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,
    KC_NO,      KC_1,       KC_2,       KC_3,      KC_NO,            KC_NO,      KC_GUIM,      KC_NO,      KC_NO,     KC_NO,
                            KC_MINS,    KC_0,   KC_SDEL,           KC_SENT,     KC_BSPC,    KC_NO
  ),
  [_NAVIGATION] = LAYOUT_split_3x5_3(
    KC_NO,      KC_F2,      KC_NO,      KC_NO,      KC_NO,          KC_NO,      KC_HOME,    KC_UP,      KC_END,     KC_BSPC,
    KC_TAB,     KC_NO,      KC_NO,      KC_NO,      KC_NO,          KC_NO,      KC_LEFT,    KC_DOWN,    KC_RIGHT,   KC_SENT,
    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,          KC_NO,      KC_MPRV,    KC_MPLY,    KC_MNXT,    KC_SDEL,
                            KC_LCTL,    KC_OSYM,    KC_OSFT,        KC_SPC,     KC_ONUM,    KC_SENT 
  )
};
