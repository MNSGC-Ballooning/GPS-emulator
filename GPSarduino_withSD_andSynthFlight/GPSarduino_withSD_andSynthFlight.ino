//=============================================Edit to emultor code 6-27-22 by Ethan Thompson-Jewell  =======================================

//==========================================================================================================================================
//#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <SD.h>

/*this is the code for the communicating arduino that will send signals to the other microcontroller
   acting as a fake Ublox GPS
   Base written by: Simon Peterson      edited by: Ben Stevens  Revision #2
   date: 6/13/17                        date: 7/20/2021

    7/21/2021 Revision List
    Added ability to receive SD data in order to "re-fly" previous flights.
    Added custom serial receiver function (readSerial) that provides fast, clean data transfer from external serial input
    Added ability to handle negative decimal coordinates (Western Hemisphere)
    Added Ability to give "bad" GPS hits for testing
    Added ability to communicate with vent in order to have accurate venting emulation

    NOTE: Synthetic Flights were specifically made to be used as emulation for VENT testing,
    while SD card flights can be used for any purpose, you just need to make or get the GPS data.

             MAKE SURE TO CHOOSE TRUE OR FALSE FOR LINE 31 BEFORE ANYTHING ELSE

    User Command List: (NOTE: all commands entered into the Serial Monitor must be in enclosed in <...> where "..." is the command)
          <JUMP#> : Sets altitude to # in feet
           <ALT#>  : Sets altitude to # in feet for only one GPS hit (for bad GPS hit testing)
*/


bool SDFlight = false; //  "true" for an SD "refly" of exsisting data, set to "false" for a synthetic flight

/////////////////////////////////////////////////////////
//////////SETUP Variables for Synthetic FLight/////////// ///change these for each synthetic flight if you choose
/////////////////////////////////////////////////////////
int seed = 9696; ///CHANGE SEED FOR RNG, ELSE ALTITUDE INCREASE RANDOMNESS WILL ALWAYS BE THE SAME
float latSynth = 0.444;
float longSynth = -93.8;
float altSynth = 1000;

float leak = 0;
bool isLeaking = false;
String SynthData = "";
float lastAlt = 0;
float AltTerminatedAt = 0;
bool TerminationCheck = false;
int termDelaySeconds = 0; //variable that records how long it has been since the emulator has received the command that the vent it terminating. this is to help vent test resistor burners
float CurrentRate = 0;
bool emulationActive = false;

float altToTerminateAt = 110000;  //variable that if altitude is reached balloon will automatically burst
float ascentRateAtLaunch = 16;    //variable that sets the base ascent rate at launch here 16ft/s
//float ascentRate50kPlus = 13;  //not using currently
float postVentNoiseReduction = 0; //change this variable if want the feature of having less GPS uncertianty after venting. this variable reduces the SD of ascentrate after first time venting happens

int prevent1Alt = 70000; //altitudes for each prevent to start
int prevent2Alt = 80000;
int prevent3Alt = 90000;

//================================================VARIABLES TO ADJUST BALLOONS ASCENT RATE================================================================
const float two_pi = 6.28318530718;
float ascentRateSDatLaunch = 3; //standard deviation of ascent rate 3 based on GL175 ascent rate from 0-50K
float ascentRateSD = ascentRateSDatLaunch; 
float meanAscentRate = ascentRateAtLaunch; //mean value of ascent rate is equal to launch ascent rate (should be initialized to 16ft/s for ~5m/s ascent rate)

float meanAscentRateHold = meanAscentRate; //these variables are used to hold ascent rate variables so if changed mid flight they could be changed back using RASCENTRATE and RSDSET commands
float ascentRateSDHold = ascentRateSD;

bool meanAscentRateEnteredByUser = false; //variable that tells if a specific ascent rate has been entered by user. works with ascent rate logic later on
bool ascentRateSDEnteredByUser = false;  //similar to above variable but for the standard deviation
//================================================END OF VARIABLES TO ADJUST BALLOONS ASCENT RATE================================================================

///////////////////////////////////
///////////GPS Variables///////////
///////////////////////////////////
#define MAXMESSAGE 120
unsigned long Time = 0;    //Time in seconds
float latf = 00.0000;   //DDMM.MMMM
char latCard = 'N';
char longiCard = 'W';
//the alt array is global to prevent memory allocation overlap in NMEA function
char alt[15];
float longf = 00.0000;  //DDDMM.MMMM
float altf = 300;         //Altitude in meters. 300 is pretty standard starting place
char command[MAXMESSAGE];
char GPGGA[7] = "$GPGGA";
char GPRMC[7] = "$GPRMC";
#define GPSserial Serial1
bool ventState = false;
float HitAltf = 0.0;
float HoldAlt = 0.0;

//////////////////////////////////
//////Serial Com Variables////////
//////////////////////////////////
boolean recvd = false;
unsigned long Timer = 0;
float ventBy = 0.00;
int GPSsemi = 0;
char GPSchars[50];
int GPScounter = 0;
int GPStrack[3] = {0, 0, 0};
char GPSreplace[] = ";";
bool altCommand = false;
const byte numChars = 25;
char receivedChars[numChars];


//////////////////////////////////
//////////SD Variables////////////
//////////////////////////////////
#define chipSelect BUILTIN_SDCARD                       // Using built in chipselect on Teensy 3.5
File datalog;                                           // File object to be opened, written to, and closed
char filename[] = "TST01.CSV";                          // File name of flight that will be read, FILE ON SD MUST HAVE EXACTLY THE SAME NAME
bool sdActive = false;
int dataLogs = 0;

//////////////////////////////////
/////Troubleshooting Variables////    (Was used for Trouble shooting GPS runtime issue, resolved 6/6/22)
//////////////////////////////////
/*
float currentRMCmillis;
float currentNMEAmillis;

float pastRMCmillis [10]; //arrays of times that NMEA and RMC print to gps serial
float pastNMEAmillis [10];

float diffRMCmillis;
float pastDiffRMC [10]; 

float diffNMEAmillis;
float pastDiffNMEA [10];
*/
void setup() {
  Serial.begin(14400);
  GPSserial.begin(9600); //for ublox GPS modules. Varies by model.
  pinMode(LED_BUILTIN, OUTPUT);
  if (SDFlight == true) {
    SDSetup();
  }
  randomSeed(seed); //change to random number else flight will be the same
  Serial.println("Using code edited 6-27-22");                            //////////////////////////////CHANGE DATE WHEN DONE EDITING ///////////////////////////////////
}

void loop() {
  Time = millis() / 1000;
  if (SDFlight == true) {
    readCommand();
    getData();
    Serial.println("End of Simulation");
    delay(100000); // Basically freeze program once the simulation has ended
  }

  else {
    SyntheticFlight();
  }

}
