#pragma once

#include <Arduino.h>

class EspNowSender
{
public:

    bool begin();

    bool send(
        const void *data,
        size_t size);

    bool scanChannels();
    bool needChannelScan();
};

extern EspNowSender ESPNOW;