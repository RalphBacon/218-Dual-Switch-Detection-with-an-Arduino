#include "Arduino.h"

// Define the two switches that are closed when the fridge or freezer door is opened
#define FRIDGE 6
#define FREEZER 7

// Just for fun an LED to show when a door is open
#define LED 13

// SETUP    SETUP   SETUP   SETUP   SETUP
void setup() {
  // Debugging window
  Serial.begin(115200);

  // Declare the door switches as INPUT with pullups so they don't float
  pinMode(FRIDGE, INPUT_PULLUP);
  pinMode(FREEZER, INPUT_PULLUP);

  // The LED is an OUTPUT and it must be OFF initially
  digitalWrite(LED, LOW);
  pinMode(LED, OUTPUT);

  Serial.println("Setup completed.");
}

// LOOP   LOOP    LOOP    LOOP    LOOP    LOOP
void loop() {
  // Read the state of BOTH door switches
  bool fridge_door_open = digitalRead(FRIDGE) == LOW;
  bool freezer_door_open = digitalRead(FREEZER) == LOW;

  // If EITHER door is open...
  if (fridge_door_open || freezer_door_open) {

    // Light up the LED as a warning that a door is open
    digitalWrite(LED, HIGH);

    // Whilst EITHER door remains open keep monitoring
    while (fridge_door_open || freezer_door_open) {
      if (fridge_door_open) Serial.println("FRIDGE OPEN");
      if (freezer_door_open) Serial.println("FREEZER OPEN");

      // Read those door switch states again
      fridge_door_open = digitalRead(FRIDGE) == LOW;
      freezer_door_open = digitalRead(FREEZER) == LOW;

      // Just for this demo, slow things down a bit
      delay(100);
    }

    // No door is open so turn off the LED, all done
    digitalWrite(LED, LOW);
    Serial.println("All doors closed\n");
  }
}
