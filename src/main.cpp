#include <Arduino.h>
#include <EncButton.h>
#include <Functions.h>
#include <RF24.h>
#include <SPI.h>
#include <nRF24L01.h>

RF24 radio(9, 8);
Button AUX1button(6);
Button AUX2button(7);

TransmitterData data;

void setup() {
  Serial.begin(9600);
  Serial.println("Start");
  radio.begin();
  radio.setAutoAck(false);
  radio.setChannel(95);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_HIGH);
  radio.openWritingPipe(pipeOut);
  initDefaultData(data);
}

void loop() {

  AUX1button.tick();
  AUX2button.tick();

  data.throttle = mapJoystickValues(analogRead(A3), 0, 515, 1020, true);
  data.yaw = mapJoystickValues(analogRead(A4), 0, 513, 1023, true);
  data.pitch = mapJoystickValues(analogRead(A2), 0, 522, 1023, true);
  data.roll = mapJoystickValues(analogRead(A1), 0, 505, 1023, true);
  HandleButtonPress(AUX1button, data.AUX1);
  HandleButtonPress(AUX2button, data.AUX2);

  logData(data);

  radio.write(&data, sizeof(TransmitterData));
}