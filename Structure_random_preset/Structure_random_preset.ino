/*
 * Structure random MIDI preset switcher
 * by j4s0n 6-2-2021
 * 
 * - Adjust the 3 defines below to how you want them and upload to your Arduino
 * - On the Structure: Press "Actions" button, set the following...
 * -- BANK 1 : F6
 * -- BANK 2 : F#6
 * -- BANK 3 : G6
 * -- BANK 4 : G#6
 * -- Load PRESET 1 : C#-2
 * -- Load PRESET 2 : D-2
 * -- Load PRESET 3 : D#-2
 * -- Load PRESET 4 : E-2
 * -- Load PRESET 5 : F-2
 * -- Load PRESET 6 : F#-2
 * -- Load PRESET 7 : G-2
 * -- Load PRESET 8 : G#-2
 * -- Load PRESET 9 : A-2
 * -- Load PRESET 10 : A#-2
 * -- Load PRESET 11 : B-2
 * -- Load PRESET 12 : C-1
 * -- Load PRESET 13 : C#-1
 * -- Load PRESET 14 : D-1
 * -- Load PRESET 15 : D#-1
 * -- Load PRESET 16 : E-1
 *    (This is the same as BANK 1-4 = MIDI note #101-104, and PRESET 1-16 = MIDI note #1-16)
 * - Plug the Arduino into the Structure and walk away ;)
 */

#include "MIDIUSB.h"

#define banks 4 //how many banks to randomly switch through (1-4)
#define presets 16 //how many presets to randomly switch through (1-16)
#define switchTime 10 //how many seconds between random switch

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0) + analogRead(3));
}

void loop() {
  int randBank = random(banks) + 101;
  int randPreset = random(presets) + 1;
  
  noteOn(0, randBank, 127);
  noteOn(0, randPreset, 127);
  MidiUSB.flush();

  noteOff(0, randBank, 127);
  noteOff(0, randPreset, 127);
  MidiUSB.flush();

  delay(switchTime * 1000);
}
