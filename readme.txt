GPS EMULATOR

by Simon Peterson

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