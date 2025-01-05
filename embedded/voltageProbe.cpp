#include <Arduino.h>

#include "constants.h"
#include "voltageProbe.h"

/**
 * Function from Arduino WMath.cpp modified to work for floating point number
**/
float VoltageProbe::map_f(double value, double fromLow, double fromHigh, double toLow, double toHigh) {
  return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}

/**
* Function to calculate battery voltage from resistor bridge voltages
* @param volt (int): Voltage reading from the resistor bridge
* @param batteryNumber (int): Battery Number
* @return (float) Battery Voltage
**/

float VoltageProbe::calcVoltage(float volt, int batteryNumber) {
  if (batteryNumber == 0) {
    return (map_f(volt, 1.72, 2.48, 10, 14.4));
  }
  if (batteryNumber == 1) {
    return (map_f(volt, 1.89, 2.72, 10, 14.4));
  }
  if (batteryNumber == 2) {
    return (map_f(volt, 1.95, 2.81, 10, 14.4));
  }
  if (batteryNumber == 3) {
    return (map_f(volt, 1.98, 2.85, 10, 14.4));
  }
  if (batteryNumber == 4) {
    return (map_f(volt, 2.00, 2.88, 10, 14.4));
  }
  if (batteryNumber == 5) {
    return (map_f(volt, 2.01, 2.90, 10, 14.4));
  }
  if (batteryNumber == 6) {
    return (map_f(volt, 2.02, 2.91, 10, 14.4));
  }
  if (batteryNumber == 7) {
    return (map_f(volt, 2.03, 2.92, 10, 14.4));
  }
  if (batteryNumber == 8) {
    return (map_f(volt, 2.04, 2.93, 10, 14.4));
  }
  if (batteryNumber == 9) {
    return (map_f(volt, 2.04, 2.94, 10, 14.4));
  }
  if (batteryNumber == 10) {
    return (map_f(volt, 2.04, 2.94, 10, 14.4));
  }
  if (batteryNumber == 11) {
    return (map_f(volt, 2.05, 2.95, 10, 14.4));
  }
  if (batteryNumber == 12) {
    return (map_f(volt, 2.05, 2.95, 10, 14.4));
  }
  if (batteryNumber == 13) {
    return (map_f(volt, 2.05, 2.96, 10, 14.4));
  }
  if (batteryNumber == 14) {
    return (map_f(volt, 2.05, 2.96, 10, 14.4));
  }
  if (batteryNumber == 15) {
    return (map_f(volt, 2.06, 2.96, 10, 14.4));
  }
  if (batteryNumber == 16) {
    return (map_f(volt, 2.06, 2.96, 10, 14.4));
  }
  return -1;
}

/**
 * Get raw voltage reading from Resistor Bridge
 * @param batteryNumber (int): Battery Index
 * @return (int) raw ADC Battery Voltage Reading
 **/
float VoltageProbe::readVoltage(int batteryNumber) {
  if (batteryNumber > 17 || batteryNumber < 0) {
    return 0;
  }

  else if (batteryNumber == 17) {
    return analogRead(READ_BATTERY_17_PIN);
  }

  setMux(batteryNumber);
  return analogRead(READ_MUX);
}


/** 
 * Set the Mux Select line to the channel
 * @param line2Select(int): Channel to select
 * @return (int): -1 on error, 0 otherwise
 **/
int VoltageProbe::setMux(int line2Select) {
  if (line2Select < 0 || line2Select > 15) {
    return -1;
  }

  Serial.print("Binary bits: ");
  Serial.print(int(line2Select % 2));
  Serial.print(int(line2Select / 2) % 2);
  Serial.print(int(line2Select / 4) % 2);
  Serial.println(int(line2Select / 8) % 2);

  digitalWrite(selectLines[0], line2Select % 2);
  digitalWrite(selectLines[1], int(line2Select / 2) % 2);
  digitalWrite(selectLines[2], int(line2Select / 4) % 2);
  digitalWrite(selectLines[3], int(line2Select / 8) % 2);

  return 0;
}