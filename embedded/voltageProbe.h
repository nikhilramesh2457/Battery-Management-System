#include <Arduino.h>

#ifndef __PROBE_VOLTAGE_H
#define __PROBE_VOLTAGE_H

#define NO_SAMPLES 10

//Ratios of resistor bridges
#define ATTEN_RATIO_1 5.913461538
#define ATTEN_RATIO_2 10.84070796
#define ATTEN_RATIO_3 15.95652174
#define ATTEN_RATIO_4 21.98198198
#define ATTEN_RATIO_5 25.94017094
#define ATTEN_RATIO_6 31.29310345
#define ATTEN_RATIO_7 37.93721973
#define ATTEN_RATIO_8 83.44827586
#define ATTEN_RATIO_9 46.35193133
#define ATTEN_RATIO_10 122.6993865
#define ATTEN_RATIO_11 45.54794521
#define ATTEN_RATIO_12 56.80933852
#define ATTEN_RATIO_13 56.98924731
#define ATTEN_RATIO_14 0
#define ATTEN_RATIO_15 0
#define ATTEN_RATIO_16 0
#define ATTEN_RATIO_17 0

class VoltageProbe {

public:

  // Function to calculate battery voltage from resistor bridge voltages
  float calcVoltage(float volt, int batteryNumber, float prevSeriesLinkVoltage);

  //Get raw voltage reading from Resistor Bridge
  float readVoltage(int batteryNumber);

private:
  // Function from Arduino WMath.cpp modified to work for floating point number
  float map_f(double x, double in_min, double in_max, double out_min, double out_max);

  // Set the Mux Select line to the channel
  int setMux(int line2Select);

  // Sample ADC and average out the value
  float sampleAverage(int pinNumber);
};

#endif