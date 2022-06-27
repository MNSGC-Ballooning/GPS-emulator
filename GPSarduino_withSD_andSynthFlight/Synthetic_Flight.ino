int TermIndx = 0;
int VentIndx = 0; //variable tracks how long the vent has remained open. this affects ascent rate based on a flat rate depending on current altitude
float NewRate = 0;
int leakIndx = 0;

void SyntheticFlight() {

  ReadSerial(); //check for command

  if ( emulationActive == true) { //if statement that runs synthetic flight after '<START>' command has been given

    lastAlt = altSynth;   //saving altSynth from previous loop

    if (altCommand == true) {   // move alt to holding space and put in commandable alt into altSynth if '<ALT#>' command has been given
      HoldAlt = altSynth;
      altSynth = HitAltf;
    }
    if (isLeaking == true) { //itterates leaking variable if there is a leak
      leak = -0.0089 * leakIndx;
      leakIndx++;
    }
    if (lastAlt > altToTerminateAt) { // emulate the bursting of the balloon if it goes too high. variable 'altToTerminateAt' in vairables to change before flight
      CommandRead("TERM");
    }

    if (TerminationCheck == true) {//function to simulate altit9ude behavior of GPS data post-termination (mathmatical function based on averages of parachute descents)
      if (termDelaySeconds > 120) {
        if (lastAlt > 1000) {
          /*Above If statement checks if it has been 120s since termination command is given then runs termination ascentRate logic.
            This is to simulate the delay it takes for the vent to decide to terminate, and the delay it takes for the resistor burners to stop working.
            IF YOU WANT TO TEST EMERGENCY CUTTER -->>>  change 120 to over 240s (4 mins) this should cause the vent to run the emergency cutter*/
          altSynth = (0.0253 * TermIndx * TermIndx) - (82.835 * TermIndx) + AltTerminatedAt;
          TermIndx++;
        }
        else {
          Serial.println("Flight Has Landed, End of Simulation");
          delay(1000000);
        }

      }//end of termDelay if statement
      else { //if not delayed 2 min after termination then ascend as normal until 2 min after term command is given. this is to simulate delay in actual flight
        termDelaySeconds++;
        altSynth = lastAlt + calcRandAscentRate(meanAscentRate, ascentRateSD);
      }
    }//end of termination check if statement

    //else because if termination is happening/has happened if termination is true then uses termination decent logic instead
    else if (ventState == true) {  //checks to see if currently venting, WILL INFLUENCE ASCENT RATE IF ALTITUDE IS BELOW 80,000 FEET (unrealistic, but no data exsists to model this behavior)
/*
      if ( lastAlt < 60000) { //this is a error case of venting. if the vent tries to vent before it is supposed to IE before prevent 1 alt, then nothing happens and it ascends as usual
        altSynth = lastAlt + calcRandAscentRate(meanAscentRate, ascentRateSD);
      }
      else {

        */
      
       // if (lastAlt >= prevent1Alt) { // simulates vent rate above 70,000 feet. variable is 'set up variables'

          meanAscentRate -= (0.0459);// adjusts mean ascent rate down 0.0459ft/s for 1s of venting. seyon found this number based on GL175 venting data

          altSynth = lastAlt + calcRandAscentRate(meanAscentRate, ascentRateSD); //sets new altidude based on last alt plus current ascent rate ajusted for vent plus noise

      //  }
        //commented out to possible change the emulator so there is a constant decrease in ascent rate
        /*
        else if (lastAlt >= prevent2Alt) { //simulates vent rate above 80K feet. variable is 'set up variables'

          //adjust mean ascent rate down for 1s of venting
          meanAscentRate -= 0.158;  //not sure where 0.158 is from

          //ajust new altitude based on last alt plus new ascent rate with noise
          altSynth = lastAlt + calcRandAscentRate(meanAscentRate, ascentRateSD);

        }
        else if (lastAlt >= prevent3Alt) { // simualtes vent rate above 90K feet. variable is 'set up variables'

          //ajust mean ascent rate down for 1s of venting
          meanAscentRate -= 0.1835;  //not sure where 0.1835 is from

          //adjust new altitude based on last alt plus new ascent rate with noise
          altSynth = lastAlt + calcRandAscentRate(meanAscentRate, ascentRateSD);

        }
        */

        //serial print commands to show while venting
        VentIndx++; //increment how long vent has been open
        //Prints to the serial monitor how long device has been venting for and current mean ascent rate the ascent rate is being calculated off of
        Serial.println("Vent Index: " + String(VentIndx));   //displays seconds that vent has been open
        Serial.println("Current Time (seconds): " + String(Time));
        Serial.println("Mean ascent Rate: " + String(meanAscentRate));

        /*In old code if device has vented in past, reduce standard deviation size by half. This was a change of +/-4 -> +/-2 in the old code.
          I am not sure if it is true that the noise of the GPS is reduced because the device has vented or we just want that to be the case for testing purposes but...
          the standard deviation of the meanAscentRate prevs post vent on GL175 with venting at ~85K ft is only a standard deviation different of 0.13 ft/s in ascent rate
          we are setting it to 2 here (SD of gps values found after 50K ft of alt is gained in GL175) minus any aditional postvent noise reduction specified by user in set up variables
        */
        if (ascentRateSD >= 2) {
          ascentRateSD = 2;
          ascentRateSD -= postVentNoiseReduction;
        }

     // } //end of if statement that sees if alt is below prevent1 alt
    } //end of if statement checking if ventState == true

    else if (ventState == false ) {   // checks to see if not venting, if not venting then controls ascent based on constant ascent of 16 ft/s (~5m/s) with noise of increase to simulate Ublox GPS
      VentIndx = 0; //resent the vent index in preperation of next vent event

      if (ventHasBeenUsed == false && lastAlt < 50000) { //function for ascent before ANY preventing/venting occurs, standard ascent profile

        if (meanAscentRateEnteredByUser == false) { //if a meanAscentRate has been entered by user then dont reset it here
          meanAscentRate = ascentRateAtLaunch; //since balloon hasnt vented and is below 50K ft it still has a mean ascent rate of usually 16
        }

        altSynth = altSynth + calcRandAscentRate(meanAscentRate, ascentRateSD);


      }

      else if (ventHasBeenUsed == false && lastAlt > 50000) { //if has never vented and above 50,000ft slow down ascent rate to 13ft/s base +/- noise
        //commenting out so it has a constant ascent rate all the way up: 
        /*
        if (meanAscentRateEnteredByUser == false) { //if a meanAscentRate has been entered by user then dont reset it here
          meanAscentRate = ascentRate50kPlus; //setting new mean ascentRate specified in 'set up variables' usually 13ft/s at 50k+
        }
        */
        if (ascentRateSDEnteredByUser == false) { //if an ascent rate SD has been entered by user then dont reset it here
          ascentRateSD = 2;     //Ascent Rate SD is set to 2 after 50,000 ft this is from analysis of GL175
        }
        altSynth = altSynth + calcRandAscentRate(meanAscentRate, ascentRateSD);

      }

      else { //condition that not currently venting but has vented in the past.

        //only need to calculate new alt because in venting funciton we changed ascentRateSD if needed and decreased the mean ascent rate
        altSynth = altSynth + calcRandAscentRate(meanAscentRate, ascentRateSD);

      }

    }

    //===================IF statements that ajust lat and long values to simulate how balloonn is drifting ========================

    float randomNum = int(random(-1.0, 2.0)); //getting a random number either -1 or 1
    while (randomNum == 0) {
      randomNum = int(random(-1.0, 2.0));
    }

    latSynth += (randomNum * random(1.0, 4.0)) * 0.0001 ; //aither adds or subtracts a random number from 0.0001 -> 0.0003
    longSynth += randomNum * 0.0001;  //either plus or minus 0.0001 from longSynth

    Serial.print("Current Lat/Long:  ");
    Serial.print(latSynth, 4);
    Serial.print("/");
    Serial.println(longSynth, 4);


    //=================== END OF IF statements that ajust lat and long values to simulate how balloonn is drifting  ========================



    SynthData = String(latSynth) + "," + String(longSynth) + "," + String(altSynth);

    dataSort(SynthData); //calls funciton data sort which then communicates with the GPS through RMC and NMEA

    if (altCommand == true) { //change back for "bad GPS hit" simulation
      altSynth = HoldAlt;
      altCommand = false;
    }

    CurrentRate = altSynth - lastAlt;
    Serial.println("Current Rate (ft/s) : " + String(CurrentRate)); //use to check rates in ft/s
    Serial.println("Current Rate (m/s) : " + String((CurrentRate) * 0.3048));
    Serial.println("Current Altitude (ft) : " + String(altSynth));
    Serial.println("Leak Rate -(ft/s) : " + String(leak));
    Serial.println("Current mean Ascent Rate (ft/s): " + String(meanAscentRate) + "\nCurrent Standard Deviation of Ascent Rate: " + String(ascentRateSD));
    Serial.println("   ");
    //Time++;    <----------------THis was removed because now variable Time = millis() / 1000  <-- in loop()


    while ( (millis() % 1000) != 0) {
      /*until millis is divisible by 1000, dont do anything. This insures that the loop is happening ever 1second. this is important because if there is a delay it will disrupt the 
      vent's ascent rate calculations. This is smarter than a delay function */
    }
    
  }
}

//================================================= calcRandAscentRate ========================================
/*funciton that calculates a random ascent rate based on a BOX-Muller transform: https://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform
  The function is also called gaussian noise, the code was taken from the wiki link above bottom of pge
  INPUTS:
  --Mu is the mean ascent rate, this is the "base ascent rate" usually 16ft/s but might change later in flight
  --sigma is the amout of standard deviation following a standard normal distribution 68-95-99.7 rule
  sigma can be changed at the top of Synthetic_flight funciton to varry range of "noise" there is on flight
  OUTPUTS:
  Function outputs float variable of ascent rate in ft/s
*/
//=======================================================================================================
float calcRandAscentRate(float mu, float sigma) {
  //function will return float z0 whish is the calculated ascent rate, initialized to -999
  float z0 = -999;
  float u1 = random(0.0, 100000.0) / 100000.0; //function creates two random numbers from 0 -> 1 exclusive
  float u2 = random(0.0, 100000.0) / 100000.0;

  //using Box-Muller transform to find two random numbers with mean of 'mu' and SD of 'sigma'
  float magOfNoise = sigma * sqrt(-2.0 * log(u1)); //this part of transform is finding out how much variation ("noise") is generated

  z0  = magOfNoise * cos(two_pi * u2) + mu; //the trig decides if the noise (magOfNoise) is additive of subtractive from the meanAscentRate (mu). cos and sin are interchageable in this part

  //at this point z0 is a randomly generated number with a standard normal distribution with a mean of mu and SD of sigma

  return z0;
}
