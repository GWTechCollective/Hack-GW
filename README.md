# Hack-GW
A MIDI-keyboard controlled LED light show to accompany musical performances.

## Arduino

The provided Arduino code sets up a serial monitor to listen for values sent by the computer parsing the MIDI commands, in this case a Raspberry Pi. It then determines the R,G,B values to assign based on which key is pressed and uses PWM to control the LEDs. 

### Installation

Simply upload the Arduino sketch provided in the Arduino folder using the Arduino IDE.

### Circuit

An LED driver circuit is required to control the RGB LED strip running at 12V with the Arduino Uno, which runs at 5V. The basic circuit used can be found at https://learn.adafruit.com/rgb-led-strips/usage. For this implementation, we used a 12V, 5A power supply connected directly to the LED strip. *Do not connect through the Vin pin on the Arduino as shown in the diagram if you will be pulling more than 1A as this may damage the Arduino.* Assume roughly 1A per meter to be safe.

## Raspberry Pi

A Raspberry Pi is used to read MIDI values from a USB-MIDI adapter. However, any computer with Python 2.7 should be able to run this code with minimal modification.

### Requirements
Run the following to make sure the required modules are available in your Python installation:
```
sudo apt-get install python-pygame python-serial
```


### Installation

The Python script may be found in the `opto-audio` folder from the `raspberry-pi` subdirectory. You may run this by calling `python ./opto-audio.py`.

On a Raspberry Pi, you may set the script up as a daemon that runs at boot by adding the provided `opto-audio.sh` file to `/etc/init.d/` and running `sudo update.rc opto-audio.sh defaults`. You may then start and stop the service using the built in commands:
```
sudo service opto-audio start
sudo service opto-audio stop
```
