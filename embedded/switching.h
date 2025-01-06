#include <Arduino.h>

#ifndef __SWITCHING_H
#define __SWITCHING_H

class Switching {

public:
  // Start Charging Battery x
  void startChargingBattery(int batteryNumber);

  // Stop Charging Battery x
  void stopChargingBattery(int batteryNumber);

  // TODO: Remove this
  // Logic to toggle Panel Relays
  int panelSwitchingLogic(int batteryNumber);

private:
  // Logic to toggle Relays
  int batterySwitchingLogic(int batteryNumber);

  // // Logic to toggle Panel Relays
  // int panelSwitchingLogic(int batteryNumber);

  // Connect Panel to battery set
  void connectPanelLine(int lineNumber);

  // Disconnect panel from battery set
  void disconnectPanelLine(int lineNumber);
};

#endif