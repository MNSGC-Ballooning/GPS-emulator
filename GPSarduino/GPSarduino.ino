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
char command[MAXMESSAGE];
char Serialcom[20];
char GPGGA[] = "$GPGGA";
char GPRMC[] = "$GPRMC";
SoftwareSerial GPSserial(7,8); //Rx, Tx
boolean recvd = false;
unsigned long Timer = 0;
unsigned long sendTimer = 0;

// New variables 
int mode;

void setup() {
  Serial.begin(9600);
  GPSserial.begin(4800);
  Serial.println("Which mode would you like to enter? Enter \"1\" for custom mode or \"2\" for SD card mode."); // Mode
  
  while(true)
  { mode = Serial.read(); // The issue here is an ASCII issue
    delay(500);
    Serial.println(mode);
    if(mode=="1" || mode=="2")
    {
       // Read in the string when available
      Serial.println("SUCCESSS!!!!");      // For debugging
      break;
    }
  }          // Wait until user input is received
       
  Serial.println("Not in loop" + mode);
  if(mode=="1")
  {
    Serial.println("Mode 1"); 
    // Run the custom version of the emulator
    // **Ask to input variables
    // **Run the GPS emulator loop
  }
  else if(mode=="2")
  {
    Serial.println("Mode 2");
    // Do some SD card setup stuff (*maybe within the function itself or better here?)
    // Run the SD card version of the emulator
  }
  else
  {
    Serial.println("Error: No Mode Established");
    // Go back and re-enter parameters
  }
  
}

void loop() {
  readCommand();
  //if(recvd){
    Serial.println(String(command));
    //if(String(command)==PMTK_SET_NMEA_UPDATE_1HZ){
      while(altf<31000){
         readSerial();
         if(millis()-Timer>5000){
            sendGGA(GPGGA, 6); // Different companies, only send one of these at a time
            // sendRMC(GPRMC, 6); // Different companies, only send one of these at a time
            Serial.println(String(altf));
            //GPSserial.
            Time++;
            altf+=5;
            Timer = millis();
          }
      }
      while(altf>0){
        readSerial();
        if(millis()-Timer>5000){
          // RMC and GGA are two different kinds of NMEA strings
            sendGGA(GPGGA, 6);
            //sendRMC(GPRMC, 6);
            Serial.println(String(altf));
            Timer = millis();
            Time++;
            altf-=20;
        }
      }
    //}
//    else{
//      Serial.print("not set");
//    }
//    recvd = false;
  //}
//
//  if (millis() - sendTimer > 5000) {
//    sendGGA(GPGGA, 6);
//    sendTimer = millis();
//  }
  /*sendRMC(GPRMC, 6);
  Time++;
  altf+=1;*/
}
