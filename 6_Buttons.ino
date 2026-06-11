#include <Control_Surface.h>

USBMIDI_Interface usbmidi;

// ---- Config ----
const uint8_t PULSE_MS = 20;      // Length of the MIDI CC pulse
const uint8_t DEBOUNCE_MS = 30;   // Prevents one button press being read multiple times

// Pins (COM -> GND, NO -> pin)
const uint8_t PINS[6] = {9, 10, 11, A0, A1, A2};

// CC addresses (Channel 1), using raw numbers to avoid fromRaw()
MIDIAddress CC_ADDRS[6] = {
  {20, Channel_1},  // D9  -> CC20
  {21, Channel_1},  // D10 -> CC21
  {22, Channel_1},  // D11 -> CC22
  {23, Channel_1},  // A0  -> CC23
  {24, Channel_1},  // A1  -> CC24
  {25, Channel_1},  // A2  -> CC25
};

bool lastPressed[6] = {false, false, false, false, false, false};
bool stablePressed[6] = {false, false, false, false, false, false};
unsigned long lastChangeTime[6] = {0, 0, 0, 0, 0, 0};

static inline void pulseCC(const MIDIAddress &addr) {
  usbmidi.sendControlChange(addr, 127);
  delay(PULSE_MS);
  usbmidi.sendControlChange(addr, 0);
}

void setup() {
  Control_Surface.begin();
  for (uint8_t i = 0; i < 6; ++i) {
    pinMode(PINS[i], INPUT_PULLUP);  // internal pull-up; LOW when pressed
  }
}

void loop() {
  Control_Surface.loop();

  for (uint8_t i = 0; i < 6; ++i) {
    bool reading = (digitalRead(PINS[i]) == LOW);

    // If the raw reading changed, restart the debounce timer.
    if (reading != lastPressed[i]) {
      lastChangeTime[i] = millis();
      lastPressed[i] = reading;
    }

    // Only accept the new state once it has stayed stable for DEBOUNCE_MS.
    if ((millis() - lastChangeTime[i]) > DEBOUNCE_MS && reading != stablePressed[i]) {
      stablePressed[i] = reading;

      // Button has just been pressed, so send one short CC pulse.
      if (stablePressed[i]) {
        pulseCC(CC_ADDRS[i]);
      }
    }
  }
}
