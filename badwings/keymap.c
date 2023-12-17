// Copyright 2023 Jason Hazel (@jasonhazel)
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H

void pointing_device_init_user(void) {
    set_auto_mouse_layer(5); // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
    set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
}

enum layers {
  _ALPHA,
  _FUNCT,
  _SYMBOL,
  _NUMBER,
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
#define KC_FUNCT  LT(_FUNCT, KC_TAB)
#define KC_OSYMa  LT(_SYMBOL, KC_F)
#define KC_OSYMb  LT(_SYMBOL, KC_J)
#define KC_LEFTS  LT(_SYMBOL, KC_LEFT)

// Mouse keys
#define KC_MSL KC_MS_BTN1 
#define KC_MSR KC_MS_BTN2 
#define KC_MSC KC_MS_BTN3 

// Movement
#define KC_WORDL C(KC_LEFT)
#define KC_WORDR C(KC_RIGHT) 

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

const uint16_t PROGMEM jk_combo[] = {KC_OSYMb, RCTL_T(KC_K), COMBO_END};
const uint16_t PROGMEM kl_combo[] = {RCTL_T(KC_K), LALT_T(KC_L), COMBO_END};
/* const uint16_t PROGMEM alt_combo[] = {KC_OSYM, KC_ONUM, COMBO_END}; */
const uint16_t PROGMEM gf_combo[] = {KC_G, LGUI_T(KC_F), COMBO_END};
const uint16_t PROGMEM fd_combo[] = {KC_CTLD, KC_OSYMa, COMBO_END};
const uint16_t PROGMEM caps_combo[] = {LT(3,KC_ESC), LT(1,KC_BSPC), COMBO_END};
const uint16_t PROGMEM chws_combo[] = {LT(3,KC_ESC), LT(4,KC_SPC), COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [KL] = COMBO(kl_combo, KC_SCLN),
  [JK] = COMBO(jk_combo, KC_COLN),
  [GF] = COMBO(gf_combo, KC_CIRC),
  [FD] = COMBO(fd_combo, KC_SCRL),
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
    KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,            KC_Y,      KC_U,       KC_I,       KC_O,      KC_P,
    KC_A,       KC_ALTS,    KC_CTLD,    KC_OSYMa,   KC_G,            KC_H,      KC_OSYMb,   KC_CTLK,    KC_ALTL,   KC_SLSH,
    KC_SFTZ,    KC_X,       KC_C,       KC_GUIV,    KC_B,            KC_N,      KC_GUIM,    KC_COMM,    KC_DOT,    KC_SFTQ,
                            KC_SPC,     KC_ESC,     KC_SDEL,         KC_SENT,   KC_ONUM,    KC_FUNCT
  ),     
  [_FUNCT] = LAYOUT_split_3x5_3(
    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,           KC_F6,     KC_F7,      KC_F8,      KC_F9,     KC_F10,
    G(KC_1),    G(KC_2),    G(KC_3),    G(KC_4),    G(KC_5),         G(KC_6),   G(KC_7),    G(KC_8),    G(KC_9),   G(KC_W),
    KC_F11,     KC_F12,     KC_F13,     KC_F14,     KC_F15,          KC_F16,    KC_F17,     KC_F18,     KC_F19,    KC_F20,
                            KC_SPC,     KC_ESC,     KC_SDEL,         KC_SENT,   KC_ONUM,    KC_TAB
  ),
  [_SYMBOL] = LAYOUT_split_3x5_3(
    KC_NO,      KC_AT,      KC_HASH,    KC_NO,      KC_NO,          KC_NO,     S(KC_COMM),  KC_EQL,    S(KC_DOT),  KC_NO,
    KC_EXLM,    KC_PERC,    KC_CIRC,    KC_DLR,     KC_AT,          KC_NO,     KC_PARN,     KC_MINS,   KC_SBKT,    KC_BSLS,
    KC_NO,      KC_AMPR,    KC_ASTR,    KC_TILD,    KC_NO,          KC_NO,     KC_CBKT,     KC_PLS,    KC_RBRC,    KC_NO,
                            KC_SPC,     KC_ESC,     KC_SDEL,        KC_SENT,   S(KC_MINS),  KC_FUNCT
  ),
  [_NUMBER] = LAYOUT_split_3x5_3(
    KC_NO,      KC_7,       KC_8,       KC_9,      KC_NO,            KC_NO,    KC_WORDL,    KC_HOME,    KC_WORDR,  KC_NO,
    KC_END,     KC_4,       KC_5,       KC_6,      KC_NO,            KC_NO,    KC_LEFTS,    KC_DOWN,    KC_UP,     KC_RIGHT,
    KC_NO,      KC_1,       KC_2,       KC_3,      KC_NO,            KC_NO,    KC_GUIM,     KC_NO,      KC_NO,     KC_NO,
                            KC_MINS,    KC_0,      KC_SDEL,          KC_SENT,  KC_BSPC,     KC_NO
  ),
  [5] = LAYOUT_split_3x5_3(
    KC_NO,     KC_NO,      KC_NO,      KC_NO,      KC_NO,          KC_NO,      KC_NO,      KC_NO,      KC_NO,     KC_NO,
    KC_NO,     KC_MSL,     KC_MSC,     KC_MSR,      KC_NO,          KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
    KC_NO,     C(KC_X),    C(KC_C),    C(KC_V),    KC_NO,          KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
                           KC_NO,      KC_NO,      KC_NO,          KC_NO,      KC_NO,      KC_NO 
  )
};
