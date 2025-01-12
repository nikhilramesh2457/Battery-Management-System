#include <cmath>
#include <Arduino.h>

#include "constants.h"
#include "switching.h"

/**
 * Toggle set of switches to start charging given battery
 * @param batteryNumber (int): Battery Number to charge
 **/
void Switching::startChargingBattery(int batteryNumber) {

  // Safety Check
  if (batteryNumber < BATTERY_01 || batteryNumber > BATTERY_17) {
    return;
  }

  byte panelNumber = panelSwitchingLogic(batteryNumber);

  // Disconnect the panel from battery set before switching
  disconnectPanelLine(panelNumber);

  // Small delay to ensure complete switching
  delay(1000);

  // Toggle the relay switches for the battery
  int relayLogicValue = batterySwitchingLogic(batteryNumber);
  Serial.print(relayLogicValue);
  Serial.print(" > ");
  Serial.print(String(int(relayLogicValue % 2)) + String(int(relayLogicValue / 2) % 2) + String(int(relayLogicValue / 4) % 2));

  // Set the relay bits on the GPIO
  // TODO: Invert the logic for relays here
  digitalWrite(batteryControlPins[panelNumber][2], !bool(int(relayLogicValue % 2)));
  digitalWrite(batteryControlPins[panelNumber][1], !bool(int(relayLogicValue / 2) % 2));
  if(batteryControlPins[panelNumber][1] == 25 && bool(int(relayLogicValue / 2) % 2)){
    analogWrite(25, 255);
  }
  digitalWrite(batteryControlPins[panelNumber][0], !bool(int(relayLogicValue / 4) % 2));

  // Small delay to ensure complete switching
  delay(1000);

  // Connect the Panel to the battery set
  connectPanelLine(panelSwitchingLogic(batteryNumber));
}

/**
 * Toggle set of switches to stop charging given battery
 * @param batteryNumber (int): Battery Number to charge
 **/
void Switching::stopChargingBattery(int batteryNumber) {
  disconnectPanelLine(panelSwitchingLogic(batteryNumber));
}

/**
 * Disconnect panel from battery sets
 * @param lineNumber (int): Panel to completely disconnect 
 **/
void Switching::disconnectPanelLine(int lineNumber) {
  if (lineNumber < PANEL_1 || lineNumber > PANEL_4) {
    return;
  }
  digitalWrite(panelControlPins[lineNumber], HIGH);
}

/**
 * Connect Panel to battery set
 * @param lineNumber (int): Panel to completely disconnect 
 **/
void Switching::connectPanelLine(int lineNumber) {
  if (lineNumber < PANEL_1 || lineNumber > PANEL_4) {
    return;
  }
  // TODO: Invert the logic here for relays
  digitalWrite(panelControlPins[lineNumber], LOW);
  // Serial.println("Connecting Panel: " + String(lineNumber));
}

/**
 * Relays to toggle to charge the selected battery
 * @param batteryNumber (int): Battery to charge
 * @return (int): relay toggling Number
 **/
int Switching::batterySwitchingLogic(int batteryNumber) {
  if (batteryNumber == BATTERY_17) {
    return 4;
  } else if (batteryNumber < BATTERY_17 && batteryNumber >= BATTERY_01) {
    return batteryNumber % 4;
  }
  return -1;
}

/**
 * Get the Panel Number to switch for the given battery
 * @param batteryNumber (int): BatteryNumber for the panel
 * @return (int): Panel connected to the battery
 **/
int Switching::panelSwitchingLogic(int batteryNumber) {
  if (batteryNumber == BATTERY_17) {
    return PANEL_4;
  } else if (batteryNumber < BATTERY_17 && batteryNumber >= BATTERY_01) {
    return int(ceil(batteryNumber / 4));
  }
  return -1;
}