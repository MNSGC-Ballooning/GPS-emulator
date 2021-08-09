int TermIndx = 0;
int VentIndx = 0;
float NewRate = 0;
void SyntheticFlight() {

  ReadSerial(); //check for command

  if ( emulationActive == true) {
    float randomChange = random(0.0, 5.0);
    float randomVent = random(0.0, 3.0); //used for later as slower alts/rates tend to have a tigher spread
    int PlusMinus = random(0, 2);
    int latRand = random(0, 4);

    lastAlt = altSynth;

    if (altCommand == true) {   // move alt to holding space and put in commandable alt into altSynth
      HoldAlt = altSynth;
      altSynth = HitAltf;
    }

    if (TerminationCheck == true) {  //function to simulate altitude behavior of GPS data post-termination (mathmatical function based on averages of parachute descents)
      if (lastAlt > 1000) {
        altSynth = (0.0253 * TermIndx * TermIndx) - (82.835 * TermIndx) + AltTerminatedAt;
        TermIndx++;
      }
      else {
        Serial.println("Flight Has Landed, End of Simulation");
        delay(1000000);
      }
    }


    else if (ventState == true) {  //function to simulates ascent/decent during vent events

      if (lastAlt >= 80000) {

        altSynth = lastAlt + (CurrentRate - (0.0506 * VentIndx));
        VentIndx++;
        NewRate = altSynth - lastAlt; // make new rate
      }
      else if (lastAlt >= 100000) {

        altSynth = lastAlt + (CurrentRate - (0.158 * VentIndx));
        VentIndx++;
        NewRate = altSynth - lastAlt; // make new rate
      }
      else if (lastAlt >= 108000) {
        altSynth = lastAlt + (CurrentRate - (0.1835 * VentIndx));
        VentIndx++;
        NewRate = altSynth - lastAlt; // make new rate
      }
    }


    else if (ventState == false ) {   // function to simulate constant ascent of 16 ft/s (~5m/s) with "random" points of increase to simulate Ublox GPS
      VentIndx = 0; //resent the vent index in preperation of next vent event

      if (ventCounter == 0 && lastAlt < 50000) { //function for ascent before ANY preventing/venting occurs, standard ascent profile

        if ( PlusMinus == 1) {

          altSynth = (altSynth + 16 + randomChange);
        }
        else {

          altSynth = (altSynth + 16 - randomChange);
        }
      }

      else if ( ventCounter == 0 && lastAlt > 50000) {
        if ( PlusMinus == 1) {

          altSynth = (altSynth + 13 + randomChange);
        }
        else {

          altSynth = (altSynth + 13 - randomChange);
        }
      }

      else { //function for ascent AFTER venting has occured

        if ( PlusMinus == 1) {

          altSynth = (altSynth + NewRate + randomVent);
        }
        else {

          altSynth = (altSynth + NewRate - randomVent);
        }
      }

    }

    if ( PlusMinus == 1) { // Function to simulate the latitude and longitude part of GPS data

      if (latRand == 3) {
        latSynth = latSynth + 0.0003;
      }
      else if (latRand == 2) {
        latSynth = latSynth + 0.0002;
      }
      else if (latRand == 1) {
        latSynth = latSynth + 0.0001;
      }
      longSynth = longSynth + 0.0001;
    }
    else {

      if (latRand == 3) {
        latSynth = latSynth - 0.0003;
      }
      else if (latRand == 2) {
        latSynth = latSynth - 0.0002;
      }
      else if (latRand == 1) {
        latSynth = latSynth - 0.0001;
      }
      longSynth = longSynth - 0.0001;
    }




    SynthData = String(latSynth) + "," + String(longSynth) + "," + String(altSynth);

    dataSort(SynthData);

    if (altCommand == true) { //change back for "bad GPS hit" simulation
      altSynth = HoldAlt;
      altCommand = false;
    }

    Serial.println("Current Rate (ft/s) : " + String(altSynth - lastAlt)); //use to check rates in ft/s
    Serial.println("Current Altitude (ft) : " + String(altSynth));
    Serial.println("   ");
    Time++;
    delay(999);
  }
}
