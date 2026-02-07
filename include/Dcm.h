#pragma once

#include "Dcm_Types.h"

/*
 * DCM core interface
 * Responsible for dispatching UDS services
 */
class Dcm
{
public:
    /* Initialize DCM module */
    static void Init();

    /* Process a diagnostic request and return response */
    static Buffer ProcessRequest(const Buffer& request);
};
