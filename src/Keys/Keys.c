// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#include "Keys.h"
#include "pico/stdlib.h"
#include "tusb.h"

#include "keymap.h"
#include "../usb_descriptors.h"
#include "../util.h"

static int8_t currentLayer;

void initKeys() {
    // Set Pull up resistors for key GPIOs
    gpio_pull_up(ROT_BTN);
    gpio_pull_up(KEY1);
    gpio_pull_up(KEY2);
    gpio_pull_up(KEY3);
    gpio_pull_up(KEY4);
    gpio_pull_up(KEY5);
    gpio_pull_up(KEY6);
    gpio_pull_up(KEY7);
    gpio_pull_up(KEY8);
    gpio_pull_up(KEY9);
    gpio_pull_up(KEY10);
    gpio_pull_up(KEY11);
    gpio_pull_up(KEY12);

    currentLayer = 0;
}

void sendKeyboardReport() {
    hid_keyboard_report_t keyState = {0};
    static bool hasSentMacro = false;

    if (!gpio_get(ROT_BTN)) {
        memcpy(
            &keyState,
            &layers[currentLayer].macros[ROT_BTN],
            sizeof(hid_keyboard_report_t));
    }
    else if (!gpio_get(KEY1)) {
        memcpy(
            &keyState, 
            &layers[currentLayer].macros[KEY1],
            sizeof(hid_keyboard_report_t));
    }
    else if (!gpio_get(KEY2)) {
        memcpy(
            &keyState, 
            &layers[currentLayer].macros[KEY2],
            sizeof(hid_keyboard_report_t));
    }
    else if (!gpio_get(KEY3)) {
        memcpy(
            &keyState, 
            &layers[currentLayer].macros[KEY3],
            sizeof(hid_keyboard_report_t));
    }
    else if (!gpio_get(KEY4)) {
        memcpy(
            &keyState, 
            &layers[currentLayer].macros[KEY4],
            sizeof(hid_keyboard_report_t));
    }
    else if (!gpio_get(KEY5)) {
        memcpy(
            &keyState, 
            &layers[currentLayer].macros[KEY5],
            sizeof(hid_keyboard_report_t));
    }
    else if (!gpio_get(KEY6)) {
        memcpy(
            &keyState, 
            &layers[currentLayer].macros[KEY6],
            sizeof(hid_keyboard_report_t));
    }
    else if (!gpio_get(KEY7)) {
        memcpy(
            &keyState, 
            &layers[currentLayer].macros[KEY7],
            sizeof(hid_keyboard_report_t));
    }
    else if (!gpio_get(KEY8)) {
        memcpy(
            &keyState, 
            &layers[currentLayer].macros[KEY8],
            sizeof(hid_keyboard_report_t));
    }
    else if (!gpio_get(KEY9)) {
        memcpy(
            &keyState, 
            &layers[currentLayer].macros[KEY9],
            sizeof(hid_keyboard_report_t));
    }
    else if (!gpio_get(KEY10)) {
        memcpy(
            &keyState, 
            &layers[currentLayer].macros[KEY10],
            sizeof(hid_keyboard_report_t));
    }
    else if (!gpio_get(KEY11)) {
        memcpy(
            &keyState, 
            &layers[currentLayer].macros[KEY11],
            sizeof(hid_keyboard_report_t));
    }
    else if (!gpio_get(KEY12)) {
        memcpy(
            &keyState, 
            &layers[currentLayer].macros[KEY12],
            sizeof(hid_keyboard_report_t));
    }

    if (keyState.modifier != 0 || keyState.keycode[0] != 0) {
        tud_hid_keyboard_report(
            REPORT_ID_KEYBOARD,
            keyState.modifier,
            keyState.keycode);

        hasSentMacro = true;
    }
    else if (hasSentMacro) {
        // Send empty key report if previously has key pressed
        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
        hasSentMacro = false;
    }
}

void updateCurrentLayer(int amount) {
    currentLayer += amount;
    currentLayer %= NUM_LAYERS;
}