// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#include "LampArray.h"
#include "LampArrayHidStructs.h"
#include "Neopixel.h"
#include "../util.h"
#include "tusb.h"
#include "../Keys/keymap.h"

static uint16_t currentLampId = 0;

uint16_t GetLampArrayAttributesReport(uint8_t* buffer) {
    LampArrayAttributesReport report = {
        LAMPARRAY_LAMP_COUNT,
        LAMPARRAY_WIDTH,
        LAMPARRAY_HEIGHT,
        LAMPARRAY_DEPTH,
        LAMPARRAY_KIND,
        LAMPARRAY_UPDATE_INTERVAL
    };

    memcpy(buffer, &report, sizeof(LampArrayAttributesReport));

    return sizeof(LampArrayAttributesReport);
}

uint16_t GetLampAttributesReport(uint8_t* buffer) {
    LampAttributesResponseReport report = {
        currentLampId,                                          // LampId
        LampPositions[currentLampId],                           // Lamp position               
        LAMPARRAY_UPDATE_INTERVAL,                              // Lamp update interval
        LAMP_PURPOSE_CONTROL,                                   // Lamp purpose
        255,                                                    // Red level count
        255,                                                    // Blue level count
        255,                                                    // Green level count
        1,                                                      // Intensity
        1,                                                      // Is Programmable
        layers[0].macros[LampIdToKey(currentLampId)].keycode[0] // InputBinding
    };

    memcpy(buffer, &report, sizeof(LampAttributesResponseReport));
    currentLampId = currentLampId + 1 >= LAMPARRAY_LAMP_COUNT ?  currentLampId : currentLampId + 1;

    return sizeof(LampAttributesResponseReport);
}

void SetLampAttributesId(const uint8_t* buffer) {
    LampAttributesRequestReport* report = (LampAttributesRequestReport*) buffer;
    currentLampId = report->lampId;
}

void SetMultipleLamps(const uint8_t* buffer) {
    LampMultiUpdateReport* report = (LampMultiUpdateReport*) buffer;

    for (int i = 0; i < report->lampCount; i++) {
        NeopixelSetColor(report->lampIds[i], report->colors[i]);
    }
}

void SetLampRange(const uint8_t* buffer) {
    LampRangeUpdateReport* report = (LampRangeUpdateReport*) buffer;
    NeopixelSetColorRange(report->lampIdStart, report->lampIdEnd, report->color);
}

void SetAutonomousMode(const uint8_t* buffer) {
    LampArrayControlReport* report = (LampArrayControlReport*) buffer;
    NeopixelSetEffect(report->autonomousMode ? AUTONOMOUS_LIGHTING_EFFECT : HID, AUTONOMOUS_LIGHTING_COLOR);
}
