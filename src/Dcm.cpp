#include "Dcm.h"
#include "Dcm_Parser.h"
#include "Dcm_Services.h"

/*
 * Initialize DCM module
 */
void Dcm::Init()
{
    // Future: initialize sessions, security, timers
}

/*
 * Main DCM request dispatcher
 */
Buffer Dcm::ProcessRequest(const Buffer& request)
{
    if (request.empty())
    {
        return Dcm_Services::NegativeResponse(
            0x00, NRC::INCORRECT_MESSAGE_LENGTH);
    }

    Byte sid = Dcm_Parser::GetServiceId(request);

    switch (sid)
    {
        case 0x10:
            return Dcm_Services::DiagnosticSessionControl(request);

        case 0x11:
            return Dcm_Services::ECUReset(request);

        case 0x22:
            return Dcm_Services::ReadDataByIdentifier(request);

        case 0x3E:
            return Dcm_Services::TesterPresent(request);
        
        case 0x27:
            return Dcm_Services::SecurityAccess(request);

        default:
            return Dcm_Services::NegativeResponse(
                sid, NRC::SERVICE_NOT_SUPPORTED);
    }
}
