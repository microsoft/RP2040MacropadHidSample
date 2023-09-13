#include "Neopixel.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "neopixel.pio.h"

#include "../util.h"

static const uint8_t _NeoPixelSineTable[256] = {
    128, 131, 134, 137, 140, 143, 146, 149, 152, 155, 158, 162, 165, 167, 170,
    173, 176, 179, 182, 185, 188, 190, 193, 196, 198, 201, 203, 206, 208, 211,
    213, 215, 218, 220, 222, 224, 226, 228, 230, 232, 234, 235, 237, 238, 240,
    241, 243, 244, 245, 246, 248, 249, 250, 250, 251, 252, 253, 253, 254, 254,
    254, 255, 255, 255, 255, 255, 255, 255, 254, 254, 254, 253, 253, 252, 251,
    250, 250, 249, 248, 246, 245, 244, 243, 241, 240, 238, 237, 235, 234, 232,
    230, 228, 226, 224, 222, 220, 218, 215, 213, 211, 208, 206, 203, 201, 198,
    196, 193, 190, 188, 185, 182, 179, 176, 173, 170, 167, 165, 162, 158, 155,
    152, 149, 146, 143, 140, 137, 134, 131, 128, 124, 121, 118, 115, 112, 109,
    106, 103, 100, 97,  93,  90,  88,  85,  82,  79,  76,  73,  70,  67,  65,
    62,  59,  57,  54,  52,  49,  47,  44,  42,  40,  37,  35,  33,  31,  29,
    27,  25,  23,  21,  20,  18,  17,  15,  14,  12,  11,  10,  9,   7,   6,
    5,   5,   4,   3,   2,   2,   1,   1,   1,   0,   0,   0,   0,   0,   0,
    0,   1,   1,   1,   2,   2,   3,   4,   5,   5,   6,   7,   9,   10,  11,
    12,  14,  15,  17,  18,  20,  21,  23,  25,  27,  29,  31,  33,  35,  37,
    40,  42,  44,  47,  49,  52,  54,  57,  59,  62,  65,  67,  70,  73,  76,
    79,  82,  85,  88,  90,  93,  97,  100, 103, 106, 109, 112, 115, 118, 121,
    124};

typedef struct {
    uint sm;
    PIO pio;
    LampColor pixels[NEOPIXEL_COUNT];
    NeopixelEffect currentEffect;
    LampColor startingColor;
} NeopixelController;

static NeopixelController Controller;

void NeopixelInit(NeopixelEffect effect, LampColor initialEffectColor) {
    // Set effect also initializes pixels
    NeopixelSetEffect(effect, initialEffectColor);

    // Load program into PIO and choose state machine
    Controller.pio = NEOPIXEL_PIO;
    Controller.sm = pio_claim_unused_sm(Controller.pio, true);
    uint offset = pio_add_program(Controller.pio, &ws2812_program);
    
    // Init pins
    pio_gpio_init(Controller.pio, NEOPIXEL);
    pio_sm_set_consecutive_pindirs(Controller.pio, Controller.sm, NEOPIXEL, 1, true);

    // Set config values
    pio_sm_config config = ws2812_program_get_default_config(offset);
    sm_config_set_sideset_pins(&config, NEOPIXEL);
    sm_config_set_out_shift(&config, false, true, 24);
    sm_config_set_fifo_join(&config, PIO_FIFO_JOIN_TX);

    // Calculate and set clock divider
    int cyclesPerBit = ws2812_T1 + ws2812_T2 + ws2812_T3;
    float div = clock_get_hz(clk_sys) / (NEOPIXEL_BITRATE * cyclesPerBit);
    sm_config_set_clkdiv(&config, div);

    // Init state machine with config values and start
    pio_sm_init(Controller.pio, Controller.sm, offset, &config);
    pio_sm_set_enabled(Controller.pio, Controller.sm, true);
}

void NeopixelSetEffect(NeopixelEffect effect, LampColor effectColor) {
    Controller.currentEffect = effect;
    Controller.startingColor = effectColor;

    for (int i = 0; i < NEOPIXEL_COUNT; i++) {
        Controller.pixels[i] = effectColor;
    }
}

void NeopixelSetColor(uint16_t lampId, LampColor lampColor) {
    if (lampId >= NEOPIXEL_COUNT) {
        return;
    }

    Controller.pixels[lampId] = lampColor;
}

void NeopixelSetColorRange(uint16_t lampIdStart, uint16_t lampIdEnd, LampColor lampColor) {
    if (lampIdStart >= NEOPIXEL_COUNT) {
        return;
    }

    for (int i = lampIdStart; i <= lampIdEnd && i < NEOPIXEL_COUNT; i++) {
        NeopixelSetColor(i, lampColor);
    }
}

void NeopixelSendColors() {
    for (int i = 0; i < NEOPIXEL_COUNT; i++) {
        uint32_t grb_value = (Controller.pixels[i].green << 24) | 
                             (Controller.pixels[i].red << 16)   | 
                             (Controller.pixels[i].blue << 8);

        pio_sm_put_blocking(Controller.pio, Controller.sm, grb_value);
    }
}

void NeopixelSineWaveStep() {
    static uint8_t t = 0;

    for (int i = 0; i < NEOPIXEL_COUNT; i++) {
        uint16_t outputColor;

        outputColor = (Controller.startingColor.red * _NeoPixelSineTable[t]) >> 8;
        Controller.pixels[i].red = outputColor;

        outputColor = (Controller.startingColor.green * _NeoPixelSineTable[t]) >> 8;
        Controller.pixels[i].green = outputColor;

        outputColor = (Controller.startingColor.blue * _NeoPixelSineTable[t]) >> 8;
        Controller.pixels[i].blue = outputColor;
    }

    t++;
}

void NeopixelUpdateEffect() {
    if (Controller.currentEffect == BLINK) {
        NeopixelSineWaveStep();
    }

    NeopixelSendColors();
}
