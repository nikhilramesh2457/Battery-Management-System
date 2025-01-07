#ifndef __CONSTANTS_H
#define __CONSTANTS_H

// Battery numbers
#define BATTERY_01 0
#define BATTERY_02 1
#define BATTERY_03 2
#define BATTERY_04 3
#define BATTERY_05 4
#define BATTERY_06 5
#define BATTERY_07 6
#define BATTERY_08 7
#define BATTERY_09 8
#define BATTERY_10 9
#define BATTERY_11 10
#define BATTERY_12 11
#define BATTERY_13 12
#define BATTERY_14 13
#define BATTERY_15 14
#define BATTERY_16 15
#define BATTERY_17 16

// Panel Numbers
#define PANEL_1 0
#define PANEL_2 1
#define PANEL_3 2
#define PANEL_4 3

// Mux Output ADC Pin
#define READ_MUX 35

// 16th Battery ADC Pin
#define READ_BATTERY_17_PIN 37

// Select lines 
const int selectLines[] = {25, 26, 27,14};

// Battery Relay Controller Pins
const int batteryControlPins[4][3] = {{-1, 5, 4}, {-1, 2, 32}, {-1, 13, 15}, {16, 17, 18}};

// Panel Relay Control Pins
const byte panelControlPins[] = {23, 22, 21, 19};

#endif