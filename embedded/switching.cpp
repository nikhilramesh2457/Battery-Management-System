#include <cmath>
#include <Arduino.h>

#include "constants.h"
#include "switching.h"

/**
 * Toggle set of switches to start charging given battery
 * @param batteryNumber (int): Battery Number to charge
 **/
void Switching::startChargingBattery(int batteryNumber) {
  // Connect the Panel to the battery set
  connectPanelLine(panelSwitchingLogic(batteryNumber));

  // Toggle the relay switches for the battery
  int relayLogicValue = batterySwitchingLogic(batteryNumber);
  Serial.print(relayLogicValue);
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
  
}

/**
 * Connect Panel to battery set
 * @param lineNumber (int): Panel to completely disconnect 
 **/
void Switching::connectPanelLine(int lineNumber) {

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