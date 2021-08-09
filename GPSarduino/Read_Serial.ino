void ReadSerial() { //function to pass bytes in, make into chars, and put into a char array
  static boolean recvInProgress = false; //keep track of if data is incoming
  static byte indx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;

  while (Serial.available() > 0) {
    rc = Serial.read();
    if (recvInProgress == true) { //logic for normal data
      if (rc != endMarker) {
        receivedChars[indx] = rc;
        indx++;
        if (indx >= numChars) {
          indx = numChars - 1;
        }
      }
      else {
        receivedChars[indx] = '\0'; // terminate the string
        CommandRead(String(receivedChars)); 
        recvInProgress = false;
        indx = 0;

      }
    }

    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
  
  while (Serial1.available() > 0) {
    rc = Serial1.read();
    if (recvInProgress == true) { //logic for normal data
      if (rc != endMarker) {
        receivedChars[indx] = rc;
        indx++;
        if (indx >= numChars) {
          indx = numChars - 1;
        }
      }
      else {
        receivedChars[indx] = '\0'; // terminate the string
        CommandRead(String(receivedChars)); 
        recvInProgress = false;
        indx = 0;

      }
    }

    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}
