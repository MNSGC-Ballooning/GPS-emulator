Main Note: Use the Synthetic Flight option for VENT TESTING ONLY. 
           SD card flight will work for any microcontroller expecting Ublox GPS input. 
           Connect to your device via Serial 1 (Teensy pins 0/1) on the microcontroller utilizing this code. 
         
this is the code for the communicating arduino that will send signals to the other microcontroller
   acting as a fake Ublox GPS
   Base written by: Simon Peterson/Andrew Van Gerpen      edited by: Ben Stevens  Revision #2
   date: 6/13/17                                          date: 7/20/2021

    7/21/2021 Revision List (Ben Stevens) 
    Added ability to receive SD data in order to "re-fly" previous flights.
      --> Allows for copy/paste of GPS data from old flights onto a blank SD card of same name "in code" (default "TST01.CSV") 
      --> See example file TST01.CSV attached for an example of card format, 
          you can change the name of this file, but change it in code too (line 87)
      
    Added ability to fly a "synthetic" flight based on previous flight behavior (no SD data needed) 
      --> Based off of computer generated functions that simulate an "ideal" flight
      
    Added custom serial receiver function (readSerial) that provides fast, clean data transfer from external serial input
    Added ability to handle negative longitudinal decimal degree coordinates (Western Hemisphere)
    Added Ability to give "bad" GPS hits for testing (altitude via alt command) 
    Added ability to communicate with a vent in order to have accurate venting emulation
     
             MAKE SURE TO CHOOSE TRUE OR FALSE FOR LINE 27 BEFORE ANYTHING ELSE

    User Command List: (NOTE: all commands entered into the Serial Monitor must be in enclosed in <...> where "..." is the command)
          <START>  : Begins the emulation 
          <JUMP#>  : Sets altitude to # in feet
          <ALT#>   : Sets altitude to # in feet for only one GPS hit (for bad GPS hit testing)
          <LEAK>   : Begins emulation of a leak in the vent, will continue until vent tries to fix it 

