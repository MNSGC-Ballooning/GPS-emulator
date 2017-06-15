#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

/*this is the code for the communicating arduino that will send signals to the other microcontroller
 * acting as a fake GPS
 * writtten by: Simon Peterson
 * date: 6/13/17
 */
 #define MAXMESSAGE 120

unsigned long Time = 50000;    //Time in seconds
float latf = 4458.843;   //DDMM.MMMM
char latCard = 'N';
char longiCard = 'W';
//the alt array is global to prevent memory allocation overlap in NMEA function
char alt[15];
float longf = 07400.4184;  //DDDMM.MMMM
float altf = 300;         //Altitude in meters. 300 is pretty standard starting place
char command[MAXMESSAGE];
char GPGGA[6] = "$GPGGA";
char GPRMC[6] = "$GPRMC";
SoftwareSerial GPSserial(7,8); //Rx, Tx
boolean recvd = false;

void setup() {
  Serial.begin(9600);
  GPSserial.begin(9600);
  
}

void loop() {
  readCommand();
  if(recvd){
    Serial.println(String(command));
    if(String(command)==PMTK_SET_NMEA_UPDATE_1HZ){
      while(altf<30000){
         sendGGA(GPGGA, 6);
         delay(1000);
         Time++;
         altf+=5;
      }
      while(altf>0){
        sendGGA(GPGGA, 6);
        delay(1000);
        Time++;
        altf-=20;
      }
    }
    else{
      Serial.print("not set");
    }
    recvd = false;
  }
  sendRMC(GPRMC, 6);
}


