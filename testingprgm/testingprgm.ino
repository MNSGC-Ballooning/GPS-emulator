#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>

SoftwareSerial GPSserial(7,8);
Adafruit_GPS GPS(&GPSserial);



void setup() {
GPS.begin(9600);
Serial.begin(9600);
}

void loop() {
  for(int i = 0; i<10;i++){
    GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
    delay(1000);
  }
  GPS.sendCommand("simon_test_command*12");
  delay(1000);


}
