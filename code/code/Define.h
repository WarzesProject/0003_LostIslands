#pragma once

#define TERMINAL_VERSION "Sapphire"

/*
* Generic mode enum.
* Right now it is used for composition option only.
*/
#define TK_OFF                 0
#define TK_ON                  1

/*
* Keyboard scancodes for events/states
*/
#define TK_A                0x04
#define TK_B                0x05
#define TK_C                0x06
#define TK_D                0x07
#define TK_E                0x08
#define TK_F                0x09
#define TK_G                0x0A
#define TK_H                0x0B
#define TK_I                0x0C
#define TK_J                0x0D
#define TK_K                0x0E
#define TK_L                0x0F
#define TK_M                0x10
#define TK_N                0x11
#define TK_O                0x12
#define TK_P                0x13
#define TK_Q                0x14
#define TK_R                0x15
#define TK_S                0x16
#define TK_T                0x17
#define TK_U                0x18
#define TK_V                0x19
#define TK_W                0x1A
#define TK_X                0x1B
#define TK_Y                0x1C
#define TK_Z                0x1D
#define TK_1                0x1E
#define TK_2                0x1F
#define TK_3                0x20
#define TK_4                0x21
#define TK_5                0x22
#define TK_6                0x23
#define TK_7                0x24
#define TK_8                0x25
#define TK_9                0x26
#define TK_0                0x27
#define TK_RETURN           0x28
#define TK_ENTER            0x28
#define TK_ESCAPE           0x29
#define TK_BACKSPACE        0x2A
#define TK_TAB              0x2B
#define TK_SPACE            0x2C
#define TK_MINUS            0x2D /*  -  */
#define TK_EQUALS           0x2E /*  =  */
#define TK_LBRACKET         0x2F /*  [  */
#define TK_RBRACKET         0x30 /*  ]  */
#define TK_BACKSLASH        0x31 /*  \  */
#define TK_SEMICOLON        0x33 /*  ;  */
#define TK_APOSTROPHE       0x34 /*  '  */
#define TK_GRAVE            0x35 /*  `  */
#define TK_COMMA            0x36 /*  ,  */
#define TK_PERIOD           0x37 /*  .  */
#define TK_SLASH            0x38 /*  /  */
#define TK_F1               0x3A
#define TK_F2               0x3B
#define TK_F3               0x3C
#define TK_F4               0x3D
#define TK_F5               0x3E
#define TK_F6               0x3F
#define TK_F7               0x40
#define TK_F8               0x41
#define TK_F9               0x42
#define TK_F10              0x43
#define TK_F11              0x44
#define TK_F12              0x45
#define TK_PAUSE            0x48 /* Pause/Break */
#define TK_INSERT           0x49
#define TK_HOME             0x4A
#define TK_PAGEUP           0x4B
#define TK_DELETE           0x4C
#define TK_END              0x4D
#define TK_PAGEDOWN         0x4E
#define TK_RIGHT            0x4F /* Right arrow */
#define TK_LEFT             0x50 /* Left arrow */
#define TK_DOWN             0x51 /* Down arrow */
#define TK_UP               0x52 /* Up arrow */
#define TK_KP_DIVIDE        0x54 /* '/' on numpad */
#define TK_KP_MULTIPLY      0x55 /* '*' on numpad */
#define TK_KP_MINUS         0x56 /* '-' on numpad */
#define TK_KP_PLUS          0x57 /* '+' on numpad */
#define TK_KP_ENTER         0x58
#define TK_KP_1             0x59
#define TK_KP_2             0x5A
#define TK_KP_3             0x5B
#define TK_KP_4             0x5C
#define TK_KP_5             0x5D
#define TK_KP_6             0x5E
#define TK_KP_7             0x5F
#define TK_KP_8             0x60
#define TK_KP_9             0x61
#define TK_KP_0             0x62
#define TK_KP_PERIOD        0x63 /* '.' on numpad */
#define TK_SHIFT            0x70
#define TK_CONTROL          0x71
#define TK_ALT              0x72

/*
* Mouse events/states
*/
#define TK_MOUSE_LEFT       0x80 /* Buttons */
#define TK_MOUSE_RIGHT      0x81
#define TK_MOUSE_MIDDLE     0x82
#define TK_MOUSE_X1         0x83
#define TK_MOUSE_X2         0x84
#define TK_MOUSE_MOVE       0x85 /* Movement event */
#define TK_MOUSE_SCROLL     0x86 /* Mouse scroll event */
#define TK_MOUSE_X          0x87 /* Cusor position in cells */
#define TK_MOUSE_Y          0x88
#define TK_MOUSE_PIXEL_X    0x89 /* Cursor position in pixels */
#define TK_MOUSE_PIXEL_Y    0x8A
#define TK_MOUSE_WHEEL      0x8B /* Scroll direction and amount */
#define TK_MOUSE_CLICKS     0x8C /* Number of consecutive clicks */

/*
* If key was released instead of pressed, it's code will be OR'ed with TK_KEY_RELEASED:
* a) pressed 'A': 0x04
* b) released 'A': 0x04|VK_KEY_RELEASED = 0x104
*/
#define TK_KEY_RELEASED     0x100

/*
* Virtual key-codes for internal terminal states/variables.
* These can be accessed via terminal_state function.
*/
#define TK_WIDTH            0xC0 /* Terminal window size in cells */
#define TK_HEIGHT           0xC1
#define TK_CELL_WIDTH       0xC2 /* Character cell size in pixels */
#define TK_CELL_HEIGHT      0xC3
#define TK_COLOR            0xC4 /* Current foregroung color */
#define TK_BKCOLOR          0xC5 /* Current background color */
#define TK_LAYER            0xC6 /* Current layer */
#define TK_COMPOSITION      0xC7 /* Current composition state */
#define TK_CHAR             0xC8 /* Translated ANSI code of last produced character */
#define TK_WCHAR            0xC9 /* Unicode codepoint of last produced character */
#define TK_EVENT            0xCA /* Last dequeued event */
#define TK_FULLSCREEN       0xCB /* Fullscreen state */

/*
* Other events
*/
#define TK_CLOSE            0xE0
#define TK_RESIZED          0xE1