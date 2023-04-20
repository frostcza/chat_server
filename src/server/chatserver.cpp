#include "chatserver.hpp"
#include "chatservice.hpp"
#include <muduo/base/Logging.h>
#include <string>
#include <iostream>
#include <functional>
#include "json.hpp"

using json = nlohmann::json;
using namespace placeholders;

ChatServer::ChatServer(EventLoop* loop, const InetAddress& listenAddr, const string& nameArg)
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
}

void ChatServer::start()
{
    _server.start();
}

void ChatServer::onConnection(const TcpConnectionPtr& conn)
{
    cout << conn->peerAddress().toIpPort() << "->" <<
            conn -> localAddress().toIpPort() << endl;
    if(!conn->connected())
    {
        LOG_INFO << "state: offline";
        ChatService::instance()->clientCloseException(conn);
        conn->shutdown();
    }
    else
    {
        LOG_INFO << "state: online";
    }
}

void ChatServer::onMessage(const TcpConnectionPtr& conn, Buffer* buffer, Timestamp time)
{
    string buf = buffer->retrieveAllAsString();
    json js = json::parse(buf);
    // 解耦网络模块和业务模块
    // 通过js["msgid"] 获取业务handler 基于回调函数选择处理方式
    auto msgHandler = ChatService::instance()->getHandler(js["msgid"].get<int>());
    // 回调消息类型绑定的事件处理器，执行不同业务的处理
    msgHandler(conn, js, time);
}