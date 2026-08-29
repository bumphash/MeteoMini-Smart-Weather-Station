#include "BME680Sensor.h"

#include <Wire.h>
#include <Adafruit_BME680.h>

Adafruit_BME680 bme;

BME680Sensor BME680;

bool BME680Sensor::begin()
{
    Wire.beginTransmission(0x77);

    if(Wire.endTransmission() != 0)
    {
        Wire.beginTransmission(0x76);

        if(Wire.endTransmission() != 0)
        {
            Serial.println("BME680 not found");

            m_ready = false;

            return false;
        }
    }

    if(!bme.begin())
    {
        Serial.println("BME680 initialization failed");

        m_ready = false;

        return false;
    }

    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_2X);
    bme.setPressureOversampling(BME680_OS_4X);
    bme.setIIRFilterSize(BME680_FILTER_SIZE_3);

    m_ready = true;

    Serial.println("BME680 detected");

    return true;
}

void BME680Sensor::update()
{
    if(!m_ready)
{
    return;
}
    if (!bme.performReading())
        return;

    m_temperature = bme.temperature;

    m_humidity = bme.humidity;

    m_pressure = bme.pressure / 100.0;

    m_gas = bme.gas_resistance / 1000.0;
}

float BME680Sensor::temperature()
{
    return m_temperature;
}

float BME680Sensor::humidity()
{
    return m_humidity;
}

float BME680Sensor::pressure()
{
    return m_pressure;
}

float BME680Sensor::gas()
{
    return m_gas;
}

bool BME680Sensor::isReady() const
{
    return m_ready;
}