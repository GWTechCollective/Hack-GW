import serial
import time
import sets
import logging
import subprocess

from oaconst import *

def parse_midi(midi_string, note_list):

    midi_string = midi_string[0]

    status = midi_string[0][0]
    note = midi_string[0][1]
    action = midi_string[0][2]

    note -= NOTE_OFFSET

    if(status == STATUS_GOOD):
        if(action == MIDI_NOTE_DOWN):
            note_list.add(note)

        elif(action == MIDI_NOTE_UP):
            note_list.discard(note)

        else:
            logging.warning("Invalid MIDI Action")
            note_list.clear()

    else:
        logging.warning("MIDI Interface Status Error - " + str(status))
        note_list.clear()

    return note_list

def pack_note_list(note_list):

    note_string = ''

    if(len(note_list) == 0):
        note_string = '255\x00\n'
    else:
        for note in note_list:
            note_string += (str(note) + '\x00\n')

    return note_string

def init_serial_connection():

    ser = None

    port = subprocess.check_output("find /dev/ -name \"*Arduino*\"", shell=True)
    port = port.strip()
    logging.info("Serial Port: " + port)

    while(ser == None):
        try:
            ser = serial.Serial(port, BAUD_RATE)
        except serial.serialutil.SerialException:
            logging.warning("Unable to create serial connection")
            time.sleep(2)
            ser = None

    return ser
