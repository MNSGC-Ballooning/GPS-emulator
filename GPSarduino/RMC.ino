void sendRMC(char* type, int sz){
  char toSend[MAXMESSAGE];
  String knots = "5.03";  //speed in knots
  String trueCourse = "314.59";
  String date = "023013";
  int ndx=0;
  char lat[9];
    /*The function "dtostrf" converts a float to a char
   * array. The arguments are (float, width, precsion, array). 
   * width does not seem to matter.
   * NOTE: the alt array had to be a global variable
   * to prevent memory allocation overlap.
   */
  dtostrf(latf, 1, 3, lat);
  dtostrf(altf, 1, 1, alt);    
  char longi[11];
  dtostrf(longf, 1, 4, longi);
  for(int i = 0; i<sz;i++)
  {
    toSend[ndx++]=type[i];
  }
  //sending the time
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
  toSend[ndx++] = ',';
  toSend[ndx++] = 'A';    //the A is for the fix. V is no fix.
  toSend[ndx++] = ',';
  //now we send the latitude
  for(int i = 0;i<8;i++){
    toSend[ndx++] = lat[i];
  }
  toSend[ndx++] = ',';
  toSend[ndx++] = latCard;
  toSend[ndx++] = ',';
     //next comes the longitude
     //first see if we need to add a zero
  if(latf<10000){   
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
    //next up we need to send the speed in knots. how about 5 knots, cuz why knot?
    //cmon now
    //that was funny
  for(int i =0;i<4;i++){
    toSend[ndx++] = knots[i];
  }
  toSend[ndx++] = ',';
  for(int i =0; i<6;i++){
    toSend[ndx++] = trueCourse[i];
  }
  toSend[ndx++] = ',';
    //send the date
  for(int i =0;i<6;i++){
    toSend[ndx++] = date[i];
  }
    //send three commas
  for(int i =0; i<3; i++){
    toSend[ndx++] = ',';
  }
     //another A, unlike my grades
  toSend[ndx++] = 'A';
     //make sure ndx is null and add the checksunm
  for(int i = ndx; i<MAXMESSAGE;i++){
    toSend[i] = NULL;
  }
  makeCheck(toSend, ndx);
  ndx+=3;
  
    //send the true course heading
  toSend[ndx]= '\0';
  GPSserial.println(toSend);
}
