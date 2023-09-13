#ifndef KEYMAP_H
#define KEYMAP_H

#include "tusb.h"

typedef struct {
    hid_keyboard_report_t macros[13];
} MacroLayer;

static const MacroLayer layers[] = {
    // Layer 0
    {{
        {KEYBOARD_MODIFIER_LEFTGUI, 0, {0, 0, 0, 0, 0, 0}},                         // Rotary Encoder
        {0, 0,                         {HID_KEY_7, 0, 0, 0, 0, 0}},                 // Key 1
        {0, 0,                         {HID_KEY_8, 0, 0, 0, 0, 0}},                 // Key 2
        {0, 0,                         {HID_KEY_9, 0, 0, 0, 0, 0}},                 // Key 3
        {0, 0,                         {HID_KEY_4, 0, 0, 0, 0, 0}},                 // Key 4
        {0, 0,                         {HID_KEY_5, 0, 0, 0, 0, 0}},                 // Key 5
        {0, 0,                         {HID_KEY_6, 0, 0, 0, 0, 0}},                 // Key 6
        {0, 0,                         {HID_KEY_1, 0, 0, 0, 0, 0}},                 // Key 7
        {0, 0,                         {HID_KEY_2, 0, 0, 0, 0, 0}},                 // Key 8
        {0, 0,                         {HID_KEY_3, 0, 0, 0, 0, 0}},                 // Key 9
        {0, 0,                         {HID_KEY_KEYPAD_DECIMAL, 0, 0, 0, 0, 0}},    // Key 10
        {0, 0,                         {HID_KEY_0, 0, 0, 0, 0, 0}},                 // Key 11
        {0, 0,                         {HID_KEY_KEYPAD_ENTER, 0, 0, 0, 0, 0}}       // Key 12
    }},
    // Layer 1
    {{
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}
    }}
};

#define NUM_LAYERS sizeof(layers)/sizeof(MacroLayer)

#endif