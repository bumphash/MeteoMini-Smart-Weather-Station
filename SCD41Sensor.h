#pragma once

#include <Arduino.h>


class SCD41Sensor
{
public:

    bool begin();

    void update();

    bool isReady() const;

    uint16_t co2();

    float temperature();

    float humidity();

private:

    bool m_ready = false;

    uint16_t m_co2 = 0;

    float m_temperature = NAN;

    float m_humidity = NAN;
};

extern SCD41Sensor SCD41;