[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

# Sensor Reading

Decode and display data recieved through a serial port from sensors.
The data is sent as "protocol buffers" with the
Consistent Overhead Byte Stuffing algorithm for the data transmission
over serial port.

# Build the project

## Requirements

### Python

* protobuf
* pyserial
* cobs

### C++

* Protocol buffer

## Make

You can use GNU make with the following rules:

* [all] : compiles all the protoc files and the sensor\_reading binary
        (python and c++)
* [pb-python] : generates python protobuf files from ``sensor.proto``
* [pb-cpp] : generates c++ protobuf files from ``sensor.proto``
* [init] : installs the python requirements with pip
* [build] : generates a sensor\_reading binary from the c++ code.
* [debug] : compiles the c++ code with debug flags
* [clean] : cleans the project

# Usage

Usage python:
    ./sensor_reading.py [Serial Port] [baudrate] (timeout)

Usage c++:
    ./sensor_reading [Serial Port] [baudrate] (timeout)

The two first arguments are mandatory.
The timeout value is expected as an integer in seconds. It is optionnal.
If it is not specified the program will wait on the serial.

# Message sent

The message recieved can be customized through the sensor.proto file.
For now it is composed of two uint32 and two floats as followed:

```
message SensorReading {
    uint32 id = 1;
    uint32 co2 = 2;
    float temperature = 3;
    float humidity = 4;
}
```

# Sources

## Python

The code is the file ``sensor_reading.py``
in the python folder. To execute the script you have to at least build
the python protobuf file with the ``make pb-python`` rule.

## C++

When you ``make`` or ``make build`` the binary ``sensor_reading`` is created
at the root of the repository. The c++ code is available in the
``sensor_reading.cc`` file in the ``cpp`` directory.

# Tests

The program was tested on a debian architechture. Two python scripts are
available in the ``tests`` directory:
* ``sensor_writing.py`` : Script to encode in protobuf and cobs
    some dummy sensor datas.
* ``serial_simulator.py`` : Creates a dummy serial port wich behaves
like a pipe based on a pseudoterminal on linux.

## Run the tests

To run the test first of all ``make`` the project. Then launch the
``serial_simulator`` script. Il will print the serial port available.

For example:
```bash
$ > ./tests/serial_simulator.py
Hey use this serial port: /dev/pts/5
```

Following the example above you then have to launch the ``sensor_reading``
program on the serial port ``/dev/pts/5`` and then launch the
``sensor_writing.py`` script also on the serial port ``/dev/pts/5``.
The sensor writing script takes the same parameters as the sensor reading.

# Author

* Loic Banet

# License

MIT License

Copyright (c) 2018 Loic Banet

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

