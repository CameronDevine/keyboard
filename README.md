#The Emoji Keyboard#

##FAQ##

If you run into any problems using the keyboard normally, please see the FAQ located here.

##Reprograming##

###Drivers###

This keybaord is an Adafruit Trinket 5V with three button and missing a couple of LEDs. If you would like to try to reprogram the board, the webpage here will guide you through installing the necessary drivers. And give a general introduction.

###Bootloader###

Once the correct drivers are installed, and you are ready to program the board, the bootloader needs to be activated. On the Adafruit Trinket there is a button supplied for this purpose. On the keyboard there are two ways this can be done.

####Method 1####

One way to activate the bootloader is to unplug the USB cable and plug it back in. This will start the bootloader for a couple seconds before the board enters its keyboard mode.

####Method 2####

The other meathod is to short the reset (Rst) and ground (Gnd) pins. This second method has the exact same effect as the reset button on the Trinket.
