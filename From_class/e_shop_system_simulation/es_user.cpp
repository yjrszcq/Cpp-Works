#include<bits/stdc++.h>
#include "es_cart.cpp"

using namespace std;

class User{
public:
    enum Permission{USER, ROOT};
    User(Permission permission);
    void set_name(string name);
    void set_password(string password);
    void set_money(double money);
    void set_cart(Cart cart);
    void set_permission(Permission permission = USER);
    string get_name();
    string get_password();
    double get_money();
    Cart get_cart();
    Permission get_permission();
    void info();
    void info_root();
protected:
    string name;
    string password;
    Permission permission;
private:
    double money;
    Cart cart;
};

User::User(Permission permission){
    name = "NULL";
    password = "NULL";
    money = 0;
    cart = Cart();
    this->permission = permission;
}

void User::set_name(string name){
    this->name = name;
}

void User::set_password(string password){
    this->password = password;
}

void User::set_money(double money){
    this->money = money;
}

void User::set_cart(Cart cart){
    this->cart = cart;
}

void User::set_permission(Permission permission){
    this->permission = permission;
}

string User::get_name(){
    return name;
}

string User::get_password(){
    return password;
}

double User::get_money(){
    return money;
}

Cart User::get_cart(){
    return cart;
}

User::Permission User::get_permission(){
    return permission;
}

void User::info(){
    cout << "Name: " << name << endl;
    cout << "Money: $" << money << endl;
    cout << "Cart: " << endl;
    cart.show();
}

void User::info_root(){
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