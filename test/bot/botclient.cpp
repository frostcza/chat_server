#include <arpa/inet.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
using namespace std;

int main() 
{
    // 1. 创建客户端，并连接到服务端
    int sock_client = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);
    connect(sock_client, (sockaddr*)&server_addr, sizeof(sockaddr));

    // 2. 发送数据，并接受服务端数据
    while(1) 
    {
        char buf[1024] = {0};
        cin.getline(buf, 1024);
        string question(buf);

        send(sock_client, question.c_str(), strlen(question.c_str()) + 1, 0);
        printf("send:    %s\n", question.c_str());

        if(question != "bye")
        {
            char answer[4096];
            memset(answer, '\0', 4096);
            recv(sock_client, answer, 4096, 0);
            printf("receive: %s\n", answer);
        }
        else
        {
            break;
        }
    }

    // 3. 关闭客户端
    close(sock_client);
    return 0;
}
