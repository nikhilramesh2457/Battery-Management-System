#include "constants.h"
#include "network.h"
#include "voltageProbe.h"

Network net;
VoltageProbe probe;

void setup() {
  Serial.begin(115200, SERIAL_8N1);
  delay(1000);
  Serial.end();
  Serial.begin(115200, SERIAL_8N1);

  // Set GPIO Direction
  for (int x = 0; x < 4; x++) {
    pinMode(selectLines[x], OUTPUT);
  }

  pinMode(READ_MUX, INPUT);
  pinMode(READ_BATTERY_17_PIN, INPUT);

  // Connect to the network
  net.connect();

  Serial.println("Ready...");
}

void loop() {
  // if (Serial.available() > 0) {
  //   int battery = Serial.parseInt();
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

  net.logBatteryVoltage(random(0, 17), random(10, 14.4), random(0, 1));
  net.logPanelUsage(random(0, 4), random(0, 1));
  delay(7000);
}
