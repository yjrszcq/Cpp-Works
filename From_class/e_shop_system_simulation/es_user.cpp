#include<bits/stdc++.h>
#include "es_cart.cpp"

using namespace std;

class User{ // 用户类
public:
    enum Permission{USER, ROOT}; // 权限枚举
    User(Permission permission); // 构造函数
    void set_name(string name); // 设置用户名
    void set_password(string password); // 设置密码
    void set_money(double money); // 设置余额
    void set_cart(Cart cart); // 设置购物车
    void set_permission(Permission permission = USER); // 设置权限
    string get_name(); // 获取用户名
    string get_password(); // 获取密码
    double get_money(); // 获取余额
    Cart get_cart(); // 获取购物车
    Permission get_permission(); // 获取权限
    void info(); // 显示用户信息
    void info_root(); // 显示管理员信息
protected:
    string name; // 用户名
    string password; // 密码
    Permission permission; // 权限
private:
    double money; // 余额
    Cart cart; // 购物车
};

User::User(Permission permission){ // 构造函数
    name = "NULL";
    password = "NULL";
    money = 0;
    cart = Cart();
    this->permission = permission;
}

void User::set_name(string name){ // 设置用户名
    this->name = name;
}

void User::set_password(string password){ // 设置密码
    this->password = password;
}

void User::set_money(double money){ // 设置余额
    this->money = money;
}

void User::set_cart(Cart cart){ // 设置购物车
    this->cart = cart;
}

void User::set_permission(Permission permission){ // 设置权限
    this->permission = permission;
}

string User::get_name(){ // 获取用户名
    return name;
}

string User::get_password(){ // 获取密码
    return password;
}

double User::get_money(){ // 获取余额
    return money;
}

Cart User::get_cart(){ // 获取购物车
    return cart;
}

User::Permission User::get_permission(){ // 获取权限
    return permission;
}

void User::info(){ // 显示用户信息
    cout << "Name: " << name << endl;
    cout << "Money: $" << money << endl;
    cout << "Cart: " << endl;
    cart.show();
}

void User::info_root(){ // 在管理员操作下显示用户信息
    cout << "Name: " << name << endl;
    cout << "Password: " << password << endl;
    cout << "Money: $" << money << endl;
    double coupon = cart.get_coupon();
    cout << "Coupon: ";
    if(coupon == 1){
        cout << "No" << endl;
    } else{
        cout << coupon << endl;
    }
    cout << "Code flag: " << (cart.get_code_flag() == true ? "1" : "0") << endl;
    cout << "Cart: " << endl;
    cart.show();
}