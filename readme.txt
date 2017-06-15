GPS EMULATOR

by Simon Peterson

This program uses an arduino uno to act as an adafruit ultimate GPS, allowing for testing payloads
that require GPS data without actually flying them.

Currently sends a GGA NMEA messgae which contains latitude, longitude, fix, and altitude. Code can
easily be modified to simulate different flight conditions.

Future improvements: adding RMX NMEA message sending, which would allow speed and heading to be sent.