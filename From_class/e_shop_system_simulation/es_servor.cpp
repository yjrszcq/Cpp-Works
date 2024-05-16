#include <bits/stdc++.h>
#include <unistd.h>
#include "es_root.cpp"
#include "es_code.cpp"

using namespace std;

class Servor{ // 服务器类
public:
    Servor(); // 构造函数
    bool servor_file_check(); // 检查文件
    bool servor_start(); // 启动服务器
    void servor_start_failed(); // 启动服务器失败
    bool servor_save(); // 保存数据
    bool servor_exit(); // 退出服务器
    //数据加载
    bool load_product_data(); // 加载商品数据
    bool load_user_data(); // 加载用户数据
    bool lode_code_data(); // 加载兑换码数据
    //数据保存
    bool save_product_data(); // 保存商品数据
    bool save_user_data(); // 保存用户数据
    bool save_code_data(); // 保存兑换码数据
    //用户操作
    User* get_current_user(); // 获取当前用户
    bool is_user(); // 判断是否为用户
    bool user_signup(string name, string password); // 用户注册
    bool user_login(string name, string password); // 用户登录
    bool user_logout(); // 用户登出
    bool user_change_password(string original_password, string password); // 修改密码
    bool user_recharge(double money); // 充值
    bool user_ask_for_coupon(); // 领取优惠券
    string user_ask_for_code(); // 领取兑换码
    //商品操作
    Product product_get(int insex); // 获取商品
    Product product_get(string name); // 获取商品
    vector<Product> products_get(); // 获取商品列表
    bool product_show(); // 显示商品
    bool product_search(string name); // 搜索商品
    //购物车操作
    bool cart_add(Product product, int num); // 从服务器商品列表中添加商品
    bool cart_reduce(Product product, int num); // 从购物车商品列表中减少商品数量
    bool cart_delete(Product product); // 通过名称, 从购物车商品列表中删除商品
    bool cart_delete(int index); // 通过下标, 从购物车商品列表中删除商品
    double cart_get_total_price(vector<int> index); // 获取总价
    double cart_check(vector<int> index); // 结算
    bool cart_payment(vector<int> index, double total_price); // 支付
    bool cart_save_history(vector<int> index, Cart original_cart, double total_price); // 保存历史
    bool cart_show_history(); // 显示历史
    bool cart_analysis(vector<int> start_time, vector<int> end_time); // 通过具体时间分析历史
    bool cart_analysis(long long seconds_begin, long long seconds_end); // 通过时间戳分析历史
    //兑换码操作
    string code_create(int n, bool publush_flag); // 创建兑换码, 并随机生成折扣额度
    string code_create(int n, double discount, bool publush_flag); // 创建兑换码, 并指定折扣额度
    int code_search(string code); // 搜索兑换码
    double code_get_discount(string code); // 获取兑换码折扣
    bool code_delete(int code_index); // 删除兑换码
    bool code_eligibility_check(); // 检查用户是否有资格领取兑换码
    bool code_eligibility_initialize(); // 初始化用户领取兑换码的资格
    //活动操作
    double activity_get(); // 获取活动折扣
    //管理员操作
    bool is_root(); // 判断是否为管理员
    bool root_login(string name, string password); // 管理员登录
    bool root_logout(); // 管理员登出
    bool root_coupon_set(double min, double max); // 管理员设置优惠券折扣范围
    bool root_activity_set(double discount); // 管理员设置活动折扣
    //管理员-操作兑换码
    vector<Code> root_codes_get(); // 获取兑换码列表
    bool root_code_add(double discount); // 添加兑换码
    void root_code_show(); // 显示兑换码
    bool root_code_delete(int code_index); // 删除兑换码
    bool root_code_delete(string code); // 删除兑换码
    //管理员-操作用户
    User root_user_get(int index); // 通过下标获取用户
    User root_user_get(string name); // 通过名称获取用户
    vector<User> root_users_get(); // 获取用户列表
    bool root_user_add(string name, string password, int money); // 添加用户
    bool root_user_set(int user_index, User new_user); // 通过下标设置用户
    bool root_user_set(User origin_user, User new_user); // 通过名称设置用户
    bool root_user_delete(int user_index); // 通过下标删除用户
    bool root_user_delete(User origin_user); // 通过名称删除用户
    bool root_user_show(); // 显示用户
    bool root_user_search(string name); // 搜索用户
    //管理员-操作商品
    bool root_product_add(string name, string type, double price, int num); // 添加商品
    bool root_product_set(int product_index, Product new_product); // 通过下标设置商品
    bool root_product_set(Product origin_product, Product new_product); // 通过名称设置商品
    bool root_product_delete(int product_index); // 通过下标删除商品
    bool root_product_delete(User origin_product); // 通过名称删除商品
private:
    vector<User> users; // 用户列表
    vector<Product> products; // 商品列表
    vector<Code> codes; // 兑换码列表
    User* current_user; // 当前用户
    double coupon_min; // 优惠券最小折扣
    double coupon_max; // 优惠券最大折扣
    double activity_discount; // 活动折扣
};

Servor::Servor(){ // 构造函数
    if(servor_start() == false){ // 启动服务器
        servor_start_failed(); // 启动服务器失败
    }
    current_user = NULL;
    coupon_min = 0.7;
    coupon_max = 0.9;
    activity_discount = 1;
}

bool Servor::servor_file_check(){ // 检查文件
    bool jud = true;
    if (access("data", 0) != 0){ // 判断数据文件夹是否存在
        cout << "ERROR: 'data/products.csv' not found" << endl;
        cout << "ERROR: 'data/users.csv' not found" << endl;
        cout << "ERROR: 'data/codes.csv' not found" << endl;
		mkdir("data");
        return false;
	}
    if(access("data/products.csv", 0) != 0){ // 判断商品数据文件是否存在
        cout << "ERROR: 'data/products.csv' not found" << endl;
        jud = false;
    }
    if(access("data/users.csv", 0) != 0){ // 判断用户数据文件是否存在
        cout << "ERROR: 'data/users.csv' not found" << endl;
        jud = false;
    }
    if(access("data/codes.csv", 0) != 0){ // 判断兑换码数据文件是否存在
        cout << "ERROR: 'data/codes.csv' not found" << endl;
        jud = false;
    }
    return jud;
}

bool Servor::servor_start(){ // 启动服务器
    if(!servor_file_check()){ // 检查文件
        return false;
    }
    if(load_product_data() && load_user_data() && lode_code_data()){ // 加载数据
        return true;
    }
    return false;
}

void Servor::servor_start_failed(){ // 启动服务器失败
    cout << endl;
    cout << "Please check the documents and restart the system" << endl;
    cout << endl;
    system("pause");
    exit(0);
}

bool Servor::servor_save(){ // 保存数据
    if(save_user_data() && save_product_data() && save_code_data()){ // 保存每个数据文件的数据
        return true;
    }
    return false;
}

bool Servor::servor_exit(){ // 退出服务器
    if(servor_save()){ // 保存数据
        if(current_user != NULL){ // 判断当前用户是否存在, 存在则登出
            if(current_user->get_permission() == User::USER){ // 判断当前用户权限
                user_logout();
            } else{
                root_logout();
            }
        }
        return false;
    }
    return true;
}

bool Servor::load_product_data(){ // 加载商品数据
    ifstream ifs("data/products.csv");
    if(!ifs){
        cout << "ERROR: 'data/products.csv' not found" << endl;
        return false;
    }
    string line;
    while (getline(ifs, line)){ // 逐行读取数据
        stringstream ss(line);
        string temp;
        int i = 0;
        string name;
        string type;
        double price;
        int num;
        while (getline(ss, temp,',')){ // 逐个读取数据
            if (i == 0){ // 读取商品名称
                name = temp;
            } else if (i == 1){ // 读取商品类型
                type = temp;
            } else if (i == 2){ // 读取商品价格
                price = stod(temp);
            } else if (i == 3){ // 读取商品数量
                num = stoi(temp);
            }
            i++;
        }
        Product product(name, type, price, num);
        products.push_back(product);
    }
    ifs.close();
    return true;
}

bool Servor::load_user_data(){ // 加载用户数据
    ifstream ifs("data/users.csv");
    if(!ifs){
        cout << "ERROR: 'data/users.csv' not found" << endl;
        return false;
    }
    string line;
    while (getline(ifs, line)){ // 逐行读取数据
		stringstream ss(line);
		string temp;
		int i = 0;
        User user(User::USER);
		Cart cart;
        Product product("NULL", "NULL", 0, 0);
		while (getline(ss, temp,',')){ // 逐个读取数据
			if (i == 0){ // 读取用户名称
				user.set_name(temp);
			} else if (i == 1){ // 读取用户密码
				user.set_password(temp);
			} else if (i == 2){ // 读取用户余额
				user.set_money(stod(temp));
			} else if (i == 3){ // 读取购物车中的优惠券
                cart.set_coupon(stod(temp));
            } else if (i == 4){ // 读取购物车中是否使用优惠码
                cart.set_code_flag(stoi(temp) == 1 ? true : false);
            } else { // 读取购物车中的商品
				if(i % 2 == 1){ // 读取商品名称
                    product = product_get(temp); // 通过商品名称, 从服务器获取商品完整信息
				} else{ // 读取购物车中的商品数量
                    if(product.get_name() != "NULL"){ // 在服务器中判断商品是否存在
                        cart.load_cart(product, stoi(temp)); // 将商品加载到购物车中
                    } else{
                        cout << "ERROR: product not found" << endl;
                    }
                }
			}
			i++;
		}
		user.set_cart(cart);
		users.push_back(user);
    }
    ifs.close();
    return true;
}

bool Servor::lode_code_data(){ // 加载兑换码数据
    ifstream ifs("data/codes.csv");
    if(!ifs){
        cout << "ERROR: 'data/codes.csv' not found" << endl;
        return false;
    }
    string line;
    while (getline(ifs, line)){ // 逐行读取数据
        stringstream ss(line);
        string temp;
        int i = 0;
        string code_string;
        double discount;
        bool pubilsh_flag;
        while (getline(ss, temp,',')){ // 逐个读取数据
            if (i == 0){ // 读取兑换码
                code_string = temp;
            } else if (i == 1){ // 读取折扣
                discount = stod(temp);
            } else if (i == 2){ // 读取是否发布
                pubilsh_flag = stoi(temp);
            }
            i++;
        }
        Code code(code_string, discount, pubilsh_flag);
        codes.push_back(code);
    }
    ifs.close();
    return true;

}

bool Servor::save_product_data(){ // 保存商品数据
    ofstream ofs("data/products.csv");
    for(auto product : products){
        ofs << product.get_name() << "," << product.get_type() << "," << product.get_price() << "," << product.get_num() << endl;
    }
    ofs.close();
    return true;
}

bool Servor::save_user_data(){ // 保存用户数据
    ofstream ofs("data/users.csv");
    if(is_user()){ // 判断是否为登录中的用户, 是则保存到服务器
        for(auto &user : users){
            if(user.get_name() == current_user->get_name()){
                user = *current_user;
                break;
            }
        }
    }
    for(auto user : users){ // 保存所有用户数据
        ofs << user.get_name() << "," << user.get_password() << "," << user.get_money() << ",";
        Cart cart = user.get_cart();
        ofs << cart.get_coupon() << "," << cart.get_code_flag() << ",";
        vector<Product> user_products = cart.get_products();
        for(auto user_product : user_products){
            ofs << user_product.get_name() << "," << user_product.get_num() << ",";
        }
        ofs << endl;
    }
    ofs.close();
    return true;
}

bool Servor::save_code_data(){ // 保存兑换码数据
    ofstream ofs("data/codes.csv");
    for(auto code : codes){
        ofs << code.get_code() << "," << code.get_discount() << "," << code.get_pubilsh_flag() << endl;
    }
    ofs.close();
    return true;

}

User* Servor::get_current_user(){ // 获取当前用户
    return current_user;
}

bool Servor::is_user(){ // 判断是否为用户
    if(current_user != NULL && current_user->get_permission() == User::USER){
        return true;
    } else{
        return false;
    }
}

bool Servor::user_signup(string name, string password){ // 用户注册
    if (password.length() < 6 || password.length() > 16) { // 判断密码长度是否合法
        cout << "ERROR: Password length should be between 6 and 16 characters" << endl;
        return false;
    }
    regex pattern_password("^[A-Za-z0-9_!?@#.]+$");
    if (!regex_match(password, pattern_password)) { // 判断密码是否合法
        cout << "ERROR: illegal password" << endl;
        return false;
    }
    regex pattern_name("^[A-Za-z0-9_]+$");
    if (!regex_match(name, pattern_name)) { // 判断用户名是否合法
        cout << "ERROR: illegal name" << endl;
        return false;
    }
    for(auto user : users){ // 判断用户名是否重复
        if(user.get_name() == name){
            return false;
        }
    }
    User user(User::USER);
    user.set_name(name);
    user.set_password(password);
    user.set_money(0);
    users.push_back(user);
    if(!save_user_data()){ // 保存用户数据
        return false;
    }
    return true;
}

bool Servor::user_login(string name, string password){ // 用户登录
    for(auto user : users){ // 遍历用户列表
        if(user.get_name() == name && user.get_password() == password){ // 判断用户名和密码是否正确
            if(current_user != NULL){ // 判断当前用户是否存在, 存在则登出
                if(current_user->get_permission() == User::USER){
                    user_logout();
                } else{
                    root_logout();
                }
            }
            current_user = new User(User::USER);
            current_user->set_name(user.get_name());
            current_user->set_password(user.get_password());
            current_user->set_money(user.get_money());
            current_user->set_cart(user.get_cart());
            return true;
        }
    }
    return false;
}

bool Servor::user_logout(){ // 用户登出
    for(auto &user : users){ // 遍历用户列表, 将当前用户信息保存到服务器
        if(user.get_name() == current_user->get_name()){
            user = *current_user;
            break;
        }
    }
    delete current_user;
    current_user = NULL;
    if(!save_user_data()){ // 保存用户数据
        return false;
    }
    return true;
}

bool Servor::user_change_password(string original_password, string password){ // 修改密码
    if(current_user->get_password() != original_password){ // 判断原密码是否正确
        cout << "ERROR: original password is wrong" << endl;
        return false;
    }
    if (password.length() < 6 || password.length() > 16) { // 判断密码长度是否合法
        cout << "ERROR: Password length should be between 6 and 16 characters" << endl;
        return false;
    }
    regex pattern_password("^[A-Za-z0-9_!?@#.]+$");
    if (!regex_match(password, pattern_password)) { // 判断密码是否合法
        cout << "ERROR: illegal password" << endl;
        return false;
    }
    current_user->set_password(password); 
    string name = current_user->get_name();
    if(user_logout() && user_login(name, password)){ // 登出并重新登录
        return true;
    }
    return false;
}

bool Servor::user_recharge(double money){ // 充值
    current_user->set_money(current_user->get_money() + money);
    for(auto &user : users){ // 遍历用户列表, 将当前用户信息保存到服务器
        if(user.get_name() == current_user->get_name()){
            user = *current_user;
            if(!save_user_data()){ // 保存用户数据
                return false;
            }
            return true;
        }
    }
    return false;

}

bool Servor::user_ask_for_coupon(){ // 领取优惠券
    if(current_user->get_cart().get_coupon() != 1){ // 判断是否已经领取优惠券
        cout << "You have had a coupon!" << endl;
        return false;
    }
    srand(time(0)); // 随机生成优惠券
    double coupon = (double)(rand() % (int)(coupon_max * 100 - coupon_min * 100) + coupon_min * 100) / 100.0;
    Cart cart = current_user->get_cart();
    if(cart.set_coupon(coupon) == false){ // 设置优惠券
        return false;
    }
    current_user->set_cart(cart);
    return save_user_data(); // 保存用户数据
}

string Servor::user_ask_for_code(){ // 领取兑换码
    if(current_user->get_cart().get_coupon() != 1){ // 判断是否已经领取优惠券
        cout << "You have had a coupon. You can't ask for redemption code" << endl;
        return "NULL";
    }
    if(current_user->get_cart().get_code_flag() == true){ // 判断是否已经领取兑换码
        cout << "You have had a redemption code. You can't ask for redemption code" << endl;
        return "NULL";
    }
    current_user->get_cart().set_code_flag(true);
    for(auto &code : codes){ // 遍历兑换码列表
        if(code.get_pubilsh_flag() == false){ // 如果存在未发布的兑换码, 则发布
            code.set_pubilsh_flag(true);
            save_code_data(); // 保存兑换码数据
            Cart cart = current_user->get_cart();
            cart.set_code_flag(true);
            current_user->set_cart(cart);
            save_user_data(); // 保存用户数据
            return code.get_code();
        }
    }
    if(code_create(25, true) != "NULL"){ // 如果不存在未发布的兑换码, 则创建兑换码并发布
        Cart cart = current_user->get_cart();
        cart.set_code_flag(true);
        current_user->set_cart(cart);
        save_user_data(); // 保存用户数据, 兑换码数据已于创建时保存
        return codes[codes.size() - 1].get_code();
    } else{
        return "NULL";
    }
}

Product Servor::product_get(int index){ // 根据下标获取商品
    if(index >= 0 && index < products.size()){ // 判断下标是否合法
        return products[index];
    } else{
        return Product("NULL", "NULL", 0, 0);
    }
}

Product Servor::product_get(string name){ // 根据名称获取商品
    for(auto product : products){ // 遍历商品列表
        if(product.get_name() == name){
            return product;
        }
    }
    return Product("NULL", "NULL", 0, 0);
}

vector<Product> Servor::products_get(){ // 获取商品列表
    return products;
}

bool Servor::product_show(){ // 显示商品
    int i = 0;
    for(auto product : products){ // 遍历商品列表
        cout << "Order number: " << i << endl;
        product.info();
        cout << endl;
        i ++;
    }
    if(i == 0){ // 如果商品列表为空, 则返回错误
        cout << "ERROR: product is empty" << endl;
        return false;
    }
    return true;
}

bool Servor::product_search(string name){ // 搜索商品
    bool jud = 0;
    int i = 0;
    for(auto product : products){ // 遍历商品列表
        if(product.get_name() == name || product.get_name().find(name) != string::npos){
            cout << "Order number: " << i << endl;
            product.info();
            cout << endl;
            jud = 1;
        }
        i ++;
    }
    if(jud == 1){ // 如果搜索到商品, 则返回正确
        return true;
        
    } else{
        cout << "ERROR: product not found" << endl;
        return false;
    }
}

bool Servor::cart_add(Product product, int num){ // 从服务器商品列表中添加商品
    Cart cart = current_user->get_cart();
    if(cart.add(product, num) == false){ // 添加商品
        return false;
    }
    current_user->set_cart(cart);
    return save_user_data();
}

bool Servor::cart_reduce(Product product, int num){ // 从购物车商品列表中减少商品数量
    Cart cart = current_user->get_cart();
    if(cart.reduce(product, num) == false){ // 减少商品数量
        return false;
    }
    current_user->set_cart(cart);
    return save_user_data();
}

bool Servor::cart_delete(Product product){ // 通过名称, 从购物车商品列表中删除商品
    Cart cart = current_user->get_cart();
    if(cart.del(product.get_name()) == false){ // 通过名称删除商品
        return false;
    }
    current_user->set_cart(cart);
    return save_user_data();
}

bool Servor::cart_delete(int index){ // 通过下标, 从购物车商品列表中删除商品
    Cart cart = current_user->get_cart();
    if(cart.del(index) == false){ // 通过下标删除商品
        return false;
    }
    current_user->set_cart(cart);
    return save_user_data();

}

double Servor::cart_get_total_price(vector<int> index){ // 获取总价
    double total_price = 0;
    vector<Product> cart_products = current_user->get_cart().get_products(); 
    for(auto i : index){ // 遍历购物车中的商品, 计算总价
        total_price += cart_products[i].get_price() * cart_products[i].get_num();
    }
    return total_price;

}

double Servor::cart_check(vector<int> index){ // 结算
    vector<Product> cart_products = current_user->get_cart().get_products();
    for(auto i : index){ // 遍历购物车中的商品
        Product product = product_get(cart_products[i].get_name());
        if(product.get_name() == "NULL"){ // 判断商品是否存在
            cout << "ERROR: product not found" << endl;
            return -1;
        }
        if(product.get_num() < cart_products[i].get_num()){ // 判断商品数量是否足够
            cout << "ERROR: not enough products" << endl;
            return -1;
        }
    }
    double total_price = cart_get_total_price(index);
    if(activity_discount == 1){ // 判断是否有活动折扣
        cout << "Total price: $" << total_price << endl;
    } else{ // 如果有活动折扣, 则计算乘上活动折扣的总价
        total_price *= activity_discount;
        cout << "Total price (with activity discount): $" << total_price << endl;
    }
    return total_price;
}

bool Servor::cart_payment(vector<int> index, double total_price){ // 支付
    if(index.size() == 0){ // 判断购物车是否为空
        cout << "ERROR: cart is empty" << endl;
        return false;
    }
    if(total_price == -1){ // 判断结算是否通过
        return false;
    }
    int code_index = -1;
    int use_coupon = -1;
    cout << "Use coupon? (Y/N): ";
    char jud_coupon;
    cin >> jud_coupon;
    if(jud_coupon == 'y' || jud_coupon == 'Y'){ // 判断是否使用优惠券
        if(current_user->get_cart().get_coupon() < 0 || current_user->get_cart().get_coupon() >= 1){ // 判断是否有优惠券, 如果没有则提示是否使用兑换码
            cout << "You don't have coupon. Do you want to use redemption code? (Y/N): ";
            char jud_code;
            cin >> jud_code;
            if(jud_code == 'y' || jud_code == 'Y'){ // 判断是否使用兑换码
                cout << "Enter your redemption code: ";
                string redemption_code;
                cin >> redemption_code;
                code_index = code_search(redemption_code);
                if(code_index == -1 || codes[code_index].get_discount() == 1){ // 判断兑换码是否存在, 是否已经使用
                    cout << "Redemption code is wrong" << endl;
                } else{ // 如果兑换码存在且未使用, 则计算乘上兑换码折扣的总价
                    cout << "Total price (with redemption code " << (activity_discount == 1 ? "" : "and activity discount");
                    total_price *= codes[code_index].get_discount();
                    cout << " ): $" << total_price  << endl;
                    
                }
            }
        } else{ // 如果有优惠券, 则计算乘上优惠券折扣的总价
            cout << "Total price (with coupon " << (activity_discount == 1 ? "" : "and activity discount");
            total_price *= current_user->get_cart().get_coupon();
            cout << " ): $" << total_price << endl;
            use_coupon = 1;
        }
    } else{ // 如果不使用优惠券, 则判断是否使用兑换码
        cout << "Use redemption code? (Y/N): ";
        char jud_code;
        cin >> jud_code;
        if(jud_code == 'y' || jud_code == 'Y'){ // 判断是否使用兑换码
            cout << "Enter your redemption code: ";
            string redemption_code;
            cin >> redemption_code;
            code_index = code_search(redemption_code);
            if(code_index == -1 || codes[code_index].get_discount() == 1){ // 判断兑换码是否存在, 是否已经使用
                cout << "Redemption code is wrong" << endl;
            } else{ // 如果兑换码存在且未使用, 则计算乘上兑换码折扣的总价
                cout << "Total price (with redemption code " << (activity_discount == 1 ? "" : "and activity discount");
                total_price *= codes[code_index].get_discount();
                cout << " ): $" << total_price  << endl;
                
            }
        }
    }
    cout << "Confirm payment (Y/N): ";
    char jud_confirm;
    cin >> jud_confirm;
    if(jud_confirm == 'N' || jud_confirm == 'n'){ // 判断是否确认支付
        return false;
    } else{
        if(total_price > current_user->get_money()){ // 判断余额是否足够
            cout << "ERROR: not enough money" << endl;
            return false;
        }
        if(code_index != -1){ // 如果使用兑换码, 则删除兑换码
            code_delete(code_index); // 删除兑换码, 并保存兑换码数据
            current_user->get_cart().set_code_flag(false);
        } else if(use_coupon != -1){ // 如果使用优惠券, 则删除优惠券
            current_user->get_cart().set_coupon(1);
        }
        Cart original_cart = current_user->get_cart();
        vector<Product> cart_products = original_cart.get_products(); // 获取购物车中的商品
        vector<string> p_names; // 保存购物车中的商品名称
        for(auto i : index){ // 遍历购物车中的商品, 减少商品数量
            for(auto &product : products){ // 遍历服务器商品列表
                if(product.get_name() == cart_products[i].get_name()){ // 判断商品是否存在
                    p_names.push_back(cart_products[i].get_name()); // 保存商品名称
                    product.set_num(product.get_num() - cart_products[i].get_num()); // 减少服务器商品列表的商品数量
                    break;
                }
            }
        }
        if(!save_product_data()){ // 保存商品数据
            return false;
        }
        current_user->set_money(current_user->get_money() - total_price);
        Cart cart = current_user->get_cart();
        for(auto p_name : p_names){ // 根据记录的商品名称, 从购物车中删除商品
            cart.del(p_name);
        }
        current_user->set_cart(cart); // 保存购物车
        for(auto &user : users){ // 遍历用户列表, 将当前用户信息保存到服务器
            if(user.get_name() == current_user->get_name()){ // 通过用户名找到当前用户
                user = *current_user; // 保存当前用户信息
                if(!save_user_data()){ // 保存用户数据
                    return false;
                }
                cart_save_history(index, original_cart, total_price); // 保存历史
                return true;
            }
        }
        return false;
    }
}

bool Servor::cart_save_history(vector<int> index, Cart original_cart, double total_price){ // 保存历史
    if (access("history", 0) != 0){ // 判断历史文件夹是否存在
        mkdir("history");
    }
    ofstream ofs("history/" + current_user->get_name() + ".txt", ios::app);
    long long seconds;
    // int yy, mm, dd;
    int h, m, s;
    seconds = time(0);
    // yy = seconds / (3600 * 24 * 365) + 1970;
    // long long seconds_mm = seconds % (3600 * 24 * 365);
    // mm = seconds_mm / (3600 * 24 * 30) + 1;
    // long long seconds_dd = seconds_mm % (3600 * 24 * 30);
    // dd = seconds_dd / (3600 * 24) + 1;
    s = seconds % 60;
    m = (seconds % 3600) / 60;
    h = ((seconds % (3600 * 24)) / 3600 + 8) % 24;
    ofs << "Time: ";
    // ofs << yy << "/" << (mm < 10 ? "0" : "") << mm << "/" << (dd < 10 ? "0" : "") << dd << "-";
    ofs << (h < 10 ? "0" : "") << h << ":" << (m < 10 ? "0" : "") << m;
    ofs << ":" << (s < 10 ? "0" : "") << s << " " << seconds << endl;
    vector<Product> cart_products = original_cart.get_products();
    for(auto i : index){ // 遍历购物车中的商品, 保存历史
        int num = cart_products[i].get_num() - current_user->get_cart().get_product(cart_products[i].get_name()).get_num();
        ofs << "Product: " << cart_products[i].get_name() << " Type: " << cart_products[i].get_type();
        ofs << " Price: " << cart_products[i].get_price() << " Num: " << num << endl;
    }
    ofs << "Total price: " << total_price << endl;
    ofs << endl;
    ofs.close();
    return true;
}

bool Servor::cart_show_history(){ // 显示历史
    ifstream ifs("history/" + current_user->get_name() + ".txt");
    if(!ifs){ // 判断历史是否存在
        cout << "ERROR: history not found" << endl;
        return false;
    }
    string line;
    while (getline(ifs, line)){ // 逐行读取历史
        cout << line << endl;
    }
    ifs.close();
    return true;
}

bool Servor::cart_analysis(vector<int> start_time, vector<int> end_time){ // 通过具体时间分析历史
    long long seconds_begin = 0;
    long long seconds_end = 0;
    struct tm timeinfo;
    timeinfo.tm_year = start_time[0] - 1900;
    timeinfo.tm_mon = start_time[1] - 1;
    timeinfo.tm_mday = start_time[2];
    timeinfo.tm_hour = start_time[3];
    timeinfo.tm_min = start_time[4];
    timeinfo.tm_sec = start_time[5];
    seconds_begin = mktime(&timeinfo);
    timeinfo.tm_year = end_time[0] - 1900;
    timeinfo.tm_mon = end_time[1] - 1;
    timeinfo.tm_mday = end_time[2];
    timeinfo.tm_hour = end_time[3];
    timeinfo.tm_min = end_time[4];
    timeinfo.tm_sec = end_time[5];
    seconds_end = mktime(&timeinfo);
    return cart_analysis(seconds_begin, seconds_end);
}

bool Servor::cart_analysis(long long seconds_begin, long long seconds_end){ // 通过时间戳分析历史
    ifstream ifs("history/" + current_user->get_name() + ".txt");
    if(!ifs){ // 判断历史是否存在
        cout << "ERROR: history not found" << endl;
        return false;
    }
    vector<string> lines;
    char buffer[2048];
    while(ifs.getline(buffer, 2048,'\n')){ // 逐行读取历史
        lines.push_back(buffer);
    }
    ifs.close();
    vector<Product> products_analysis;
    bool jud = false;
    for(auto line : lines){ // 遍历历史
        if(line.find("Time") != string::npos){ // 判断是否为时间
            long long seconds;
            stringstream ss(line);
            string temp;
            int i = 0;
            while (getline(ss, temp,' ')){ // 读取时间戳
                if(i == 2){
                    seconds = stoll(temp);
                }
                i ++;
            }
            if (seconds >= seconds_begin){ // 判断时间戳是否在时间范围内
                jud = true;
            }
            if (seconds > seconds_end){ // 判断时间戳是否超出时间范围
                break;
            }
        }
        if(jud == true && line.find("Product") != string::npos){ // 判断是否为商品
            stringstream ss(line);
            string temp;
            int i = 0;
            Product product("NULL", "NULL", 0, 0);
            while (getline(ss, temp,' ')){ // 读取商品信息
                if(i == 1){ // 读取商品名称
                    product.set_name(temp);
                } else if(i == 3){ // 读取商品类型
                    product.set_type(temp);
                } else if(i == 5){ // 读取商品价格
                    product.set_price(stod(temp));
                } else if(i == 7){ // 读取商品数量
                    product.set_num(stoi(temp));
                }
                i ++;
            }
            products_analysis.push_back(product);
        }
    }
    if(jud == false){ // 判断是否有数据
        cout << "ERROR: no data" << endl;
        return false;
    }
    sort(products_analysis.begin(), products_analysis.end(), [](const Product& p1, const Product& p2) { // 对商品进行排序
        if (p1.get_type() == p2.get_type()) {
            return p1.get_name() < p2.get_name();
        }
        return p1.get_type() < p2.get_type();
    });
    products_analysis.push_back(Product("NULL", "NULL", 0, 0));
    cout << "Analysis result:" << endl;
    double type_price = 0;
    for(int i = 0; i < products_analysis.size() - 1; i ++){ // 遍历商品, 输出分析结果
        if(i == 0 || products_analysis[i].get_type() != products_analysis[i - 1].get_type()){ // 输出商品类型
            cout << endl << "Type: " << products_analysis[i].get_type() << endl;
        }
        cout << "Product: " << products_analysis[i].get_name() << " Price: $" << products_analysis[i].get_price(); // 输出商品名称和价格
        int num = 0;
        while(i < products_analysis.size() - 1){ // 计算商品数量
            num += products_analysis[i].get_num();
            if(products_analysis[i].get_name() != products_analysis[i + 1].get_name()){ // 输出商品数量
                cout << " Num: " << num << endl;
                break;
            }
            i ++;
        }
        type_price += num * products_analysis[i].get_price(); // 计算商品类型总价
        if(products_analysis[i].get_type() != products_analysis[i + 1].get_type()){ // 输出商品类型总价
            cout << "Type total price: $" << type_price << endl;
            type_price = 0;
        }
    }
    return true;
}

string Servor::code_create(int n, bool publush_flag){ // 创建随机折扣的兑换码
    string library1 = "0123456789";
    string library2 = "abcdefghijklmnopqrstuvwxyz";
    string library3 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string library = library1 + library2 + library3;
    srand(time(0));
    string code;
    while(1){ // 随机生成兑换码
        code = "";
        for (int i = 0; i < n; i++) {
            int key = rand() % library.length();
            code += library[key];
        }
        if(code_search(code) == -1){
            break;
        }
    }
    double discount = (double)(rand() % 3 + 7) / 10.0; // 随机生成折扣
    Code new_code(code, discount, publush_flag);
    codes.push_back(new_code);
    save_code_data(); // 保存兑换码数据
    return code;
}

string Servor::code_create(int n, double discount, bool publush_flag){ // 创建指定折扣的兑换码
    string library1 = "0123456789";
    string library2 = "abcdefghijklmnopqrstuvwxyz";
    string library3 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string library = library1 + library2 + library3;
    srand(time(0));
    string code;
    while(1){ // 随机生成兑换码
        code = "";
        for (int i = 0; i < n; i++) {
            int key = rand() % library.length();
            code += library[key];
        }
        if(code_search(code) == -1){
            break;
        }
    }
    Code new_code(code, discount, publush_flag);
    codes.push_back(new_code);
    save_code_data(); // 保存兑换码数据
    return code;
}

int Servor::code_search(string code){ // 搜索兑换码
    for(int i = 0; i < codes.size(); i ++){ // 遍历兑换码列表
        if(codes[i].get_code() == code){ // 判断兑换码是否存在
            return i;
        }
    }
    return -1;
}

double Servor::code_get_discount(string code){ // 获取兑换码折扣
    int code_index = code_search(code);
    if(code_index != -1){ // 判断兑换码是否存在
        return codes[code_index].get_discount();
    } else{
        return 1;
    }
}

bool Servor::code_delete(int code_index){ // 删除兑换码
    if(code_index >=0 && code_index < codes.size()){ // 判断下标是否合法
        codes.erase(codes.begin() + code_index);
        return save_code_data(); // 保存兑换码数据
    }
    return false;
}

bool Servor::code_eligibility_check(){ // 检查是否有资格申请兑换码
    if(get_current_user()->get_cart().get_code_flag() == false && get_current_user()->get_cart().get_coupon() == 1){ // 判断是否有资格申请兑换码
        cout << "You are already eligible to apply for redemption code." << endl;
        return false;
    }
    return true;
}

bool Servor::code_eligibility_initialize(){ // 初始化申请兑换码资格
    Cart cart = current_user->get_cart();
    cart.set_coupon(1);
    cart.set_code_flag(false);
    current_user->set_cart(cart);
    return save_user_data();
}

double Servor::activity_get(){ // 获取活动折扣
    return activity_discount;
}

bool Servor::is_root(){ // 判断是否为管理员
    if(current_user != NULL && current_user->get_permission() == User::ROOT){ // 判断是否为管理员
        return true;
    } else{
        return false;
    }
}

bool Servor::root_login(string name, string password){ // 管理员登录
    Root* root = new Root();
    if(root->get_name() == name && root->get_password() == password){ // 判断用户名和密码是否正确
        if(current_user != NULL){ // 判断当前用户是否存在, 存在则登出
            if(current_user->get_permission() == User::USER){
                user_logout();
            } else{
                root_logout();
            }
        }
        current_user = root;
        return true;
    }
    return false;
}

bool Servor::root_logout(){ // 管理员登出
    if(servor_save()){ // 保存服务器数据
        delete current_user;
        current_user = NULL;
        return true;
    }
    return false;
}

bool Servor::root_coupon_set(double min, double max){ // 设置优惠券范围
    if(!is_root()){ // 判断是否为管理员
        return false;
    }
    this->coupon_min = min;
    this->coupon_max = max;
    return true;
}

bool Servor::root_activity_set(double discount){ // 设置活动折扣
    if(!is_root()){ // 判断是否为管理员
        return false;
    }
    this->activity_discount = discount;
    return true;
}

vector<Code> Servor::root_codes_get(){ // 获取兑换码列表
    if(!is_root()){ // 判断是否为管理员
        return vector<Code>();
    }
    return codes;
}

bool Servor::root_code_add(double discount){ // 添加兑换码
    if(!is_root()){ // 判断是否为管理员
        return false;
    }
    code_create(25, discount, false);
    return true;
}

void Servor::root_code_show(){ // 显示兑换码
    if(!is_root()){ // 判断是否为管理员
        return;
    }
    int i = 0;
    for(auto code : codes){ // 遍历兑换码列表
        cout << "Order number: " << i << endl;
        cout << "Code: " << code.get_code() << endl;
        cout << "Discount: " << code.get_discount() << endl;
        cout << "Pubilsh flag: " << code.get_pubilsh_flag() << endl;
        cout << endl;
        i ++;
    }
    if(i == 0){ // 如果兑换码列表为空, 则返回错误
        cout << "ERROR: code is empty" << endl;
    }
}

bool Servor::root_code_delete(int code_index){ // 删除兑换码
    if(!is_root()){ // 判断是否为管理员
        return false;
    }
    codes.erase(codes.begin() + code_index);
    return true;
}

bool Servor::root_code_delete(string code){ // 删除兑换码
    if(!is_root()){ // 判断是否为管理员
        return false;
    }
    for(auto it = codes.begin(); it != codes.end(); it ++){ // 遍历兑换码列表
        if(it->get_code() == code){ // 判断兑换码是否存在
            codes.erase(it);
            return true;
        }
    }
    return false;

}

User Servor::root_user_get(int index){ // 根据下标获取用户
    if(!is_root()){ // 判断是否为管理员
        return User(User::USER);
    }
    if(index >= 0 && index < users.size()){ // 判断下标是否合法
        return users[index];
    } else{
        return User(User::USER);
    }
    
}

User Servor::root_user_get(string name){ // 根据名称获取用户
    if(!is_root()){ // 判断是否为管理员
        return User(User::USER);
    }
    for(auto user : users){ // 遍历用户列表
        if(user.get_name() == name){
            return user;
        }
    }
    return User(User::USER);
}

vector<User> Servor::root_users_get(){ // 获取用户列表
    if(!is_root()){ // 判断是否为管理员
        return vector<User>();
    }
    return users;
}

bool Servor::root_user_add(string name, string password, int money){ // 添加用户
    if(!is_root()){ // 判断是否为管理员
        return false;
    }
    User new_user(User::USER);
    new_user.set_name(name);
    new_user.set_password(password);
    new_user.set_money(money);
    new_user.set_cart(Cart());
    users.push_back(new_user);
    return true;
}

bool Servor::root_user_set(int user_index, User new_user){ // 设置用户
    if(!is_root()){ // 判断是否为管理员
        return false;
    }
    users[user_index] = new_user;
    return true;
}

bool Servor::root_user_set(User origin_user, User new_user){ // 设置用户
    if(!is_root()){ // 判断是否为管理员
        return false;
    }
    for(auto &user : users){ // 遍历用户列表
        if(user.get_name() == origin_user.get_name()){ // 根据用户名找到用户
            user = new_user;
            return true;
        }
    }
    return false;
}

bool Servor::root_user_delete(int user_index){ // 删除用户
    if(!is_root()){ // 判断是否为管理员
        return false;
    }
    users.erase(users.begin() + user_index);
    return true;
}

bool Servor::root_user_delete(User origin_user){ // 删除用户
    if(!is_root()){ // 判断是否为管理员
        return false;
    }
    for(auto it = users.begin(); it != users.end(); it ++){ // 遍历用户列表
        if(it->get_name() == origin_user.get_name()){ // 根据用户名找到用户
            users.erase(it);
            return true;
        }
    }
    return false;
}

bool Servor::root_user_show(){ // 显示用户
    if(!is_root()){ // 判断是否为管理员
        return false;
    }
    int i = 0;
    for(auto user : users){ // 遍历用户列表
        cout << "Order number: " << i << endl;
        user.info_root();
        cout << endl;
        i ++;
    }
    if(i == 0){ // 如果用户列表为空, 则返回错误
        cout << "ERROR: user is empty" << endl;
        return false;
    }
    return true;
}

bool Servor::root_user_search(string name){ // 搜索用户
    if(!is_root()){ // 判断是否为管理员
        return false;
    }
    bool jud = 0;
    int i = 0;
    for(auto user : users){ // 遍历用户列表
        if(user.get_name() == name || user.get_name().find(name) != string::npos){ // 判断用户是否存在
            cout << "Order number: " << i << endl;
            user.info();
            cout << endl;
            jud = 1;
        }
        i ++;
    }
    if(jud == 1){ // 如果用户存在, 则返回正确
        return true;
        
    } else{ // 如果用户不存在, 则返回错误
        cout << "ERROR: user not found" << endl;
        return false;
    }
}

bool Servor::root_product_add(string name, string type, double price, int num){ // 添加商品
    if(!is_root()){ // 判断是否为管理员
        return false;
    }
    for(auto product : products){ // 遍历商品列表
        if(product.get_name() == name){ // 根据商品名称找到商品
            product.set_num(product.get_num() + num);
            return true;
        }
    }
    Product product(name, type, price, num); // 添加商品
    products.push_back(product);
    return true;
}

bool Servor::root_product_set(int product_index, Product new_product){ // 设置商品
    if(!is_root()){ // 判断是否为管理员
        return false;
    }
    products[product_index] = new_product;
    return true;
}

bool Servor::root_product_set(Product origin_product, Product new_product){ // 设置商品
    if(!is_root()){ // 判断是否为管理员
        return false;
    }
    for(auto &product : products){ // 遍历商品列表
        if(product.get_name() == origin_product.get_name()){ // 根据商品名称找到商品
            product = new_product;
            return true;
        }
    }
    return false;
}

bool Servor::root_product_delete(int product_index){ // 删除商品
    if(!is_root()){ // 判断是否为管理员
        return false;
    }
    products.erase(products.begin() + product_index);
    return true;
}

bool Servor::root_product_delete(User origin_product){ // 删除商品
    if(!is_root()){ // 判断是否为管理员
        return false;
    }
    for(auto it = products.begin(); it != products.end(); it ++){ // 遍历商品列表
        if(it->get_name() == origin_product.get_name()){ // 根据商品名称找到商品
            products.erase(it);
            return true;
        }
    }
    return false;
}