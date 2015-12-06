# Hack-GW
A MIDI-keyboard controlled LED light show to accompany musical performances.

## Arduino

The provided arduino code sets up a serial monitor to listen for values sent by the computer parsing the MIDI commands, in this case a Raspberry Pi.

### Installation

Simply upload the Arduino sketch provided in the Arduino folder using the Arduino IDE.

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
