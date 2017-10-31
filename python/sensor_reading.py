#! /usr/bin/env python3

import sys

import sensor_pb2 as spb
import serial

from cobs import cobs

# For example : ./sensor_reading.py /dev/ttyUSB0 19200
if len(sys.argv) != 3 and len(sys.argv) != 4:
    print('Usage:')
    print('    {} [Serial Port] [baudrate] (timeout)'.format(sys.argv[0]))
    sys.exit(1)

port = sys.argv[1]
baud = int(sys.argv[2])
tOut = None

if sys.argv == 4:
    tOut = int(sys.argv[3])


def printSensor(data):
    sensor = spb.SensorReading()
    sensor.ParseFromString(data)
    print('Read from sensor reading number {}'.format(sensor.id))
    print('    co2 level : {}'.format(sensor.co2))
    print('    temperature : {:.{prec}f}'.format(sensor.temperature, prec=3))
    print('    humidity : {:.{prec}f}'.format(sensor.humidity, prec=3))
    print('')


with serial.Serial(port, baud, timeout=tOut) as ser:
    while True:
        data = []
        c = ser.read()
        if c == b'':
            break
        while c != b'\x00' and c != b'':
            data.append(c)
            c = ser.read()
        data = b''.join(data)
        printSensor(cobs.decode(data))
