void makeCheck(char* nmea, int index){
    uint16_t sum = 0; 
    int counter = 0;
    char* jerry;
    for (uint8_t i=1; i < MAXMESSAGE; i++) {
      if(nmea[i]!=NULL){
        sum^= nmea[i];
      }
      else{
        counter++;
      }
    }
    nmea[index++] = '*';
    jerry = toHex(sum);
    //Serial.println(String(jerry));
    for(int i = 0;i<2;i++){
      nmea[index++] = jerry[i];
    }
}
