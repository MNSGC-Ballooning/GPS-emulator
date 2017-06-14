void sendNMEA(char* type, int sz){
  char toSend[MAXMESSAGE];
  int ndx=0;
  for(ndx; ndx<sz;ndx++)
  {
    toSend[ndx]=type[ndx];
  }
  ndx++;
  toSend[ndx++] = ',';
  int hours = int(Time/3600);
  if(hours>9){
    toSend[ndx++] = '0' +(hours/10);
    toSend[ndx++] = '0' +(hours%10);
  }
  else{
    toSend[ndx++] = '0';
    toSend[ndx++] = '0' +hours;
  }
  toSend[ndx]= '\0';
  Serial.println(toSend);
}

