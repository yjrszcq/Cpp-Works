#include<bits/stdc++.h>

using namespace std;

class Code{ // 优惠码类
public:
    Code(string code, double discount, bool pubilsh_flag); // 构造函数
    string get_code(); // 获取优惠码
    double get_discount(); // 获取折扣
    bool get_pubilsh_flag(); // 获取是否发布
    void set_code(string code, double discount); // 设置优惠码
    void set_pubilsh_flag(bool pubilsh_flag); // 设置是否发布
private:
    string code; // 优惠码
    double discount; // 折扣
    bool pubilsh_flag; // 是否发布
};

Code::Code(string code, double discount, bool pubilsh_flag){ // 构造函数
    this->code = code;
    this->discount = discount;
    this->pubilsh_flag = pubilsh_flag;
}

string Code::get_code(){ // 获取优惠码
    return code;
}

double Code::get_discount(){ // 获取折扣
    return discount;
}

bool Code::get_pubilsh_flag(){ // 获取是否发布
    return pubilsh_flag;
}

void Code::set_code(string code, double discount){ // 设置优惠码
    this->code = code;
    this->discount = discount;
}

void Code::set_pubilsh_flag(bool pubilsh_flag){ // 设置是否发布
    this->pubilsh_flag = pubilsh_flag;
}