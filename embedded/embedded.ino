#include "constants.h"
#include "voltageProbe.h"

// VoltageProbe Object
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

  Serial.println("Ready...");
}

void loop() {
  if (Serial.available() > 0) {
    int battery = Serial.parseInt();
    float voltage = (probe.readVoltage(battery) / 4095) * 3.3;
    Serial.print("Battery: ");
    Serial.print(battery);
    Serial.print(" @ ");
    Serial.print(voltage);
    Serial.print(" : ");
    Serial.println(probe.calcVoltage(voltage, battery));
    delay(1000);
  }
  delay(1000);
}
