#! /usr/bin/env python3

"""
Simulating a serial device that behaves like a pipe but still retains
the serial properties such as baudrate.
Inspired by a talk from Remi Audebert at the LSE EPITA on the 09/12/2014
Slides available here:
https://www.lse.epita.fr/data/lt/2014-12-09/lt-2014-12-09-R%C3%A9mi_Audebert-Serial_emulation.pdf
"""

import os
import pty
import time


class SerialEmulator:
    def __init__(self):
        self.master, slave = pty.openpty()
        print("Hey use this serial port:", os.ttyname(slave))

    def loop(self):
        while True:
            length = os.read(self.master, 15)
            print("received : {}".format(length))
            os.write(self.master, length)


i = SerialEmulator()
i.loop()
