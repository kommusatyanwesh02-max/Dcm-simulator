#include "Dcm_Services.h"

/*
 * 0x10 - Diagnostic Session Control
 */
Buffer Dcm_Services::DiagnosticSessionControl(const Buffer& request)
{
    if (request.size() != 2)
    {
        return NegativeResponse(0x10, NRC::INCORRECT_MESSAGE_LENGTH);
    }

    // Positive response: 0x50 + session type
    return { 0x50, request[1] };
}

/*
 * 0x11 - ECU Reset
 */
Buffer Dcm_Services::ECUReset(const Buffer& request)
{
    if (request.size() != 2)
    {
        return NegativeResponse(0x11, NRC::INCORRECT_MESSAGE_LENGTH);
    }

    // Positive response: 0x51 + reset type
    return { 0x51, request[1] };
}

/*
 * 0x22 - Read Data By Identifier
 */
Buffer Dcm_Services::ReadDataByIdentifier(const Buffer& request)
{
    if (request.size() != 3)
    {
        return NegativeResponse(0x22, NRC::INCORRECT_MESSAGE_LENGTH);
    }

    // Dummy DID data
    return { 0x62, request[1], request[2], 0x12, 0x34 };
}

/*
 * 0x3E - Tester Present
 */
Buffer Dcm_Services::TesterPresent(const Buffer&)
{
    return { 0x7E, 0x00 };
}

/*
 * Negative Response (0x7F)
 */
Buffer Dcm_Services::NegativeResponse(Byte sid, NRC nrc)
{
    return { 0x7F, sid, static_cast<Byte>(nrc) };
}
