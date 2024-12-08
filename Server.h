#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <cstring>
#include <iostream>
#include <thread>
#include <mutex>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

class Server {
public:
	Server(int port);
    ~Server();
	void start();
    void addAClient();
	void sendMessage(const string &message, int senderSocket);
    
    string getCurrentTime();
    void stopServer();

    void sd(){
        stopServer();
    }

private:
	int serverSocket;
	vector<int> clientSockets;
    sockaddr_in  serverAddress;
    bool running;
    mutex clientMutex;
    void closeClients();
    
};

#endif
