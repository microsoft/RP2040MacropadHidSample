#ifndef NEOPIXEL_H
#define NEOPIXEL_H

#include "pico/stdlib.h"
#include "LampArrayHidStructs.h"

typedef enum {
    HID,
    SOLID,
    BLINK
} NeopixelEffect;

void NeopixelInit(NeopixelEffect effect, LampColor initialEffectColor);
void NeopixelSetEffect(NeopixelEffect effect, LampColor effectColor);

void NeopixelSetColor(uint16_t lampId, LampColor lampColor);
void NeopixelSetColorRange(uint16_t lampIdStart, uint16_t lampIdEnd, LampColor lampColor);

void NeopixelSendColors();
void NeopixelUpdateEffect();


#endif