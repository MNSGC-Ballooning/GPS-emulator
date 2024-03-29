void sendGGA(char* type, int sz) {
  char toSend[MAXMESSAGE];
  int ndx = 0;
  char lat[9];
  dtostrf(latf, 1, 3, lat);
  /*The function "dtostrf" converts a float to a char
     array. The arguments are (float, width, precsion, array).
     width does not seem to matter.
     NOTE: the alt array had to be a global variable
     to prevent memory allocation overlap.
  */
  dtostrf(altf, 1, 1, alt);
  char longi[11];
  dtostrf(longf, 1, 4, longi);
  for (int i = 0; i < sz; i++)
  {
    toSend[ndx++] = type[i];
  }
  toSend[ndx++] = ',';
  //add the time in format HHMMSS.ss
  int hours = Time / 3600;
  if (hours > 9) {
    toSend[ndx++] = '0' + (hours / 10);
    toSend[ndx++] = '0' + (hours % 10);
  }
  else {
    toSend[ndx++] = '0';
    toSend[ndx++] = '0' + hours;
  }
  int minutes = (Time % 3600) / 60;
  if (minutes > 9) {
    toSend[ndx++] = '0' + (minutes / 10);
    toSend[ndx++] = '0' + (minutes % 10);
  }
  else {
    toSend[ndx++] = '0';
    toSend[ndx++] = '0' + minutes;
  }
  int seconds = (Time % 60);
  if (seconds > 9) {
    toSend[ndx++] = '0' + (seconds / 10);
    toSend[ndx++] = '0' + (seconds % 10);
  }
  else {
    toSend[ndx++] = '0';
    toSend[ndx++] = '0' + seconds;
  }
  toSend[ndx++] = '.';
  for (int i = 0; i < 3; i++) {
    toSend[ndx++] = '0';
  }
  toSend[ndx++] = ',';
  //add the latitude

  for (int i = 0; i < 8; i++) {
    toSend[ndx++] = lat[i];
  }
  toSend[ndx++] = ',';
  toSend[ndx++] = latCard;
  toSend[ndx++] = ',';
  //add the longitude
  if (latf < 10000) { //first see if we need to add a zero and check if negative
    if (longi[0] == '-') {

      longi[0] = '0';
    }
    else {

      toSend[ndx++] = '0';
    }
  }
  for (int i = 0; i < 10; i++) { //send the longitude
    if (longi[i] != NULL) {
      toSend[ndx++] = longi[i];
    }
  }
  toSend[ndx++] = ',';
  toSend[ndx++] = longiCard;
  toSend[ndx++] = ',';
  //now we add the fix data
  //1 for fix, 0 for not fix
  toSend[ndx++] = '1';
  toSend[ndx++] = ',';
  //next up is the number of satellites, anything between 4 and 10 willl do
  toSend[ndx++] = '5';
  toSend[ndx++] = ',';
  //now we send the relative accuracy. 1.5 is common
  toSend[ndx++] = '1';
  toSend[ndx++] = '.';
  toSend[ndx++] = '5';
  toSend[ndx++] = ',';
  //heres this biggie. the altitude in meters
  for (int i = 0; i < 10; i++) {
    if (alt[i] != NULL) {
      toSend[ndx++] = alt[i];
    }
  }
  toSend[ndx++] = ',';
  toSend[ndx++] = 'M';
  toSend[ndx++] = ',';

  //next up is the altitude above elisoidal. -34.2 seems to be the standard.
  toSend[ndx++] = '-';
  toSend[ndx++] = '3';
  toSend[ndx++] = '4';
  toSend[ndx++] = '.';
  toSend[ndx++] = '2';
  toSend[ndx++] = ',';
  toSend[ndx++] = 'M';
  toSend[ndx++] = ',';
  //extra comma on the end for some reason
  toSend[ndx++] = ',';
  //and finally we add the checksum


  //we need to make sure not allocated characters are null for the checksum;
  for (int i = ndx; i < MAXMESSAGE; i++) {
    toSend[i] = NULL;
  }
  uint16_t sum = 0;
  String jerry = "";
  for (uint8_t i = 1; i < MAXMESSAGE; i++) {
    if (toSend[i] != NULL) {
      sum ^= toSend[i];
    }
  }
  toSend[ndx++] = '*';
  jerry = toHex(sum);
  for (int i = 0; i < 2; i++) {
    toSend[ndx++] = jerry[i];
  }
  // Serial.println(jerry);
  toSend[ndx++] = '\0';

  //////////////////////////// This section was used to troubleshoot a mis-match in timing between vent and GPS updates resolved 6-6-22 ////////////////////////////
  /*
  Serial.println("Current time in millis gps has sent data over in NMEA: " + String(millis()));
  currentNMEAmillis = millis();
  diffNMEAmillis = currentNMEAmillis - pastNMEAmillis[9];
  
   for (int i = 0; i < 10; i++) // for loop to calculate the average ascent rate (averaged over the last 10 hits--or 20 seconds worth of data--to reduce noise)
  {
    if (i < 9) //moving the parts of teh array towards zero
    {
      pastNMEAmillis[i] = pastNMEAmillis[i + 1];
      pastDiffNMEA[i] = pastDiffNMEA[i + 1];
    }
    if (i == 9) //set 10th place equal to current ascent rate
    {
      pastNMEAmillis[i] = currentNMEAmillis;
      pastDiffNMEA[i] = diffNMEAmillis;
    }
  }
  Serial.println("past 10 NMEA millis:");
  for (int i = 0; i < 10; i++){
    Serial.print(String(pastNMEAmillis[i]) + ", ");
  }
  Serial.println("");
  Serial.println("past 10 diff NMEA millis:");
  for (int i = 0; i < 10; i++){
    Serial.print(String(pastDiffNMEA[i]) + ", ");
  }
  Serial.println("\n");
  */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  GPSserial.println(toSend);
  GPSserial.flush();
  //Serial.println(toSend);
  //Serial.flush();

}
