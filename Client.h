#include <string>
#include <netinet/in.h>


using namespace std;


class Client{
public:
    Client(const string &serverIP, int port, const string &username);
    void connectToServer();
    void start();

   
private:
    void message(const string &mess);
    void getMess();

    int clientSocket;
    sockaddr_in serverAddress;
    string serverIP;

    int serverPort;
    string username;
};
    
