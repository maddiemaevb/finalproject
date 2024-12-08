#include <iostream>
#include "Server.h"
#include "Client.h"


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

        thread serverThread([&server]() {
            server.start();
        });

        cout << "Server running on port " << port << ". Type '/shutdown' to close the server." << endl;

        while (true) {
            string input;
            getline(cin, input);

            if (input == "/shutdown") {
                cout << "Shutting down server..." << endl;
                server.sd();  // Calls the 'sd()' function
                serverThread.join();
                break;
            }
        }
    }

}
