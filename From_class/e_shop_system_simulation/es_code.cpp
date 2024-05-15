#include<bits/stdc++.h>

using namespace std;

class Code{
public:
    Code(string code, double discount, bool pubilsh_flag);
    string get_code();
    double get_discount();
    bool get_pubilsh_flag();
    void set_code(string code, double discount);
    void set_pubilsh_flag(bool pubilsh_flag);
private:
    string code;
    double discount;
    bool pubilsh_flag;
};

Code::Code(string code, double discount, bool pubilsh_flag){
    this->code = code;
    this->discount = discount;
    this->pubilsh_flag = pubilsh_flag;
}

string Code::get_code(){
    return code;
}

double Code::get_discount(){
    return discount;
}

bool Code::get_pubilsh_flag(){
    return pubilsh_flag;
}

void Code::set_code(string code, double discount){
    this->code = code;
    this->discount = discount;
}

void Code::set_pubilsh_flag(bool pubilsh_flag){
    this->pubilsh_flag = pubilsh_flag;
}