#ifndef __OFFLINEMSGMODEL_H__
#define __OFFLINEMSGMODEL_H__

#include "user.hpp"
#include <vector>

class OfflineMsgModel
{
public:
    void insert(int userid, string msg); // 新增离线消息
    void remove(int userid); // 清空离线消息
    vector<string> query(int userid); // 查询离线消息

private:

};
#endif