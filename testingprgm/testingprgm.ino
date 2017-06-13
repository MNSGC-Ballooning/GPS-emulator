#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>

SoftwareSerial GPSserial(7,8);
Adafruit_GPS GPS(&GPSserial);



void setup() {
GPS.begin(9600);
Serial.begin(9600);
}

void loop() {
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  delay(1000);

}
