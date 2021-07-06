//#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <SD.h>
/*this is the code for the communicating arduino that will send signals to the other microcontroller
   acting as a fake GPS
   writtten by: Simon Peterson      edited by: Ben Stevens 
   date: 6/13/17                    date: 6/04/2021

   *Added ability to receive serial data in order to "re-fly" previous flights. 
   *Added custom serial reciver function (readSerial) that provides fast, clean data transfer from external serial input 
   *Added ability to handle negative decimal coordinates (Western Hemisphere) 
   *Possible future improvments: emulate from an onboard SD card (would require heavy recoding) 
*/
#define MAXMESSAGE 120
#define VENT "vent"
unsigned long Time = 0;    //Time in seconds
float latf = 00.0000;   //DDMM.MMMM
char latCard = 'N';
char longiCard = 'W';
//the alt array is global to prevent memory allocation overlap in NMEA function
char alt[15];
float longf = 00.0000;  //DDDMM.MMMM
float altf = 300;         //Altitude in meters. 300 is pretty standard starting place
char command[MAXMESSAGE];
char Serialcom[20];
char GPGGA[7] = "$GPGGA";
char GPRMC[7] = "$GPRMC";
//SoftwareSerial GPSserial(2, 3); //Rx, Tx
#define GPSserial Serial1
boolean recvd = false;
unsigned long Timer = 0; 
float ventBy = 0.00; 
int GPSsemi = 0; 
char GPSchars[50]; 
int GPScounter = 0;  
int GPStrack[3] = {0,0,0}; 
char GPSreplace[] = ";";  
//DELAY LOOP / DATA RECEPTION VARIABLES
int period = 10;
unsigned long time_now = 0;
const byte numChars = 25;
char receivedChars[numChars];

const byte numChar = 10;
char receivedChar[numChar];
//SD Variables 
#define chipSelect BUILTIN_SDCARD                       // Using built in chipselect on Teensy 3.5
File datalog;                                           // File object to be opened, written to, and closed
char filename[] = "TST01.csv";                          // File name as will be seen on SD card -- can have maximum of 99 files on SD card 
bool sdActive = false;                                  // Boolean to check if there are any available filenames left to be used
int dataLogs = 0;

void setup() {
  Serial.begin(14400);
  GPSserial.begin(9600); //for ublox GPS modules. Varies by model.
  pinMode(LED_BUILTIN, OUTPUT);
  SDSetup();

}

void loop() {
 readCommand();
  getData();
  Serial.println("End");
  time_now = millis();
}
