#include<bits/stdc++.h>
#include "es_servor.cpp"

using namespace std;

class EShop{ // 网上购物模拟系统类
public:
    EShop(); // 构造函数
    static void e_shop(){ // 运行网上购物模拟系统
        EShop();
    }
    //通用函数
    bool functions(); // 运行功能
    void welcome(); // 欢迎界面
    void pause(); // 暂停
    //部分通用函数
    bool activity(); // 活动
    bool product_search(); // 搜索商品
    //访客函数
    bool visitor(); // 访客
    //访客函数-账户
    bool visitor_account(); // 访客账户
    bool visitor_account_signup(); // 注册
    bool visitor_account_user_login(); // 用户登录
    bool visitor_account_root_login(); // 管理员登录
    //用户函数
    bool user();
    //用户函数-账户
    bool user_account(); // 用户账户
    bool user_account_edit(); // 编辑账户
    bool user_account_edit_recharge(); // 充值
    bool user_account_edit_eligibility(); // 获取兑换码资格
    bool user_account_edit_password(); // 修改密码
    void user_account_information(); // 显示用户信息
    bool user_account_logout(); // 登出
    //用户函数-购物车
    bool user_cart(); // 用户购物车
    bool user_cart_add(); // 添加商品
    bool user_cart_search_add(string name); // 搜索商品时添加
    //用户函数-购物车-编辑
    bool user_cart_edit(); // 编辑购物车
    bool user_cart_edit_quantity(Product product_in_servor, Product product); // 编辑数量
    bool user_cart_edit_quantity_add(Product product_in_servor); // 增加数量
    bool user_cart_edit_quantity_reduce(Product product); // 减少数量
    bool user_cart_edit_delete(int index); // 删除商品
    //用户函数-购物车-优惠
    bool user_cart_preferential(); // 优惠
    bool user_cart_preferential_coupon(); // 优惠券
    bool user_cart_preferential_code(); // 兑换码
    //用户函数-购物车-结算
    bool user_cart_checkout(); // 结算
    //用户函数-购物车-历史
    bool user_cart_show_history(); // 显示购物历史
    bool user_cart_show_history_analysis(); // 显示购物历史分析
    //管理员函数
    bool root(); // 管理员
    //管理员函数-账户
    bool root_logout(); // 管理员登出
    //管理员函数-商品
    bool root_products(); // 管理商品
    bool root_products_add(); // 添加商品
    bool root_products_edit(); // 编辑商品
    bool root_products_edit_set(int index); // 设置商品
    bool root_products_edit_delete(int index); // 删除商品
    //管理员函数-用户
    bool root_users(); // 管理用户
    bool root_users_add(); // 添加用户
    bool root_users_search(); // 搜索用户
    bool root_users_edit(); // 编辑用户
    bool root_users_edit_set(int index); // 设置用户
    bool root_users_edit_delete(int index); // 删除用户
    //管理员函数-优惠
    bool root_preferential(); // 管理优惠
    bool root_preferential_coupon(); // 优惠券
    bool root_preferential_activity(); // 活动
    bool root_preferential_code(); // 兑换码
    bool root_preferential_code_add(); // 添加兑换码
    bool root_preferential_code_search(); // 搜索兑换码
    bool root_preferential_code_delete(); // 删除兑换码
    //管理员函数-保存
    bool root_save(); // 保存更改
private:
    Servor servor; // 服务器
};

EShop::EShop(){ // 构造函数
    servor = Servor(); // 初始化服务器
    while(functions()); // 运行功能
}

//通用函数
bool EShop::functions(){ // 运行功能
    if(servor.get_current_user() == NULL){ // 判断当前用户是否为空
        return visitor();
    } else{ // 当前用户不为空
        if(servor.is_root() == false){ // 判断是否为管理员, 不是管理员
            return user();
        } else{ // 是管理员
            return root();
        }
    }
}

void EShop::welcome(){ // 欢迎界面
    system("cls");
    cout << "Welcome to the e-shop system!" << endl << endl;
    cout << "Cuttent user: ";
    cout << (servor.get_current_user() == NULL ? "Not Logged In" : servor.get_current_user()->get_name());
    cout << endl << endl;
}

void EShop::pause(){ // 暂停
    cout << endl;
    system("pause");
}

//部分通用函数
bool EShop::activity(){ // 活动
    if(servor.activity_get() != 1){ // 判断是否有活动
        cout << "Activity: " << servor.activity_get() << endl << endl ;
        return true;
    } else{
        cout << "Activity: " << "No" << endl << endl;
        return false;
    }
}

bool EShop::product_search(){ // 搜索商品
    cout << "Enter the product name to search: ";
    string name;
    cin >> name;
    if(servor.product_search(name) == false){ // 搜索商品, 没有找到则返回false
        cout << "Product not found!" << endl;
        return false;
    }
    cout << endl;
    if(servor.is_user() == true){ // 判断是否为用户, 是用户则询问是否将搜索到的商品添加到购物车
        cout << "Add to cart? (Y/N)" << endl;
        string jud_ac;
        cin >> jud_ac;
        if(jud_ac == "Y" || jud_ac == "y"){ // 是否继续添加添加
            while(user_cart_search_add(name));
        }
    }
    return true;
}

//访客函数
bool EShop::visitor(){ // 访客
    welcome();
    activity();
    cout << "Products: " << endl << endl;
    servor.product_show();
    cout << endl;
    cout << "Please select a function: " << endl;
    cout << "1. Login or Signup" << endl;
    cout << "2. Search products" << endl;
    cout << "0. Exit" << endl;
    cout << endl;
    char jud;
    cin >> jud;
    cout << endl;
    switch(jud){
        case '0':{ // 退出
            welcome();
            cout << "Goodbye!" << endl << endl;
            pause();
            return servor.servor_exit();
        }
        case '1':{ // 登录或注册
            welcome();
            visitor_account();
            break;
        }
        case '2':{ // 搜索商品
            welcome();
            product_search();
            break;
        }
        default:{
            cout << "Invalid choice" << endl;
            break;
        }
    }
    pause();
    return true;
}

//访客函数-账户
bool EShop::visitor_account(){ // 访客账户
    cout << "Login or Signup? (L/S)" << endl;
    string jud_ls;
    cin >> jud_ls;
    if(jud_ls == "L" || jud_ls == "l"){ // 登录
        cout << "User or Root? (U/R)" << endl;
        string jud_ur;
        cin >> jud_ur;
        if(jud_ur == "U" || jud_ur == "u"){ // 用户登录
            return visitor_account_user_login();
        } else if(jud_ur == "R" || jud_ur == "r"){ // 管理员登录
            return visitor_account_root_login();
        } else{
            cout << "Invalid input!" << endl;
            return false;
        }
    } else if(jud_ls == "S" || jud_ls == "s"){ // 注册
        return visitor_account_signup();
    } else{
        cout << "Invalid input!" << endl;
        return false;
    }
}

bool EShop::visitor_account_signup(){ // 注册
    cout << "Please enter your username and password:" << endl;
    string name, password;
    cin >> name >> password;
    if(servor.user_signup(name, password)){ // 注册
        cout << "Signup successfully!" << endl;
        return true;
    } else{
        cout << "Signup failed!" << endl;
        return false;
    }
}

bool EShop::visitor_account_user_login(){ // 用户登录
    cout << "Please enter your username and password:" << endl;
    string name, password;
    cin >> name >> password;
    if(servor.user_login(name, password)){ // 用户登录
        cout << "Login successfully!" << endl;
        return true;
    } else{
        cout << "Login failed!" << endl;
        return false;
    }
}

bool EShop::visitor_account_root_login(){ // 管理员登录
    cout << "Please enter your username and password:" << endl;
    string name, password;
    cin >> name >> password;
    if(servor.root_login(name, password)){ // 管理员登录
        cout << "Login successfully!" << endl;
        return true;
    } else{
        cout << "Login failed!" << endl;
        return false;
    }
}

//用户函数
bool EShop::user(){ // 用户
    welcome();
    activity();
    cout << "Products: " << endl << endl;
    servor.product_show();
    cout << endl;
    cout << "Please select a function: " << endl;
    cout << "1. Account" << endl;
    cout << "2. Search products" << endl;
    cout << "3. Add to cart" << endl;
    cout << "4. Go to cart" << endl;
    cout << "0. Exit" << endl;
    cout << endl;
    char jud;
    cin >> jud;
    cout << endl;
    switch(jud){
        case '0':{ // 退出
            welcome();
            cout << "Goodbye!" << endl << endl;
            pause();
            return servor.servor_exit();
        }
        case '1':{ // 账户
            while(user_account());
            break;
        }
        case '2':{ // 搜索商品
            welcome();
            product_search();
            break;
        }
        case '3':{ // 添加商品
            user_cart_add();
            break;
        }
        case '4':{ // 购物车
            while(user_cart());
            break;
        }
        default:{
            cout << "Invalid choice" << endl;
            break;
        }
    }
    pause();
    return true;
}

//用户函数-账户
bool EShop::user_account(){ // 用户账户
    welcome();
    cout << "Please select a function: " << endl;
    cout << "1. Edit account" << endl;
    cout << "2. Information" << endl;
    cout << "3. Logout" << endl;
    cout << "0. Back" << endl;
    cout << endl;
    char jud_ea;
    cin >> jud_ea;
    cout << endl;
    switch(jud_ea){
        case '0':{ // 返回
            welcome();
            return false;
        }
        case '1':{ // 编辑账户
            while(user_account_edit());
            break;
        }
        case '2':{ // 信息
            welcome();
            user_account_information();
            break;
        }
        case '3':{ // 登出
            if(user_account_logout() == true){
                return false;
            } else{
                break;
            }
           
        }
        default:{
            cout << "Invalid choice" << endl;
            break;
        }
    }
    pause();
    return true;
}

bool EShop::user_account_edit(){ // 编辑账户
    welcome();
    cout << "Please select a function: " << endl;
    cout << "1. Recharge" << endl;
    cout << "2. Get the eligibility of appling for redemption code" << endl;
    cout << "3. Change password" << endl;
    cout << "0. Back" << endl;
    char jud;
    cin >> jud;
    cout << endl;
    switch(jud){
        case '0':{ // 返回
            welcome();
            return false;
        }
        case '1':{ // 充值
            user_account_edit_recharge();
            break;
        }
        case '2':{ // 获取兑换码资格
            user_account_edit_eligibility();
            break;
        }
        case '3':{ // 修改密码
            user_account_edit_password();
            break;
        }
        default:{
            cout << "Invalid choice" << endl;
            break;
        }
    }
    pause();
    return true;
}

bool EShop::user_account_edit_recharge(){ // 充值
    cout << "Enter the amount to recharge: ";
    double money;
    cin >> money;
    if(servor.user_recharge(money) == true){ // 充值
        cout << "Succeed!" << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

bool EShop::user_account_edit_eligibility(){ // 获取兑换码资格
    if(servor.code_eligibility_check() == true){ // 判断是否有资格
        cout << "You can get the eligibility of appling for redemption code." << endl;
        if(servor.get_current_user()->get_cart().get_coupon() != 1){ // 判断是否已经有优惠券
            cout << endl << "Warning: You already have a coupon." << endl;
            cout << "Warning: If you continue to getting the eligibility, you will lose your coupon." << endl;
            cout << endl << "Continue? (Y/N)" << endl;
            string jud;
            cin >> jud;
            cout << endl;
            if(jud == "N" || jud == "n"){
                cout << "You have canceled the operation." << endl;
                return false;
            }
        }
        if(servor.code_eligibility_initialize() == true){ // 初始化资格
            cout << "You have successfully get the eligibility." << endl;
            return true;
        } else{
            cout << "You have failed to get the eligibility." << endl;
            return false;
        }
    } else{
        cout << "You can not get the eligibility of appling for redemption code." << endl;
        return false;
    }
}

bool EShop::user_account_edit_password(){ // 修改密码
    cout << "Enter the original password and new password (OP NP): " << endl;
    string original_password;
    string password;
    cin >> original_password >> password;
    if(servor.user_change_password(original_password, password) == true){ // 修改密码
        cout << "Succeed!" << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

void EShop::user_account_information(){ // 显示用户信息
    servor.get_current_user()->info();
}

bool EShop::user_account_logout(){ // 登出
    if(servor.user_logout() == true){ // 登出
        cout << "Logout successfully!" << endl;
        return true;
    } else{
        cout << "Logout failed!" << endl;
        return false;
    }
}

//用户函数-购物车
bool EShop::user_cart(){ // 用户购物车
    welcome();
    cout << "Money: $" << servor.get_current_user()->get_money() << endl;
    double coupon = servor.get_current_user()->get_cart().get_coupon();
    if(coupon != 1){
        cout << "Coupon: " << coupon << endl;
    } else{
        cout << "Coupon: " << "No" << endl;
    }
    activity();
    cout << "Cart: " << endl;
    servor.get_current_user()->get_cart().show();
    cout << endl;
    cout << "Please select a function: " << endl;
    cout << "1. Edit cart" << endl;
    cout << "2. Get some preferential" << endl;
    cout << "3. Check out" << endl;
    cout << "4. Show purchase history" << endl;
    cout << "5. Show purchase history analysis" << endl;
    cout << "0. Back" << endl;
    cout << endl;
    char jud_uc;
    cin >> jud_uc;
    switch(jud_uc){
        case '0':{ // 返回
            welcome();
            return false;
        }
        case '1':{ // 编辑购物车
            user_cart_edit();
            break;
        }
        case '2':{ // 优惠
            welcome();
            user_cart_preferential();
            break;
        }
        case '3':{ // 结算
            user_cart_checkout();
            break;
        }
        case '4':{ // 显示购物历史
            welcome();
            user_cart_show_history();
            break;
        }
        case '5':{ // 显示购物历史分析
            welcome();
            user_cart_show_history_analysis();
            break;
        }
        default:{
            cout << "Invalid choice" << endl;
            break;
        }
    }
    pause();
    return true;
}

bool EShop::user_cart_add(){ // 添加商品
    cout << "Enter the order number of the product to add: ";
    int index;
    cin >> index;
    Product product = servor.product_get(index);
    if(product.get_name() == "NULL"){ // 判断商品是否存在
        cout << "Product not found!" << endl;
        return false;
    } else{ // 添加商品
        cout << "Enter the quantity to add: ";
        int quantity;
        cin >> quantity;
        if(servor.cart_add(product, quantity) == true){ // 添加商品
            cout << "Succeed!" << endl;
            return true;
        } else{
            cout << "Failed!" << endl;
            return false;
        }
    }
}

bool EShop::user_cart_search_add(string name){ // 搜索商品时添加
    welcome();
    activity();
    servor.product_search(name);
    user_cart_add();
    cout << endl;
    cout << "Continue to add? (Y/N)" << endl;
    string jud_ca;
    cin >> jud_ca;
    if(jud_ca == "Y" || jud_ca == "y"){ // 继续添加
        return true;
    } else{
        return false;
    }
}

//用户函数-购物车-编辑
bool EShop::user_cart_edit(){ // 编辑购物车
    cout << "Enter the order number of the product to edit: ";
    int index;
    cin >> index;
    Product product = servor.get_current_user()->get_cart().get_product(index);
    Product product_in_servor = servor.product_get(product.get_name());
    if(product.get_name() == "NULL"){ // 判断商品是否存在
        cout << "Product not found!" << endl;
        return false;
    }
    if(product_in_servor.get_num() < product.get_num()){ // 判断库存是否足够
        if(product_in_servor.get_num() == 0){ // 判断是否缺货
            cout << "Product out of stock!" << endl;
        } else{
            cout << "Not enough products in the servor!" << endl;
        }
        return false;
    }
    cout << "Set quantity or delete? (S/D)" << endl;
    string jud_sd;
    cin >> jud_sd;
    if(jud_sd == "S" || jud_sd == "s"){ // 编辑数量
        return user_cart_edit_quantity(product_in_servor, product);
    } else if(jud_sd == "D" || jud_sd == "d"){ // 删除商品
        return user_cart_edit_delete(index);
    } else{
        cout << "Invalid input!" << endl;
        return false;
    }
}

bool EShop::user_cart_edit_quantity(Product product_in_servor, Product product){ // 编辑数量
    cout << "Add or reduce? (A/R)" << endl;
    string jud_ar;
    cin >> jud_ar;
    if(jud_ar == "A" || jud_ar == "a"){ // 增加数量
        return user_cart_edit_quantity_add(product_in_servor);
    } else if(jud_ar == "R" || jud_ar == "r"){ // 减少数量
        return user_cart_edit_quantity_reduce(product);
    } else{
        cout << "Invalid input!" << endl;
        return false;
    }
}

bool EShop::user_cart_edit_quantity_add(Product product_in_servor){ // 增加数量
    cout << "Enter the quantity to add: ";
    int quantity;
    cin >> quantity;
    if(servor.cart_add(product_in_servor, quantity) == true){ // 增加数量
        cout << "Succeed!" << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

bool EShop::user_cart_edit_quantity_reduce(Product product){ // 减少数量
    cout << "Enter the quantity to reduce: ";
    int quantity;
    cin >> quantity;
    if(servor.cart_reduce(product, quantity) == true){ // 减少数量
        cout << "Succeed!" << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

bool EShop::user_cart_edit_delete(int index){ // 删除商品
    if(servor.cart_delete(index) == true){ // 删除商品
        cout << "Succeed!" << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

//用户函数-购物车-优惠
bool EShop::user_cart_preferential(){ // 优惠
    cout << "Get a coupon or a redemption code? (C/R)" << endl;
    string jud_cr;
    cin >> jud_cr;
    if(jud_cr == "C" || jud_cr == "c"){ // 优惠券
        return user_cart_preferential_coupon();
    } else if(jud_cr == "R" || jud_cr == "r"){ // 兑换码
        return user_cart_preferential_code();
    } else{
        cout << "Invalid input!" << endl;
        return false;
    }
}

bool EShop::user_cart_preferential_coupon(){ // 优惠券
    if(servor.user_ask_for_coupon() == true){ // 优惠券
        cout << "Succeed! Discount: " << servor.get_current_user()->get_cart().get_coupon() << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

bool EShop::user_cart_preferential_code(){ // 兑换码
    string code = servor.user_ask_for_code();
    if(code != "NULL"){ // 兑换码
        cout << "Succeed! Your redemption code is '" << code << "', ";
        cout << "discount: " << servor.code_get_discount(code) << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

//用户函数-购物车-结算
bool EShop::user_cart_checkout(){ // 结算
    vector<int> indexs;
    cout << "Enter the indexs of the products to check out (separated by space, end by '-1'): ";
    int index;
    while(cin >> index){ // 统计结算商品的下标
        if(index == -1){
            break;
        }
        if(index < 0 || index >= servor.get_current_user()->get_cart().get_products().size()){ // 判断下标是否合法
            cout << "Invalid index!" << endl;
            return false;
        } else{
            indexs.push_back(index);
        }
    }
    if(servor.cart_payment(indexs, servor.cart_check(indexs)) == true){ // 结算
        cout << "Succeed!" << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

//用户函数-购物车-历史
bool EShop::user_cart_show_history(){ // 显示购物历史
    if(servor.cart_show_history() == false){ // 显示购物历史
        return false;
    }
    cout << endl;
    cout << "Analysis? (Y/N)" << endl;
    string jud_a;
    cin >> jud_a;
    if(jud_a == "Y" || jud_a == "y"){ // 询问是否分析
        return user_cart_show_history_analysis();
    }
    return true;
}

bool EShop::user_cart_show_history_analysis(){ // 显示购物历史分析
    cout << "Enter the start timestamp of the analysis: ";
    long long start_time;
    cin >> start_time;
    cout << "Enter the end timestamp of the analysis: ";
    long long end_time;
    cin >> end_time;
    welcome();
    cout << "Analyze the purchase history from " << start_time << " to " << end_time << endl << endl;
    if(servor.cart_analysis(start_time, end_time) == true){ // 分析购物历史
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

//管理员函数
bool EShop::root(){ // 管理员
    welcome();
    activity();
    cout << "Products: " << endl << endl;
    servor.product_show();
    cout << endl;
    cout << "Please select a function: " << endl;
    cout << "1. Logout" << endl;
    cout << "2. Edit products" << endl;
    cout << "3. Edit users" << endl;
    cout << "4. Edit preferential" << endl;
    cout << "5. Save changes" << endl;
    cout << "0. Exit" << endl;
    cout << endl;
    char jud;
    cin >> jud;
    cout << endl;
    switch(jud){
        case '0':{ // 退出
            welcome();
            cout << "Goodbye!" << endl << endl;
            pause();
            return servor.servor_exit();
        }
        case '1':{ // 登出
            welcome();
            root_logout();
            break;
        }
        case '2':{ // 管理商品
            while(root_products());
            break;
        }
        case '3':{ // 管理用户
            while(root_users());
            break;
        }
        case '4':{ // 管理优惠
            while(root_preferential());
            break;
        }
        case '5':{ // 保存更改
            welcome();
            root_save();
            break;
        }
        default:{
            cout << "Invalid choice" << endl;
            break;
        }
    }
    pause();
    return true;
}

//管理员函数-账户
bool EShop::root_logout(){ // 管理员登出
    if(servor.root_logout() == true){ // 管理员登出
        cout << "Logout successfully!" << endl;
        return true;
    } else{
        cout << "Logout failed!" << endl;
        return false;
    }
}

//管理员函数-商品
bool EShop::root_products(){ // 管理商品
    welcome();
    cout << "Products: " << endl << endl;
    servor.product_show();
    cout << endl;
    cout << "Please select a function: " << endl;
    cout << "1. Add a product" << endl;
    cout << "2. Search products" << endl;
    cout << "3. Edit a product" << endl;
    cout << "0. Back" << endl;
    cout << endl;
    char jud_rp;
    cin >> jud_rp;
    cout << endl;
    switch(jud_rp){
        case '0':{ // 返回
            welcome();
            return false;
        }
        case '1':{ // 添加商品
            welcome();
            root_products_add();
            break;
        }
        case '2':{ // 搜索商品
            welcome();
            if(product_search() == false){ // 判断是否搜索到商品
                break;
            }
            cout << "Edit product? (Y/N)" << endl;
            string jud_ep;
            cin >> jud_ep;
            if(jud_ep == "N" || jud_ep == "n"){ // 询问是否编辑商品
                break;
            }
        }
        case '3':{ // 编辑商品
            root_products_edit();
            break;
        }
        default:{
            cout << "Invalid choice" << endl;
            break;
        }
    }
    pause();
    return true;
}

bool EShop::root_products_add(){ // 添加商品
    cout << "Enter the product attribute to add (name type price quantity): ";
    string name;
    string type;
    double price;
    int quantity;
    cin >> name >> type >> price >> quantity;
    if(servor.root_product_add(name, type, price, quantity) == true){ // 添加商品
        cout << "Succeed!" << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

bool EShop::root_products_edit(){ // 编辑商品
    cout << "Enter the order number of the product to edit: ";
    int index;
    cin >> index;
    if(servor.product_get(index).get_name() == "NULL"){ // 判断商品是否存在
        cout << "Product not found!" << endl;
        return false;
    }
    cout << "Set attribute or delete? (S/D)" << endl;
    string jud_sd;
    cin >> jud_sd;
    if(jud_sd == "S" || jud_sd == "s"){ // 设置商品
        return root_products_edit_set(index);
    } else if(jud_sd == "D" || jud_sd == "d"){ // 删除商品
        return root_products_edit_delete(index);
    } else{
        cout << "Invalid input!" << endl;
        return false;
    }
}

bool EShop::root_products_edit_set(int index){ // 设置商品
    Product new_product = servor.product_get(index);
    cout << "Set name? (Y/N)" << endl;
    string jud_n;
    cin >> jud_n;
    bool jud_nb = false;
    if(jud_n == "Y" || jud_n == "y"){ // 设置商品名
        jud_nb = true;
        cout << "Enter the new name: ";
        string name;
        cin >> name;
        new_product.set_name(name);
    }
    cout << "Set type? (Y/N)" << endl;
    string jud_t;
    cin >> jud_t;
    bool jud_tb = false;
    if(jud_t == "Y" || jud_t == "y"){ // 设置商品类型
        jud_tb = true;
        cout << "Enter the new type: ";
        string type;
        cin >> type;
        new_product.set_type(type);
    }
    cout << "Set price? (Y/N)" << endl;
    string jud_p;
    cin >> jud_p;
    bool jud_pb = false;
    if(jud_p == "Y" || jud_p == "y"){ // 设置商品价格
        jud_pb = true;
        cout << "Enter the new price: ";
        double price;
        cin >> price;
        new_product.set_price(price);
    }
    cout << "Set quantity? (Y/N)" << endl;
    string jud_q;
    cin >> jud_q;
    bool jud_qb = false;
    if(jud_q == "Y" || jud_q == "y"){ // 设置商品数量
        jud_qb = true;
        cout << "Enter the new quantity: ";
        int quantity;
        cin >> quantity;
        new_product.set_num(quantity);
    }
    if(!jud_nb && !jud_tb && !jud_pb && !jud_qb){ // 判断是否有修改
        cout << "No change!" << endl;
        return false;
    }
    if(servor.root_product_set(index, new_product) == true){ // 设置商品
        cout << "Succeed!" << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

bool EShop::root_products_edit_delete(int index){ // 删除商品
    if(servor.root_product_delete(index) == true){ // 删除商品
        cout << "Succeed!" << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

//管理员函数-用户
bool EShop::root_users(){ // 管理用户
    welcome();
    cout << "Users: " << endl << endl;
    servor.root_user_show();
    cout << endl;
    cout << "Please select a function: " << endl;
    cout << "1. Add a user" << endl;
    cout << "2. Search users" << endl;
    cout << "3. Edit a user" << endl;
    cout << "0. Back" << endl;
    cout << endl;
    char jud_ru;
    cin >> jud_ru;
    cout << endl;
    switch(jud_ru){
        case '0':{ // 返回
            welcome();
            return false;
        }
        case '1':{ // 添加用户
            welcome();
            root_users_add();
            break;
        }
        case '2':{ // 搜索用户
            welcome();
            if(root_users_search() == false){ // 判断是否搜索到用户
                break;
            }
            cout << "Edit user? (Y/N)" << endl;
            string jud_eu;
            cin >> jud_eu;
            if(jud_eu == "N" || jud_eu == "n"){ // 询问是否编辑用户
                break;
            }
        }
        case '3':{ // 编辑用户
            root_users_edit();
            break;
        }
        default:{
            cout << "Invalid choice" << endl;
            break;
        }
    }
    pause();
    return true;
}

bool EShop::root_users_add(){ // 添加用户
    cout << "Enter the user attribute to add (name password money): ";
    string name, password;
    double money;
    cin >> name >> password >> money;
    if(servor.root_user_add(name, password, money) == true){ // 添加用户
        cout << "Succeed!" << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

bool EShop::root_users_search(){ // 搜索用户
    cout << "Enter the user name to search: ";
    string name;
    cin >> name;
    if(servor.root_user_search(name) == false){ // 搜索用户
        cout << "User not found!" << endl;
        return false;
    } else{
        return true;
    }
    
}

bool EShop::root_users_edit(){ // 编辑用户
    cout << "Enter order number of the user to edit: ";
    int index;
    cin >> index;
    if(servor.root_user_get(index).get_name() == "NULL"){ // 判断用户是否存在
        cout << "User not found!" << endl;
        return false;
    }
    cout << "Set attribute or delete? (S/D)" << endl;
    string jud_sd;
    cin >> jud_sd;
    if(jud_sd == "S" || jud_sd == "s"){ // 设置用户
        return root_users_edit_set(index);
    } else if(jud_sd == "D" || jud_sd == "d"){ // 删除用户
        return root_users_edit_delete(index);
    } else{
        cout << "Invalid input!" << endl;
        return false;
    }
}

bool EShop::root_users_edit_set(int index){ // 设置用户
    User new_user = servor.root_user_get(index);
    cout << "Set name? (Y/N)" << endl;
    string jud_n;
    cin >> jud_n;
    bool jud_nb = false;
    if(jud_n == "Y" || jud_n == "y"){ // 设置用户名
        jud_nb = true;
        cout << "Enter the new name: ";
        string name;
        cin >> name;
        new_user.set_name(name);
    }
    cout << "Set password? (Y/N)" << endl;
    string jud_p;
    cin >> jud_p;
    bool jud_pb = false;
    if(jud_p == "Y" || jud_p == "y"){ // 设置密码
        jud_pb = true;
        cout << "Enter the new password: ";
        string password;
        cin >> password;
        new_user.set_password(password);
    }
    cout << "Set money? (Y/N)" << endl;
    string jud_m;
    cin >> jud_m;
    bool jud_mb = false;
    if(jud_m == "Y" || jud_m == "y"){ // 设置余额
        jud_mb = true;
        cout << "Enter the new money: ";
        double money;
        cin >> money;
        new_user.set_money(money);
    }
    cout << "Set coupon? (Y/N)" << endl;
    string jud_c;
    cin >> jud_c;
    bool jud_cb = false;
    if(jud_c == "Y" || jud_c == "y"){ // 设置优惠券
        jud_cb = true;
        cout << "Enter the new coupon: ";
        double coupon;
        cin >> coupon;
        Cart cart = new_user.get_cart();
        cart.set_coupon(coupon);
        new_user.set_cart(cart);
    }
    cout << "Set code flag? (Y/N)" << endl;
    string jud_f;
    cin >> jud_f;
    bool jud_fb = false;
    if(jud_f == "Y" || jud_f == "y"){ // 设置优惠券
        jud_fb = true;
        cout << "Enter the new code flag: ";
        int code_flag;
        cin >> code_flag;
        Cart cart = new_user.get_cart();
        cart.set_code_flag(code_flag == 1 ? true : false);
        new_user.set_cart(cart);
    }
    if(!jud_nb && !jud_pb && !jud_mb && !jud_cb && !jud_fb){ // 判断是否有修改
        cout << "No change!" << endl;
        return false;
    }
    if(servor.root_user_set(index, new_user) == true){ // 设置用户
        cout << "Succeed!" << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

bool EShop::root_users_edit_delete(int index){ // 删除用户
    if(servor.root_user_delete(index) == true){ // 删除用户
        cout << "Succeed!" << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

//管理员函数-优惠
bool EShop::root_preferential(){ // 管理优惠
    welcome();
    cout << "Please select a function: " << endl;
    cout << "1. Set coupon" << endl;
    cout << "2. Set activity" << endl;
    cout << "3. Set redemption code" << endl;
    cout << "0. Back" << endl;
    cout << endl;
    char jud_rc;
    cin >> jud_rc;
    cout << endl;
    switch(jud_rc){
        case '0':{ // 返回
            welcome();
            return false;
        }
        case '1':{ // 设置优惠券
            root_preferential_coupon();
            break;
        }
        case '2':{ // 设置活动
            root_preferential_activity();
            break;
        }
        case '3':{ // 设置兑换码
            while(root_preferential_code());
            break;
        }
        default:{
            cout << "Invalid choice" << endl;
            break;
        }
    }
    pause();
    return true;
}

bool EShop::root_preferential_coupon(){ // 设置优惠券
    cout << "Enter the discount range of the coupon (min max): ";
    double min, max;
    cin >> min >> max;
    if(servor.root_coupon_set(min, max) == true){ // 设置优惠券
        cout << "Succeed!" << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

bool EShop::root_preferential_activity(){ // 设置活动
    cout << "Enter the discount of the activity: ";
    double discount;
    cin >> discount;
    if(servor.root_activity_set(discount) == true){ // 设置活动
        cout << "Succeed!" << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

bool EShop::root_preferential_code(){ // 设置兑换码
    welcome();
    cout << "Redemption codes: " << endl << endl;
    servor.root_code_show();
    cout << endl;
    cout << "Please select a function: " << endl;
    cout << "1. Add a redemption code" << endl;
    cout << "2. Search redemption codes" << endl;
    cout << "3. Delete a redemption code" << endl;
    cout << "0. Back" << endl;
    cout << endl;
    char jud_rc;
    cin >> jud_rc;
    cout << endl;
    switch(jud_rc){
        case '0':{ // 返回
            welcome();
            return false;
        }
        case '1':{ // 添加兑换码
            welcome();
            root_preferential_code_add();
            break;
        }
        case '2':{ // 搜索兑换码
            welcome();
            if(root_preferential_code_search() == false){ // 判断是否搜索到兑换码
                break;
            }
            cout << "Delete redemption code? (Y/N)" << endl;
            string jud_dc;
            cin >> jud_dc;
            if(jud_dc == "N" || jud_dc == "n"){ // 询问是否删除兑换码
                break;
            }
        }
        case '3':{ // 删除兑换码
            root_preferential_code_delete();
            break;
        }
        default:{
            cout << "Invalid choice" << endl;
            break;
        }
    }
    pause();
    return true;
}

bool EShop::root_preferential_code_add(){ // 添加兑换码
    cout << "Enter the discount of the code: ";
    double discount;
    cin >> discount;
    if(servor.root_code_add(discount) == true){ // 添加兑换码
        cout << "Succeed!" << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

bool EShop::root_preferential_code_search(){ // 搜索兑换码
    cout << "Enter the redemption code to search: ";
    string code;
    cin >> code;
    if(servor.code_search(code) == -1){ // 搜索兑换码
        cout << "Redemption code not found!" << endl;
        return false;
    } else{
        cout << "Redemption code found!" << endl;
        cout << endl;
        return true;
    }
}

bool EShop::root_preferential_code_delete(){ // 删除兑换码
    cout << "Enter the order number of redemption code to delete: ";
    int index;
    cin >> index;
    if(index < 0 || index >= servor.root_codes_get().size()){ // 判断兑换码是否存在
        cout << "Redemption code not found!" << endl;
        return false;
    }
    if(servor.root_code_delete(index) == true){ // 删除兑换码
        cout << "Succeed!" << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

//管理员函数-保存
bool EShop::root_save(){ // 保存更改
    if(servor.servor_save() == true){ // 保存更改
        cout << "Succeed!" << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

