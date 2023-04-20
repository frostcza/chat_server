#ifndef __REDIS_H__
#define __REDIS_H__

#include <hiredis/hiredis.h>
#include <thread>
#include <functional>
#include <string>

using namespace std;

class Redis
{
public:
    Redis();
    ~Redis();

    // 连接redis服务器
    bool connect();

    // 向channel发布message
    bool publish(int channel, string message);

    // 订阅channel
    bool subscribe(int channel);

    // 取消订阅channel
    bool unsubscribe(int channel);

    // 开子线程接收订阅通道的消息
    void observer_channel_message();

    // 初始化向业务层上报信息的回调
    // 留给上层实现一个处理函数，绑定至_notify_message_handler
    // 当redis subscribe的channel有消息来时，调用上层绑定的函数
    void init_notify_handler(function<void(int, string)> fn);


private:
    // hiredis负责publish的上下文
    redisContext* _publish_context;

    // hiredis负责publish的上下文
    redisContext* _subscribe_context;

    // 接受订阅的消息，向业务层上报 的回调
    function<void(int, string)> _notify_message_handler; 
};

#endif