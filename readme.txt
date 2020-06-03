*********************************************************************************************************
*********************************************************************************************************
********************* MASTER BRANCH WORKS WITH ADAFRUIT ULTIMATE GPS ONLY.*******************************
********************* VISIT UBLOXGPS BRANCH IF YOU ARE USING A UBLOX      *******************************
*********************************************************************************************************
*********************************************************************************************************

GPS EMULATOR
by Simon Peterson (modified by Andrew Van Gerpen)

Revised by Andrew Van Gerpen for combatibility with Ublox GPS. (UbloxGPS branch)
 --> original code did not correctly output checksum value required for use with TinyGPS++ library
 --> Modified to use old flight data in simulating a flight rather than incrementing values. Feel free to change lat,lon,and alt arrays          using flight data of your choice.

---old readme---

This program uses an arduino uno to act as an adafruit ultimate GPS, allowing for testing payloads
that require GPS data without actually flying them.

Currently sends a GGA NMEA and RMC messgages which contains latitude, longitude, fix, and altitude. Code
can easily be modified to simulate different flight conditions.

To "Jump" a certain altitude in while simulating a flight, simply type "jumpALT", where alt is the
positive or negative altitude you wish to jump by. For example, jumping up 150 meters is done by
typing "jump150" into the serial monitor and sending the message. Make sure the ending is set to 
newline. Note that the jump does not automatically jump back. This is useful for testing what happens
when gps data gets scrambled at higher altitudes.

Possible future modifications include SD GPS data reading - the Arduino reads coordinates and altitude 
from a previous flight and sends them as GPS signals, making it possible to "refly" a previous flight.

