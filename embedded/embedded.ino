#include "constants.h"
#include "network.h"
#include "switching.h"
#include "voltageProbe.h"

Network net;
Switching s;
VoltageProbe probe;

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
  net.connect();

  Serial.println("Ready...");
}

void loop() {
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
    delay(1000);
  }
}
// }
