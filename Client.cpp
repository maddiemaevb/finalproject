#include <iostream>
#include <sys/socket.h>
#include "Client.h"
#include <cstring>
#include <thread>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

Client::Client(const string& serverAddr, int serverPort, const string &username) : serverIP(serverIP), serverPort(serverPort), username(username) {}


void Client::connectToServer(){
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSocket == -1){
        throw runtime_error("Error with creating client socket.");
    }


    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = hton(serverPort);
    inet_pton(AF_INET, serverIP.c_str(), &serverAddress.sin_addr);

    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
    {
        close(clientSocket);
        throw runtime_error("Error connecting to server.");
    }

    cout << "Connected to server as " << username << "." << endl;
}

