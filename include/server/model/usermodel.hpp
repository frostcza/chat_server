#ifndef __USERMODEL_H__
#define __USERMODEL_H__

#include "user.hpp"

class UserModel
{
public:
    bool insert(User &user);
    User query(int id);
    bool updateState(User user);
    void resetState();
private:

};

#endif