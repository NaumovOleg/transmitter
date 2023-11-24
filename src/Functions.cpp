#include <Arduino.h>
#include <Functions.h>

void HandleButtonPress(Button button, byte &value) {
  if (button.release()) {
    value = value ? 0 : 1;
  }
}

void initDefaultData(TransmitterData &data) {
  data.throttle = 0;
  data.yaw = 127;
  data.pitch = 127;
  data.roll = 127;
  data.AUX1 = 0;
  data.AUX2 = 0;
}

int mapJoystickValues(int val, int lower, int middle, int upper, bool reverse) {
  if (val < middle)
    val = map(val, lower, middle, 0, 128);
  else
    val = map(val, middle, upper, 128, 255);

  return (reverse ? 255 - val : val);
}

void logData(TransmitterData data) {
  Serial.print(data.throttle);
  Serial.print("---");
  Serial.print(data.yaw);
  Serial.print("---");
  Serial.print(data.pitch);
  Serial.print("---");
  Serial.print(data.roll);
  Serial.print("---");
  Serial.print(data.AUX1);
  Serial.print("----");
  Serial.println(data.AUX2);
}