#! /usr/bin/env python3

import os
import sys
import serial

from cobs import cobs

sys.path.append('{}/../python'.format(os.path.dirname(sys.argv[0])))

import sensor_pb2 as spb

# For example : ./sensor_writing.py /dev/ttyUSB0
if len(sys.argv) != 3:
    print('Usage:')
    print('    {} [Serial Port] [baudrate]'.format(sys.argv[0]))
    sys.exit(1)

port = sys.argv[1]
baud = int(sys.argv[2])
__index = 1


def writeDummyReading(co2, temp, humid):
    global __index
    sensor = spb.SensorReading()
    sensor.id = __index
    __index += 1
    sensor.co2 = co2
    sensor.temperature = temp
    sensor.humidity = humid
    return sensor.SerializeToString()

with serial.Serial(port, baud, timeout=None) as ser:
    data1 = cobs.encode(writeDummyReading(30, 24.4, 12.8))
    ser.write(data1)
    ser.write(b'\0')
    data2 = cobs.encode(writeDummyReading(45, 22.4, 19.8))
    ser.write(data2)
    ser.write(b'\0')
    data3 = cobs.encode(writeDummyReading(11, 12.6, 90.2))
    ser.write(data3)
    ser.write(b'\0')
