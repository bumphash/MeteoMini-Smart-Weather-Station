#include "SCD41Sensor.h"

#include <Wire.h>
#include <SensirionI2cScd4x.h>

static SensirionI2cScd4x scd4x;

SCD41Sensor SCD41;

bool SCD41Sensor::begin()
{
    Wire.beginTransmission(0x62);

    if(Wire.endTransmission() != 0)
    {
        Serial.println("SCD41 not found");

        m_ready = false;

        return false;
    }

    scd4x.begin(Wire, 0x62);

    int16_t error;

    error = scd4x.stopPeriodicMeasurement();

    delay(500);

    error = scd4x.startPeriodicMeasurement();

    m_ready = (error == 0);

    if(m_ready)
    {
        Serial.println("SCD41 detected");
    }
    else
    {
        Serial.println("SCD41 initialization failed");
    }

    return m_ready;
}

void SCD41Sensor::update()
{
    if(!m_ready)
    {
        return;
    }

    int16_t error;

    bool ready = false;

    error = scd4x.getDataReadyStatus(ready);

    if(error)
    {
        return;
    }

    if(!ready)
    {
        return;
    }

    error = scd4x.readMeasurement(
        m_co2,
        m_temperature,
        m_humidity);

    if(error)
    {
        return;
    }
}

uint16_t SCD41Sensor::co2()
{
    return m_co2;
}

float SCD41Sensor::temperature()
{
    return m_temperature;
}

float SCD41Sensor::humidity()
{
    return m_humidity;
}

bool SCD41Sensor::isReady() const
{
    return m_ready;
}