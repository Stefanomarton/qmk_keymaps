#include QMK_KEYBOARD_H

/* // Tap Dance declarations */
enum {
    TD_AP,
    TD_VIR,
    /* TD_SLS, */
    /* NCIRC, */
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
  [TD_AP] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_QUOTE),
  [TD_VIR] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, LSFT(KC_QUOTE)),
  /* [TD_SLS] = ACTION_TAP_DANCE_DOUBLE(KC_P, KC_SLSH), */
};

void caps_word_set_user(bool active) {

   if (active) {
       autoshift_disable();  // disable autoshift if capsword turned on
   } else {
       autoshift_enable();   // enable autoshift if capsword turned off
   }
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
   switch (keycode) {
       case GUI_T(KC_SPC):
           return TAPPING_TERM + 1000;
       default:
           return TAPPING_TERM;
   }
}

//Avoid the hold function when another key is tapped
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
   switch (keycode) {
       case GUI_T(KC_BSPC):
           // Immediately select the hold action when another key is tapped.
           return true;
       default:
           // Do not select the hold action when another key is tapped.
           return true;
   }
}

bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
   switch(keycode) {
       case KC_V:
           return true;
       case KC_A:
           return true;
       case KC_MINUS:
           return true;
       case KC_I:
           return true;
       case KC_O:
           return true;
       default:
           return false;
}}

// Add combos for faster typing
enum combos {
  JK,
  KL,
  GF,
  FD,
  ALT,
  CAPS,
  CHWS
};

const uint16_t PROGMEM jk_combo[] = {LT(4,KC_J), RCTL_T(KC_K), COMBO_END};
const uint16_t PROGMEM kl_combo[] = {RCTL_T(KC_K), LALT_T(KC_L), COMBO_END};
const uint16_t PROGMEM alt_combo[] = {LT(1,KC_BSPC), LT(4,KC_TAB), COMBO_END};
const uint16_t PROGMEM gf_combo[] = {KC_G, LGUI_T(KC_F), COMBO_END};
const uint16_t PROGMEM fd_combo[] = {LGUI_T(KC_F), LCTL_T(KC_D), COMBO_END};
const uint16_t PROGMEM caps_combo[] = {LT(3,KC_ESC), LT(1,KC_BSPC), COMBO_END};
const uint16_t PROGMEM chws_combo[] = {LT(3,KC_ESC), LT(4,KC_SPC), COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [KL] = COMBO(kl_combo, KC_SCLN),
  [JK] = COMBO(jk_combo, KC_COLN),
  [GF] = COMBO(gf_combo, KC_CIRC),
  [FD] = COMBO(fd_combo, S(KC_MINS)),
  [ALT] = COMBO(alt_combo, OSM(MOD_RALT)),
  [CAPS] = COMBO(caps_combo, CW_TOGG),
  [CHWS] = COMBO(chws_combo, OSL(3)),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
     //┌──────────────┬────────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬──────────────┐
         QK_BOOT,       KC_TRNS,    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
     //├──────────────┼────────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼──────────────┤
         KC_Q,           KC_W,        KC_E,    KC_R,    KC_T,  KC_TRNS,                            KC_TRNS,  KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,   
     //├──────────────┼────────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼──────────────┤
         LCTL_T(KC_A),  LALT_T(KC_S), LCTL_T(KC_D),   LT(2,KC_F), KC_G,                  KC_TRNS,  KC_TRNS,  RSFT_T(KC_H), LT(4,KC_J), RCTL_T(KC_K), LALT_T(KC_L),   LCTL_T(KC_SLSH),
     //├──────────────┼────────────┼────────┼────────┼────────┼────────┼───────────────┐ ┌────────┼────────┼────────┼────────┼────────┼────────┼──────────────┤
         LSFT_T(KC_Z),  KC_X,       KC_C,    LGUI_T(KC_V),KC_B, KC_SCRL,  KC_TRNS,         KC_TRNS,   KC_TRNS,  KC_N, LGUI_T(KC_M), KC_COMM, KC_DOT, LSFT_T(KC_QUOTE),
     //└──────────────┴────────────┴────────┴────────┼────────┼────────┼───────────────┤ ├────────┼────────┼────────┼────────┴────────┴────────┴──────────────┘
                                          LT(4,KC_SPC),  LT(3,KC_ESC), LSFT_T(KC_DEL), LSFT_T(KC_ENT), LT(1,KC_BSPC), LT(4,KC_TAB)
                                                  // └────────┴────────┴───────────────┘ └────────┴────────┴────────┘
     ), 
[1] = LAYOUT(
  //┌──────────────┬────────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬──────────────┐
      KC_TRNS,      KC_TRNS,    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,                              KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  
  //├──────────────┼────────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼──────────────┤
      KC_TRNS,     LCTL(KC_RIGHT), KC_TRNS,  KC_TRNS, KC_SCRL, KC_TRNS,                     KC_TRNS,   KC_TRNS, KC_TRNS, KC_HOME, KC_TRNS, KC_TRNS, 
  //├──────────────┼────────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼──────────────┤
      KC_END,    LALT_T(KC_S), LCTL_T(KC_D),  LGUI_T(KC_MINS), S(KC_MINS),  KC_TRNS,             KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN,  KC_UP,  KC_RIGHT, 
  //├──────────────┼────────────┼────────┼────────┼────────┼────────┼───────────────┐ ┌────────┼────────┼────────┼────────┼────────┼────────┼──────────────┤
      LSFT_T(KC_Z),     KC_X,    KC_C,    KC_V,  LCTL(KC_LEFT),  KC_TRNS,  KC_DEL,       KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,   KC_TRNS, 
  //└──────────────┴────────────┴────────┴────────┼────────┼────────┼───────────────┤ ├────────┼────────┼────────┼────────┴────────┴────────┴──────────────┘
                                                  KC_SPC, KC_MINS, KC_CIRC,     RSFT_T(KC_ENTER),LT(1,KC_INT5), KC_TRNS
                                               // └────────┴────────┴───────────────┘ └────────┴────────┴────────┘
             ),
[2] = LAYOUT(
  //┌──────────────┬────────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬──────────────┐
      KC_TRNS,        KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    
  //├──────────────┼────────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼──────────────┤
      KC_TRNS,        KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, LSFT(KC_LBRC), KC_EQL, S(KC_RBRC), KC_TRNS,  
  //├──────────────┼────────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼──────────────┤
      KC_TRNS,        KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                           KC_TRNS, KC_TRNS, KC_LPRN, KC_MINS,  KC_RPRN,  KC_TRNS,    
  //├──────────────┼────────────┼────────┼────────┼────────┼────────┼───────────────┐ ┌────────┼────────┼────────┼────────┼────────┼────────┼──────────────┤
      LSFT_T(KC_Z),    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS,KC_LBRC,  LSFT(KC_EQL), KC_RBRC, KC_TRNS,  
  //└──────────────┴────────────┴────────┴────────┼────────┼────────┼───────────────┤ ├────────┼────────┼────────┼────────┴────────┴────────┴──────────────┘
                                                   GUI_T(KC_SPC), KC_MINS, OSL(2),     RSFT_T(KC_ENTER), KC_MINS,  KC_TRNS 
                                               // └────────┴────────┴───────────────┘ └────────┴────────┴────────┘
),

[3] = LAYOUT(
  //┌──────────────┬────────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬──────────────┐
     KC_TRNS,        KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,                         KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,
  //├──────────────┼────────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼──────────────┤
     KC_TRNS,        KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,                             KC_TRNS,  S(KC_LBRC),  KC_7, KC_8,    KC_9,    KC_TRNS,    
  //├──────────────┼────────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼──────────────┤
      KC_TRNS,  LALT_T(KC_S), LCTL_T(KC_D),  LGUI_T(KC_F), KC_TRNS, KC_TRNS,                 KC_TRNS,  KC_LPRN, KC_4,     KC_5,    KC_6,    KC_EQL, 
  //├──────────────┼────────────┼────────┼────────┼────────┼────────┼───────────────┐ ┌────────┼────────┼────────┼────────┼────────┼────────┼──────────────┤
     LSFT_T(KC_Z),    KC_X,    KC_C,    LGUI_T(KC_V),    KC_B,    KC_DEL,    KC_TRNS,          KC_TRNS, KC_TRNS, KC_LBRC, KC_1,    KC_2,    KC_3,   KC_TRNS,
  //└──────────────┴────────────┴────────┴────────┼────────┼────────┼───────────────┤ ├────────┼────────┼────────┼────────┴────────┴────────┴──────────────┘
                                                 GUI_T(KC_SPC), S(KC_MINS), OSL(2),      KC_ASTR ,S(KC_MINS),  KC_0
                                               // └────────┴────────┴───────────────┘ └────────┴────────┴────────┘
),
[4] = LAYOUT(
  //┌──────────────┬────────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬──────────────┐
    KC_TRNS,        KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,                         KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,
  //├──────────────┼────────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼──────────────┤
      KC_F1,          KC_F2,      KC_F3,   KC_F4,  KC_F5,    KC_TRNS,                           KC_TRNS,    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  
  //├──────────────┼────────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼──────────────┤
     KC_EXLM,     KC_AT,  KC_HASH,  KC_DLR,  KC_PERC,       KC_TRNS,                            KC_TRNS,  KC_AMPR,  KC_CIRC,  KC_ASTR, KC_TILD, KC_BSLS,    
  //├──────────────┼────────────┼────────┼────────┼────────┼────────┼───────────────┐ ┌────────┼────────┼────────┼────────┼────────┼────────┼──────────────┤
      LSFT_T(KC_Z),     KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,  KC_F11,  KC_F12,  KC_F13,   KC_TRNS,   
  //└──────────────┴────────────┴────────┴────────┼────────┼────────┼───────────────┤ ├────────┼────────┼────────┼────────┴────────┴────────┴──────────────┘
                                                   GUI_T(KC_SPC), KC_MINS, OSL(2),     RSFT_T(KC_ENTER),LT(1,KC_INT5),  MOD_RALT),
                                               // └────────┴────────┴───────────────┘ └────────┴────────┴────────┘
};

