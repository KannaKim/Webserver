#pragma once
#include <winsock2.h>
#include <string>
class Server{
    public:
        static Server& getInstance();
        void start();
        void handleClient(SOCKET clientSocket);

    private:
        Server();
        static const int PORT = 8080;
        static const int BUFFER_SIZE = 1024;
        WSADATA wsaData;
        SOCKET serverSocket;
        sockaddr_in serverAddr;
        std::string readFile(const std::string& filename);
};