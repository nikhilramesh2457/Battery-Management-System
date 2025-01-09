#include "constants.h"
#include "network.h"
#include "switching.h"
#include "voltageProbe.h"

Network net;
Switching s;
VoltageProbe probe;

float batteryVoltages[] = {};

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

  // Connect to the network
  net.connect();

  Serial.println("Ready...");
}

void loop() {
  // if (Serial.available() > 0) {
  // int x = Serial.parseInt();
  //   float voltage = (probe.readVoltage(battery) / 4095) * 3.3;
  //   Serial.print("Battery: ");
  //   Serial.print(battery);
  //   Serial.print(" @ ");
  //   Serial.print(voltage);
  //   Serial.print(" : ");
  //   Serial.println(probe.calcVoltage(voltage, battery));
  //   delay(1000);
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

  for (int x = 0; x < 17; x++) {
    float voltage = (probe.readVoltage(x) / 4095) * 3.3;
    float calc_voltage = probe.calcVoltage(voltage, x);
    net.logger(String("Battery") + String(x) + ":" + String(calc_voltage) + "->" + String(voltage));
    net.logBatteryVoltage(x, calc_voltage, 0);
    delay(100);
  }
  // }
}
