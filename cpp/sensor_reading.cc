#include <iostream>
#include <cstdlib>
#include <string>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>

#include "sensor.pb.h"

void dump_sensor(const SensorReading& sr, std::ostream& ostr)
{
    ostr << "Read from sensor reading number "
        << sr.id() << std::endl
        << "\tco2 level : "
        << sr.co2() << std::endl
        << "\ttemperature : "
        << sr.temperature() << std::endl
        << "\thumidity : "
        << sr.humidity() << std::endl
        << std::endl;
}

void help(const std::string& name)
{
    std::cerr << "Usage:" << std::endl
        << "\t"
        << name
        << " [Serial Port] [baudrate] (timeout)"
        << std::endl;
}

std::string cobs_decode(const std::string& input)
{
    size_t read_idx = 0;
    std::string output;

    while (read_idx < input.length())
    {
        uint8_t value = input[read_idx++];

        // overhead byte
        if (read_idx + value - 1 > input.length() && value != 1)
            break;

        for (uint8_t i = 0; i < value; ++i)
            output += input[read_idx++];

        /*auto substr = input.substr(read_idx, value);
        output += substr;
        read_idx += substr.length();*/

        if (value < 0xFF && read_idx != input.length())
            output += '\0';
    }
    return output;
}

int decode_and_dump(const std::string& line)
{
    auto data = cobs_decode(line);
    SensorReading sr;
    if (sr.ParseFromString(data))
    {
        std::cerr << "Error: Input data is not a valid sensor reading"
            << std::endl;
        return 0;
    }

    dump_sensor(sr, std::cout);
    return 1;
}

// returns fd
int open_port(const char* port, int baud, int timeout)
{
    int fd = open(port, O_RDWR | O_NOCTTY | O_SYNC);
    struct termios settings;
    speed_t baudrate = baud;

    tcgetattr(fd, &settings);
    cfsetispeed(&settings, baudrate);

    settings.c_cflag &= ~PARENB; /* no parity */
    settings.c_cflag &= ~CSTOPB; /* 1 stop bit */
    settings.c_cflag &= ~CSIZE;
    settings.c_cflag |= CS8 | CLOCAL; /* 8 bits */
    /* echo off, echo newline off, canonical mode off,
     * extended input processing off, signal chars off
     */
    settings.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
    settings.c_oflag = 0; /* Turn off output processing */
    settings.c_cflag &=  ~CRTSCTS;
    /* Read settings :
     * To understand the settings have a look at man 3 termios
     * ``Canonical and noncanonical mode`` section
     */
    settings.c_cc[VMIN]   =  1; /* read doesn't block */
    settings.c_cc[VTIME]  =  timeout * 10; /* read timeout in ds */
    settings.c_cflag     |=  CREAD;

    /* Flush Port, then applies attributes */
    tcflush(fd, TCIFLUSH);
    if (tcsetattr(fd, TCSANOW, &settings) < 0) /* apply the settings */
        return -1;

    return fd;
}


int main(int argc, char **argv)
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    if (argc != 3 && argc != 4)
    {
        help(argv[0]);
        return 1;
    }
    auto port = argv[1];
    auto baud = std::atoi(argv[2]);
    int timeout = (argc == 4) ? std::atoi(argv[3]) : 0;

    int fd = open_port(port, baud, timeout);
    if (fd == -1)
    {
        std::cerr << "Error while opening port " << port << std::endl;
        help(argv[0]);
        return 1;
    }

    char c;
    std::string line;
    while (read(fd, &c, 1) > 0)
    {
        if (c == '\0')
        {
            if (!decode_and_dump(line))
                return 2;
            line.clear();
        }
        else
            line += c;
    }

    close(fd);
    return 0;
}
