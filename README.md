# Subject

The aim of the task is to write a small programm to display data from a captor
sent through a serial port of the computer. The data is sent as
"protocol buffers".

# Author

* Loic Banet

# Rules of the Makefile

* [all] : compiles all the protoc files and the sensor\_reading binary
        (python and c++)
* [pb-python] : generates python protobuf files from ``sensor.proto``
* [pb-cpp] : generates c++ protobuf files from ``sensor.proto``
* [init] : installs the python requirements with pip
* [build] : generates a ``sensor\_reading`` binary from the c++ code.
* [debug] : compiles the c++ code with debug flags
* [clean] : cleans the project

# Submission

## Python

The solution of the exercice is the file ``sensor_reading.py``
in the python folder. To execute the script you have to at least build
the python protobuf file with the ``make pb-python`` rule.

## C++

When you ``make`` or ``make build`` the binary ``sensor_reading`` is created
at the root of the repository. The c++ code is available in the
``sensor_reading.cc`` file in the ``cpp`` directory.

# Usage

Usage python:
    ./sensor_reading.py [Serial Port] [baudrate] (timeout)

Usage c++:
    ./sensor_reading [Serial Port] [baudrate] (timeout)

The two first arguments are mandatory.
The timeout value is expected as an integer in seconds. It is optionnal.
If it is not specified the program will wait on the serial.

# Tests

The program was tested on a debian architechture. Two python scripts are
available in the ``tests`` directory:
* ``sensor\_writing.py`` : Script to encode in protobuf and cobs
    some dummy sensor datas.
* ``serial\_simulator.py`` : Creates a dummy serial port wich behaves
like a pipe based on a pseudoterminal on linux.

## Run the tests

To run the test first of all ``make`` the project. Then launch the
``serial\_simulator`` script. Il will print the serial port available.

For example:
```bash
$ > ./tests/serial\_simulator.py
Hey use this serial port: /dev/pts/5
```

Following the example above you then have to launch the ``sensor\_reading``
program on the serial port ``/dev/pts/5`` and then launch the
``sensor\_writing.py`` script also on the serial port ``/dev/pts/5``.
The sensor writing script takes the same parameters as the sensor reading.
