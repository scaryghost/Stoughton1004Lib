#include "Stoughton1004Lib/Network/network.h"

#include <cstdlib>
#include <iostream>
#include <thread>

using namespace Stoughton1004Lib;
using std::atoi;
using std::endl;
using std::cout;
using std::thread;


void handler(Socket *client) {
    cout << client->readLine() << endl;
    client->write("HTTP/1.0 200 OK\nConnection: close\nContent-Type: text/html\n\n");
    client->write("This is a webserver");
    client->close();
}


int main(int argc, char **argv) {
    int port= atoi(argv[1]);
    ServerSocket server(port);

    cout << "Listening on port: " << port << endl;
    while(true) {
        Socket client= server.accept();
        cout << "Recieved connection" << endl;
        thread th(handler, &client);
        th.detach();
    }

    return 0;
}
