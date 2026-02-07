#pragma once

#include "Dcm_Types.h"
#include <cstdint>

/*
 * Simplified DoIP header (ISO 13400 inspired)
 */
struct DoIPHeader
{
    uint16_t protocolVersion;   // 0x02FD
    uint16_t payloadType;       // 0x8001 (Diagnostic)
    uint32_t payloadLength;     // Length of UDS payload
};

class DoIP
{
public:
    static Buffer Encode(const Buffer& udsPayload);
    static Buffer Decode(const Buffer& doipFrame);
};
