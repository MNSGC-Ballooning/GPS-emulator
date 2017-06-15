String toHex(uint16_t dec){
  int major = dec/16;
  int minor = dec%16;
  String witch;   //the german word for witch is "die Hexe"; 
  if(major<10){
    witch[0] = '0' + major;
  }
  else{
    witch[0] = '0' + major%10 + 17;
  }
  if(minor<10){
    witch[1] = '0' + minor;
  }
  else{
    witch[1] = '0' + major%10 + 17;
  }
  return witch;
}

