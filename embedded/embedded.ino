#include "constants.h"
#include "network.h"
#include "switching.h"
#include "voltageProbe.h"
#include "batteryCharger.h"
#include "adcLUT.h"

Network net;
Switching s;
VoltageProbe probe;
BatteryCharger charger;
AdcLUT Adc(10);

int loopCount = 0;

//stores all battery voltages
float batteryVoltages[17];
//stores the battery number being charged by all 4 panels. (-1) for no battery charged
int batteryCharging[4] = {-1, -1, -1, -1};

void setup() {
  Serial.begin(115200, SERIAL_8N1);
  delay(1000);
  Serial.end();
  Serial.begin(115200, SERIAL_8N1);

  // Set GPIO Direction
  for (int x = 0; x < 4; x++) {
    pinMode(selectLines[x], OUTPUT);
    digitalWrite(selectLines[x], LOW);
  }

  // GPIO Direction for Battery Relays
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 3; y++) {
      if (x != 3 && y == 0) {
        continue;
      }
      Serial.println("Configuring GPIO:" + String(batteryControlPins[x][y]));
      pinMode(batteryControlPins[x][y], OUTPUT);
      digitalWrite(batteryControlPins[x][y], HIGH);
    }
  }

  // GPIO Direction for Panel Relays
  for (int x = 0; x < 4; x++) {
    pinMode(panelControlPins[x], OUTPUT);
    digitalWrite(panelControlPins[x], HIGH);
  }

  pinMode(READ_MUX, INPUT);
  pinMode(READ_BATTERY_17_PIN, INPUT);

  // Set Analog Sampling Configuration
  analogSetAttenuation(ADC_11db);
  analogSetWidth(10);
  analogReadResolution(10);

  // Connect to the network
  //net.connect();
#ifdef __TEST_RELAY_GPIO__
  Serial.println("Ready...");
  for(int x = 0; x < 17; x++){
    s.startChargingBattery(x);
    s.stopChargingBattery(x);
  }
#endif
}

void loop() {

/*
  while(true){
    net.logBatteryVoltage(1, 1.0, true);
  }
*/

  // if (Serial.available() > 0) {
  //   int x = Serial.parseInt();
  //   //   float voltage = (probe.readVoltage(battery) / 4095) * 3.3;
  //   //   Serial.print("Battery: ");
  //   //   Serial.print(battery);
  //   //   Serial.print(" @ ");
  //   //   Serial.print(voltage);
  //   //   Serial.print(" : ");
  //   //   Serial.println(probe.calcVoltage(voltage, battery));
  //   //   delay(1000);
  //   s.startChargingBattery(x);
  // }
  // }
  // delay(1000);

  // net.logBatteryVoltage(random(0, 17), random(10, 14.4), random(0, 1));
  // net.logPanelUsage(random(0, 4), random(0, 1));
  // for (int x = 0; x < 17; x++) {
  // Serial.print(x);
  // Serial.print(":");
  // s.startChargingBattery(x);
  // Serial.print("-");
  // Serial.println(s.panelSwitchingLogic(x));
  // delay(1000);

  // for(int x = 0;x < 17; x ++){
  //   s.startChargingBattery(x);
  //   delay(1000);
  //   s.stopChargingBattery(x);
  //   delay(1000);
  // }

  //below code is cpommented out to test new loop code with battery charger algorithm
/*
  for (int x = 0; x < 17; x++) {
    float v = probe.readVoltage(x);
    float voltage = ( v / 1024) * 3.3;
    float calcVoltage = probe.calcVoltage(voltage, x, 0);

    net.logger("Battery" + String(x) + ":" + String(voltage) + "=" + String(calcVoltage) + "=" + String(v), LOG_LEVEL_DEBUG);

    s.startChargingBattery(x);

    net.logBatteryVoltage(x, calcVoltage, 1);
    delay(5000);
    s.stopChargingBattery(x);
    net.logBatteryVoltage(x, calcVoltage, 0);
    //delay(1000);
  }
*/
  // read all battery voltages
  float voltageSum = 0;
  for (int x = 0; x < 17; x++) {
    float v = probe.readVoltage(x);
    float voltage = ( v / (1024)) * 3.3;
    #ifdef __SERIAL_DEBUG__
      Serial.println("*************************************");
      Serial.print("ADC voltage before compensation : ");
      Serial.println(voltage);
    #endif
    voltage = (voltage < 2.75? voltage + ADC_COMPENSATION:voltage);
    #ifdef __SERIAL_DEBUG__
      Serial.print("ADC voltage after compensation : ");
      Serial.println(voltage);
    #endif
    batteryVoltages[x] = probe.calcVoltage(voltage, x, voltageSum);
    voltageSum += batteryVoltages[x];

    #ifdef __SERIAL_DEBUG__
      Serial.print("Battery : ");
      Serial.println(x);
      Serial.print("ADC Voltage : ");
      Serial.println(voltage);
      Serial.print("battery voltage : ");
      Serial.println(batteryVoltages[x]);
      Serial.print("Bus voltage : ");
      Serial.println(voltageSum);
    #endif
    // s.startChargingBattery(x);
    // delay(500);
    // s.stopChargingBattery(x);

    //net.logger("Battery" + String(x) + ":" + String(voltage) + "=" + String(batteryVoltages[x]) + "=" + String(v), LOG_LEVEL_DEBUG);
  }
  #ifdef __SERIAL_DEBUGGER__
    Serial.println("*************************************");
  #endif

  loopCount++;

  // test if charging stopps after exceeding MAX_BATTERY_VOLTAGE
/*
  batteryVoltages[3] = loopCount > 1? 14:batteryVoltages[3];
  batteryVoltages[4] = loopCount > 1? 14:batteryVoltages[4];
  batteryVoltages[8] = loopCount > 1? 14:batteryVoltages[8];
  batteryVoltages[15] = loopCount > 1? 14:batteryVoltages[15];
*/
  // check for need to change panel and battery connections
  int chargerInstruction = charger.batteryChargingController();
  #ifdef __SERIAL_DEBUG__
    Serial.print("charger instruction = ");
    Serial.println(chargerInstruction);
  #endif
  // service change in panel and battery connections if need rises
  if (chargerInstruction > 0){
    for(int i = 0; i < 4; i++){
      #ifdef __SERIAL_DEBUG__
        Serial.println("panel iter");
      #endif
      if ((chargerInstruction & (0b1 << i)) > 0){
        #ifdef __SERIAL_DEBUG__
          Serial.println(i);
        #endif
        // check if charging is to be stopped
        if (batteryCharging[i] == -1){
          #ifdef __SERIAL_DEBUG__
            Serial.println("stop charging!");
          #endif
          s.stopChargingBattery(i);
          for(int j = 0; j < (i == 3? 5:4); j++){
            net.logBatteryVoltage((4*i + j), batteryVoltages[4*i + j], LOW);
          }
          net.logPanelUsage(i, LOW);
        }
        // battery has to be charged
        else{
          #ifdef __SERIAL_DEBUG__
            Serial.println("Start Charging!");
          #endif
          s.startChargingBattery(batteryCharging[i]);
          net.logBatteryVoltage(batteryCharging[i], batteryVoltages[batteryCharging[i]], true);
          net.logPanelUsage(i, HIGH);
        }
      }
    }
  }
  delay(1000);
}