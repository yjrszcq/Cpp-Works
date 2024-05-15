#include<bits/stdc++.h>
using namespace std;

class Product{
public:
    Product(string name, string type, double price, int num);
    string get_name() const;
    string get_type() const;
    double get_price();
    int get_num();
    void set_name(string name);
    void set_type(string type);
    void set_price(double price);
    void set_num(int num);
    void add_num(int num);
    void info();
private:
    string name;
    string type;
    double price;
    int num;
};

Product::Product(string name, string type, double price, int num){
    this->name = name;
    this->type = type;
    this->price = price;
    this->num = num;
}

string Product::get_name() const{
    return name;
}

string Product::get_type() const{
    return type;
}

double Product::get_price(){
    return price;
}

int Product::get_num(){
    return num;
}

void Product::set_name(string name){
    this->name = name;
}

void Product::set_type(string type){
    this->type = type;
}

void Product::set_price(double price){
    this->price = price;
}

void Product::set_num(int num){
    this->num = num;
}

void Product::add_num(int num){
    this->num += num;
}

void Product::info(){
    cout << "Name: " << name << "\tType: " << type << endl;
    cout << "Price: $" << price << "\tNum: " << num << endl;
}