char* makeCheck(char * nmea){
    uint16_t sum = 0; 
    int counter = 0;
    for (uint8_t i=1; i < MAXMESSAGE; i++) {
      if(nmea[i]!=NULL){
        sum^= nmea[i];
      }
      else{
        counter++;
      }
    }
    Serial.println(String(counter));
    Serial.print(String(sum, HEX));
    //return hex;
}
