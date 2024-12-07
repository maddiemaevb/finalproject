#ifdef SERVER_H
#define SERVER_H
#include <vector>
#include <string>



class Server {
public:
	Server();
	void start();
	void sendMessage(const std::string& input);

private:
	int serverSocket;
	std::vector<int> clientSocket;
	std::map<int, std::string> clientName;



	void acceptingClient();
	void handlingClient(int clientSocket);
	void sendMessage(const std::string& message, int senderSocket);
};
#endif
