#include "DoIP.h"

/*
 * Encode UDS payload into DoIP frame
 */
Buffer DoIP::Encode(const Buffer& udsPayload)
{
    Buffer frame;

    uint16_t protocolVersion = 0x02FD;   // DoIP
    uint16_t payloadType     = 0x8001;   // Diagnostic message
    uint32_t payloadLength   = static_cast<uint32_t>(udsPayload.size());

    // ---- Header ----
    frame.push_back(static_cast<Byte>((protocolVersion >> 8) & 0xFF));
    frame.push_back(static_cast<Byte>(protocolVersion & 0xFF));

    frame.push_back(static_cast<Byte>((payloadType >> 8) & 0xFF));
    frame.push_back(static_cast<Byte>(payloadType & 0xFF));

    frame.push_back(static_cast<Byte>((payloadLength >> 24) & 0xFF));
    frame.push_back(static_cast<Byte>((payloadLength >> 16) & 0xFF));
    frame.push_back(static_cast<Byte>((payloadLength >> 8) & 0xFF));
    frame.push_back(static_cast<Byte>(payloadLength & 0xFF));

    // ---- Payload ----
    for (Byte b : udsPayload)
    {
        frame.push_back(b);
    }

    return frame;
}

/*
 * Decode DoIP frame and extract UDS payload
 */
Buffer DoIP::Decode(const Buffer& doipFrame)
{
    Buffer udsPayload;

    // Minimum DoIP header size = 8 bytes
    if (doipFrame.size() < 8)
    {
        return udsPayload;
    }

    uint32_t payloadLength =
        (doipFrame[4] << 24) |
        (doipFrame[5] << 16) |
        (doipFrame[6] << 8) |
        (doipFrame[7]);

    if (doipFrame.size() < 8 + payloadLength)
    {
        return udsPayload;
    }

    for (size_t i = 0; i < payloadLength; ++i)
    {
        udsPayload.push_back(doipFrame[8 + i]);
    }

    return udsPayload;
}
