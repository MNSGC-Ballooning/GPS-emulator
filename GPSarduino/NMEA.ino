void sendNMEA(char* type, int sz){
  char toSend[MAXMESSAGE];
  int ndx=0;
  for(ndx; ndx<sz;ndx++)
  {
    toSend[ndx]=type[ndx];
  }
  ndx++;
  toSend[ndx] = ',';
  ndx++;
  
  
  
}

