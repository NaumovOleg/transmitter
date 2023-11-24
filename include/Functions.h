#ifndef DECLARATIONS_H_
#define DECLARATIONS_H_

#include <Arduino.h>
#include <EncButton.h>

const uint64_t pipeOut = 0xF0F1F2F3F4LL;

struct TransmitterData {
  byte throttle;
  byte yaw;
  byte pitch;
  byte roll;
  byte AUX1;
  byte AUX2;
};

void initDefaultData(TransmitterData &data);
int mapJoystickValues(int val, int lower, int middle, int upper, bool reverse);
void HandleButtonPress(Button button, byte &value);
void logData(TransmitterData data);
#endif