String dataline;
String G1;
int toss = 0;

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



  datalog = SD.open(filename, FILE_READ);

  while (datalog.available() > 0) {
    ReadSerial();
    //Time++;    <----------------THis was removed because now variable Time = millis() / 1000  <-- in loop()
    dataline = datalog.readStringUntil('\r');

    if (toss < 1) { // loop to toss header
      dataline = "";
      toss++;
    }

    else {
      for (int i = 0; i < dataline.length() + 1; i++) {
        GPSchars[i] = dataline.charAt(i);

        if (i == dataline.length()) {
          GPSchars[i] = '\0';
        }
      }
      G1 = "";
      G1 = String(GPSchars);
      //Serial.println(G1);
      dataSort(G1);
      delay(1000);

    }
  }

  datalog.close();
  return;
}
