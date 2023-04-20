#ifndef __PUBLIC_H__
#define __PUBLIC_H__

enum EnMsgType
{
    LOGIN_MSG = 1, // 登陆消息
    LOGIN_MSG_ACK = 2, // 登陆响应消息
    REG_MSG = 3, // 注册消息
    REG_MSG_ACK = 4, // 注册响应消息
    ONE_CHAT_MSG = 5, // 一对一聊天消息
    GROUP_CHAT_MSG = 6, // 群组聊天消息
    ADD_FRIEND_MSG = 7, // 添加好友消息

    CREATE_GROUP_MSG = 8, // 创建群组消息
    ADD_GROUP_MSG = 9, // 加入群组消息

    LOGOUT_MSG = 10 // 登出消息
};

#endif