/*
 * BRLTTY - A background process providing access to the console screen (when in
 *          text mode) for a blind person using a refreshable braille display.
 *
 * Copyright (C) 1995-2013 by The BRLTTY Developers.
 *
 * BRLTTY comes with ABSOLUTELY NO WARRANTY.
 *
 * This is free software, placed under the terms of the
 * GNU General Public License, as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any
 * later version. Please see the file LICENSE-GPL for details.
 *
 * Web Page: http://mielke.cc/brltty/
 *
 * This software is maintained by Dave Mielke <dave@mielke.cc>.
 */

#include "prologue.h"

#include <android/keycodes.h>

#include "sys_android.h"

#include "kbd.h"
#include "kbd_internal.h"
#include "kbd_android.h"

BEGIN_KEY_CODE_MAP
  [ANDROID_KEY_0] = KBD_KEY_SYMBOL(Zero_RightParenthesis),
  [ANDROID_KEY_1] = KBD_KEY_SYMBOL(One_Exclamation),
  [ANDROID_KEY_2] = KBD_KEY_SYMBOL(Two_At),
  [ANDROID_KEY_3] = KBD_KEY_SYMBOL(Three_Number),
  [ANDROID_KEY_3D_MODE] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_4] = KBD_KEY_SYMBOL(Four_Dollar),
  [ANDROID_KEY_5] = KBD_KEY_SYMBOL(Five_Percent),
  [ANDROID_KEY_6] = KBD_KEY_SYMBOL(Six_Circumflex),
  [ANDROID_KEY_7] = KBD_KEY_SYMBOL(Seven_Ampersand),
  [ANDROID_KEY_8] = KBD_KEY_SYMBOL(Eight_Asterisk),
  [ANDROID_KEY_9] = KBD_KEY_SYMBOL(Nine_LeftParenthesis),

  [ANDROID_KEY_A] = KBD_KEY_LETTER(A),
  [ANDROID_KEY_ALT_LEFT] = KBD_KEY_FUNCTION(AltLeft),
  [ANDROID_KEY_ALT_RIGHT] = KBD_KEY_FUNCTION(AltRight),
  [ANDROID_KEY_APOSTROPHE] = KBD_KEY_SYMBOL(Apostrophe_Quote),
  [ANDROID_KEY_APP_SWITCH] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_ASSIST] = KBD_KEY_FUNCTION(Help),
  [ANDROID_KEY_AT] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_AVR_INPUT] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_AVR_POWER] = KBD_KEY_UNKNOWN,

  [ANDROID_KEY_B] = KBD_KEY_LETTER(B),
  [ANDROID_KEY_BACK] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_BACKSLASH] = KBD_KEY_SYMBOL(Backslash_Bar),
  [ANDROID_KEY_BOOKMARK] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_BREAK] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_BUTTON_1] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_BUTTON_10] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_BUTTON_11] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_BUTTON_12] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_BUTTON_13] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_BUTTON_14] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_BUTTON_15] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_BUTTON_16] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_BUTTON_2] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_BUTTON_3] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_BUTTON_4] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_BUTTON_5] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_BUTTON_6] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_BUTTON_7] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_BUTTON_8] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_BUTTON_9] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_BUTTON_A] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_BUTTON_B] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_BUTTON_C] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_BUTTON_L1] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_BUTTON_L2] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_BUTTON_MODE] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_BUTTON_R1] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_BUTTON_R2] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_BUTTON_SELECT] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_BUTTON_START] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_BUTTON_THUMBL] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_BUTTON_THUMBR] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_BUTTON_X] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_BUTTON_Y] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_BUTTON_Z] = KBD_KEY_UNKNOWN,

  [ANDROID_KEY_C] = KBD_KEY_LETTER(C),
  [ANDROID_KEY_CALCULATOR] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_CALENDAR] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_CALL] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_CAMERA] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_CAPS_LOCK] = KBD_KEY_LOCK(Capitals),
  [ANDROID_KEY_CAPTIONS] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_CHANNEL_DOWN] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_CHANNEL_UP] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_CLEAR] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_COMMA] = KBD_KEY_SYMBOL(Comma_Less),
  [ANDROID_KEY_CONTACTS] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_CTRL_LEFT] = KBD_KEY_FUNCTION(ControlLeft),
  [ANDROID_KEY_CTRL_RIGHT] = KBD_KEY_FUNCTION(ControlRight),

  [ANDROID_KEY_D] = KBD_KEY_LETTER(D),
  [ANDROID_KEY_DEL] = KBD_KEY_FUNCTION(DeleteBackward),
  [ANDROID_KEY_DPAD_CENTER] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_DPAD_DOWN] = KBD_KEY_FUNCTION(ArrowDown),
  [ANDROID_KEY_DPAD_LEFT] = KBD_KEY_FUNCTION(ArrowLeft),
  [ANDROID_KEY_DPAD_RIGHT] = KBD_KEY_FUNCTION(ArrowRight),
  [ANDROID_KEY_DPAD_UP] = KBD_KEY_FUNCTION(ArrowUp),
  [ANDROID_KEY_DVR] = KBD_KEY_UNKNOWN,

  [ANDROID_KEY_E] = KBD_KEY_LETTER(E),
  [ANDROID_KEY_EISU] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_ENDCALL] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_ENTER] = KBD_KEY_FUNCTION(Enter),
  [ANDROID_KEY_ENVELOPE] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_EQUALS] = KBD_KEY_SYMBOL(Equals_Plus),
  [ANDROID_KEY_ESCAPE] = KBD_KEY_FUNCTION(Escape),
  [ANDROID_KEY_EXPLORER] = KBD_KEY_UNKNOWN,

  [ANDROID_KEY_F] = KBD_KEY_LETTER(F),
  [ANDROID_KEY_F1] = KBD_KEY_FUNCTION(F1),
  [ANDROID_KEY_F10] = KBD_KEY_FUNCTION(F10),
  [ANDROID_KEY_F11] = KBD_KEY_FUNCTION(F11),
  [ANDROID_KEY_F12] = KBD_KEY_FUNCTION(F12),
  [ANDROID_KEY_F2] = KBD_KEY_FUNCTION(F2),
  [ANDROID_KEY_F3] = KBD_KEY_FUNCTION(F3),
  [ANDROID_KEY_F4] = KBD_KEY_FUNCTION(F4),
  [ANDROID_KEY_F5] = KBD_KEY_FUNCTION(F5),
  [ANDROID_KEY_F6] = KBD_KEY_FUNCTION(F6),
  [ANDROID_KEY_F7] = KBD_KEY_FUNCTION(F7),
  [ANDROID_KEY_F8] = KBD_KEY_FUNCTION(F8),
  [ANDROID_KEY_F9] = KBD_KEY_FUNCTION(F9),
  [ANDROID_KEY_FOCUS] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_FORWARD] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_FORWARD_DEL] = KBD_KEY_FUNCTION(DeleteForward),
  [ANDROID_KEY_FUNCTION] = KBD_KEY_UNKNOWN,

  [ANDROID_KEY_G] = KBD_KEY_LETTER(G),
  [ANDROID_KEY_GRAVE] = KBD_KEY_SYMBOL(Grave_Tilde),
  [ANDROID_KEY_GUIDE] = KBD_KEY_UNKNOWN,

  [ANDROID_KEY_H] = KBD_KEY_LETTER(H),
  [ANDROID_KEY_HEADSETHOOK] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_HENKAN] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_HOME] = KBD_KEY_UNKNOWN,

  [ANDROID_KEY_I] = KBD_KEY_LETTER(I),
  [ANDROID_KEY_INFO] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_INSERT] = KBD_KEY_FUNCTION(Insert),

  [ANDROID_KEY_J] = KBD_KEY_LETTER(J),

  [ANDROID_KEY_K] = KBD_KEY_LETTER(K),
  [ANDROID_KEY_KANA] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_KATAKANA_HIRAGANA] = KBD_KEY_UNKNOWN,

  [ANDROID_KEY_L] = KBD_KEY_LETTER(L),
  [ANDROID_KEY_LANGUAGE_SWITCH] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_LEFT_BRACKET] = KBD_KEY_SYMBOL(LeftBracket_LeftBrace),

  [ANDROID_KEY_M] = KBD_KEY_LETTER(M),
  [ANDROID_KEY_MANNER_MODE] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_MEDIA_CLOSE] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_MEDIA_EJECT] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_MEDIA_FAST_FORWARD] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_MEDIA_NEXT] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_MEDIA_PAUSE] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_MEDIA_PLAY] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_MEDIA_PLAY_PAUSE] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_MEDIA_PREVIOUS] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_MEDIA_RECORD] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_MEDIA_REWIND] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_MEDIA_STOP] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_MENU] = KBD_KEY_FUNCTION(Menu),
  [ANDROID_KEY_META_LEFT] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_META_RIGHT] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_MINUS] = KBD_KEY_SYMBOL(Minus_Underscore),
  [ANDROID_KEY_MOVE_END] = KBD_KEY_FUNCTION(End),
  [ANDROID_KEY_MOVE_HOME] = KBD_KEY_FUNCTION(Home),
  [ANDROID_KEY_MUHENKAN] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_MUSIC] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_MUTE] = KBD_KEY_FUNCTION(Mute),

  [ANDROID_KEY_N] = KBD_KEY_LETTER(N),
  [ANDROID_KEY_NOTIFICATION] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_NUM] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_NUMPAD_0] = KBD_KEY_KEYPAD(Zero_Insert),
  [ANDROID_KEY_NUMPAD_1] = KBD_KEY_KEYPAD(One_End),
  [ANDROID_KEY_NUMPAD_2] = KBD_KEY_KEYPAD(Two_ArrowDown),
  [ANDROID_KEY_NUMPAD_3] = KBD_KEY_KEYPAD(Three_PageDown),
  [ANDROID_KEY_NUMPAD_4] = KBD_KEY_KEYPAD(Four_ArrowLeft),
  [ANDROID_KEY_NUMPAD_5] = KBD_KEY_KEYPAD(Five),
  [ANDROID_KEY_NUMPAD_6] = KBD_KEY_KEYPAD(Six_ArrowRight),
  [ANDROID_KEY_NUMPAD_7] = KBD_KEY_KEYPAD(Seven_Home),
  [ANDROID_KEY_NUMPAD_8] = KBD_KEY_KEYPAD(Eight_ArrowUp),
  [ANDROID_KEY_NUMPAD_9] = KBD_KEY_KEYPAD(Nine_PageUp),
  [ANDROID_KEY_NUMPAD_ADD] = KBD_KEY_KEYPAD(Plus),
  [ANDROID_KEY_NUMPAD_COMMA] = KBD_KEY_KEYPAD(Comma),
  [ANDROID_KEY_NUMPAD_DIVIDE] = KBD_KEY_KEYPAD(Slash),
  [ANDROID_KEY_NUMPAD_DOT] = KBD_KEY_KEYPAD(Period_Delete),
  [ANDROID_KEY_NUMPAD_ENTER] = KBD_KEY_KEYPAD(Enter),
  [ANDROID_KEY_NUMPAD_EQUALS] = KBD_KEY_KEYPAD(Equals),
  [ANDROID_KEY_NUMPAD_LEFT_PAREN] = KBD_KEY_KEYPAD(LeftParenthesis),
  [ANDROID_KEY_NUMPAD_MULTIPLY] = KBD_KEY_KEYPAD(Asterisk),
  [ANDROID_KEY_NUMPAD_RIGHT_PAREN] = KBD_KEY_KEYPAD(RightParenthesis),
  [ANDROID_KEY_NUMPAD_SUBTRACT] = KBD_KEY_KEYPAD(Minus),
  [ANDROID_KEY_NUM_LOCK] = KBD_KEY_KEYPAD(NumLock_Clear),

  [ANDROID_KEY_O] = KBD_KEY_LETTER(O),

  [ANDROID_KEY_P] = KBD_KEY_LETTER(P),
  [ANDROID_KEY_PAGE_DOWN] = KBD_KEY_FUNCTION(PageDown),
  [ANDROID_KEY_PAGE_UP] = KBD_KEY_FUNCTION(PageUp),
  [ANDROID_KEY_PERIOD] = KBD_KEY_SYMBOL(Period_Greater),
  [ANDROID_KEY_PICTSYMBOLS] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_PLUS] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_POUND] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_POWER] = KBD_KEY_FUNCTION(Power),
  [ANDROID_KEY_PROG_BLUE] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_PROG_GREEN] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_PROG_RED] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_PROG_YELLOW] = KBD_KEY_UNKNOWN,

  [ANDROID_KEY_Q] = KBD_KEY_LETTER(Q),

  [ANDROID_KEY_R] = KBD_KEY_LETTER(R),
  [ANDROID_KEY_RIGHT_BRACKET] = KBD_KEY_SYMBOL(RightBracket_RightBrace),
  [ANDROID_KEY_RO] = KBD_KEY_UNKNOWN,

  [ANDROID_KEY_S] = KBD_KEY_LETTER(S),
  [ANDROID_KEY_SCROLL_LOCK] = KBD_KEY_LOCK(Scroll),
  [ANDROID_KEY_SEARCH] = KBD_KEY_FUNCTION(Find),
  [ANDROID_KEY_SEMICOLON] = KBD_KEY_SYMBOL(Semicolon_Colon),
  [ANDROID_KEY_SETTINGS] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_SHIFT_LEFT] = KBD_KEY_FUNCTION(ShiftLeft),
  [ANDROID_KEY_SHIFT_RIGHT] = KBD_KEY_FUNCTION(ShiftRight),
  [ANDROID_KEY_SLASH] = KBD_KEY_SYMBOL(Slash_Question),
  [ANDROID_KEY_SOFT_LEFT] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_SOFT_RIGHT] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_SPACE] = KBD_KEY_FUNCTION(Space),
  [ANDROID_KEY_STAR] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_STB_INPUT] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_STB_POWER] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_SWITCH_CHARSET] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_SYM] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_SYSRQ] = KBD_KEY_FUNCTION(SystemRequest),

  [ANDROID_KEY_T] = KBD_KEY_LETTER(T),
  [ANDROID_KEY_TAB] = KBD_KEY_FUNCTION(Tab),
  [ANDROID_KEY_TV] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_TV_INPUT] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_TV_POWER] = KBD_KEY_UNKNOWN,

  [ANDROID_KEY_U] = KBD_KEY_LETTER(U),
  [ANDROID_KEY_UNKNOWN] = KBD_KEY_UNKNOWN,

  [ANDROID_KEY_V] = KBD_KEY_LETTER(V),
  [ANDROID_KEY_VOLUME_DOWN] = KBD_KEY_FUNCTION(VolumeDown),
  [ANDROID_KEY_VOLUME_MUTE] = KBD_KEY_FUNCTION(Mute),
  [ANDROID_KEY_VOLUME_UP] = KBD_KEY_FUNCTION(VolumeUp),

  [ANDROID_KEY_W] = KBD_KEY_LETTER(W),
  [ANDROID_KEY_WINDOW] = KBD_KEY_UNKNOWN,

  [ANDROID_KEY_X] = KBD_KEY_LETTER(X),

  [ANDROID_KEY_Y] = KBD_KEY_LETTER(Y),
  [ANDROID_KEY_YEN] = KBD_KEY_UNKNOWN,

  [ANDROID_KEY_Z] = KBD_KEY_LETTER(Z),
  [ANDROID_KEY_ZENKAKU_HANKAKU] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_ZOOM_IN] = KBD_KEY_UNKNOWN,
  [ANDROID_KEY_ZOOM_OUT] = KBD_KEY_UNKNOWN,
END_KEY_CODE_MAP

int
forwardKeyEvent (int code, int press) {
  return 0;
}

int
monitorKeyboards (KeyboardCommonData *kcd) {
  return 1;
}
