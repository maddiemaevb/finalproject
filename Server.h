#ifdef SERVER_H
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
	void sendMessage(const std::string& message, int senderSocket);
    
    string getCurrentTime();

    void sd(){
        close(serverSocket);
        
        for(int client : clientSocket){
            close(client);
        }

        running = false;

    }

private:
	int serverSocket;
	vector<int> clientSocket;
    sockaddr_in  serverAddress;
    bool running = false;
    mutex clientMutex;
    
};

#endif
