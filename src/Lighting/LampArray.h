#ifndef LAMP_ARRAY_H
#define LAMP_ARRAY_H

#include "pico/stdlib.h"
#include "LampArrayHidStructs.h"

// Get Reports
uint16_t GetLampArrayAttributesReport(uint8_t* buffer);
uint16_t GetLampAttributesReport(uint8_t* buffer);

// Set Reports
void SetLampAttributesId(const uint8_t* buffer);
void SetMultipleLamps(const uint8_t* buffer);
void SetLampRange(const uint8_t* buffer);
void SetAutonomousMode(const uint8_t* buffer);

#endif