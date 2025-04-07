#pragma once
#include <winsock2.h>
#include <string>
using namespace std;
class Server{
    public:
        static Server& getInstance();
        void start();

    private:
        Server();
        static const int PORT = 8080;
        static const int BUFFER_SIZE = 1024;
        WSADATA wsaData;
        SOCKET serverSocket;
        sockaddr_in serverAddr;
        string readFile(const string& filename);
        void handleClient(SOCKET clientSocket);
        string getContentPath(string filePath);
        string getResponse(string filePath, string content);
};