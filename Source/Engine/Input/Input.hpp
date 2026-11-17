#pragma once

#include "glfw3.h"

class Input
{
public:
    // Printable keys
    inline static constexpr int Key_Space         = GLFW_KEY_SPACE;
    inline static constexpr int Key_Apostrophe    = GLFW_KEY_APOSTROPHE;
    inline static constexpr int Key_Comma         = GLFW_KEY_COMMA;
    inline static constexpr int Key_Minus         = GLFW_KEY_MINUS;
    inline static constexpr int Key_Period        = GLFW_KEY_PERIOD;
    inline static constexpr int Key_Slash         = GLFW_KEY_SLASH;

    // Numbers
    inline static constexpr int Key_0 = GLFW_KEY_0;
    inline static constexpr int Key_1 = GLFW_KEY_1;
    inline static constexpr int Key_2 = GLFW_KEY_2;
    inline static constexpr int Key_3 = GLFW_KEY_3;
    inline static constexpr int Key_4 = GLFW_KEY_4;
    inline static constexpr int Key_5 = GLFW_KEY_5;
    inline static constexpr int Key_6 = GLFW_KEY_6;
    inline static constexpr int Key_7 = GLFW_KEY_7;
    inline static constexpr int Key_8 = GLFW_KEY_8;
    inline static constexpr int Key_9 = GLFW_KEY_9;

    inline static constexpr int Key_Semicolon     = GLFW_KEY_SEMICOLON;
    inline static constexpr int Key_Equal         = GLFW_KEY_EQUAL;

    // Alphabet
    inline static constexpr int Key_A = GLFW_KEY_A;
    inline static constexpr int Key_B = GLFW_KEY_B;
    inline static constexpr int Key_C = GLFW_KEY_C;
    inline static constexpr int Key_D = GLFW_KEY_D;
    inline static constexpr int Key_E = GLFW_KEY_E;
    inline static constexpr int Key_F = GLFW_KEY_F;
    inline static constexpr int Key_G = GLFW_KEY_G;
    inline static constexpr int Key_H = GLFW_KEY_H;
    inline static constexpr int Key_I = GLFW_KEY_I;
    inline static constexpr int Key_J = GLFW_KEY_J;
    inline static constexpr int Key_K = GLFW_KEY_K;
    inline static constexpr int Key_L = GLFW_KEY_L;
    inline static constexpr int Key_M = GLFW_KEY_M;
    inline static constexpr int Key_N = GLFW_KEY_N;
    inline static constexpr int Key_O = GLFW_KEY_O;
    inline static constexpr int Key_P = GLFW_KEY_P;
    inline static constexpr int Key_Q = GLFW_KEY_Q;
    inline static constexpr int Key_R = GLFW_KEY_R;
    inline static constexpr int Key_S = GLFW_KEY_S;
    inline static constexpr int Key_T = GLFW_KEY_T;
    inline static constexpr int Key_U = GLFW_KEY_U;
    inline static constexpr int Key_V = GLFW_KEY_V;
    inline static constexpr int Key_W = GLFW_KEY_W;
    inline static constexpr int Key_X = GLFW_KEY_X;
    inline static constexpr int Key_Y = GLFW_KEY_Y;
    inline static constexpr int Key_Z = GLFW_KEY_Z;

    inline static constexpr int Key_LeftBracket  = GLFW_KEY_LEFT_BRACKET;
    inline static constexpr int Key_Backslash    = GLFW_KEY_BACKSLASH;
    inline static constexpr int Key_RightBracket = GLFW_KEY_RIGHT_BRACKET;
    inline static constexpr int Key_GraveAccent  = GLFW_KEY_GRAVE_ACCENT;

    inline static constexpr int Key_World1 = GLFW_KEY_WORLD_1;
    inline static constexpr int Key_World2 = GLFW_KEY_WORLD_2;

    // Control keys
    inline static constexpr int Key_Escape       = GLFW_KEY_ESCAPE;
    inline static constexpr int Key_Enter        = GLFW_KEY_ENTER;
    inline static constexpr int Key_Tab          = GLFW_KEY_TAB;
    inline static constexpr int Key_Backspace    = GLFW_KEY_BACKSPACE;
    inline static constexpr int Key_Insert       = GLFW_KEY_INSERT;
    inline static constexpr int Key_Delete       = GLFW_KEY_DELETE;

    // Arrow keys
    inline static constexpr int Key_Right        = GLFW_KEY_RIGHT;
    inline static constexpr int Key_Left         = GLFW_KEY_LEFT;
    inline static constexpr int Key_Down         = GLFW_KEY_DOWN;
    inline static constexpr int Key_Up           = GLFW_KEY_UP;

    // Navigation keys
    inline static constexpr int Key_PageUp       = GLFW_KEY_PAGE_UP;
    inline static constexpr int Key_PageDown     = GLFW_KEY_PAGE_DOWN;
    inline static constexpr int Key_Home         = GLFW_KEY_HOME;
    inline static constexpr int Key_End          = GLFW_KEY_END;

    // Lock keys
    inline static constexpr int Key_CapsLock     = GLFW_KEY_CAPS_LOCK;
    inline static constexpr int Key_ScrollLock   = GLFW_KEY_SCROLL_LOCK;
    inline static constexpr int Key_NumLock      = GLFW_KEY_NUM_LOCK;

    inline static constexpr int Key_PrintScreen  = GLFW_KEY_PRINT_SCREEN;
    inline static constexpr int Key_Pause        = GLFW_KEY_PAUSE;

    // Function keys
    inline static constexpr int Key_F1  = GLFW_KEY_F1;
    inline static constexpr int Key_F2  = GLFW_KEY_F2;
    inline static constexpr int Key_F3  = GLFW_KEY_F3;
    inline static constexpr int Key_F4  = GLFW_KEY_F4;
    inline static constexpr int Key_F5  = GLFW_KEY_F5;
    inline static constexpr int Key_F6  = GLFW_KEY_F6;
    inline static constexpr int Key_F7  = GLFW_KEY_F7;
    inline static constexpr int Key_F8  = GLFW_KEY_F8;
    inline static constexpr int Key_F9  = GLFW_KEY_F9;
    inline static constexpr int Key_F10 = GLFW_KEY_F10;
    inline static constexpr int Key_F11 = GLFW_KEY_F11;
    inline static constexpr int Key_F12 = GLFW_KEY_F12;
    inline static constexpr int Key_F13 = GLFW_KEY_F13;
    inline static constexpr int Key_F14 = GLFW_KEY_F14;
    inline static constexpr int Key_F15 = GLFW_KEY_F15;
    inline static constexpr int Key_F16 = GLFW_KEY_F16;
    inline static constexpr int Key_F17 = GLFW_KEY_F17;
    inline static constexpr int Key_F18 = GLFW_KEY_F18;
    inline static constexpr int Key_F19 = GLFW_KEY_F19;
    inline static constexpr int Key_F20 = GLFW_KEY_F20;
    inline static constexpr int Key_F21 = GLFW_KEY_F21;
    inline static constexpr int Key_F22 = GLFW_KEY_F22;
    inline static constexpr int Key_F23 = GLFW_KEY_F23;
    inline static constexpr int Key_F24 = GLFW_KEY_F24;
    inline static constexpr int Key_F25 = GLFW_KEY_F25;

    // Keypad
    inline static constexpr int Key_KP_0       = GLFW_KEY_KP_0;
    inline static constexpr int Key_KP_1       = GLFW_KEY_KP_1;
    inline static constexpr int Key_KP_2       = GLFW_KEY_KP_2;
    inline static constexpr int Key_KP_3       = GLFW_KEY_KP_3;
    inline static constexpr int Key_KP_4       = GLFW_KEY_KP_4;
    inline static constexpr int Key_KP_5       = GLFW_KEY_KP_5;
    inline static constexpr int Key_KP_6       = GLFW_KEY_KP_6;
    inline static constexpr int Key_KP_7       = GLFW_KEY_KP_7;
    inline static constexpr int Key_KP_8       = GLFW_KEY_KP_8;
    inline static constexpr int Key_KP_9       = GLFW_KEY_KP_9;

    inline static constexpr int Key_KP_Decimal  = GLFW_KEY_KP_DECIMAL;
    inline static constexpr int Key_KP_Divide   = GLFW_KEY_KP_DIVIDE;
    inline static constexpr int Key_KP_Multiply = GLFW_KEY_KP_MULTIPLY;
    inline static constexpr int Key_KP_Subtract = GLFW_KEY_KP_SUBTRACT;
    inline static constexpr int Key_KP_Add      = GLFW_KEY_KP_ADD;
    inline static constexpr int Key_KP_Enter    = GLFW_KEY_KP_ENTER;
    inline static constexpr int Key_KP_Equal    = GLFW_KEY_KP_EQUAL;

    // Modifier keys
    inline static constexpr int Key_LeftShift    = GLFW_KEY_LEFT_SHIFT;
    inline static constexpr int Key_LeftControl  = GLFW_KEY_LEFT_CONTROL;
    inline static constexpr int Key_LeftAlt      = GLFW_KEY_LEFT_ALT;
    inline static constexpr int Key_LeftSuper    = GLFW_KEY_LEFT_SUPER;

    inline static constexpr int Key_RightShift   = GLFW_KEY_RIGHT_SHIFT;
    inline static constexpr int Key_RightControl = GLFW_KEY_RIGHT_CONTROL;
    inline static constexpr int Key_RightAlt     = GLFW_KEY_RIGHT_ALT;
    inline static constexpr int Key_RightSuper   = GLFW_KEY_RIGHT_SUPER;

    inline static constexpr int Key_Menu         = GLFW_KEY_MENU;

    // Mouse buttons
    inline static constexpr int Mouse_Left   = GLFW_MOUSE_BUTTON_LEFT;
    inline static constexpr int Mouse_Right  = GLFW_MOUSE_BUTTON_RIGHT;
    inline static constexpr int Mouse_Middle = GLFW_MOUSE_BUTTON_MIDDLE;
    inline static constexpr int Mouse_4      = GLFW_MOUSE_BUTTON_4;
    inline static constexpr int Mouse_5      = GLFW_MOUSE_BUTTON_5;
    inline static constexpr int Mouse_6      = GLFW_MOUSE_BUTTON_6;
    inline static constexpr int Mouse_7      = GLFW_MOUSE_BUTTON_7;
    inline static constexpr int Mouse_8      = GLFW_MOUSE_BUTTON_8;

    // Keyboard / Mouse Actions
    inline static constexpr int On_Key_Press    = GLFW_PRESS;
    inline static constexpr int On_Key_Release  = GLFW_RELEASE;
    inline static constexpr int On_Key_Repeat   = GLFW_REPEAT;

    // Input States
    inline static constexpr int Press   = GLFW_PRESS;
    inline static constexpr int Release = GLFW_RELEASE;
    inline static constexpr int Repeat  = GLFW_REPEAT;
};