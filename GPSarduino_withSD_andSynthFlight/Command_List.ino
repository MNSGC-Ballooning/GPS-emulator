bool stateChange = true;
bool ventHasBeenUsed = false;
void CommandRead(String command) {

  if (command.startsWith("ALT")) {
    command.remove(0, 3);
    HitAltf = command.toFloat();
    altCommand = true;
    Serial.println("BAD HIT SENT AT ALTITUDE: " + String( HitAltf));
  }
  else if (command.startsWith("START")) {
    emulationActive = true;
  }
  else if (command.startsWith("JUMP")) {
    command.remove(0, 4);
    altSynth = command.toFloat();
    Serial.println("ALTITUDE SET TO: " + String(altSynth));
  }
  else if (command.startsWith("RATE")) {
    command.remove(0, 4);
    CurrentRate = command.toFloat() * 3.281;
    Serial.println("LAST AVG RATE: " + String(CurrentRate)) + " ft/s";
  }

  else if (command.startsWith("VENT") &&  emulationActive == true) {
    command.remove(0, 4);

    if (command == "0" && stateChange == false) { ///vent is CLOSED
      ventState = false;
      Serial.println("VENT CLOSED");
      for (int i = 0; i < 15; i++) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(50);
        digitalWrite(LED_BUILTIN, LOW);
        delay(50);
      }
      digitalWrite(LED_BUILTIN, LOW);
      stateChange = true;

      if ( isLeaking == true) { //emulate fixing of leak when vent detects is and tries to jiggle the vent
        isLeaking = false;
        Serial.println("LEAK SEALED!");
      }
    }
    else if ( command == "1" && stateChange == true) { ///vent is OPEN
      ventState = true;
      Serial.println("VENT OPENED");
      ventHasBeenUsed = true;
      for (int i = 0; i < 15; i++) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(50);
        digitalWrite(LED_BUILTIN, LOW);
        delay(50);
      }
      digitalWrite(LED_BUILTIN, HIGH);
      stateChange = false;
    }

  }
  else if (command.startsWith("TERM")) {
    TerminationCheck = true;
    AltTerminatedAt = altSynth;
  }
  else if (command.startsWith("LEAK")) {
    isLeaking = true;
    Serial.println("Leak Begining!");
  }
  else if (command.startsWith("ASCENTRATE")) {   //command to set the mean ascent Rate mid flight
    command.remove(0, 10);
    meanAscentRateHold = meanAscentRate;
    meanAscentRate = command.toFloat();
    Serial.println("MEAN ASCENT RATE SET TO: " + String(meanAscentRate));
    Serial.println("VALUE OF HELD ASCENT RATE IS: " + String(meanAscentRateHold));
    meanAscentRateEnteredByUser = true;
  }
  else if (command.startsWith("SDSET")) {   //command to set the SD or 'noise'. set to zero if you want no noise during flight
    command.remove(0, 5);
    ascentRateSDHold = ascentRateSD;
    ascentRateSD = command.toFloat();
    Serial.println("STANDARD DEVIATION OF ASCENT RATE SET TO: " + String(ascentRateSD));
    Serial.println("VALUE OF HELD SD OF ASCENT RATE IS: " + String(ascentRateSDHold));
    ascentRateSDEnteredByUser = true;
  }
  else if (command.startsWith("RASCENTRATE")) {   //resets ascent rate back to previous value if changed mid flight. DONT TYPE NUMBERS AFTER!
    command.remove(0, 10);
    meanAscentRate = meanAscentRateHold;

    Serial.println("MEAN ASCENT RATE RESET TO: " + String(meanAscentRate));
    meanAscentRateEnteredByUser = false;
  }
  else if (command.startsWith("RSDSET")) {   //Resets the SD of ascent rate back to previous value if changed mid flight. DONT TYPE NUMBERS AFTER
    command.remove(0, 5);
    ascentRateSD = ascentRateSDHold;
    Serial.println("STANDARD DEVIATION OF ASCENT RATE RESET TO: " + String(ascentRateSD));
    ascentRateSDEnteredByUser = false;
  }

}
