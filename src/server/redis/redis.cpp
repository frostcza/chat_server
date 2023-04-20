#include "redis.hpp"
#include <iostream>


Redis::Redis() 
    : _publish_context(nullptr), _subscribe_context(nullptr)
{
}

Redis::~Redis()
{
    if(_publish_context != nullptr)
    {
        redisFree(_publish_context);
    }
    if(_subscribe_context != nullptr)
    {
        redisFree(_subscribe_context);
    }
}

bool Redis::connect()
{
    _publish_context = redisConnect("127.0.0.1", 6379);
    if(nullptr == _publish_context)
    {
        cerr << "connect redis falied" << endl;
        return false;
    }

    _subscribe_context = redisConnect("127.0.0.1", 6379);
    if(nullptr == _subscribe_context)
    {
        cerr << "connect redis falied" << endl;
        return false;
    }

    thread sub(&Redis::observer_channel_message, this);
    sub.detach();

    cout << "connect redis success" << endl;
    return true;
}

bool Redis::publish(int channel, string message)
{
    redisReply* reply = (redisReply*)redisCommand(_publish_context, "PUBLISH %d %s", 
        channel, message.c_str());
    
    if(nullptr == reply)
    {
        cerr << "publish command failed" << endl;
        return false;
    }
    freeReplyObject(reply);
    return true;
}

bool Redis::subscribe(int channel)
{
    // subscribe操作会阻塞当前线程，所以不能像publish一样简单的使用redisCommand
    if(REDIS_ERR == redisAppendCommand(this->_subscribe_context, "SUBSCRIBE %d", channel))
    {
        cerr << "subscribe command failed" << endl;
        return false;
    }

    int done = 0;
    while(!done)
    {
        if(REDIS_ERR == redisBufferWrite(this->_subscribe_context, &done))
        {
            cerr << "subscribe command failed" << endl;
            return false;
        }
    }
    return true;
}

bool Redis::unsubscribe(int channel)
{
    if(REDIS_ERR == redisAppendCommand(this->_subscribe_context, "UNSUBSCRIBE %d", channel))
    {
        cerr << "unsubscribe command failed" << endl;
        return false;
    }

    int done = 0;
    while(!done)
    {
        if(REDIS_ERR == redisBufferWrite(this->_subscribe_context, &done))
        {
            cerr << "unsubscribe command failed" << endl;
            return false;
        }
    }
    return true;
}

void Redis::observer_channel_message()
{
    redisReply* reply;
    while(REDIS_OK == redisGetReply(this->_subscribe_context, (void**)&reply))
    {
        if(reply != nullptr && reply->element[1] != nullptr
            && reply->element[2]->str != nullptr)
        {
            _notify_message_handler(atoi(reply->element[1]->str), reply->element[2]->str);
        }
        freeReplyObject(reply);
    }

}

void Redis::init_notify_handler(function<void(int, string)> fn)
{
    this->_notify_message_handler = fn;
}