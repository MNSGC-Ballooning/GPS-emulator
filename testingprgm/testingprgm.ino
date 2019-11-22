#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>


#define GPSserial Serial2 // RX and TX
Adafruit_GPS GPS(&GPSserial);
#define MAXMESSAGE 120
char recieved[MAXMESSAGE];
int ndx = 0;

struct GPSe
{
//  double latitudeDegrees;
//  double longitudeDegrees;
//  double altitude;
  String latitudeDegrees = "999";
  String longitudeDegrees = "999";
  String alt = "999";
}Fake_GPS;

void setup() {
GPS.begin(4800);
Serial.begin(9600);
GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);  
}

void loop() {
//
//Serial.println(GPSserial.available());

while (GPSserial.available() > 0) {
    GPS.read();
}
 
 if(GPS.newNMEAreceived()){
 Serial.println(GPS.lastNMEA());
  parse(GPS.lastNMEA());
  //getalt_parse(GPS.lastNMEA());
//  Serial.println("lat " + String(Fake_GPS.latitudeDegrees, 4)+ ", long " + String(Fake_GPS.longitudeDegrees, 4) + ", alt" + String(Fake_GPS.alt, 3));
  Serial.println("lat " + Fake_GPS.latitudeDegrees + ", long " + Fake_GPS.longitudeDegrees + ", alt " + String(3.28084*Fake_GPS.alt.toDouble()) + " feet (converted from meters)");
  ndx = 0;
 //}
 }
// else {
//  Serial.println("No GPS Data Received");
// }
 

}



// A function to parse the nmea strings for their latitude, longitude, and altitude. 
void parse(String lastNMEA) {
  int count = 0;      // Counts the number of commas iterated over thus far in the NMEA string
  int lat_count = 2;  //2 commas before the latitude reading
  int long_count = 4; // 4 commas before the longitude reading
  int alt_count = 9;  // 9 commas before the altitude reading

  int len = lastNMEA.length(); // We won't iterate past this number in the parser loop
  int index = 0;              // We'll iterate over the string with this
  while(index <= len) // Run while index is less then end of string 
  {
    if(lastNMEA[index]==',')
    {
      count++;
    }
    if(count==2)
    {
      int index_2 = index + 1;
      while(lastNMEA[index_2 + 1] != ',')
      {
        index_2++;
      }
      Fake_GPS.latitudeDegrees = lastNMEA.substring(index + 1, index_2); // You're at the latitude string, take and save it
      index = index_2 + 1;
      continue;
    }
    else if(count==4) // You're at the longitude string, take it and save it
    {
      int index_2 = index + 1;
      while(lastNMEA[index_2 + 1] != ',')
      {
        index_2++;
      }
      Fake_GPS.longitudeDegrees = lastNMEA.substring(index + 1, index_2); // You're at the latitude string, take and save it
      index = index_2 + 1;
      continue;
    }
    else if(count==9) // You're at the altitude string and now have to obtain it
    {
      int index_2 = index + 1;
      while(lastNMEA[index_2 + 1] != ',')
      {
        index_2++;
      }
      Fake_GPS.alt = lastNMEA.substring(index + 1, index_2); // You're at the latitude string, take and save it
      index = index_2 + 1;
      continue;
    }
      index++;
  }

}
