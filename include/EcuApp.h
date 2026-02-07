#pragma once

#include <cstdint>
#include <string>

/*
 * Virtual ECU Application State
 */
struct EcuState
{
    bool ignitionOn;
    uint16_t vehicleSpeed;
    std::string vin;
    bool securityUnlocked;
    uint32_t resetCounter;
};

class EcuApp
{
public:
    static void Init();
    static EcuState& GetState();
    static void Reset();
};
