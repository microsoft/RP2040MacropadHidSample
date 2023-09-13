#include <stdio.h>
#include <stdlib.h>

#include "pico/binary_info.h"
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/gpio.h"
#include "tusb.h"

#include "usb_descriptors.h"
#include "util.h"
#include "Keys/Keys.h"
#include "Encoder/Encoder.h"
#include "Lighting/Neopixel.h"
#include "Lighting/LampArray.h"
#include "Lighting/LampArrayHidStructs.h"

// Functions
bool lightingTimerCallback(struct repeating_timer* t);
bool keyboardTimerCallback(struct repeating_timer* t);

int main() {
    stdio_init_all();
    tusb_init();
    initKeys();
    initEncoder();
    NeopixelInit(AUTONOMOUS_LIGHTING_EFFECT, AUTONOMOUS_LIGHTING_COLOR);
    
    struct repeating_timer lightingTimer;
    struct repeating_timer keyboardTimer;

    // Set up timer interrupts
    add_repeating_timer_ms(
        LAMP_UPDATE_RATE_MS,    // Output rate of LampArray HID device
        lightingTimerCallback,  // Callback to update LED state
        NULL,                   // Passed in callback data
        &lightingTimer);        // Timer object

    add_repeating_timer_ms(
        KEY_POLLING_RATE,       // Polling rate of GPIO pins
        keyboardTimerCallback,  // Callback to update pin state of GPIO outputs
        NULL,                   // No user data needed
        &keyboardTimer);        // Timer object

    while (1) { 
        tud_task();
    }

    cancel_repeating_timer(&lightingTimer);
    cancel_repeating_timer(&keyboardTimer);
    
    return 0;
}

//--------------------------------------------------------------------
// Timer Callbacks
//--------------------------------------------------------------------

bool lightingTimerCallback(struct repeating_timer* t) {
    NeopixelUpdateEffect();

    return true;
}

bool keyboardTimerCallback(struct repeating_timer *t) {
    // Remote wakeup
    if (tud_suspended()) {
        // Wake up host if we are in suspend mode
        // and REMOTE_WAKEUP feature is enabled by host
        tud_remote_wakeup();
    } 
    else if (tud_hid_ready()) {
        sendKeyboardReport();
    }

    return true;
}

//--------------------------------------------------------------------
// TinyUSB HID Callbacks
//--------------------------------------------------------------------

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(
        uint8_t instance,
        uint8_t report_id,
        hid_report_type_t report_type,
        uint8_t* buffer,
        uint16_t reqlen) {
    switch (report_id) {
        case REPORT_ID_LIGHTING_LAMP_ARRAY_ATTRIBUTES: {
            return GetLampArrayAttributesReport(buffer);
            break;
        }
        case REPORT_ID_LIGHTING_LAMP_ATTRIBUTES_RESPONSE: { 
            return GetLampAttributesReport(buffer);
            break;
        }
        default: {
            break;
        }
    }

    return 0;
}

// Invoked when recieved SET_REPORT control request or
// recieved data on OUT endpoint (Report ID = 0, Type = 0)
void tud_hid_set_report_cb(
        uint8_t instance,
        uint8_t report_id,
        hid_report_type_t report_type,
        uint8_t const* buffer,
        uint16_t bufsize) {
    switch (report_id) {
        case REPORT_ID_LIGHTING_LAMP_ATTRIBUTES_REQUEST: {
            SetLampAttributesId(buffer);
            break;
        }
        case REPORT_ID_LIGHTING_LAMP_MULTI_UPDATE: {
            SetMultipleLamps(buffer);
            break;   
        }
        case REPORT_ID_LIGHTING_LAMP_RANGE_UPDATE: {
            SetLampRange(buffer);
            break;   
        }
        case REPORT_ID_LIGHTING_LAMP_ARRAY_CONTROL: {
            SetAutonomousMode(buffer);
            break;
        }
        default: {
            break;
        }
    }
}

// Invoked when sent REPORT successfully to host
// Application can use this to send the next report
// Note: For composite reports, report[0] is report ID
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const* report, uint16_t len) {}

//--------------------------------------------------------------------
// TinyUSB Device callbacks
//--------------------------------------------------------------------

// Invoked when line state DTR & RTS are changed via SET_CONTROL_LINE_STATE e.g connected/disconnected
void tud_cdc_line_state_cb(uint8_t itf, bool dtr, bool rts) {}

// Invoked when device is mounted
void tud_mount_cb() {}

// Invoked when device is unmounted
void tud_unmount_cb() {}

// Invoked when USB bus is suspended
void tud_suspend_cb(bool remote_wakeup_en) {}

// Invoked when USB bus is resumed
void tud_resume_cb() {}