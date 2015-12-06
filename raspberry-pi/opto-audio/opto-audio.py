# Opto-Audio
#
# Reads MIDI input and converts notes to colors forwarding them to an arduino via serial
#
# Mark Tentindo & Brandon Bernier
# markten@gwu.edu
#

## IMPORTS
import pygame.midi
import serial
import sets
import serial.serialutil
import logging

from oaconst import *
from oafuncs import *

if __name__ == '__main__':

    # GLOBALS
    note_list = set()

    logging.basicConfig(filename='opto-audio.log',level=logging.DEBUG)

    # Create MIDI Connection
    pygame.midi.init()

    midi_device = pygame.midi.Input(DEVICE_ID)

    # Create serial connection
    ser = init_serial_connection()

    # Listen for instrument notes
    while(True):

        if(midi_device.poll()):
            midi_string = midi_device.read(1)
            note_list = parse_midi(midi_string, note_list)

        note_string = pack_note_list(note_list)

        try:
            ser.write(note_string)

        except serial.serialutil.SerialException:
            logging.error("Serial Connection Lost")
            note_list.clear()
            ser = init_serial_connection()
