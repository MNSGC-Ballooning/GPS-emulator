GPS EMULATOR

by Simon Peterson

This program uses an arduino uno to act as an adafruit ultimate GPS, allowing for testing payloads
that require GPS data without actually flying them.

Currently sends a GGA NMEA and RMC messgages which contains latitude, longitude, fix, and altitude. Code
can easily be modified to simulate different flight conditions.

Possible future modifications include SD GPS data reading - the Arduino reads coordinates and altitude 
from a previous flight and sends them as GPS signals, making it possible to "refly" a previous flight.