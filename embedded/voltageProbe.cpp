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
    return volt * GAIN_RATIO_1 - prevSeriesLinkVoltage;
  }
  if (batteryNumber == BATTERY_02) {
    return volt * GAIN_RATIO_2 - prevSeriesLinkVoltage;
  }
  if (batteryNumber == BATTERY_03) {
    return volt * GAIN_RATIO_3 - prevSeriesLinkVoltage;
  }
  if (batteryNumber == BATTERY_04) {
    return volt * GAIN_RATIO_4 - prevSeriesLinkVoltage;
  }
  if (batteryNumber == BATTERY_05) {
    return volt * GAIN_RATIO_5 - prevSeriesLinkVoltage;
  }
  if (batteryNumber == BATTERY_06) {
    return volt * GAIN_RATIO_6 - prevSeriesLinkVoltage;
  }
  if (batteryNumber == BATTERY_07) {
    return volt * GAIN_RATIO_7 - prevSeriesLinkVoltage;
  }
  if (batteryNumber == BATTERY_08) {
    return volt * GAIN_RATIO_8 - prevSeriesLinkVoltage;
  }
  if (batteryNumber == BATTERY_09) {
    return volt * GAIN_RATIO_9 - prevSeriesLinkVoltage;
  }
  if (batteryNumber == BATTERY_10) {
    return volt * GAIN_RATIO_10 - prevSeriesLinkVoltage;
  }
  if (batteryNumber == BATTERY_11) {
    return volt * GAIN_RATIO_11 - prevSeriesLinkVoltage;
  }
  if (batteryNumber == BATTERY_12) {
    return volt * GAIN_RATIO_12 - prevSeriesLinkVoltage;
  }
  if (batteryNumber == BATTERY_13) {
    return volt * GAIN_RATIO_13 - prevSeriesLinkVoltage;
  }
  if (batteryNumber == BATTERY_14) {
    return volt * GAIN_RATIO_14 - prevSeriesLinkVoltage;
  }
  if (batteryNumber == BATTERY_15) {
    return volt * GAIN_RATIO_15 - prevSeriesLinkVoltage;
  }
  if (batteryNumber == BATTERY_16) {
    return volt * GAIN_RATIO_16 - prevSeriesLinkVoltage;
  }
  if (batteryNumber == BATTERY_17) {
    return volt * GAIN_RATIO_17 - prevSeriesLinkVoltage;
  }
  return -1;
  }

/**
 * Get raw voltage reading from Resistor Bridge
 * @param batteryNumber (int): Battery Index
 * @return (int) raw ADC Battery Voltage Reading
 **/
float VoltageProbe::readVoltage(int batteryNumber) {
  if (batteryNumber > BATTERY_17 || batteryNumber < BATTERY_01) {
    return 0;
  }

  else if (batteryNumber == BATTERY_17) {
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

  // Serial.print("Binary bits: ");
  // Serial.print(!bool(int(line2Select % 2)));
  // Serial.print(!bool(int(line2Select / 2) % 2));
  // Serial.print(!bool(int(line2Select / 4) % 2));
  // Serial.println(!bool(int(line2Select / 8) % 2));

  digitalWrite(selectLines[0], !bool(line2Select % 2));
  digitalWrite(selectLines[1], !bool(int(line2Select / 2) % 2));
  digitalWrite(selectLines[2], !bool(int(line2Select / 4) % 2));
  digitalWrite(selectLines[3], !bool(int(line2Select / 8) % 2));

  // Delay to switch the MUX and establish connection
  delay(1000);

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
    delay(1);
  }

  return sum / NO_SAMPLES;
}