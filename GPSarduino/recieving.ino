
/*void readCommand(){
  static uint8_t ndx = 0;
  char END = '*';
  char red;
  static boolean checksum = false;
  static int checksumCount = 3;
  while(GPSserial.available()>0)
  {
    red = GPSserial.read();
    if(red!= END&&!checksum){
      if(red!= '\r' && red!= '\n'){
        command[ndx] = red;
        ndx++;
      }
    }
    else if(checksumCount>0){
      checksum = true;
      command[ndx] = red;
      ndx++;
      checksumCount--;
    }
    else{
      command[ndx]='\0';
      ndx = 0;
      checksumCount = 3;
      checksum = false;
      recvd= true;
    }
  }
}*/

