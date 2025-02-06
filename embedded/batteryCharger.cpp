#include <Arduino.h>

#include "constants.h"
#include "batteryCharger.h"

/**
 * return information for battery charging instruction (in int* batteryCharging) based on battery voltages (float* batteryVoltages).
 * @return bit field for change in panel usage. (bit = 1 as a sign of a required change in panel usage, bit = 0 for no change needed)
 **/
int BatteryCharger::batteryChargingController(){
  int retVal = 0;
    // pass through all pannels to check for charging requirement
  for (int i = 0; i < 4; i++){
    float lowestBatVol = MAX_BATTERY_VOLTAGE;
    int lowestBatNo = -1;
    // check if any of the batteries are currently being charged
    //if the chosen panel is not charging any battery
    if (batteryCharging[i] == -1){
      //iterate through all batteries of current pannel.
      for (int j = 0; j < (i == 4? 5:4); j++){
        if (batteryVoltages[4*i + j] < lowestBatVol){
          lowestBatVol = batteryVoltages[4*i + j];
          lowestBatNo = 4*i + j;
          #ifdef __SERIAL_DEBUG__
          Serial.println("entered low voltage battery detected");
            // Serial.print("lowestBatNo & lowestBatVol : ");
            // Serial.print(lowestBatNo);
            // Serial.print(" : ");
            // Serial.println(lowestBatVol);
          #endif
        }
      }
      #ifdef __SERIAL_DEBUG__
        Serial.print("lowestBatNo & lowestBatVol : ");
        Serial.print(lowestBatNo);
        Serial.print(" : ");
        Serial.println(lowestBatVol);
      #endif
      batteryCharging[i] = lowestBatNo;
      // raise flag for need of a change in charge state in case a battery with low battery voltage is detected
      if (lowestBatNo != -1)
        retVal = retVal | (1 << i);
      #ifdef __SERIAL_DEBUG__
        Serial.print("retVal after checking (lowestBatNo ! == -1) =");
        Serial.println(retVal);
      #endif
    }

    // if the pannel is charging a battery
    else{
      // chack if battery is flly charged
      if(batteryVoltages[batteryCharging[i]] >= MAX_BATTERY_VOLTAGE){
        batteryCharging[i] = -1;
        // raise flag for change in charge state in case the battery is fully charged.
        retVal = retVal & (1 << i);
      }
    }
  }
  #ifdef __SERIAL_DEBUG__
    Serial.print("retVal =");
    Serial.println(retVal);
  #endif
  return retVal;
}