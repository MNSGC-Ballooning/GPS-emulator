#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

/*this is the code for the communicating arduino that will send signals to the other microcontroller
 * acting as a fake GPS
 * writtten by: Simon Peterson
 * date: 6/13/17
 */
 #define MAXMESSAGE 120
 #define JUMP "jump"
unsigned long Time = 50000;    //Time in seconds
float latf = 4458.843;   //DDMM.MMMM
char latCard = 'N';
char longiCard = 'W';
//the alt array is global to prevent memory allocation overlap in NMEA function
char alt[15];
float longf = 07400.4184;  //DDDMM.MMMM
float altf = 300;         //Altitude in meters. 300 is pretty standard starting place
float altc = 300;          //Copy of alitude to continuing propagating during fix loss
char command[MAXMESSAGE];
char Serialcom[20];
char GPGGA[6] = "$GPGGA";
char GPRMC[6] = "$GPRMC";
SoftwareSerial GPSserial(7,8); //Rx, Tx
boolean recvd = false;
boolean fix = true;
unsigned long Timer = 0;
void setup() {
  Serial.begin(9600);
  GPSserial.begin(4800);
  randomSeed(analogRead(0));
  
}

void loop() {
  readCommand();
  //if(recvd){
    Serial.println(String(command));
    //if(String(command)==PMTK_SET_NMEA_UPDATE_1HZ){
      while(altc<36700){
         readSerial();
         Fix();
         if(millis()-Timer>1000){
            sendGGA(GPGGA, 6);
            sendRMC(GPRMC, 6);
            Serial.println(String(altf));
            Timer = millis();
            Time++;
            altc+=5;
            if(fix){
              altf=altc;
            }
            else{
              altf=0;
            }
          }
      }
      while(altc>24200){
         readSerial();
         Fix();
         if(millis()-Timer>1000){
            sendGGA(GPGGA, 6);
            sendRMC(GPRMC, 6);
            Serial.println(String(altf));
            Timer = millis();
            Time++;
            altc-=3;
            if(fix){
              altf=altc;
            }
            else{
              altf=0;
            }
          }
      }
      while(altc>0){
        readSerial();
        Fix();
        if(millis()-Timer>1000){
            sendGGA(GPGGA, 6);
            sendRMC(GPRMC, 6);
            Serial.println(String(altf));
            Timer = millis();
            Time++;
            altc-=15;
            if(fix){
              altf=altc;
            }
            else{
              altf=0;
            }
        }
      }
    //}
//    else{
//      Serial.print("not set");
//    }
//    recvd = false;
  //}
  /*sendGGA(GPGGA, 6);
  sendRMC(GPRMC, 6);
  Time++;
  altf+=1;*/
}


