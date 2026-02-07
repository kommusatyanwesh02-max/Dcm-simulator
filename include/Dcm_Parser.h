#pragma once

#include "Dcm_Types.h"

/*
 * Responsible for parsing incoming diagnostic requests
 */
class Dcm_Parser
{
public:
    /* Extract Service ID (SID) from request */
    static Byte GetServiceId(const Buffer& request);
};
