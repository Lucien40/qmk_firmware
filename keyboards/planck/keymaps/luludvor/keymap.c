// sdothum - 2016 (c) wtfpl

// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.
//
// To flash corne / chimera / planck firmware
// ═════════════════════════
//   Reset keyboard or press hw reset button on base
//
//   cd qmk_firmware/keyboards/<keyboard>
//   sudo make KEYMAP=<keymap> dfu
//
//   sudo make clean           (good practice before flashing)
//   sudo make KEYMAP=<keymap> (to compile check)
//
// Package requirements (for arch linux)
// ═════════════════════════════════════
//   avr-gcc-atmel
//   avr-libc-atmel
//   dfu-programmer
//
// Notes
// ═════
//   ** E R G O   W I D E   S P L I T ** Layout
//
//   Autocompletion tap dance key pairs (),[],{} are available from the
//   number/symbol layer, as well as, numerous (un)shift key values
//
//   #define PRIVATE_STRING includes private_string.h, a user defined code
//   block for the PRIV tap dance e.g. SEND_STRING("secret messape"),
//   see function private()
//
// Code
// ════
//   This source is shamelessly based on the "default" planck layout
//
//   #ifdef/#endif block structures are not indented, as syntax highlighting
//   in vim is sufficient for identification
//
//   c++ commenting style is used throughout
//
// Change history
// ══════════════
//   See http://thedarnedestthing.com/colophon
//
//                === N O T E ===
//
// sudo CPATH=<keymap.c directory>/common make ...

// Hardware
// ═════════════════════════════════════════════════════════════════════════════

#include "hardware.h"

// Keymaps
// ═════════════════════════════════════════════════════════════════════════════

extern keymap_config_t keymap_config;

// ...................................................................... Layers

enum keyboard_layers {
    _BASE = 0,
    _SHIFT,
    _TTCAPS,
    _SYMGUI,
    _REGEX,
    _MOUSE,
    _NUMBER,
    _FNCKEY,
    _EDIT,
    _TTBASEL,
    _TTBASER,
    _TTFNCKEY,
    _TTCURSOR,
    _TTMOUSE,
    _TTNUMBER,
    _TTREGEX
#ifdef PLANCK
    ,
    _ADJUST
#endif
#ifdef TEST
    ,
    _TEST
#endif
    ,
    _END_LAYERS
};

// .................................................................... Keycodes

#include "keycodes.h"

// .............................................................. Tapdance Codes

#include "tapcodes.h"

// Layouts
// ═════════════════════════════════════════════════════════════════════════════

// ........................................................ Default Alpha Layout

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

#include "base_layout.h"

// ...................................................... Number / Function Keys

#include "number_fkey_layout.h"

// ......................................................... Symbol / Navigation

#include "symbol_guifn_layout.h"

// ............................................................... Toggle Layers

#include "toggle_layout.h"

// .............................................................. Mouse / Chords

#include "mouse_chord_layout.h"

};

// User Keycode Trap
// ═════════════════════════════════════════════════════════════════════════════

#include "keycode_functions.c"
#include "tapdance.c"

// ............................................................... Keycode Cycle

static uint16_t first_tap = 0;  // tap timer (time) first (0) second

#define DOUBLETAP                                             \
    if (KEY_DOWN) {                                           \
        first_tap = KEY_TAPPED(first_tap) ? 0 : timer_read(); \
    }
#define LEADERCAP leadercap = KEY_DOWN ? 1 : 0
#define MOD_ROLL(m, k, c) mod_roll(record, m, LOWER, k, c)

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LU_CARET:
            if (record->event.pressed) {
                // when keycode LU_CARET is pressed
                SEND_STRING("^");
            } else {
                // when keycode LU_CARET is released
            }
            break;
        case LU_BTICK:
            if (record->event.pressed) {
                // when keycode LU_BTICK is pressed
                SEND_STRING("`");
            } else {
                // when keycode LU_BTICK is released
            }
            break;
        case LU_TILD:
            if (record->event.pressed) {
                // when keycode LU_TILD is pressed
                SEND_STRING("~");
            } else {
                // when keycode LU_TILD is released
            }
            break;

            // ...................................................... Smart Keypad Delimiter

            static uint16_t postfix    = KC_SPC;  // see case DELIM
            static bool     numerating = 0;       // see case LT_TAB
            static bool     smart      = 1;       // see case SMART

#ifdef SMART_DELIM
            if (numerating && smart) {
                switch (keycode) {
                    case KC_0:
                        LEADERCAP;  // DELIM -> 0x
                    case KC_1:
                    case KC_2:
                    case KC_3:
                    case KC_4:
                    case KC_5:
                    case KC_6:
                    case KC_7:
                    case KC_8:
                    case KC_9:
                        postfix = KC_G;  // Vim ..G'oto
                        break;
                    case DELIM:
                        break;  // apply context rule
                    default:
                        postfix = KC_SPC;
                }
            } else {
                postfix = KC_SPC;
            }
#endif

            // Home Row
            // ═════════════════════════════════════════════════════════════════════════════

            // .......................................................... Home Row Modifiers

            switch (keycode) {
#define HOME_MOD(k)         \
    if (KEY_UP) {           \
        unregister_code(k); \
    };                      \
    MOD_BITS(k);            \
    break

                case HOME_T:
                    LEADERCAP;
                    HOME_MOD(KC_LSFT);  // space/enter + shift shortcut, see leader_cap()
                case HOME_N:
                    HOME_MOD(KC_RSFT);
                    break;

                    // Thumb Keys
                    // ═════════════════════════════════════════════════════════════════════════════

                    // ............................................................. Left Thumb Keys

                case TT_ESC:
                    base_layer(0);
                    return false;  // exit TT layer

                case TT_SPC:
                    layer_toggle(record, _REGEX, UPPER, KC_SPC);
                    break;

                    // ............................................................ Right Thumb Keys

                    // Key Pad
                    // ═════════════════════════════════════════════════════════════════════════════

                    // .................................................................... HEX Keys

                    static bool hexcase = HEXADECIMAL_CASE;  // hex case (0) lower case abcdef (1) upper case ABCDEF, see case HEXCASE

#define HEX(m, k) mod_tap(record, m, hexcase, k)

                case HEX_A:
                    HEX(0, KC_A);
                case HEX_B:
                    HEX(MOD_LALT | MOD_LCTL, KC_B);
                case HEX_C:
                    HEX(0, KC_C);
                case HEX_D:
                    HEX(KC_LCTL, KC_D);
                case HEX_E:
                    HEX(KC_LALT, KC_E);
                case HEX_F:
                    HEX(KC_LSFT, KC_F);

                    // ......................................................... Numpad Bracket Keys

                    static uint16_t brkts[][3] = {{LOWER, KC_LBRC, KC_RBRC},   // [] (side 1 -> 2)
                                                  {UPPER, KC_9, KC_0},         // ()
                                                  {UPPER, KC_LCBR, KC_RCBR}};  // {}
                    static uint8_t  brktype    = 0;                            // default (0) [], see case BRKTYPE

#define BRACKET(m, s)                                         \
    mod_tap(record, m, brkts[brktype][0], brkts[brktype][s]); \
    break

                case L_BRKT:
                    BRACKET(0, LEFT);
                case R_BRKT:
                    BRACKET(MOD_LALT | MOD_LSFT, RIGHT);

                    // ............................................................. Smart Delimiter

#define POSTCASE postfix == KC_G ? UPPER : LOWER

                case DELIM:
                    e if (leadercap) { mod_tap(record, _BASE, LOWER, KC_X); }  // 0x
                    else {
                        mod_tap(record, _BASE, POSTCASE, postfix);
                    }  // smart vim goto
                    break;

                    // Symbols
                    // ═════════════════════════════════════════════════════════════════════════════

                    // Alpha Keys
                    // ═════════════════════════════════════════════════════════════════════════════

                    // ...................................................... Capslock Modifier Keys

#define SHIFT_LAYER(m, l, k)           \
    layer_toggle(record, l, UPPER, k); \
    MOD_BITS(m);                       \
    break

                case TT_T:
                    SHIFT_LAYER(KC_LSFT, _TTBASEL, KC_A);
                case TT_N:
                    SHIFT_LAYER(KC_RSFT, _TTBASER, KC_T);

                    // ..................................................... Remaining Rollover Keys

                    // Layers
                    // ═════════════════════════════════════════════════════════════════════════════

                    // .................................................... Toggle Layer Pinkie Keys

                    // ............................................................... Toggle Layers

                    static uint8_t dual_down = 0;  // dual keys down (2 -> 1 -> 0) reset on last up stroke, see case TGL_TL, TGL_TR

#define DEFAULTS                \
    brktype = 0;                \
    hexcase = HEXADECIMAL_CASE; \
    postfix = KC_SPC;           \
    smart   = 1;                \
    stagger = PINKIE_STAGGER

#define RAISE(s)                                   \
    if (dualkey_raise(record, _BASE, s, INVERT)) { \
        dual_down = 2;                             \
        return false;                              \
    }                                              \
    if (dual_down) {                               \
        dual_down--;                               \
        base_layer(dual_down);                     \
        DEFAULTS;                                  \
        return false;                              \
    }                                              \
    tt_escape(record, keycode);                    \
    break

                case TGL_TL:
                    RAISE(LEFT);
                case TGL_TR:
                    RAISE(RIGHT);
                case TGL_HL:
                case TGL_HR:
                case TGL_BL:
                case TGL_BR:
                    tt_escape(record, keycode);
                    break;

                    // .................................................................. Steno Keys

                    // Special Keys
                    // ═════════════════════════════════════════════════════════════════════════════

                    // .................................................................. Other Keys

#define CYCLE(n)                               \
    if (KEY_DOWN) {                            \
        n = (n == 0) ? 1 : ((n == 1) ? 2 : 0); \
    };                                         \
    return false
#define TOGGLE(b)   \
    if (KEY_DOWN) { \
        b = !b;     \
    };              \
    return false

                case BRKTYPE:
                    CYCLE(brktype);  // see BRACKET()
                case HEXCASE:
                    TOGGLE(hexcase);
                case SMART:
                    TOGGLE(smart);
                case STAGGER:
                    CYCLE(stagger);  // see PINKIE()
            }

            CLR_1SHOT;  // see leader_cap()
            return true;
    }

        // Initialization
        // ═════════════════════════════════════════════════════════════════════════════

#include "initialize.c"
