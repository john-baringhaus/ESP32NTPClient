#include <WiFi.h> 
#include <WiFiUdp.h>
#include <Update.h>
#include <WiFiManager.h> //https://github.com/tzapu/WiFiManager
#include "ESP32NTPClient.h"


WiFiUDP ntpUDP;

TaskHandle_t Task2;

WiFiManager wifiManager;

ESP32NTPClient ntp = ESP32NTPClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

void setup() {
  Serial.begin(115200);
  
  wifiManager.autoConnect("Lamp");
  wifiManager.setWiFiAutoReconnect(true);
  delay(1500);

  ntp.start();

  xTaskCreatePinnedToCore(Task2code, "Task2", 10000, NULL, 1, &Task2, 1);
  delay(500);
}


void Task2code(void* parameter) {

  for (;;) {
    Serial.printf("Task2 is running on core %d\n", xPortGetCoreID());
    
    Serial.println(ntp.getEpochTime());
    delay(5000);
  }
}

void loop() {
}