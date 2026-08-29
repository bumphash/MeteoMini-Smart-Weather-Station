#pragma once

#include <Arduino.h>

struct OutdoorData
{
    float temperature;
    float humidity;
    float pressure;
    float gas;

    uint16_t co2;
};