# Subject

The aim of the task is to write a small programm to display data from a captor
sent through a serial port of the computer. The data is sent as
"protocol buffers".

# Author

* Loic Banet

# Rules of the Makefile

* [all | comp] : generates python files from ``.proto`` file with ``protoc``
* [init] : installs the requirements with pip
* [clean] : cleans the trash and generated files

# Submission

The solution of the exercice is the file ``sensor_reading.py``
in the src folder.

# Usage

Usage:
    ./sensor_reading.py [Serial Port] [baudrate] (timeout)

The two first arguments are mandatory.
The timeout value is expected as an integer in seconds. It is optionnal.
If it is not specified the programm will wait on the serial.
