# MIDI Controller

A 6-button USB MIDI controller based on an ATmega32U4 using the Control Surface library.

## Requirements

- Arduino Pro Micro (ATmega32U4)
- Control Surface library by PieterP

Install the library using the Arduino IDE Library Manager before compiling.

## Pin Mapping

| Pin | MIDI CC |
|------|---------|
| D9 | CC20 |
| D10 | CC21 |
| D11 | CC22 |
| A0 | CC23 |
| A1 | CC24 |
| A2 | CC25 |

Buttons are wired between the input pin and GND using the internal pull-up resistors.
