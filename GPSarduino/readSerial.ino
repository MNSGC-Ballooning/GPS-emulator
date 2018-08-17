void readSerial(){
  static uint8_t ndx = 0;
  char END = '\n';
  char red;
  while(Serial.available()>0)
  {
    red = Serial.read();
    if(red!= END){
        Serialcom[ndx] = red;
        ndx++;
    }
    else{
      Serialcom[ndx]='\0';
      ndx = 0;
      recvd= true;
      doCommand(Serialcom);
    }
  }
}
void doCommand(String com){
  int toJump;
  if(com.indexOf(JUMP)!=-1){
    toJump = (com.substring(4, com.length())).toInt();
    altc+= float(toJump);
  }
}
