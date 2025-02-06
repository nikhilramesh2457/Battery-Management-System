#include <Arduino.h>

#include "constants.h"
#include "adcLUT.h"

/**
* Constructor for the LUT object
* @param AdcBitDepth (int): Bit depth of ADC used ( < 12)
**/
AdcLUT::AdcLUT(int AdcBitDepth){
  bitDepth = AdcBitDepth;
}


/**
* Function to provide a linearised output ADC read value based on the raw ADC read value
* @param AdcRead (int): Raw ADC read value
* @return (float): Linearised ADC value
**/
float AdcLUT::ADC_lineariser(int AdcRead){
  int indexScaler = 1 << (12 - AdcLUT::bitDepth);
  return AdcLUT::ADC_LUT[AdcRead * indexScaler] /(1 << (12 -  AdcLUT::bitDepth));
}