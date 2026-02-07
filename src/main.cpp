#include "Dcm.h"
#include "Transport.h"
#include <iostream>

int main()
{
    Dcm::Init();

    std::cout << "DCM Simulator Started (Enter hex bytes)" << std::endl;

    while (true)
    {
        std::cout << "REQ> ";

        Buffer request = Transport::Receive();
        Buffer response = Dcm::ProcessRequest(request);

        std::cout << "RES> ";
        Transport::Send(response);
    }

    return 0;
}
