#ifndef __DB_H__
#define __DB_H__

#include <string>
#include <mysql/mysql.h>
#include <muduo/base/Logging.h>

using namespace std;

// 数据库操作类
class MySQL
{
public:

    MySQL();
    ~MySQL();
    bool connect();
    bool update(string sql);
    MYSQL_RES* query(string sql);
    MYSQL* getConnection();
private:

    MYSQL *_conn;
};
#endif