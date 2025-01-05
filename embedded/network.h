#include <Arduino.h>

#ifndef __NETWORK_H
#define __NETWORK_H

// WiFi Connection Timeout in milliseconds
#define NETWORK_CONNECT_TIMEOUT 10000

class Network {

public:
  // Connect to the network & setup
  int connect();

  // Log Panel Usage
  int logPanelUsage(int panelNumber, bool inUse);

  // Log Battery Voltage
  int logBatteryVoltage(int batteryNumber, float voltage, bool charging);
};

static const char* ssid = "muS";
static const char* pswd = "1qaz2wsx3edc4rfv";

static const String serverIp = "http://192.168.133.24:8080";

#endif