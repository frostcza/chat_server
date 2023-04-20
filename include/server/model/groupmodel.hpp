#ifndef __GROUPMODEL_H__
#define __GROUPMODEL_H__

#include "group.hpp"
#include "db.h"
#include <string>
#include <vector>
using namespace std;

class GroupModel
{
public:
    // 创建群
    bool createGroup(Group& group);
    // 加入群
    void addToGroup(int groupid, int userid, string role); 
    // 在什么群里
    vector<Group> queryGroups(int userid); 
    // 群里除了自己还有谁
    vector<int> queryUsersInGroup(int groupid, int userid);

private:

};

#endif