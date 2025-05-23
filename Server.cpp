#include <iostream>
#include <string>
#include <fstream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include "Server.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <filesystem>

using namespace std;

namespace fs = std::filesystem;

struct stat info;
const int PORT = 8080;
const int BUFFER_SIZE = 1024;

Server::Server(){
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);
}

Server& Server::getInstance(){
    static Server instance;
    return instance;
}
std::string Server::readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        return "";
    }
    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

void Server::start(){
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        return;
    }
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return;
    }
    // Bind the socket
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return;
    }
    
    // Listen for incoming connections
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return;
    }
    
    std::cout << "Server is listening on port " << PORT << "..." << std::endl;
    
    // Accept and process connections
    while (true) {
        SOCKET clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Accept failed: " << WSAGetLastError() << std::endl;
            continue;
        }
        
        std::cout << "New connection accepted" << std::endl;
        handleClient(clientSocket);
    }
}
string Server::getContentPath(string filePath){
    string contentPath="";
    cout << "File path: " << filePath << endl; 
    if(filePath.starts_with("/")) {
        filePath.erase(0,1);
    }
    if(filePath.ends_with("/")) {
        filePath.erase(filePath.length()-1,1);
    }
    fs::file_status stat = fs::status(filePath);
    if(filePath.empty()){
        contentPath = "./index.html";
    }
    else if(fs::is_directory(stat)){
        contentPath = filePath + "/index.html";
    } 
    else{
        contentPath = filePath;
    }
    cout << "contentPath:"<< contentPath << endl;
    return contentPath;
}
string Server::getResponse(string filePath, string content){
    string response;
    if(filePath.ends_with(".jpg")) {
        response = "HTTP/1.1 200 OK\r\n";
        response += "Content-Type: image/jpg\r\n";
        response += "\r\n";
        response += content;
    }
    else if (!content.empty()) {
        response = "HTTP/1.1 200 OK\r\n";
        response += "Content-Type: text/html\r\n";
        response += "\r\n";
        response += content;
    } else {
        response = "HTTP/1.1 404 Not Found\r\n";
        response += "Content-Type: text/html\r\n";
        response += "\r\n";
        response += "<h1>404 Not Found</h1>";
    }
    return response;
}
void Server::handleClient(SOCKET clientSocket){
    char buffer[BUFFER_SIZE] = {0};
    int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
    
    if (bytesReceived > 0) {
        std::string request(buffer);
        std::string filePath = "index.html"; // Default file
        string contentPath = "";
        // Parse GET request
        if (request.find("GET") != std::string::npos) {
            size_t start = request.find("GET") + 4;
            size_t end = request.find("HTTP/1.1") - 1;
            if (start < end && end != std::string::npos) {
                filePath = request.substr(start, end - start);
                contentPath = getContentPath(filePath);
            }
        }
        std::string content = readFile(contentPath);
        std::string response = getResponse(contentPath,content);
        
        send(clientSocket, response.c_str(), response.length(), 0);
    }
    
    closesocket(clientSocket);
}