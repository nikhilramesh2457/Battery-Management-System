#include<Arduino.h>

#ifndef __BATTERY_CHARGER_H
#define __BATTERY_CHARGER_H

#include "constants.h"
#include "network.h"
#include "switching.h"
#include "voltageProbe.h"

//stores all battery voltages
extern float batteryVoltages[17];
//stores the battery number being charged by all 4 panels. (-1) for no battery charged
extern int batteryCharging[4];

class BatteryCharger {

public:

  // Function for dictating all required battery switching based on battery voltages and current battery and panel relay connections.
  int batteryChargingController();

};

#endif