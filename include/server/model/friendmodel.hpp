#ifndef __FRIENDMODEL_H__
#define __FRIENDMODEL_H__

#include "user.hpp"
#include <vector>
using namespace std;

class FriendModel
{
public:
    // 添加好友
    void insert(int userid, int friendid);
    // 返回好友列表(name) 两个表的联合查询
    vector<User> query(int userid); 
};

#endif