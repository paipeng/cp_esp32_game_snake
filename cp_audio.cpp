#include "cp_audio.h"
#include <Arduino.h>
#include <AsyncTimer.h>

CPAudio::CPAudio() {

}

void CPAudio::init() {
  pinMode(CP_BEEP_GPIO, OUTPUT);       // set ESP32 pin to output mode
}

void CPAudio::beep() {
  Serial.println("beep on");
  digitalWrite(CP_BEEP_GPIO, HIGH); // turn on
  AsyncTimer t;

  t.setTimeout([]() {
    Serial.println("beep off");
    digitalWrite(CP_BEEP_GPIO, LOW); // turn on
  }, 20);
}