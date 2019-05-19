# secretOrderDoorOpener
Small Arduino project example. Enter a code in a certain order to activate a relay.

This is the implementation of an idea I've seen in a redit post.

The example uses only 2 pins that have to be pressed in a certain order of 3 presses. After that an output will be activated (HIGH) for 1 second. 
If the process is interrupted for more then 5 seconds the sequence detector will be reset.

This has been tested with an arduino UNO board. But it is a general solution that will work wit ESP8266 or ESP32 a.s.o.
