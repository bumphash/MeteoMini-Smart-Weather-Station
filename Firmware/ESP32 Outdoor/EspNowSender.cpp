#include "EspNowSender.h"
#include <esp_wifi.h>
#include <WiFi.h>
#include <esp_now.h>
#include <Preferences.h>

static Preferences prefs;

volatile bool lastSendSuccess = false;
volatile uint8_t failCounter = 0;

static void onSent(
    const wifi_tx_info_t *tx_info,
    esp_now_send_status_t status)
{
    Serial.print("Send status: ");

    if (status == ESP_NOW_SEND_SUCCESS)
{
    lastSendSuccess = true;
    failCounter = 0;

    Serial.println("SUCCESS");
}
else
{
    lastSendSuccess = false;

    if (failCounter < 255)
        failCounter++;

    Serial.println("FAIL");
}
}

EspNowSender ESPNOW;

static uint8_t receiverMac[] =
{
    0xB0, 0xCB, 0xD8, 0xCE, 0xF2, 0x44
};

bool EspNowSender::begin()
{

    prefs.begin("espnow", false);

uint8_t savedChannel =
    prefs.getUChar("channel", 1);

Serial.print("Saved channel: ");
Serial.println(savedChannel);
    Serial.println("1");

    WiFi.mode(WIFI_STA);

    Serial.println("2");

    delay(1000);

    Serial.println("3");

    Serial.print("Sender MAC: ");
    Serial.println(WiFi.macAddress());

    Serial.println("4");

    esp_wifi_set_promiscuous(true);
esp_wifi_set_channel(
    savedChannel,
    WIFI_SECOND_CHAN_NONE);
esp_wifi_set_promiscuous(false);

    if (esp_now_init() != ESP_OK)
    {
        Serial.println("ESP-NOW init failed");
        return false;
    }

    Serial.println("5");

    esp_now_register_send_cb(onSent);

    Serial.println("6");

    esp_now_peer_info_t peerInfo = {};

    Serial.println("7");

    memcpy(peerInfo.peer_addr, receiverMac, 6);

    Serial.println("8");

    peerInfo.channel = savedChannel;
    peerInfo.encrypt = false;

    Serial.println("9");

    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        Serial.println("Peer add failed");
        return false;
    }

    Serial.println("10");

    return true;
}

bool EspNowSender::send(const void *data, size_t size)
{
    esp_err_t result =
        esp_now_send(
            receiverMac,
            (const uint8_t *)data,
            size);

    return result == ESP_OK;
}

bool EspNowSender::scanChannels()
{
    Serial.println("Channel scan started");

    for(uint8_t ch = 1; ch <= 13; ch++)
    {
        Serial.print("Try channel ");
        Serial.println(ch);

        esp_wifi_set_promiscuous(true);
        esp_wifi_set_channel(
            ch,
            WIFI_SECOND_CHAN_NONE);
        esp_wifi_set_promiscuous(false);

        esp_now_del_peer(receiverMac);

esp_now_peer_info_t peerInfo = {};

memcpy(peerInfo.peer_addr,
       receiverMac,
       6);

peerInfo.channel = ch;
peerInfo.encrypt = false;

esp_now_add_peer(&peerInfo);

        lastSendSuccess = false;

esp_now_send(
    receiverMac,
    (uint8_t*)"PING",
    4);

uint32_t start = millis();

while (!lastSendSuccess &&
       millis() - start < 1000)
{
    delay(10);
}

        if(lastSendSuccess)
        {
            prefs.putUChar(
                "channel",
                ch);

            Serial.print("Found channel: ");
            Serial.println(ch);

            failCounter = 0;

            return true;
        }
    }

    Serial.println("Channel not found");

    return false;
}

bool EspNowSender::needChannelScan()
{
    return failCounter >= 10;
}