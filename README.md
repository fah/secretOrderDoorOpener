# secretOrderDoorOpener
This is a small Arduino project. 
Enter a code in a certain order to activate a relay.
Add buttons to the input pins of the controller of your choice and press them in the hard coded order.

This is the implementation of an idea I've seen in a [reddit] (http://www.reddit.com/r/arduino/comments/bpewb1/more_logical_way_of_coding_sequential_inputs/) post. 


In this example only 2 pins are used, which must be pressed in a certain order. Here the pins 11, 13, 11 (to gnd) are used. After that an output is activated for 1 second (HIGH). 
If the input process is interrupted for more than 5 seconds, the sequence detector is reset.

This was tested with an Arduino UNO board. However, it is a general solution that works with ESP8266 or ESP32 etc.

The extension to more available input ports or the modification to use a port extender should be very easy.
