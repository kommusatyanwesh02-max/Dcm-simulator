#pragma once

#include "Dcm_Types.h"

/*
 * Implements individual UDS services
 */
class Dcm_Services
{
public:
    /* UDS Services */
    static Buffer DiagnosticSessionControl(const Buffer& request);   // 0x10
    static Buffer ECUReset(const Buffer& request);                   // 0x11
    static Buffer ReadDataByIdentifier(const Buffer& request);       // 0x22
    static Buffer TesterPresent(const Buffer& request);              // 0x3E

    /* Negative response generator */
    static Buffer NegativeResponse(Byte sid, NRC nrc);
};
