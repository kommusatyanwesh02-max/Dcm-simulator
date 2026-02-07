#pragma once

#include <cstdint>
#include <vector>

/* Basic types */
using Byte   = uint8_t;
using Buffer = std::vector<Byte>;

/* Standard DCM return type */
enum class Dcm_ReturnType
{
    OK,
    NOT_OK
};

/* Negative Response Codes (ISO 14229 - subset) */
enum class NRC : uint8_t
{
    GENERAL_REJECT            = 0x10,
    SERVICE_NOT_SUPPORTED     = 0x11,
    SUBFUNCTION_NOT_SUPPORTED = 0x12,
    INCORRECT_MESSAGE_LENGTH  = 0x13
};
