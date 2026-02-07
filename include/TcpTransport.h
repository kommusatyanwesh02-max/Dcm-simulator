#pragma once

#include "Dcm_Types.h"

/*
 * TCP Transport for VECU
 * Acts like a simple DoIP-style interface
 */
class TcpTransport
{
public:
    static bool Init(uint16_t port);
    static Buffer Receive();
    static void Send(const Buffer& response);
    static void Shutdown();
};
