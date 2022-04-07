#pragma once

#include "WiFi.h"
#include <NTPClient.h>
#include <WiFiUdp.h>

#ifndef ESP32NTPCLIENT_H
#define ESP32NTPCLIENT_H

#define NTP_SERVICE_STARTED true
#define NTP_SERVICE_STOPPED false

class ESP32NTPClient {
  public:
    ESP32NTPClient(UDP& udp);
    ESP32NTPClient(UDP& udp, long timeOffset);
    ESP32NTPClient(UDP& udp, const char* poolServerName);
    ESP32NTPClient(UDP& udp, const char* poolServerName, long timeOffset);
    ESP32NTPClient(UDP& udp, const char* poolServerName, long timeOffset, unsigned long updateInterval);

    ~ESP32NTPClient();

    void start();
    void stop();
    bool status();

    int getDay() const;
    int getHours() const;
    int getMinutes() const;
    int getSeconds() const;

    unsigned long getEpochTime() const;


  private:

    TaskHandle_t _task;

    NTPClient *_client;
    bool _status = 0;

    void task();
    static void startTaskImpl(void* _this);


};

#endif