#include "WiFi.h"
#include "ESP32NTPClient.h"

ESP32NTPClient::ESP32NTPClient(UDP& udp) {
  _client = new NTPClient(udp);
}

ESP32NTPClient::ESP32NTPClient(UDP& udp, long timeOffset) {
  _client = new NTPClient(udp, timeOffset);
}

ESP32NTPClient::ESP32NTPClient(UDP& udp, const char* poolServerName) {
  _client = new NTPClient(udp, poolServerName);
}

ESP32NTPClient::ESP32NTPClient(UDP& udp, const char* poolServerName, long timeOffset) {
  _client = new NTPClient(udp, poolServerName, timeOffset);
}

ESP32NTPClient::ESP32NTPClient(UDP& udp, const char* poolServerName, long timeOffset, unsigned long updateInterval) {
  _client = new NTPClient(udp, poolServerName, timeOffset, updateInterval);
}

ESP32NTPClient::~ESP32NTPClient() {
  _client->end();
  delete _client;
}

void ESP32NTPClient::task(){
     while(1){
        _client->update();
        vTaskDelay( _client->getUpdateInterval() );
     }
}

void ESP32NTPClient::startTaskImpl(void* _this){
    static_cast<ESP32NTPClient*>(_this)->task();
}
void ESP32NTPClient::start(){
  _status = true;
  _client->begin();
  xTaskCreatePinnedToCore(this->startTaskImpl, "NTP Update Task", 2048, this, 1, &_task, 0);
}

void ESP32NTPClient::stop() {
  _client->end();
  vTaskSuspend( _task );
  _status = false;
}

bool ESP32NTPClient::status() {
  return _status;
}

unsigned long ESP32NTPClient::getEpochTime() const {
  return _client->getEpochTime();
}

int ESP32NTPClient::getDay() const {
  return (((this->getEpochTime()  / 86400L) + 4 ) % 7); //0 is Sunday
}
int ESP32NTPClient::getHours() const {
  return ((this->getEpochTime()  % 86400L) / 3600);
}
int ESP32NTPClient::getMinutes() const {
  return ((this->getEpochTime() % 3600) / 60);
}
int ESP32NTPClient::getSeconds() const {
  return (this->getEpochTime() % 60);
}