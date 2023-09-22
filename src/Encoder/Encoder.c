// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#include "Encoder.h"
#include "pico/stdlib.h"
#include "../util.h"
#include "../Keys/Keys.h"
#include "../Keys/keymap.h"

// Temp?
#include "tusb.h"
#include "../usb_descriptors.h"

void onRisingEdge(uint gpio, uint32_t eventMask);

void initEncoder() {
    // Init encoder pins
    gpio_pull_up(ROTA);
    gpio_pull_up(ROTB);

    // Enable IRQ
    gpio_set_irq_enabled_with_callback(
        ROTA,
        GPIO_IRQ_EDGE_FALL,
        true,
        &onRisingEdge);
}

void onRisingEdge(uint gpio, uint32_t eventMask) {
    if (eventMask & GPIO_IRQ_EDGE_FALL) {
        hid_keyboard_report_t keyState = {0};
        if (gpio_get(ROTB)) {
            // Counter clockwise
            updateCurrentLayer(-1);
        }
        else {
            // Clockwise
            updateCurrentLayer(1);
        }
    }
}