String toHex(uint16_t dec){
  //double majorD = dec/16;
  //Serial.println("dec = " + String(dec));
  int major = dec/16;
  //double minor = majorD - major;
  int minor = dec%16;

  //Serial.println("major = " + String(major));
  //Serial.println("minor = " + String(minor));

  int intVal[2];
  intVal[0] = major;
  intVal[1] = minor;
  char witch[2];
  
  for(int i=0; i<2; i++){
    if(intVal[i] == 0){witch[i] = '0';}
    else if(intVal[i] == 1){witch[i] = '1';}
    else if(intVal[i] == 2){witch[i] = '2';}
    else if(intVal[i] == 3){witch[i] = '3';}
    else if(intVal[i] == 4){witch[i] = '4';}
    else if(intVal[i] == 5){witch[i] = '5';}
    else if(intVal[i] == 6){witch[i] = '6';}
    else if(intVal[i] == 7){witch[i] = '7';}
    else if(intVal[i] == 8){witch[i] = '8';}
    else if(intVal[i] == 9){witch[i] = '9';}
    else if(intVal[i] == 10){witch[i] = 'A';}
    else if(intVal[i] == 11){witch[i] = 'B';}
    else if(intVal[i] == 12){witch[i] = 'C';}
    else if(intVal[i] == 13){witch[i] = 'D';}
    else if(intVal[i] == 14){witch[i] = 'E';}
    else if(intVal[i] == 15){witch[i] = 'F';}
    else{ Serial.println("ERROR");}
  }

  String out = witch;
  out = out.substring(0,2);
  //Serial.println("out = " + out);
  return out;
}


//  return witch;
  /*char witch[2];   //the german word for witch is "die Hexe"; 
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
}*/
