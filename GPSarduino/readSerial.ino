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
    }
  }
}
