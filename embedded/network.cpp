#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFi.h>

#include "constants.h"
#include "network.h"

/**
 * Initialize networking peripherals and connect to the specified network
 * Autotime out to ensure program functionality does not stop, 10 seconds to connect
 * Will run repeatedly before every data logging
 */
int Network::connect() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Already Connected");
    return 0;
  }

  WiFi.begin(ssid, pswd);

  // Try connecting until NETWORK_CONNECT_TIMEOUT
  unsigned long startTime = millis();
  while ((WiFi.status() != WL_CONNECTED) && (millis() - startTime < NETWORK_CONNECT_TIMEOUT)) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("Device IP:");
    Serial.println(WiFi.localIP());
    return 0;
  }

  return -1;
}

/**
 * Log to server the status of the Solar Panels
 * @param panelNumber (int): Solar Panel Number
 * @param inUse (bool): If panel is used to charge the battery
 * @return (int): 0 on success, error otherwise
 **/
int Network::logPanelUsage(int panelNumber, bool inUse) {
  if (connect() == -1) {
    return -1;
  }

  HTTPClient client;

  // Perform the GET request to the Server
  client.begin((String(SERVER_IP) + "/logPanelUsage?panel_number=" + panelNumber + "&in_use=" + String(int(inUse))).c_str());
  int responseCode = client.GET();

  Serial.print("Reaponse code: ");
  Serial.println(responseCode);

  // Free resources
  client.end();

  return 0;
}


/**
 * Log to server the status of batteries
 * @param batteryNumber (int): Solar Panel Number
 * @param voltage (float): Current Battery Voltage
 * @param charging (bool): Is battery charging
 * @return (int): 0 on success, error otherwise
 **/
int Network::logBatteryVoltage(int batteryNumber, float voltage, bool charging) {
  if (connect() == -1) {
    return -1;
  }

  HTTPClient client;

  // Perform the GET request to the Server
  client.begin((String(SERVER_IP) + "/logBatteryState?battery_number=" + batteryNumber + "&voltage=" + String(voltage) + "&charging=" + String(int(charging))).c_str());
  Serial.println((String(SERVER_IP) + "/logBatteryState?battery_number=" + batteryNumber + "&voltage=" + String(voltage) + "&charging=" + String(int(charging))));
  int responseCode = client.GET();

  Serial.print("Response code: ");
  Serial.println(responseCode);

  // Free resources
  client.end();

  return 0;
}

/**
 * Send logs to the server for storing and monitoring
 * @param message (String): Message to log
 * @param level (int): Log Level (DEBUG, SUCCESS, WARN)
 **/
void Network::logger(String message, int level) {
  if (connect() == -1) {
    return;
  }

  Serial.println(String(SERVER_IP) + "/console_log?msg=" + message);

  Serial.print("5");


  HTTPClient client;
  Serial.print("6");

  if (level == LOG_LEVEL_SUCCESS){
    message += "&level=success";
  } else if (level == LOG_LEVEL_DEBUG){
    message += "&level=debug";
  } else if (level == LOG_LEVEL_WARNING){
    message += "&level=warn";
  } 

  // Perform the GET request to the Server
  client.begin(String(SERVER_IP) + "/console_log?msg=" + message);
  Serial.print("7");

  int responseCode = client.GET();
  Serial.print("8");

  Serial.print("Response code: ");
  Serial.println(responseCode);
  Serial.print("9");

  // Free resources
  client.end();

  Serial.print("0");
}