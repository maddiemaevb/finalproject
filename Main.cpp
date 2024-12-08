#include <iostream>
#include "Server.h"
#include "Client.h"
#include <thread>

using namespace std;


int main(int argc, char *argv[]){
     if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <server|client> <port>" << endl;
        return 1;
    }

    string mode = argv[1];
    int port = stoi(argv[2]);

    if (mode == "server") {
        Server server(port);

        thread serverThread([&server](){
            server.start();
        });

        cout << "Server running on port " << port << ". Type '/shutdown' to close the server." << endl;

        while (true){
            string input;
            getline(cin, input);

            if (input == "/shutdown") {
                cout << "Shutting down server..." << endl;
                server.sd();  // Calls the 'sd()' function
                serverThread.join();
                break;
            }
        }
    } else if (mode == "client"){
        string username;
        cout << "Enter your username: ";
        cin >> username;
        cin.ignore();

        Client client("127.0.0.1", port, username);
        try {
            client.connectToServer();
            client.start();
        } catch (const exception &e) {
            cerr << "Client encountered an error: " << e.what() << endl;
        }
    } else {
        cerr << "Invalid mode. Use 'server' or 'client'." << endl;
        return 1;
    }

    return 0;
}

