#include "Dcm.h"
#include "Transport.h"
#include "EcuApp.h"
#include "TcpTransport.h"
#include <iostream>

int main()
{
    // ECU power ON
    EcuApp::Init();

    // Initialize DCM
    Dcm::Init();

    // Start TCP server (DoIP-like)
    if (!TcpTransport::Init(13400))
    {
        std::cerr << "Failed to start TCP transport\n";
        return -1;
    }

    std::cout << "VECU ready for diagnostic requests\n";

    while (true)
    {
        Buffer request = TcpTransport::Receive();
        if (request.empty())
        {
            continue;
        }

        Buffer response = Dcm::ProcessRequest(request);
        TcpTransport::Send(response);
    }

    TcpTransport::Shutdown();
    return 0;
}

