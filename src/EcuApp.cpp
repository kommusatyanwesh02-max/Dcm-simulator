#include "EcuApp.h"

/*
 * Internal ECU state (simulated RAM)
 */
static EcuState ecuState;

/*
 * Initialize ECU state (Power ON)
 */
void EcuApp::Init()
{
    ecuState.ignitionOn      = true;
    ecuState.vehicleSpeed   = 0;
    ecuState.vin             = "VECU123456789012";
    ecuState.securityUnlocked = false;
    ecuState.resetCounter   = 0;
}

/*
 * Get current ECU state
 */
EcuState& EcuApp::GetState()
{
    return ecuState;
}

/*
 * ECU Reset simulation
 */
void EcuApp::Reset()
{
    ecuState.resetCounter++;
    ecuState.securityUnlocked = false;
    ecuState.vehicleSpeed = 0;
}
