#include "TcpTransport.h"
#include "DoIP.h"
#include <iostream>

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#endif

static int serverSocket = -1;
static int clientSocket = -1;

bool TcpTransport::Init(uint16_t port)
{
#ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        std::cerr << "WSAStartup failed\n";
        return false;
    }
#endif

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0)
    {
        std::cerr << "Socket creation failed\n";
        return false;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
    {
        std::cerr << "Bind failed\n";
        return false;
    }

    if (listen(serverSocket, 1) < 0)
    {
        std::cerr << "Listen failed\n";
        return false;
    }

    std::cout << "VECU TCP server listening on port " << port << std::endl;

    sockaddr_in clientAddr{};
#ifdef _WIN32
    int len = sizeof(clientAddr);
#else
    socklen_t len = sizeof(clientAddr);
#endif

    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &len);
    if (clientSocket < 0)
    {
        std::cerr << "Accept failed\n";
        return false;
    }

    std::cout << "Tester connected\n";
    return true;
}

Buffer TcpTransport::Receive()
{
    Buffer tcpBuffer;
    uint8_t data[512]{};

    int received = recv(clientSocket, reinterpret_cast<char*>(data), sizeof(data), 0);
    if (received <= 0)
    {
        return tcpBuffer;
    }

    for (int i = 0; i < received; ++i)
    {
        tcpBuffer.push_back(data[i]);
    }

    // Decode DoIP frame to get UDS payload
    return DoIP::Decode(tcpBuffer);
}

void TcpTransport::Send(const Buffer& response)
{
    if (clientSocket < 0)
        return;

    Buffer doipFrame = DoIP::Encode(response);

    send(clientSocket,
         reinterpret_cast<const char*>(doipFrame.data()),
         static_cast<int>(doipFrame.size()),
         0);
}

void TcpTransport::Shutdown()
{
#ifdef _WIN32
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
#else
    close(clientSocket);
    close(serverSocket);
#endif
}
