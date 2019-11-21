//#include <SoftwareSerial.h>
//#include <Adafruit_GPS.h>
#include <UbloxGPS.h>
#include <TinyGPS++.h>

//SoftwareSerial GPSserial(7,8);
#define GPSserial Serial2
UbloxGPS GPS = UbloxGPS(&GPSserial);
#define MAXMESSAGE 120
char recieved[MAXMESSAGE];
int ndx = 0;
unsigned long int Timer = 0;

void setup() {
GPSserial.begin(9600);
GPS.init();
Serial.begin(9600);
Timer = millis();
}

void loop(){
 while (GPSserial.available()) {
    GPS.update();
    //Serial.write(GPSserial.read());
   }
 if(millis()-Timer > 1500){
    Timer = millis();
    //Serial.println(GPSserial.read());
    GPSserial.read();
    Serial.println("lat " + String(GPS.getLat(), 1)+ ", long " + String(GPS.getLon(), 1) + ", alt " + String(GPS.getAlt_feet(), 1));
  ndx = 0;
 }
 

}
