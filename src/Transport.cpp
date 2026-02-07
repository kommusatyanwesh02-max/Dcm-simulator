#include "Transport.h"
#include <iostream>
#include <sstream>
#include <cstdio>

/*
 * Receive request from console
 * Input format: hex bytes separated by space
 * Example: 22 F1 90
 */
Buffer Transport::Receive()
{
    Buffer buffer;
    std::string line;

    std::getline(std::cin, line);

    std::stringstream ss(line);
    int value;

    while (ss >> std::hex >> value)
    {
        buffer.push_back(static_cast<Byte>(value));
    }

    return buffer;
}

/*
 * Send response to console
 */
void Transport::Send(const Buffer& response)
{
    for (Byte b : response)
    {
        printf("%02X ", b);
    }
    printf("\n");
}
