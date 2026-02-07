#include "Dcm_Parser.h"

/*
 * Extract Service ID from diagnostic request
 */
Byte Dcm_Parser::GetServiceId(const Buffer& request)
{
    return request[0];
}
