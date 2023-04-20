#include "json.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;
using json = nlohmann::json;

int main()
{
    json js;
    js["msg_type"] = 2;
    js["from"] = "cza";
    js["to"] = "frost";
    js["msg"]["id"] = 0;
    js["msg"]["content"] = "hello";

    vector<int> vec;
    vec.push_back(0);
    vec.push_back(10);
    js["vec"] = vec;

    map<int, string> m;
    m[0] = "str1";
    m[7] = "str2";
    js["map"] = m;
    cout << js << endl;

    string sendBuf = js.dump(); // 用.dump()序列化(转string)
    cout << sendBuf.c_str() << endl;
    cout << sendBuf.c_str()[0] << endl; // 第一位真的是{
    

    string recvBuf = sendBuf;
    json js_recv = json::parse(recvBuf); // 用json::parse(string)反序列化
    cout << js_recv << endl;
    cout << js_recv["msg"] << endl;
    auto msgjs = js_recv["msg"];
    cout << msgjs["content"] << endl;
    cout << js_recv["from"] << endl;

    map<int, string> m_recv = js["map"];
    for(auto &p : m_recv)
    {
        cout << p.second << endl;
    }

    return 0;
}