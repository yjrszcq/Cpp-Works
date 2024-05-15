#include<bits/stdc++.h>
#include "es_product.cpp"

using namespace std;

class Cart{ // 购物车类
public:
    Cart(); // 构造函数
    bool load_cart(Product product, int n); // 在加载数据的时候使用
    Product get_product(string); // 通过名字获取商品
    Product get_product(int); // 通过下标获取商品
    vector<Product> get_products(); // 获取购物车中的所有商品
    double get_coupon(); // 获取优惠券
    bool get_code_flag(); // 获取是否使用优惠码
    bool set_coupon(double coupon); // 设置优惠券
    void set_code_flag(bool code_flag); // 设置是否使用优惠码
    bool add(Product, int); // 添加商品
    bool reduce(Product, int); // 减少商品数量
    bool del(int index); // 通过下标删除商品
    bool del(string); // 通过名字删除商品
    void show(); // 显示购物车
    double get_total_price(); // 获取购物车中商品的总价
private:
    vector<Product> products; // 购物车中的商品
    double coupon; // 优惠券
    bool code_flag; // 是否使用优惠码
};

Cart::Cart(){ // 构造函数
    products.clear();
    coupon = 1;
    code_flag = false;
}

bool Cart::load_cart(Product product, int n){ // 在加载数据的时候使用
    product.set_num(n);
    products.push_back(product);
    return true;
}

Product Cart::get_product(string name){ // 通过名字获取商品
    for(int i = 0; i < products.size(); i++){ // 遍历购物车中的商品
        if(products[i].get_name() == name){
            return products[i];
        }
    }
    return Product("NULL", "NULL", 0, 0);
}

Product Cart::get_product(int index){ // 通过下标获取商品
    if(index < 0 || index >= products.size()){ // 判断下标是否合法
        return Product("NULL", "NULL", 0, 0);
    }
    return products[index];
}

vector<Product> Cart::get_products(){ // 获取购物车中的所有商品
    return products;
}

double Cart::get_coupon(){ // 获取优惠券
    return coupon;
}

bool Cart::get_code_flag(){ // 获取是否使用优惠码
    return code_flag;
}

bool Cart::set_coupon(double coupon){ // 设置优惠券
    return this->coupon = coupon;
}

void Cart::set_code_flag(bool code_flag){ // 设置是否使用优惠码
    this->code_flag = code_flag;
}

bool Cart::add(Product p, int n){ // 添加商品
    if(p.get_name() == "NULL"){ // 判断商品是否存在于商品列表中
        cout << "Error: product not found" << endl;
        return false;
    }
    if(n <= 0){ // 判断数量是否合法
        cout << "Error: invalid number" << endl;
        return false;
    } else{ // 添加商品
        if(p.get_num() < n){ // 判断库存是否足够
            cout << "Error: not enough products" << endl;
            return false;
        } else{ // 添加商品
            for(int i = 0; i < products.size(); i++){ // 遍历购物车中的商品
                if(products[i].get_name() == p.get_name()){ // 判断商品是否已经存在于购物车中
                    if(products[i].get_num() + n > p.get_num()){ // 判断库存是否足够
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

bool Cart::reduce(Product p, int n){ // 减少商品数量
    if(p.get_name() == "NULL"){ // 判断商品是否存在于商品列表中
        cout << "Error: product not found" << endl;
        return false;
    }
    if(n <= 0){ // 判断数量是否合法
        cout << "Error: invalid number" << endl;
        return false;
    } else{ // 减少商品数量
        for(int i = 0; i < products.size(); i++){ // 遍历购物车中的商品
            if(products[i].get_name() == p.get_name()){ // 判断商品是否存在于购物车中
                if(p.get_num() < products[i].get_num() - n){ // 判断库存是否足够
                    cout << "Error: not enough products" << endl;
                    products[i].set_num(p.get_num());
                    return false;
                }
                if(products[i].get_num() < n){ // 判断商品数量是否过量减少, 如果是则在购物车中删除该商品
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

bool Cart::del(int index){ // 通过下标删除商品
    if(index < 0 || index >= products.size()){ // 判断下标是否合法
        cout << "Error: product not found" << endl;
        return false;
    }
    products.erase(products.begin() + index);
    return true;
}

bool Cart::del(string name){ // 通过名字删除商品
    for(int i = 0; i < products.size(); i++){ // 遍历购物车中的商品
        if(products[i].get_name() == name){
            products.erase(products.begin() + i);
            return true;
        }
    }
    cout << "Error: product not found" << endl;
    return false;
}

void Cart::show(){ // 显示购物车
    for(int i = 0; i < products.size(); i++){ // 遍历购物车中的商品
        cout<< "  <" << i << ">";
        cout << "\tName: " << products[i].get_name() << "\tType: " << products[i].get_type() << endl;
        cout << "\tPrice: $" << products[i].get_price() << "\tNum: " << products[i].get_num() << endl;
    }
    cout << "Total price: $" << get_total_price() << endl;
}

double Cart::get_total_price(){ // 获取购物车中商品的总价
    double total_price = 0;
    for(int i = 0; i < products.size(); i++){ // 遍历购物车中的商品, 计算总价
        total_price += products[i].get_price() * products[i].get_num();
    }
    return total_price;
}