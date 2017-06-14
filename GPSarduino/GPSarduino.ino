#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

/*this is the code for the communicating arduino that will send signals to the other microcontroller
 * acting as a fake GPS
 * writtten by: Simon Peterson
 * date: 6/13/17
 */

 #define MAXMESSAGE 82

char command[MAXMESSAGE];
char GPGGA[6] = "$GPGGA";
//SoftwareSerial GPSserial(7,8); //Rx, Tx
boolean recvd = false;

void setup() {
  Serial.begin(9600);
  //GPSserial.begin(9600);
  
}

void loop() {
 /* readCommand();
  if(recvd){
    Serial.println(String(command));
    if(String(command)==PMTK_SET_NMEA_UPDATE_1HZ){
      Serial.println("update rate set");
    }
    else{
      Serial.print("not set");
    }
    recvd = false;
  }*/
  sendNMEA(GPGGA, 6);
  delay(500);
}


