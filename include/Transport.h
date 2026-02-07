#pragma once

#include "Dcm_Types.h"

/*
 * Transport abstraction
 * For now: console-based I/O
 */
class Transport
{
public:
    /* Receive diagnostic request */
    static Buffer Receive();

    /* Send diagnostic response */
    static void Send(const Buffer& response);
};
