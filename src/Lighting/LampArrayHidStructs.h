// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#ifndef LAMP_ARRAY_HID_STRUCTS_H
#define LAMP_ARRAY_HID_STRUCTS_H

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue; 
    uint8_t intensity; 
} __attribute__((packed, aligned(1))) LampColor;

typedef struct {
    uint32_t x;
    uint32_t y;
    uint32_t z;
} __attribute__((packed, aligned(1))) Position;

typedef struct {
    uint16_t lampCount;
    
    uint32_t width;
    uint32_t height;
    uint32_t depth;

    uint32_t lampArrayKind;
    uint32_t minUpdateInterval;
} __attribute__((packed, aligned(1))) LampArrayAttributesReport;

typedef struct {
    uint16_t lampId;
} __attribute__((packed, aligned(1))) LampAttributesRequestReport;

#define LAMP_PURPOSE_CONTROL        0x01
#define LAMP_PURPOSE_ACCENT         0x02
#define LAMP_PURPOSE_BRANDING       0x04
#define LAMP_PURPOSE_STATUS         0x08
#define LAMP_PURPOSE_ILLUMINATION   0x10
#define LAMP_PURPOSE_PRESENTATION   0x20

typedef struct {
    uint16_t lampId;

    Position lampPosition;

    uint32_t updateLatency;
    uint32_t lampPurposes;

    uint8_t redLevelCount;
    uint8_t greenLevelCount;
    uint8_t blueLevelCount;
    uint8_t intensityLevelCount;

    uint8_t isProgrammable;
    uint8_t inputBinding;
} __attribute__((packed, aligned(1))) LampAttributesResponseReport;

typedef struct {
    uint8_t lampCount;
    uint8_t flags;
    uint16_t lampIds[8];

    LampColor colors[8];
} __attribute__((packed, aligned(1))) LampMultiUpdateReport;

typedef struct {
    uint8_t flags;
    uint16_t lampIdStart;
    uint16_t lampIdEnd;

    LampColor color;
} __attribute__((packed, aligned(1))) LampRangeUpdateReport;

typedef struct {
    uint8_t autonomousMode;
} __attribute__((packed, aligned(1))) LampArrayControlReport;

#endif