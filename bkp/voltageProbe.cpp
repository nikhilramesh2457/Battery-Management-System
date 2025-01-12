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
* @param prevSeriesLinkVoltage (float): Series Link Voltage until the previous Battery
* @return (float) Battery Voltage
**/
float VoltageProbe::calcVoltage(float volt, int batteryNumber, float prevSeriesLinkVoltage) {
  if (batteryNumber == BATTERY_01) {
    return (map_f(volt, 1.71, 2.39, 10 * BATTERY_01, 14.4 * BATTERY_01));
  }
  if (batteryNumber == BATTERY_02) {
    return (map_f(volt, 1.82, 2.55, 10 * BATTERY_02, 14.4 * BATTERY_02) - prevSeriesLinkVoltage);
  }
  if (batteryNumber == BATTERY_03) {
    return (map_f(volt, 1.92, 2.68, 10 * BATTERY_03, 14.4 * BATTERY_03) - prevSeriesLinkVoltage);
  }
  if (batteryNumber == BATTERY_04) {
    return (map_f(volt, 1.82, 2.54, 10 * BATTERY_04, 14.4 * BATTERY_04) - prevSeriesLinkVoltage);
  }
  if (batteryNumber == BATTERY_05) {
    return (map_f(volt, 1.93, 2.71, 10 * BATTERY_05, 14.4 * BATTERY_05) - prevSeriesLinkVoltage);
  }
  if (batteryNumber == BATTERY_06) {
    return (map_f(volt, 1.91, 2.68, 10 * BATTERY_06, 14.4 * BATTERY_06) - prevSeriesLinkVoltage);
  }
  if (batteryNumber == BATTERY_07) {
    return (map_f(volt, 1.83, 2.56, 10 * BATTERY_07, 14.4 * BATTERY_07) - prevSeriesLinkVoltage);
  }
  if (batteryNumber == BATTERY_08) {
    return (map_f(volt, 0.96, 1.35, 10 * BATTERY_08, 14.4 * BATTERY_08) - prevSeriesLinkVoltage);
  }
  if (batteryNumber == BATTERY_09) {
    return (map_f(volt, 1.93, 2.71, 10 * BATTERY_09, 14.4 * BATTERY_09) - prevSeriesLinkVoltage);
  }
  if (batteryNumber == BATTERY_10) {
    return (map_f(volt, 0.81, 1.14, 10 * BATTERY_10, 14.4 * BATTERY_10) - prevSeriesLinkVoltage);
  }
  if (batteryNumber == BATTERY_11) {
    return (map_f(volt, 2.42, 3.39, 10 * BATTERY_11, 14.4 * BATTERY_11) - prevSeriesLinkVoltage);
  }
  if (batteryNumber == BATTERY_12) {
    return (map_f(volt, 2.12, 2.97, 10 * BATTERY_12, 14.4 * BATTERY_12) - prevSeriesLinkVoltage);
  }
  if (batteryNumber == BATTERY_13) {
    return (map_f(volt, 2.30, 3.22, 10 * BATTERY_13, 14.4 * BATTERY_13) - prevSeriesLinkVoltage);
  }
  if (batteryNumber == BATTERY_14) {
    return (map_f(volt, 2.52, 3.53, 10 * BATTERY_14, 14.4 * BATTERY_14) - prevSeriesLinkVoltage);
  }
  if (batteryNumber == BATTERY_15) {
    return (map_f(volt, 2.61, 3.66, 10 * BATTERY_15, 14.4 * BATTERY_15) - prevSeriesLinkVoltage);
  }
  if (batteryNumber == BATTERY_16) {
    return (map_f(volt, 1.93, 2.70, 10 * BATTERY_16, 14.4 * BATTERY_16) - prevSeriesLinkVoltage);
  }
  if (batteryNumber == BATTERY_17) {
    return (map_f(volt, 2.42, 3.39, 10 * BATTERY_17, 14.4 * BATTERY_17) - prevSeriesLinkVoltage);
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
    return sampleAverage(READ_BATTERY_17_PIN);
  }

  setMux(batteryNumber);
  return sampleAverage(READ_MUX);
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
  Serial.print(!bool(int(line2Select % 2)));
  Serial.print(!bool(int(line2Select / 2) % 2));
  Serial.print(!bool(int(line2Select / 4) % 2));
  Serial.println(!bool(int(line2Select / 8) % 2));

  digitalWrite(selectLines[0], !bool(line2Select % 2));
  digitalWrite(selectLines[1], !bool(int(line2Select / 2) % 2));
  digitalWrite(selectLines[2], !bool(int(line2Select / 4) % 2));
  digitalWrite(selectLines[3], !bool(int(line2Select / 8) % 2));

  return 0;
}

/**
 * Sample the ADC Channel NO_SAMPLE times and average it out
 * @param pinNumber (int): ADC Pin to Channel
 * @return (float): Averaged out ADC Value
 **/
float VoltageProbe::sampleAverage(int pinNumber){
  long int sum = 0;
  for(int x = 0;x < NO_SAMPLES; x++){
    sum += analogRead(pinNumber);
  }

  return sum / NO_SAMPLES;
}