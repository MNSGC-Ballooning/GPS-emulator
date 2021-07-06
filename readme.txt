*********************************************************************************************************
*********************************************************************************************************
********************* MASTER BRANCH WORKS WITH ADAFRUIT ULTIMATE GPS ONLY.*******************************
********************* VISIT UBLOXGPS BRANCH IF YOU ARE USING A UBLOX      *******************************
*********************************************************************************************************
*********************************************************************************************************

GPS EMULATOR
by Simon Peterson (modified by Ben Stevens)

Revised by Ben Stevens for combatibility with Ublox GPS and added ability to read GPS data from an onboard SD card (7/6/2021) 

 --> original code only allowed for artifical GPS data to be fed
 --> Allows for copy/paste of GPS data from old flights onto a blank SD card of same "in code" (default "TST01.CSV") 
 --> See example file TST01.CSV attached for an example of card format
 
 Upload to any teensy, connect teensy to another microcontroller via serial1 (pins 0/1 , rx/tx) and it should act as a Ublox gps feeding at once per second


