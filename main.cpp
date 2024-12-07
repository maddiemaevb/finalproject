#include <iostream>
#include "Server.h"
#include "Client.h"


using namespace std;



int main(int argc, char *argv[]){
    server(8080);
    server.start();
    return 0;

}
