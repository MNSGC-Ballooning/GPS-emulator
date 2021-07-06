String dataline;
String G1;
void SDSetup() { //sets up SD card and names it

  pinMode(chipSelect, OUTPUT);
  if (!SD.begin(chipSelect)) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
  }

  else {
    datalog = SD.open(filename, FILE_WRITE);
    sdActive = true;
    delay(500);
  }
  if (!sdActive) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
  }
}


void getData() {
  int toss = 0;

  datalog = SD.open(filename, FILE_READ);

  while (datalog.available() > 0) {

    dataline = datalog.readStringUntil('\r');


    if (toss < 1) { // loop to toss header
      dataline = "";
      toss++;
    }
    else {
      for (int i = 0; i < dataline.length(); i++) {
        GPSchars[i] = dataline.charAt(i);
      }

      if (String(GPSchars).length() != dataline.length()) { //if data is not same length, place null at end of GPSchars to prevent memory from last loop carrying over
        GPSchars[String(GPSchars).length() + 1] = '\0';
      }

      G1 = String(GPSchars); 
      Serial.println(G1);
      dataSort(G1);
      delay(1000);

    }
  }

  datalog.close();
  return;
}
