void sendNMEA(char* type, int sz){
  char toSend[MAXMESSAGE];
  int ndx=0;
  for(ndx; ndx<sz;ndx++)
  {
    toSend[ndx]=type[ndx];
  }
  ndx++;
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
  toSend[ndx] = '\0';
  Serial.println(toSend);
}

