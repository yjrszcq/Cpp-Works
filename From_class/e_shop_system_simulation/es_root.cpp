#include<bits/stdc++.h>
using namespace std;
#include "es_user.cpp"

class Root : public User{ // 管理员类, 继承自用户类
public:
    Root(); // 构造函数
};

Root::Root() : User(User::ROOT) { // 构造函数
    ifstream file("root_config.txt");
    if(!file.is_open()){ // 如果文件不存在, 则使用默认的用户名和密码
        name = "root";
        password = "root123456";
    } else{ // 否则通过文件设置管理员的用户名和密码
        file >> name >> password;
    }
    file.close();
}