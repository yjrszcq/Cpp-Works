#include<bits/stdc++.h>
using namespace std;

class Product{ // 商品类
public:
    Product(string name, string type, double price, int num); // 构造函数
    string get_name() const; // 获取商品名
    string get_type() const; // 获取商品类型
    double get_price(); // 获取价格
    int get_num(); // 获取数量
    void set_name(string name); // 设置商品名
    void set_type(string type); // 设置商品类型
    void set_price(double price); // 设置价格
    void set_num(int num); // 设置数量
    void add_num(int num); // 增加数量
    void info(); // 显示商品信息
private:
    string name; // 商品名
    string type; // 商品类型
    double price; // 价格
    int num; // 数量
};

Product::Product(string name, string type, double price, int num){ // 构造函数
    this->name = name;
    this->type = type;
    this->price = price;
    this->num = num;
}

string Product::get_name() const{ // 获取商品名
    return name;
}

string Product::get_type() const{ // 获取商品类型
    return type;
}

double Product::get_price(){ // 获取价格
    return price;
}

int Product::get_num(){ // 获取数量
    return num;
}

void Product::set_name(string name){ // 设置商品名
    this->name = name;
}

void Product::set_type(string type){ // 设置商品类型
    this->type = type;
}

void Product::set_price(double price){ // 设置价格
    this->price = price;
}

void Product::set_num(int num){ // 设置数量
    this->num = num;
}

void Product::add_num(int num){ // 增加数量
    this->num += num;
}

void Product::info(){ // 显示商品信息
    cout << "Name: " << name << "\tType: " << type << endl;
    cout << "Price: $" << price << "\tNum: " << num << endl;
}