#include <Control_Surface.h>

USBMIDI_Interface usbmidi;

// ---- Config ----
const uint8_t PULSE_MS = 20;  // 15–30 ms typical

// Pins (COM -> GND, NO -> pin)
const uint8_t PINS[2] = {9, 10};

// CC addresses (Channel 1), using raw numbers to avoid fromRaw()
MIDIAddress CC_ADDRS[2] = {
  {20, Channel_1},  // D9  -> CC20
  {21, Channel_1},  // D10 -> CC21
};

bool lastPressed[2] = {false, false};

static inline void pulseCC(const MIDIAddress &addr) {
  usbmidi.sendControlChange(addr, 127);
  delay(PULSE_MS);
  usbmidi.sendControlChange(addr, 0);
}

void setup() {
  Control_Surface.begin();
  for (uint8_t i = 0; i < 2; ++i) {
    pinMode(PINS[i], INPUT_PULLUP);  // internal pull-up; LOW when pressed
  }
}

void loop() {
  Control_Surface.loop();

  for (uint8_t i = 0; i < 2; ++i) {
    bool pressed = (digitalRead(PINS[i]) == LOW);
    if (pressed && !lastPressed[i]) {
      // rising edge -> one-shot CC pulse
      pulseCC(CC_ADDRS[i]);
    }
    lastPressed[i] = pressed;
  }
}
