#include <iostream>
#include <string>
#include <fstream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "Server.h"
// Link with ws2_32.lib
#pragma comment(lib, "ws2_32.lib")


int main() {
    Server& server = Server::getInstance();
    server.start();
    
    return 0;
} 