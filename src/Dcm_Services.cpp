#include "Dcm_Services.h"
#include "EcuApp.h"

static Byte lastSeed = 0x00;

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

    Byte resetType = request[1];

    // Only support Hard Reset (0x01) for now
    if (resetType != 0x01)
    {
        return NegativeResponse(0x11, NRC::SUBFUNCTION_NOT_SUPPORTED);
    }

    // Perform ECU reset (application-level)
    EcuApp::Reset();

    // Positive response: 0x51 + reset type
    return { 0x51, resetType };
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

    Byte didHigh = request[1];
    Byte didLow  = request[2];

    EcuState& ecu = EcuApp::GetState();

    // ---- DID F190 : VIN ----
    if (didHigh == 0xF1 && didLow == 0x90)
    {
        Buffer response = { 0x62, 0xF1, 0x90 };

        for (char c : ecu.vin)
        {
            response.push_back(static_cast<Byte>(c));
        }

        return response;
    }

    // ---- DID F187 : Vehicle Speed (security protected) ----
    if (didHigh == 0xF1 && didLow == 0x87)
    {
        if (!ecu.securityUnlocked)
        {
            return NegativeResponse(0x22, static_cast<NRC>(0x33)); // Security Access Denied
        }

        Buffer response = {
            0x62, 0xF1, 0x87,
            static_cast<Byte>((ecu.vehicleSpeed >> 8) & 0xFF),
            static_cast<Byte>(ecu.vehicleSpeed & 0xFF)
        };

        return response;
    }

    return NegativeResponse(0x22, NRC::SUBFUNCTION_NOT_SUPPORTED);
}


/*
 * 0x3E - Tester Present
 */
Buffer Dcm_Services::TesterPresent(const Buffer&)
{
    return { 0x7E, 0x00 };
}

/*
 * 0x27 - Security Access
 * Sub-function:
 *  0x01 -> Request Seed
 *  0x02 -> Send Key
 */
Buffer Dcm_Services::SecurityAccess(const Buffer& request)
{
    if (request.size() < 2)
    {
        return NegativeResponse(0x27, NRC::INCORRECT_MESSAGE_LENGTH);
    }

    Byte subFunction = request[1];

    // ---- Request Seed (27 01) ----
    if (subFunction == 0x01)
    {
        if (request.size() != 2)
        {
            return NegativeResponse(0x27, NRC::INCORRECT_MESSAGE_LENGTH);
        }

        lastSeed = 0x5A;     // dummy seed
        EcuApp::GetState().securityUnlocked = false;

        return { 0x67, 0x01, lastSeed };
    }

    // ---- Send Key (27 02 <KEY>) ----
    if (subFunction == 0x02)
    {
        if (request.size() != 3)
        {
            return NegativeResponse(0x27, NRC::INCORRECT_MESSAGE_LENGTH);
        }

        Byte receivedKey = request[2];
        Byte expectedKey = static_cast<Byte>(lastSeed + 1);

        if (receivedKey == expectedKey)
        {
            EcuApp::GetState().securityUnlocked = true;
            return { 0x67, 0x02 };
        }
        else
        {
            return NegativeResponse(0x27, static_cast<NRC>(0x35)); // Invalid Key
        }
    }

    return NegativeResponse(0x27, NRC::SUBFUNCTION_NOT_SUPPORTED);
}

/*
 * Negative Response (0x7F)
 */
Buffer Dcm_Services::NegativeResponse(Byte sid, NRC nrc)
{
    return { 0x7F, sid, static_cast<Byte>(nrc) };
}
