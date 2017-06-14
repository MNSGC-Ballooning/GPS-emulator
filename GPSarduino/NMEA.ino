void sendNMEA(char* type, int sz){
  char toSend[MAXMESSAGE];
  int ndx=0;
  char lat[9];
  /*The function "dtostrf" converts a float to a char
   * array. The arguments are (float, width, precsion, array) 
   * width does not seem to matter.
   */
  dtostrf(latf, 4, 3, lat);      
  char longi[11];
  dtostrf(longf, 4, 4, longi);
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
  toSend[ndx] = '\0';
  Serial.println(toSend);
}

