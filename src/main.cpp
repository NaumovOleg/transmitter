#include <Arduino.h>
#include <EncButton.h>
#include <RF24.h>
#include <SPI.h>
#include <nRF24L01.h>

// const uint64_t pipeOut = 0xE8E8F0F0E1LL;
const uint64_t pipeOut = 0xF0F1F2F3F4LL;
RF24 radio(9, 8);
Button AUX1button(6);
Button AUX2button(7);
byte isAux1Clicked = 0;
byte isAux2Clicked = 0;

// The sizeof this struct should not exceed 32 bytes
// This gives us up to 32 8 bits channals
struct MyData {
  byte throttle;
  byte yaw;
  byte pitch;
  byte roll;
  byte AUX1;
  byte AUX2;
  byte BTN1;
  byte BTN2;
};

MyData data;

void resetData() {
  data.throttle = 0;
  data.yaw = 127;
  data.pitch = 127;
  data.roll = 127;
  data.AUX1 = 0;
  data.AUX2 = 0;
}

void setup() {
  radio.begin();
  radio.setAutoAck(false);
  radio.setChannel(95);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_HIGH);
  radio.openWritingPipe(pipeOut);
  resetData();
}

int mapJoystickValues(int val, int lower, int middle, int upper, bool reverse) {
  val = constrain(val, lower, upper);
  if (val < middle)
    val = map(val, lower, middle, 0, 128);
  else
    val = map(val, middle, upper, 128, 255);
  return (reverse ? 255 - val : val);
}

void AuxButtonHandler() {
  if (AUX1button.release()) {
    isAux1Clicked = isAux1Clicked ? 0 : 1;
  }
  if (AUX2button.release()) {
    isAux2Clicked = isAux2Clicked ? 0 : 1;
  }
}

void loop() {

  AUX1button.tick();
  AUX2button.tick();
  AuxButtonHandler();

  data.throttle = mapJoystickValues(analogRead(A3), 0, 516, 1023, true);
  data.yaw = mapJoystickValues(analogRead(A4), 0, 516, 1023, true);
  data.pitch = mapJoystickValues(analogRead(A2), 0, 522, 1023, true);
  data.roll = mapJoystickValues(analogRead(A1), 0, 506, 1023, true);
  data.AUX1 = isAux1Clicked;
  data.AUX2 = isAux2Clicked;
  data.BTN1 = digitalRead(2);
  data.BTN2 = digitalRead(3);

  radio.write(&data, sizeof(MyData));
}