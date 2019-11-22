GPS EMULATOR

by Simon Peterson (fixed, modified, and expanded by Jacob Meyer)

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

------New Readme------
New modes that will be implemented in Fall/Winter 2019 are the "Custom" and "Flight" modes. Custom mode
will give users the ability to specify rates of ascent and descent at any and all altitudes (on the way 
up and down) and the user will also be able to determine when cutaway/"burst" occurs. "Flight" mode will
use old flight data fed directly in via an SD card into the emulator. Both modes will allow much more 
accurate and effective simulations which will allow us to debug our flight computer(s)/state machines
 much more effectively before sending them up to 120,000+ feet. 