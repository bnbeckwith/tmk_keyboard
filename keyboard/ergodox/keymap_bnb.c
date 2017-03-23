#include <util/delay.h>
#include "action_layer.h"
#include "action_util.h"
#include "bootloader.h"
#include "keymap_common.h"


const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Keymap: Default Layer in QWERTY
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |   ~    |   1  |   2  |   3  |   4  |   5  |   \  |           |   -  |   6  |   7  |   8  |   9  |   0  |   =    |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * | Tab    |   Q  |   W  |   E  |   R  |   T  | ~L5  |           | ~L6  |   Y  |   U  |   I  |   O  |   P  |   [    |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * | Tab/Shf|   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
     * |--------+------+------+------+------+------|  L0  |           | ~L7  |------+------+------+------+------+--------|
     * | LCtrl  |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  |   ]    |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   | ~L5  | ~L2  | Caps | LAlt | LGui |                                       |  Lft |  Up  |  Dn  | Rght | ~L6  |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        | +L2  | Home |       | PgUp | Del  |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |  End |       | PgDn |      |      |
     *                                 | BkSp |  ESC |------|       |------| Enter| Space|
     *                                 |      |      |  Spc |       | Ins  |      |      |
     *                                 `--------------------'       `--------------------'
     *
     *
     *
     ****************************************************************************************************
     *
     * Under XOrg, I use my own mapping from QWERTY to "Workman for Programmers"
     * See XOrg files in ./addons/ subdirectory.
     *
     * I have to do so, because of two things:
     * 1) my native language is Russian, and XOrg keymap for it is based on QWERTY layout
     * 2) I want to have non-standart shifted keys, like $ (as normal) and @ (as shifted), or _ and -
     *
     * And even if (2) could be solved using FN* keys (but there is limit in firmware for only 32 such
     * keys), then (1) can't be solved at firmware level at all.
     *
     * So, I have to stick with QWERTY as my main layout + my own XOrg keyboard layout for English.
     * But sometimes I have to input something when XOrg is not active - for example, in Linux console,
     * or in firmware console (while debugging firmware), or when keyboard is connected to not my computer.
     *
     * For such cases I have Layer1 :)
     * // hint: switch to Layer1 is only at Layer6
     *
     ****************************************************************************************************
     *
     *
     *
     * Keymap: Default Layer in Workman
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |  ~     |   ;  |   !  |   #  |   {  |   }  |   '  |           |   ^  |   [  |   ]  |   *  |   (  |   )  |   =    |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * | Tab    |   Q  |   D  |   R  |   W  |   B  |  NO  |           | ~L7  |   J  |   F  |   U  |   P  |   $  |   :    |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * | Tab/Shf|   A  |   S  |   H  |   T  |   G  |------|           |------|   Y  |   N  |   E  |   O  |   I  |   -    |
     * |--------+------+------+------+------+------| Home |           | End  |------+------+------+------+------+--------|
     * | LCtrl  |   Z  |   X  |   M  |   C  |   V  |      |           |      |   K  |   L  |   ,  |   .  |   /  |   |    |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   | ~L5  | ~L2  | Caps | LAlt | LGui |                                       |  Lft |  Up  |  Dn  | Rght | ~L6  |
     *   `---------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |  L0  |  +L2 |       | PgUp | Del  |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |  NO  |       | PgDn |      |      |
     *                                 | BkSp |  ESC |------|       |------| Enter| Space|
     *                                 |      |      |  Spc |       | Ins  |      |      |
     *                                 `--------------------'       `--------------------'
     *
     * Keymap: Default Layer in Workman / with Shift
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |  `     |   1  |   2  |   3  |   4  |   5  |   "  |           |   \  |   6  |   7  |   8  |   9  |   0  |   +    |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * | Tab    |   Q  |   D  |   R  |   W  |   B  |  NO  |           | ~L7  |   J  |   F  |   U  |   P  |   @  |   %    |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * | Tab/Shf|   A  |   S  |   H  |   T  |   G  |------|           |------|   Y  |   N  |   E  |   O  |   I  |   _    |
     * |--------+------+------+------+------+------| Home |           | End  |------+------+------+------+------+--------|
     * | LCtrl  |   Z  |   X  |   M  |   C  |   V  |      |           |      |   K  |   L  |   ,  |   .  |   /  |   &    |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   | ~L5  | ~L2  | Caps | LAlt | LGui |                                       |  Lft |  Up  |  Dn  | Rght | ~L6  |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |  L0  |  +L2 |       | PgUp | Del  |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |  NO  |       | PgDn |      |      |
     *                                 | BkSp |  ESC |------|       |------| Enter| Space|
     *                                 |      |      |  Spc |       | Ins  |      |      |
     *                                 `--------------------'       `--------------------'
     *
     */

    KEYMAP(  // Layer0: default, leftled:none
        // left hand
        GRV, FN31,FN29,   3,   4,   5,   BSLS,
        FN11,   Q,   W,   E,   R,   T,   FN18,
        FN13,   A,   S,   D,   F,   G,
        FN12,   Z,   X,   C,   V,   B,   HOME,
        F12,   F9,F3,APP,LGUI,
                                      F4, FN17,
                                           FN24,
                                 FN5, FN6, FN7,
        // right hand
             MINS,6,   7,   8,   9,   0,   EQL,
             FN23,Y,   U,   I,   O,   P,   QUOT,
                  H,   J,   K,   L,   SCLN,FN15,
             END, N,   M,   COMM,DOT, SLSH,FN16,
                       LEFT,DOWN,UP,RGHT,RGUI,
        PGDN,PGUP,
        FN8,
        FN14, FN9, SPC
    ),


    KEYMAP(  // Layer1: Dvorak
           // left hand

        TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,  TRNS,  
        TRNS,QUOT,COMM, DOT,   P,   Y,   TRNS,  
        TRNS,   A,   O,   E,   U,   I,          
        TRNS,SCLN,   Q,   J,   K,   X,   TRNS,  
        TRNS,TRNS,TRNS,TRNS,TRNS,               
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS, TRNS, TRNS, 
        // right hand                           
             TRNS,   TRNS,TRNS,TRNS, TRNS, TRNS,TRNS, 
             TRNS,   F,   G,   C,   R,   L,TRNS,
                     D,   H,   T,   N,   S,TRNS,
             TRNS,   B,   M,   W,   V,   Z,TRNS,
                       TRNS,TRNS,TRNS,TRNS,TRNS,  
        TRNS ,TRNS,                               
        TRNS,                                   
        TRNS, TRNS, TRNS                          
             ),



    
    KEYMAP(  // Layer2: numpad, leftled:mid/blue
        // left hand
        TRNS,TRNS,  NO,  NO,  NO,PAUS,PSCR,
        TRNS,  NO,  NO,  NO,  NO,  NO,TRNS,
        TRNS,  NO,  NO,  NO,  NO,  NO,
        TRNS,  NO,  NO,  NO,  NO,  NO,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             SLCK,NLCK,PSLS,PAST,PAST,PMNS,BSPC,
             TRNS,NO,  P7,  P8,  P9,  PMNS,PGUP,
                  NO,  P4,  P5,  P6,  PPLS,PGDN,
             TRNS,NO,  P1,  P2,  P3,  PPLS,PENT,  
                       P0,  P0,PDOT,  SLSH,PENT,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),

    KEYMAP(  // Layer3: F-keys only, leftled:top/white
        // left hand
         FN0, NO,  TRNS,  NO,  NO,  NO,  NO,
        TRNS, F1, F2, F3, F4,  NO,  NO,
        TRNS, F5, F6, F7, F8,  NO,
        TRNS, F9, F10, F11, F12,  NO,  TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             NO,  NO,  NO,  NO,  NO,  NO,  TRNS,
             NO,  NO, F13, F14, F15, F16,  TRNS,
                  NO, F17, F18, F19, F20,  TRNS,
             TRNS,NO, F21, F22, F23, F24,  TRNS,
                       TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        SLEP,TRNS,TRNS
    ),

    KEYMAP(  // Layer4 mouse and navigation, leftled:mid/blue+bot/green
        // left hand
        TRNS, MPLY,MPRV,MNXT,VOLD,VOLU,MUTE,
        TRNS, WH_L,WH_D,WH_U,WH_R,HOME,PGUP,
        TRNS, MS_L,MS_D,MS_U,MS_R, END,
        TRNS,  BTN1,BTN2,BTN3, DEL, INS, PGDN,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,

        // right hand
             F16, MPLY,MPRV,MNXT,VOLD,VOLU,MUTE,
             F14, WH_L,WH_D,WH_U,WH_R,HOME,PGUP,
                  MS_L,MS_D,MS_U,MS_R, END,PGDN,
             F15, BTN1,BTN2,BTN3, DEL, INS,CAPS,
                       TRNS,TRNS,TRNS,TRNS,NLCK,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
             ),

/*
    // templates to copy from

    KEYMAP(  // LayerN: transparent on edges + hard-defined thumb keys, all others are empty
        // left hand
        TRNS,NO,  NO,  NO,  NO,  NO,  NO,
        TRNS,NO,  NO,  NO,  NO,  NO,  TRNS,
        TRNS,NO,  NO,  NO,  NO,  NO,
        TRNS,NO,  NO,  NO,  NO,  NO,  TRNS,
        TRNS,TRNS,TRNS,LALT,LGUI,
                                      TRNS,TRNS,
                                           TRNS,
                                 LCTL,LSFT,TRNS,
        // right hand
             NO,  NO,  NO,  NO,  NO,  NO,  TRNS,
             TRNS,NO,  NO,  NO,  NO,  NO,  TRNS,
                  NO,  NO,  NO,  NO,  NO,  TRNS,
             TRNS,NO,  NO,  NO,  NO,  NO,  TRNS,
                       RGUI,RALT,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,RSFT,RCTL
    ),
    KEYMAP(  // LayerN: fully transparent
        // left hand
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                       TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),
*/

};

/* id for user defined functions & macros */
enum function_id {
    TEENSY_KEY,
    CUSTOM_KEY,
    L_CTRL_ALT_ENT,
    R_CTRL_ALT_ENT,
};

/*
 * Fn action definition
 */
const uint16_t PROGMEM fn_actions[] = {
    [0] =   ACTION_FUNCTION(TEENSY_KEY),                    // FN0  - Teensy key

    [1] =   ACTION_MODS_KEY(MOD_LSFT, KC_BSLS),             // FN1  = Shifted BackSlash // " in Workman ||||s
    [2] =   ACTION_MODS_KEY(MOD_LSFT, KC_MINS),             // FN2  = Shifted Minus     // \ in Workman
    [3] =   ACTION_MODS_KEY(MOD_LSFT, KC_COMM),             // FN3  = Shifted comma     // < in Workman
    [4] =   ACTION_MODS_KEY(MOD_LSFT, KC_DOT),              // FN4  = Shifted dot       // > in Workman

    [5] =   ACTION_MODS_TAP_KEY(MOD_LCTL, KC_BSPC),         // FN5  = LShift with tap BackSpace
    [6] =   ACTION_MODS_TAP_KEY(MOD_LSFT, KC_DEL),          // FN6  = LCtrl  with tap Delete
    [7] =   ACTION_MODS_TAP_KEY(MOD_LALT, KC_ESC),          // FN7  = LAlt   with tap Escape
    [8] =   ACTION_MODS_TAP_KEY(MOD_RALT, KC_INS),          // FN8  = RAlt   with tap Ins
    [9] =   ACTION_MODS_TAP_KEY(MOD_RSFT, KC_ENT),          // FN9  = RShift with tap Enter
    [10] =  ACTION_MODS_TAP_KEY(MOD_RCTL, KC_SPC),          // FN10 = RCtrl  with tap Space

    [11] =  ACTION_MODS_TAP_KEY(MOD_LSFT, KC_TAB),          // FN11 = LShift with tap Tab
    [12] =  ACTION_MODS_TAP_KEY(MOD_LCTL, KC_GRV),          // FN12 = LCtrl  with tap Tilda
    [13] =  ACTION_MODS_TAP_KEY(MOD_LALT, KC_SPC),          // FN13 = LAlt   with tap Space
    [14] =  ACTION_MODS_TAP_KEY(MOD_LGUI, KC_ESC),          // FN14 = LGui   with tap Escape
    [15] =  ACTION_MODS_TAP_KEY(MOD_RSFT, KC_LBRC),         // FN15 = RShift with tap quotes
    [16] =  ACTION_MODS_TAP_KEY(MOD_RCTL, KC_RBRC),         // FN16 = RCtrl  with tap ]

    [17] =  ACTION_LAYER_SET(0, ON_BOTH),                   // FN17 - set Layer0
    [18] =  ACTION_LAYER_SET(1, ON_BOTH),                   // FN18 - set Layer1,
    [19] =  ACTION_LAYER_SET(3, ON_BOTH),                   // FN19 - set Layer3, to use with Numpad keys


    [20] =  ACTION_LAYER_MOMENTARY(6),            // FN20 - F keys
    [22] =  ACTION_FUNCTION_TAP(R_CTRL_ALT_ENT),            // FN22 - momentary Layer4+CTRL+ALT on Enter, to use with F* keys

    [28] =  ACTION_LAYER_TAP_KEY(3, KC_3),                  // FN28 = momentary Layer5 on 3 key, to use with unconvenient keys
    [29] =  ACTION_LAYER_TAP_KEY(3, KC_2),                  // FN29 = momentary Layer4 on 2 key, to use with F* keys
    [30] =  ACTION_LAYER_TAP_KEY(3, KC_F9),                      // FN30 = momentary Layer3, to use with mouse and navigation keys
    [31] =  ACTION_LAYER_TAP_KEY(2, KC_1),                  // FN31 = momentary Layer3 on 1 key, to use with Numpad keys

    // i'd like to remove this - will try to get used to live without this and convert them to usual keys
    [21] =  ACTION_LAYER_MOMENTARY(8),                      // FN20 - momentary Layer2, to use with Numpad keys
// or
//  [20] =  ACTION_FUNCTION_TAP(CUSTOM_KEY),                // FN20 - use custom key, with tapping support

    [23] =  ACTION_LAYER_TAP_KEY(4, KC_BSLS),               // FN23 - momentary Layer4 on ' , to use with F* keys (F1-F24)
    // TODO -- fix these to make sense.
    [24] =  ACTION_LAYER_TAP_KEY(4, KC_F4),                  // FN24 = momentary Layer4 on 4 key, to use with F* keys
    [25] =  ACTION_LAYER_TAP_KEY(5, KC_5),                  // FN25 = momentary Layer5 on 5 key, to use with F* keys
    [26] =  ACTION_LAYER_TAP_KEY(6, KC_C),                  // FN26 = momentary Layer6 on C key, to use with mouse and navigation keys 
    [27] =  ACTION_LAYER_TAP_KEY(2, KC_ENT),                  // FN26 = momentary Layer8 on C key, to use with mouse and navigation keys
};

static const uint16_t PROGMEM fn_actions_3[] = {
    [1]   =  ACTION_MODS_KEY(MOD_LSFT, KC_LBRC), // FN1  = Shifted [  - {
    [2]   =  ACTION_MODS_KEY(MOD_LSFT, KC_RBRC), // FN1  = Shifted ]  - }
    [3]   =  ACTION_MODS_KEY(MOD_LSFT, KC_9),    // FN1  = Shifted 9  - (
    [4]   =  ACTION_MODS_KEY(MOD_LSFT, KC_0),    // FN1  = Shifted 0  - ) 
    [5]   =  ACTION_MODS_KEY(MOD_LSFT, KC_6),    // FN1  = Shifted 6  - ^
    [6]   =  ACTION_MODS_KEY(MOD_LSFT, KC_1),    // FN1  = Shifted 1  - !
    [7]   =  ACTION_MODS_KEY(MOD_LSFT, KC_SLSH), // FN1  = Shifted /  - ?
    [8]   =  ACTION_MODS_KEY(MOD_LSFT, KC_4),    // FN1  = Shifted 4  - $
    [9]   =  ACTION_MODS_KEY(MOD_LSFT, KC_QUOT), // FN1  = Shifted '  - "
    [10]  =  ACTION_MODS_KEY(MOD_LSFT, KC_3),    // FN1  = Shifted 3  - #
    [11]  =  ACTION_MODS_KEY(MOD_LSFT, KC_COMM), // FN1  = Shifted ,  - <
    [12]  =  ACTION_MODS_KEY(MOD_LSFT, KC_DOT),  // FN1  = Shifted .  - >
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
	
    // print("action_function called\n");
    // print("id  = "); phex(id); print("\n");
    // print("opt = "); phex(opt); print("\n");

    if (id == TEENSY_KEY) {
        clear_keyboard();
        print("\n\nJump to bootloader... ");
        _delay_ms(50);
        bootloader_jump(); // should not return
        print("not supported.\n");
    }

    if (id == L_CTRL_ALT_ENT || id == R_CTRL_ALT_ENT) {
        if (record->tap.count == 0 || record->tap.interrupted) {
            uint8_t weak_mods;
            uint8_t layer = 4;
            if (id == L_CTRL_ALT_ENT) {
                weak_mods = MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT);
                //                layer     = 5;
            } else {
                weak_mods = MOD_BIT(KC_RCTL) | MOD_BIT(KC_RALT);
                //                layer     = 6;
            }

            if (record->event.pressed) {
                layer_on(layer);
                add_weak_mods(weak_mods);
            } else {
                del_weak_mods(weak_mods);
                layer_off(layer);
            }
        } else {
            if (record->event.pressed) {
                add_key(KC_ENT);
                send_keyboard_report();
            } else {
                del_key(KC_ENT);
                send_keyboard_report();
            }
        }
    }


/*
 * just an example of custom key implementation
 * not really needed with custom keymap_fn_to_action(),
 * because it will allow you to have 32 FN** keys on EACH layer
 */

/*
    keyevent_t event = record->event;

    if (id == CUSTOM_KEY) {
        uint8_t layer = biton32(layer_state);
        uint8_t col = event.key.col;
        uint8_t row = event.key.row;
        uint8_t handled = 0;

        if (event.pressed) {
            if (layer == XXX && col == XXX && row == XXX) {
                    action_macro_play(
                        MACRO(
                            ...........
                        END)
                    );
                    handled++;
                }
            }
        }

        if (!handled) {
            print("custom key not handled");
            print(": layer "); pdec(layer);
            print(", col "); pdec(col);
            print(", row "); pdec(row);
            print("\n");
        }
    }
*/

}

#define FN_ACTIONS_SIZE     (sizeof(fn_actions)   / sizeof(fn_actions[0]))
#define FN_ACTIONS_3_SIZE   (sizeof(fn_actions_3) / sizeof(fn_actions_3[0]))

/*
 * translates Fn keycode to action
 * for some layers, use different translation table
 */
action_t keymap_fn_to_action(uint8_t keycode)
{
    uint8_t layer = biton32(layer_state);

    action_t action;
    action.code = ACTION_NO;

    if (layer == 3 && FN_INDEX(keycode) < FN_ACTIONS_3_SIZE) {
        action.code = pgm_read_word(&fn_actions_3[FN_INDEX(keycode)]);
    }

    // by default, use fn_actions from default layer 0
    // this is needed to get mapping for same key, that was used switch to some layer,
    // to have possibility to switch layers back
    if (action.code == ACTION_NO && FN_INDEX(keycode) < FN_ACTIONS_SIZE) {
        action.code = pgm_read_word(&fn_actions[FN_INDEX(keycode)]);
    }

    return action;
}

