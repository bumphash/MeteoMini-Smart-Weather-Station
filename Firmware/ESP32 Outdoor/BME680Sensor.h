#pragma once
#include <Arduino.h>

class BME680Sensor
{
public:

    bool begin();

    void update();

    bool isReady() const;

    float temperature();

    float humidity();

    float pressure();

    float gas();

private:

    private:

    bool m_ready = false;

    float m_temperature = NAN;
    float m_humidity = NAN;
    float m_pressure = NAN;
    float m_gas = NAN;
};

extern BME680Sensor BME680;