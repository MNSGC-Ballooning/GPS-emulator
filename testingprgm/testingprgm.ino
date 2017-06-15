#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>

SoftwareSerial GPSserial(7,8);
Adafruit_GPS GPS(&GPSserial);
#define MAXMESSAGE 120
char recieved[MAXMESSAGE];
int ndx = 0;

void setup() {
GPS.begin(9600);
Serial.begin(9600);
GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
}

void loop() {
 while (GPSserial.available() > 0) {
    GPS.read();
   }
 if(GPS.newNMEAreceived()){
  GPS.parse(GPS.lastNMEA());
  Serial.println("lat " + String(GPS.latitudeDegrees, 4)+ ", long " + String(GPS.longitudeDegrees, 4) + ", alt" + String(GPS.altitude, 3));
  ndx = 0;
 }
 

}
