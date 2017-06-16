char* toHex(uint16_t dec){
  int major = dec/16;
  int minor = dec%16;
  char witch[2];   //the german word for witch is "die Hexe"; 
  if(major<10){
    witch[0] = '0' + major;
    delay(10);
  }
  else{
    witch[0] = '0' + major%10 + 17;
    delay(10);
  }
  if(minor<10){
    witch[1] = '0' + minor;
    delay(10);
  }
  else{
    witch[1] = '0' + minor%10 + 17;
    delay(10);
  }
  return witch;
}

