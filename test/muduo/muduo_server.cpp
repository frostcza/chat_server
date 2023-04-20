// 主要的类
// TcpServer  TcpClient
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <iostream>
#include <functional>

using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders;

class ChatServer
{
public:
    ChatServer(EventLoop* loop, const InetAddress & listenAddr, const string& nameArg) 
        : _server(loop, listenAddr, nameArg), _loop(loop)
    {
        // 给服务器注册用户连接/断开回调
        _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));
        // bind member function
        // 三个注意事项，1. 传地址，加& 2. 第二个参数要传入对象，这里是this 3. 其他参数要用占位符
        
        // 给服务器注册用户读写事件回调
        _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));

        // 设置服务器的线程数量
        _server.setThreadNum(4); 
        // 1个I/O线程，管用户连接/断开回调
        // 3个worker线程，管读写事件，会自动分配的
    }
    void start()
    {
        _server.start();
    }

private:
    TcpServer _server;
    EventLoop* _loop;

    // 处理用户连接创建、断开 epoll listenfd accept
    void onConnection(const TcpConnectionPtr& conn)
    {
        cout << conn->peerAddress().toIpPort() << "->" <<
            conn -> localAddress().toIpPort() << endl;
        if(conn->connected())
        {
            cout << "state: online" << endl; 
        }
        else
        {
            cout << "state: offline" << endl; 
            conn->shutdown();
            // _loop->quit();
        }
    }

    // 处理用户读写事件
    void onMessage(const TcpConnectionPtr& conn, Buffer* buffer, Timestamp time)
    {
        // echo server 实现
        string buf = buffer->retrieveAllAsString();
        cout << "recv_data: " << buf << "time: " << time.toString() <<endl;
        conn->send(buf);
    }
};

int main()
{
    EventLoop loop;
    InetAddress addr("127.0.0.1", 6000);
    ChatServer server(&loop, addr, "ChatServer");
    server.start();
    loop.loop(); // epoll wait 阻塞方式等待用户连接，读写事件等
    return 0;

    // 程序起来以后，在另一个终端telnet 127.0.0.1 6000
    // ctrl+]退出telnet
}