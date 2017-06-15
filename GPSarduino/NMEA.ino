void sendGGA(char* type, int sz){
  char toSend[MAXMESSAGE];
  char check[3];
  int ndx=0;
  char lat[9];
   dtostrf(latf, 1, 3, lat);
  /*The function "dtostrf" converts a float to a char
   * array. The arguments are (float, width, precsion, array). 
   * width does not seem to matter.
   * NOTE: the alt array had to be a global variable
   * to prevent memory allocation overlap.
   */
  dtostrf(altf, 1, 1, alt);     
  char longi[11];
  dtostrf(longf, 1, 4, longi);
  for(int i = 0; i<sz;i++)
  {
    toSend[ndx++]=type[i];
  }
  toSend[ndx++] = ',';
    //add the time in format HHMMSS.ss
  int hours = Time/3600;
  if(hours>9){
    toSend[ndx++] = '0' +(hours/10);
    toSend[ndx++] = '0' +(hours%10);
  }
  else{
    toSend[ndx++] = '0';
    toSend[ndx++] = '0' + hours;
  }
  int minutes = (Time%3600)/60;
  if(minutes>9){
    toSend[ndx++] = '0' +(minutes/10);
    toSend[ndx++] = '0' +(minutes%10);
  }
  else{
    toSend[ndx++] = '0';
    toSend[ndx++] = '0' + minutes;
  }
  int seconds = (Time%60);
  if(seconds>9){
    toSend[ndx++] = '0' +(seconds/10);
    toSend[ndx++] = '0' +(seconds%10);
  }
  else{
    toSend[ndx++] = '0';
    toSend[ndx++] = '0' + seconds;
  }
  toSend[ndx++]='.';
  for(int i = 0;i<3;i++){
    toSend[ndx++] = '0';
  }
  toSend[ndx++]= ',';
    //add the latitude
  for(int i = 0;i<8;i++){
    toSend[ndx++] = lat[i];
  }
  toSend[ndx++] = ',';
  toSend[ndx++] = latCard;
  toSend[ndx++] = ',';
    //add the longitude
  if(latf<10000){    //first see if we need to add a zero
    toSend[ndx++] = '0';
  }
  
  for(int i = 0; i<10; i++){     //send the longitude
    if(longi[i]!=NULL){
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
  toSend[ndx++]= '5';
  toSend[ndx++]= ',';
      //heres this biggie. the altitude in meters
  for(int i = 0; i<10;i++){
    if(alt[i]!=NULL){
      toSend[ndx++] = alt[i];
      Serial.print(String(alt[i]));
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
  for(int i = ndx; i<MAXMESSAGE;i++){
    toSend[i] = NULL;
  }
  makeCheck(toSend, ndx);
  ndx+=3;
  for(int i = 0; i<15;i++){
    alt[i] = NULL;
  }
  toSend[ndx] = '\0';
  GPSserial.println(toSend);
}

