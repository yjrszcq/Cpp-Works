#include<bits/stdc++.h>
using namespace std;
#include "es_user.cpp"

class Root : public User{
public:
    Root();
};

Root::Root() : User(User::ROOT) {
    ifstream file("root_config.txt");
    if(!file.is_open()){
        name = "root";
        password = "root123456";
    } else{
        file >> name >> password;
    }
    file.close();
}