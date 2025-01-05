#include <Arduino.h>

#ifndef __PROBE_VOLTAGE_H
#define __PROBE_VOLTAGE_H

class VoltageProbe {

public:

  // Function to calculate battery voltage from resistor bridge voltages
  float calcVoltage(float volt, int batteryNumber);

  //Get raw voltage reading from Resistor Bridge
  float readVoltage(int batteryNumber);

private:
  // Function from Arduino WMath.cpp modified to work for floating point number
  float map_f(double x, double in_min, double in_max, double out_min, double out_max);

  // Set the Mux Select line to the channel
  int setMux(int line2Select);
};

#endif