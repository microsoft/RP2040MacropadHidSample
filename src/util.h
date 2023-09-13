#ifndef UTIL_H
#define UTIL_H

#include "Lighting/LampArrayHidStructs.h"

// Timing
#define LAMPARRAY_UPDATE_INTERVAL   10000                               // 10 ms update interval, in us
#define LAMP_UPDATE_RATE_MS         LAMPARRAY_UPDATE_INTERVAL / 1000
#define KEY_POLLING_RATE            10                                  // 10 ms polling rate

// Rotary Encoder
#define ROT_BTN                     0
#define ROTA                        17
#define ROTB                        18

// OLED
#define OLED_CS                     22
#define OLED_RESET                  23
#define OLED_DC                     24
#define OLED_SCLK                   26
#define OLED_MOSI                   27
#define OLED_MISO                   28

// Speaker
#define SPEAKER_SHUTDOWN            14
#define SPEAKER                     16

// Neopixel                         
#define NEOPIXEL                    19
#define NEOPIXEL_PIO                pio0
#define NEOPIXEL_BITRATE            800000
#define NEOPIXEL_COUNT              12

// LampArray Attributes
#define LAMPARRAY_LAMP_COUNT        NEOPIXEL_COUNT
#define LAMPARRAY_WIDTH             59000    // 5.9 cm 
#define LAMPARRAY_HEIGHT            104000   // 10.4 cm
#define LAMPARRAY_DEPTH             25000    // 2.5 cm (including rotary encoder)
#define LAMPARRAY_KIND              1        // LampArrayKindKeyboard

// Lamp Attributes
static Position LampPositions[NEOPIXEL_COUNT] = {
    {10500, 30000, 0}, {29500, 30000, 0}, {48500, 30000, 0}, 
    {10500, 49500, 0}, {29500, 49500, 0}, {48500, 49500, 0}, 
    {10500, 69000, 0}, {29500, 69000, 0}, {48500, 69000, 0}, 
    {10500, 88500, 0}, {29500, 88500, 0}, {48500, 88500, 0}
};

// Keys
#define KEY1                        1
#define KEY2                        2
#define KEY3                        3
#define KEY4                        4
#define KEY5                        5
#define KEY6                        6
#define KEY7                        7
#define KEY8                        8
#define KEY9                        9
#define KEY10                       10
#define KEY11                       11
#define KEY12                       12

inline uint16_t LampIdToKey(uint16_t lampId) {
    // Keys start at GPIO 1, whereas LampArray starts at 0
    if (lampId + 1 > LAMPARRAY_LAMP_COUNT) {
        return LAMPARRAY_LAMP_COUNT;
    }

    return lampId + 1;
}

#define KEY_STATE_MASK              (1 << KEY1) | (1 << KEY2)  | (1 << KEY3)  | (1 << KEY4) |\
                                    (1 << KEY5) | (1 << KEY6)  | (1 << KEY7)  | (1 << KEY8) |\
                                    (1 << KEY9) | (1 << KEY10) | (1 << KEY11) | (1 << KEY12)
#define MAX_KEYCODES                6

// Misc.
#define RED_LED                     13
#define AUTONOMOUS_LIGHTING_COLOR   (LampColor){0, 255, 0}
#define AUTONOMOUS_LIGHTING_EFFECT  BLINK

#endif