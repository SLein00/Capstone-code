
#pragma once
# ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
# endif
# ifndef VC_EXTRALEAN
#   define VC_EXTRALEAN
# endif
# ifndef NOMINMAX
#   define NOMINMAX
# endif
#include <windows.h>
#include <windows.h>
#include <iostream>

class SerialPort
{
public:
    //Constructors
    SerialPort();
    SerialPort(const char* port, unsigned long BaudRate);

    //Initialization
    void Initialize(const char* port, unsigned long BaudRate);

    //Serial I/O
    void receive(unsigned char& data, unsigned int byteSize);
    void transmit(char* data, unsigned int byteSize);

    //State
    void connect();
    void disconnect();
    bool isConnected();

    //Destructor
    ~SerialPort();

private:
    HANDLE handler;
    bool isConnect;
};