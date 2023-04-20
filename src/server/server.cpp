#include "chatserver.hpp"
#include "chatservice.hpp"
#include <iostream>
#include <signal.h>

using namespace std;

void resetHandler(int signo)
{
    ChatService::instance()->reset();
    exit(0);
}

int main(int argc, char** argv)
{
    signal(SIGINT, resetHandler);

    if(argc < 3)
    {
        cerr << "command invalid. example: ./server 127.0.0.1 6000" << endl;
        exit(-1);
    }

    char* ip = argv[1];
    uint16_t port = atoi(argv[2]);

    EventLoop loop;
    InetAddress addr(ip, port);
    ChatServer server(&loop, addr, "ChatServer");
    server.start();
    loop.loop();
}