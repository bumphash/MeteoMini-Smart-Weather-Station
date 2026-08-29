#include <Arduino.h>
#include <WiFi.h>
#include "OutdoorData.h"
#include "EspNowSender.h"
#include <Wire.h>
#include "BME680Sensor.h"
#include "SCD41Sensor.h"

static uint32_t timerSend = 0;

void setup()
{
    Serial.begin(115200);

    Wire.begin(21, 22);

    BME680.begin();
    SCD41.begin();

    if (!ESPNOW.begin())
    {
        while (true)
        {
            delay(100);
        }
    }
    Serial.print("Outdoor channel: ");
    Serial.println(WiFi.channel());
}

void loop()
{
    BME680.update();
    SCD41.update();
    Serial.print("SCD41 CO2: ");
    Serial.println(SCD41.co2());

    if (millis() - timerSend >= 5000)
    {
        timerSend = millis();

        OutdoorData data;

        data.temperature = BME680.temperature();
        data.humidity    = BME680.humidity();
        data.pressure    = BME680.pressure();
        data.gas         = BME680.gas();
        data.co2         = SCD41.co2();

        bool ok =
            ESPNOW.send(
                &data,
                sizeof(data));

        Serial.print("Send: ");
        Serial.println(ok ? "OK" : "FAIL");
    }

    if (ESPNOW.needChannelScan())
{
    ESPNOW.scanChannels();
}
}