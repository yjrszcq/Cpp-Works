#include<bits/stdc++.h>
#include "es_product.cpp"

using namespace std;

class Cart{
public:
    Cart();
    bool load_cart(Product product, int n);
    Product get_product(string);
    Product get_product(int);
    vector<Product> get_products();
    double get_coupon();
    bool get_code_flag();
    bool set_coupon(double coupon);
    void set_code_flag(bool code_flag);
    bool add(Product, int);
    bool reduce(Product, int);
    bool del(int index);
    bool del(string);
    void show();
    double get_total_price();
private:
    vector<Product> products;
    double coupon;
    bool code_flag;
};

Cart::Cart(){
    products.clear();
    coupon = 1;
    code_flag = false;
}

bool Cart::load_cart(Product product, int n){
    product.set_num(n);
    products.push_back(product);
    return true;
}

Product Cart::get_product(string name){
    for(int i = 0; i < products.size(); i++){
        if(products[i].get_name() == name){
            return products[i];
        }
    }
    return Product("NULL", "NULL", 0, 0);
}

Product Cart::get_product(int index){
    if(index < 0 || index >= products.size()){
        return Product("NULL", "NULL", 0, 0);
    }
    return products[index];
}

vector<Product> Cart::get_products(){
    return products;
}

double Cart::get_coupon(){
    return coupon;
}

bool Cart::get_code_flag(){
    return code_flag;
}

bool Cart::set_coupon(double coupon){
    return this->coupon = coupon;
}

void Cart::set_code_flag(bool code_flag){
    this->code_flag = code_flag;
}

bool Cart::add(Product p, int n){
    if(p.get_name() == "NULL"){
        cout << "Error: product not found" << endl;
        return false;
    }
    if(n <= 0){
        cout << "Error: invalid number" << endl;
        return false;
    } else{
        if(p.get_num() < n){
            cout << "Error: not enough products" << endl;
            return false;
        } else{
            for(int i = 0; i < products.size(); i++){
                if(products[i].get_name() == p.get_name()){
                    if(products[i].get_num() + n > p.get_num()){
                        cout << "Error: not enough products" << endl;
                        return false;
                    }
                    products[i].add_num(n);
                    return true;
                }
            }
            products.push_back(p);
            products[products.size() - 1].set_num(n);
            return true;
        }
    }
}

bool Cart::reduce(Product p, int n){
    if(p.get_name() == "NULL"){
        cout << "Error: product not found" << endl;
        return false;
    }
    if(n <= 0){
        cout << "Error: invalid number" << endl;
        return false;
    } else{
        for(int i = 0; i < products.size(); i++){
            if(products[i].get_name() == p.get_name()){
                if(p.get_num() < products[i].get_num() - n){
                    cout << "Error: not enough products" << endl;
                    products[i].set_num(p.get_num());
                    return false;
                }
                if(products[i].get_num() < n){
                    del(i);
                    return true;
                }
                products[i].set_num(products[i].get_num() - n);
                return true;
            }
        }
        cout << "Error: product not found" << endl;
        return false;
    }
}

bool Cart::del(int index){
    if(index < 0 || index >= products.size()){
        cout << "Error: product not found" << endl;
        return false;
    }
    products.erase(products.begin() + index);
    return true;
}

bool Cart::del(string name){
    for(int i = 0; i < products.size(); i++){
        if(products[i].get_name() == name){
            products.erase(products.begin() + i);
            return true;
        }
    }
    cout << "Error: product not found" << endl;
    return false;
}

void Cart::show(){
    for(int i = 0; i < products.size(); i++){
        cout<< "  <" << i << ">";
        cout << "\tName: " << products[i].get_name() << "\tType: " << products[i].get_type() << endl;
        cout << "\tPrice: $" << products[i].get_price() << "\tNum: " << products[i].get_num() << endl;
    }
    cout << "Total price: $" << get_total_price() << endl;
}

double Cart::get_total_price(){
    double total_price = 0;
    for(int i = 0; i < products.size(); i++){
        total_price += products[i].get_price() * products[i].get_num();
    }
    return total_price;
}