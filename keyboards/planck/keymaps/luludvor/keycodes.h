// sdothum - 2016 (c) wtfpl

enum keyboard_keycodes {
    BASE = SAFE_RANGE,
    ,
    HEXCASE,  // capslock hex
    HEX_A,
    HEX_B,  // pseudo MT(MOD_LALT | MOD_LCTL, S(KC_B))
    HEX_C,
    HEX_D,    // pseudo CTL_T(S(KC_D))
    HEX_E,    // pseudo ALT_T(S(KC_E))
    HEX_F,    // pseudo SFT_T(S(KC_F))
    BRKTYPE,  // cycle brkts [] -> () -> {}
    L_BRKT,
    R_BRKT,  // pseudo MT(MOD_LALT | MOD_LSFT, R_BRKT)
    SMART,
    DELIM,
    TT_ESC,
    DT_EQL,
    TT_T,     // pseudo LT(_TTBASEL, S(CH_F))
    TT_SPC,   // pseudo LT(_REGEX,   S(KC_SPC))
    TT_N,     // pseudo LT(_TTBASER, S(CH_J))
    TT_BSPC,  // pseudo LT(_SYMGUI,  KC_BSPC)
    LU_CARET,
    LU_BTICK,
    LU_TILD

};

#define HOME_A GUI_T(CH_A)
#define HOME_R CTL_T(CH_S)
#define HOME_S ALT_T(CH_D)
#define HOME_T SFT_T(CH_F)
#define HOME_N SFT_T(CH_J)
#define HOME_E ALT_T(CH_K)
#define HOME_I CTL_T(CH_L)
#define HOME_O GUI_T(CH_DOT)

// pass through keycodes
#define __x__ KC_TRNS
#define ___ KC_NO

// editing macros
#define COPY LCTL(KC_C)
#define CUT LCTL(KC_X)
#define EOT LCTL(KC_D)
#define NAK LCTL(KC_U)
#define PASTE TD_PASTE
#define UNDO LCTL(KC_Z)
#define XCOPY LCTL(LSFT(KC_C))
#define XPASTE TD_XPASTE

// thumb keys

#define BKTAB S(KC_TAB)
#define LT_BSPC LT(_SYMGUI, KC_BSPC)
#define LT_ESC LT(_FNCKEY, KC_ESC)
#define LT_TAB LT(_NUMBER, KC_TAB)
#define LT_ENT LT(_EDIT, KC_ENT)
#define LT_SPC LT(_REGEX, KC_SPC)

// fnkey layer macros
#define OS_ALT OSM(MOD_LALT)
#define OS_CTL OSM(MOD_LCTL)
#define OS_GUI OSM(MOD_LGUI)
#define OS_SFT OSM(MOD_LSFT)

// layer toggle macros
#define TGL_TL TT(_TTFNCKEY)
#define TGL_HL TT(_TTCAPS)
#define TGL_BL TT(_TTMOUSE)
#define TGL_TR TT(_TTREGEX)
#define TGL_HR TT(_TTNUMBER)
#define TGL_BR TT(_TTCURSOR)
#ifdef PLANCK
#    define MO_ADJ MO(_ADJUST)
#endif

#ifdef TEST
#    define ROM TG(_TEST)
#else
#    ifdef CORNE
#        define ROM RESET
#    else
#        define ROM KC_NO
#    endif
#endif
