#include<bits/stdc++.h>
#include "es_servor.cpp"

using namespace std;

class EShop{
public:
    EShop();
    static void e_shop(){
        EShop();
    }
    //通用函数
    bool functions();
    void welcome();
    void pause();
    //部分通用函数
    bool activity();
    bool product_search();
    //访客函数
    bool visitor();
    //访客函数-账户
    bool visitor_account();
    bool visitor_account_signup();
    bool visitor_account_user_login();
    bool visitor_account_root_login();
    //用户函数
    bool user();
    //用户函数-账户
    bool user_account();
    bool user_account_edit();
    bool user_account_edit_recharge();
    bool user_account_edit_eligibility();
    bool user_account_edit_password();
    void user_account_information();
    bool user_account_logout();
    //用户函数-购物车
    bool user_cart();
    bool user_cart_add();
    bool user_cart_search_add(string name);
    //用户函数-购物车-编辑
    bool user_cart_edit();
    bool user_cart_edit_quantity(Product product_in_servor, Product product);
    bool user_cart_edit_quantity_add(Product product_in_servor);
    bool user_cart_edit_quantity_reduce(Product product);
    bool user_cart_edit_delete(int index);
    //用户函数-购物车-优惠
    bool user_cart_preferential();
    bool user_cart_preferential_coupon();
    bool user_cart_preferential_code();
    //用户函数-购物车-结算
    bool user_cart_checkout();
    //用户函数-购物车-历史
    bool user_cart_show_history();
    bool user_cart_show_history_analysis();
    //管理员函数
    bool root();
    //管理员函数-账户
    bool root_logout();
    //管理员函数-商品
    bool root_products();
    bool root_products_add();
    bool root_products_edit();
    bool root_products_edit_set(int index);
    bool root_products_edit_delete(int index);
    //管理员函数-用户
    bool root_users();
    bool root_users_add();
    bool root_users_search();
    bool root_users_edit();
    bool root_users_edit_set(int index);
    bool root_users_edit_delete(int index);
    //管理员函数-优惠
    bool root_preferential();
    bool root_preferential_coupon();
    bool root_preferential_activity();
    bool root_preferential_code();
    bool root_preferential_code_add();
    bool root_preferential_code_search();
    bool root_preferential_code_delete();
    //管理员函数-保存
    bool root_save();
private:
    Servor servor;
};

EShop::EShop(){
    servor = Servor();
    while(functions());
}

//通用函数
bool EShop::functions(){
    if(servor.get_current_user() == NULL){
        return visitor();
    } else{
        if(servor.is_root() == false){
            return user();
        } else{
            return root();
        }
    }
}

void EShop::welcome(){
    system("cls");
    cout << "Welcome to the e-shop system!" << endl << endl;
    cout << "Cuttent user: ";
    cout << (servor.get_current_user() == NULL ? "Not Logged In" : servor.get_current_user()->get_name());
    cout << endl << endl;
}

void EShop::pause(){
    cout << endl;
    system("pause");
}

//部分通用函数
bool EShop::activity(){
    if(servor.activity_get() != 1){
        cout << "Activity: " << servor.activity_get() << endl << endl ;
        return true;
    } else{
        cout << "Activity: " << "No" << endl << endl;
        return false;
    }
}

bool EShop::product_search(){
    cout << "Enter the product name to search: ";
    string name;
    cin >> name;
    if(servor.product_search(name) == false){
        cout << "Product not found!" << endl;
        return false;
    }
    cout << endl;
    if(servor.is_user() == true){
        cout << "Add to cart? (Y/N)" << endl;
        string jud_ac;
        cin >> jud_ac;
        if(jud_ac == "Y" || jud_ac == "y"){
            while(user_cart_search_add(name));
        }
    }
    return true;
}

//访客函数
bool EShop::visitor(){
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
        case '0':{
            welcome();
            cout << "Goodbye!" << endl << endl;
            pause();
            return servor.servor_exit();
        }
        case '1':{
            welcome();
            visitor_account();
            break;
        }
        case '2':{
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
bool EShop::visitor_account(){
    cout << "Login or Signup? (L/S)" << endl;
    string jud_ls;
    cin >> jud_ls;
    if(jud_ls == "L" || jud_ls == "l"){
        cout << "User or Root? (U/R)" << endl;
        string jud_ur;
        cin >> jud_ur;
        if(jud_ur == "U" || jud_ur == "u"){
            return visitor_account_user_login();
        } else if(jud_ur == "R" || jud_ur == "r"){
            return visitor_account_root_login();
        } else{
            cout << "Invalid input!" << endl;
            return false;
        }
    } else if(jud_ls == "S" || jud_ls == "s"){
        return visitor_account_signup();
    } else{
        cout << "Invalid input!" << endl;
        return false;
    }
}

bool EShop::visitor_account_signup(){
    cout << "Please enter your username and password:" << endl;
    string name, password;
    cin >> name >> password;
    if(servor.user_signup(name, password)){
        cout << "Signup successfully!" << endl;
        return true;
    } else{
        cout << "Signup failed!" << endl;
        return false;
    }
}

bool EShop::visitor_account_user_login(){
    cout << "Please enter your username and password:" << endl;
    string name, password;
    cin >> name >> password;
    if(servor.user_login(name, password)){
        cout << "Login successfully!" << endl;
        return true;
    } else{
        cout << "Login failed!" << endl;
        return false;
    }
}

bool EShop::visitor_account_root_login(){
    cout << "Please enter your username and password:" << endl;
    string name, password;
    cin >> name >> password;
    if(servor.root_login(name, password)){
        cout << "Login successfully!" << endl;
        return true;
    } else{
        cout << "Login failed!" << endl;
        return false;
    }
}

//用户函数
bool EShop::user(){
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
        case '0':{
            welcome();
            cout << "Goodbye!" << endl << endl;
            pause();
            return servor.servor_exit();
        }
        case '1':{
            while(user_account());
            break;
        }
        case '2':{
            welcome();
            product_search();
            break;
        }
        case '3':{
            user_cart_add();
            break;
        }
        case '4':{
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
bool EShop::user_account(){
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
        case '0':{
            welcome();
            return false;
        }
        case '1':{
            while(user_account_edit());
            break;
        }
        case '2':{
            welcome();
            user_account_information();
            break;
        }
        case '3':{
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

bool EShop::user_account_edit(){
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
        case '0':{
            welcome();
            return false;
        }
        case '1':{
            user_account_edit_recharge();
            break;
        }
        case '2':{
            user_account_edit_eligibility();
            break;
        }
        case '3':{
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

bool EShop::user_account_edit_recharge(){
    cout << "Enter the amount to recharge: ";
    double money;
    cin >> money;
    if(servor.user_recharge(money) == true){
        cout << "Succeed!" << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

bool EShop::user_account_edit_eligibility(){
    if(servor.code_eligibility_check() == true){
        cout << "You can get the eligibility of appling for redemption code." << endl;
        if(servor.get_current_user()->get_cart().get_coupon() != 1){
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
        if(servor.code_eligibility_initialize() == true){
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

bool EShop::user_account_edit_password(){
    cout << "Enter the original password and new password (OP NP): " << endl;
    string original_password;
    string password;
    cin >> original_password >> password;
    if(servor.user_change_password(original_password, password) == true){
        cout << "Succeed!" << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

void EShop::user_account_information(){
    servor.get_current_user()->info();
}

bool EShop::user_account_logout(){
    if(servor.user_logout() == true){
        cout << "Logout successfully!" << endl;
        return true;
    } else{
        cout << "Logout failed!" << endl;
        return false;
    }
}

//用户函数-购物车
bool EShop::user_cart(){
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
        case '0':{
            welcome();
            return false;
        }
        case '1':{
            user_cart_edit();
            break;
        }
        case '2':{
            welcome();
            user_cart_preferential();
            break;
        }
        case '3':{
            user_cart_checkout();
            break;
        }
        case '4':{
            welcome();
            user_cart_show_history();
            break;
        }
        case '5':{
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

bool EShop::user_cart_add(){
    cout << "Enter the order number of the product to add: ";
    int index;
    cin >> index;
    Product product = servor.product_get(index);
    if(product.get_name() == "NULL"){
        cout << "Product not found!" << endl;
        return false;
    } else{
        cout << "Enter the quantity to add: ";
        int quantity;
        cin >> quantity;
        if(servor.cart_add(product, quantity) == true){
            cout << "Succeed!" << endl;
            return true;
        } else{
            cout << "Failed!" << endl;
            return false;
        }
    }
}

bool EShop::user_cart_search_add(string name){
    welcome();
    activity();
    servor.product_search(name);
    user_cart_add();
    cout << endl;
    cout << "Continue to add? (Y/N)" << endl;
    string jud_ca;
    cin >> jud_ca;
    if(jud_ca == "Y" || jud_ca == "y"){
        return true;
    } else{
        return false;
    }
}

//用户函数-购物车-编辑
bool EShop::user_cart_edit(){
    cout << "Enter the order number of the product to edit: ";
    int index;
    cin >> index;
    Product product = servor.get_current_user()->get_cart().get_product(index);
    Product product_in_servor = servor.product_get(product.get_name());
    if(product.get_name() == "NULL"){
        cout << "Product not found!" << endl;
        return false;
    }
    if(product_in_servor.get_num() < product.get_num()){
        if(product_in_servor.get_num() == 0){
            cout << "Product out of stock!" << endl;
        } else{
            cout << "Not enough products in the servor!" << endl;
        }
        return false;
    }
    cout << "Set quantity or delete? (S/D)" << endl;
    string jud_sd;
    cin >> jud_sd;
    if(jud_sd == "S" || jud_sd == "s"){
        return user_cart_edit_quantity(product_in_servor, product);
    } else if(jud_sd == "D" || jud_sd == "d"){
        return user_cart_edit_delete(index);
    } else{
        cout << "Invalid input!" << endl;
        return false;
    }
}

bool EShop::user_cart_edit_quantity(Product product_in_servor, Product product){
    cout << "Add or reduce? (A/R)" << endl;
    string jud_ar;
    cin >> jud_ar;
    if(jud_ar == "A" || jud_ar == "a"){
        return user_cart_edit_quantity_add(product_in_servor);
    } else if(jud_ar == "R" || jud_ar == "r"){
        return user_cart_edit_quantity_reduce(product);
    } else{
        cout << "Invalid input!" << endl;
        return false;
    }
}

bool EShop::user_cart_edit_quantity_add(Product product_in_servor){
    cout << "Enter the quantity to add: ";
    int quantity;
    cin >> quantity;
    if(servor.cart_add(product_in_servor, quantity) == true){
        cout << "Succeed!" << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

bool EShop::user_cart_edit_quantity_reduce(Product product){
    cout << "Enter the quantity to reduce: ";
    int quantity;
    cin >> quantity;
    if(servor.cart_reduce(product, quantity) == true){
        cout << "Succeed!" << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

bool EShop::user_cart_edit_delete(int index){
    if(servor.cart_delete(index) == true){
        cout << "Succeed!" << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

//用户函数-购物车-优惠
bool EShop::user_cart_preferential(){
    cout << "Get a coupon or a redemption code? (C/R)" << endl;
    string jud_cr;
    cin >> jud_cr;
    if(jud_cr == "C" || jud_cr == "c"){
        return user_cart_preferential_coupon();
    } else if(jud_cr == "R" || jud_cr == "r"){
        return user_cart_preferential_code();
    } else{
        cout << "Invalid input!" << endl;
        return false;
    }
}

bool EShop::user_cart_preferential_coupon(){
    if(servor.user_ask_for_coupon() == true){
        cout << "Succeed! Discount: " << servor.get_current_user()->get_cart().get_coupon() << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

bool EShop::user_cart_preferential_code(){
    string code = servor.user_ask_for_code();
    if(code != "NULL"){
        cout << "Succeed! Your redemption code is '" << code << "', ";
        cout << "discount: " << servor.code_get_discount(code) << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

//用户函数-购物车-结算
bool EShop::user_cart_checkout(){
    vector<int> indexs;
    cout << "Enter the indexs of the products to check out (separated by space, end by '-1'): ";
    int index;
    while(cin >> index){
        if(index == -1){
            break;
        }
        if(index < 0 || index >= servor.get_current_user()->get_cart().get_products().size()){
            cout << "Invalid index!" << endl;
            return false;
        } else{
            indexs.push_back(index);
        }
    }
    if(servor.cart_payment(indexs, servor.cart_check(indexs)) == true){
        cout << "Succeed!" << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

//用户函数-购物车-历史
bool EShop::user_cart_show_history(){
    if(servor.cart_show_history() == false){
        return false;
    }
    cout << endl;
    cout << "Analysis? (Y/N)" << endl;
    string jud_a;
    cin >> jud_a;
    if(jud_a == "Y" || jud_a == "y"){
        return user_cart_show_history_analysis();
    }
    return true;
}

bool EShop::user_cart_show_history_analysis(){
    cout << "Enter the start timestamp of the analysis: ";
    long long start_time;
    cin >> start_time;
    cout << "Enter the end timestamp of the analysis: ";
    long long end_time;
    cin >> end_time;
    welcome();
    cout << "Analyze the purchase history from " << start_time << " to " << end_time << endl << endl;
    if(servor.cart_analysis(start_time, end_time) == true){
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

//管理员函数
bool EShop::root(){
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
        case '0':{
            welcome();
            cout << "Goodbye!" << endl << endl;
            pause();
            return servor.servor_exit();
        }
        case '1':{
            welcome();
            root_logout();
            break;
        }
        case '2':{
            while(root_products());
            break;
        }
        case '3':{
            while(root_users());
            break;
        }
        case '4':{
            while(root_preferential());
            break;
        }
        case '5':{
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
bool EShop::root_logout(){
    if(servor.root_logout() == true){
        cout << "Logout successfully!" << endl;
        return true;
    } else{
        cout << "Logout failed!" << endl;
        return false;
    }
}

//管理员函数-商品
bool EShop::root_products(){
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
        case '0':{
            welcome();
            return false;
        }
        case '1':{
            welcome();
            root_products_add();
            break;
        }
        case '2':{
            welcome();
            if(product_search() == false){
                break;
            }
            cout << "Edit product? (Y/N)" << endl;
            string jud_ep;
            cin >> jud_ep;
            if(jud_ep == "N" || jud_ep == "n"){
                break;
            }
        }
        case '3':{
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

bool EShop::root_products_add(){
    cout << "Enter the product attribute to add (name type price quantity): ";
    string name;
    string type;
    double price;
    int quantity;
    cin >> name >> type >> price >> quantity;
    if(servor.root_product_add(name, type, price, quantity) == true){
        cout << "Succeed!" << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

bool EShop::root_products_edit(){
    cout << "Enter the order number of the product to edit: ";
    int index;
    cin >> index;
    if(servor.product_get(index).get_name() == "NULL"){
        cout << "Product not found!" << endl;
        return false;
    }
    cout << "Set attribute or delete? (S/D)" << endl;
    string jud_sd;
    cin >> jud_sd;
    if(jud_sd == "S" || jud_sd == "s"){
        return root_products_edit_set(index);
    } else if(jud_sd == "D" || jud_sd == "d"){
        return root_products_edit_delete(index);
    } else{
        cout << "Invalid input!" << endl;
        return false;
    }
}

bool EShop::root_products_edit_set(int index){
    Product new_product = servor.product_get(index);
    cout << "Set name? (Y/N)" << endl;
    string jud_n;
    cin >> jud_n;
    bool jud_nb = false;
    if(jud_n == "Y" || jud_n == "y"){
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
    if(jud_t == "Y" || jud_t == "y"){
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
    if(jud_p == "Y" || jud_p == "y"){
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
    if(jud_q == "Y" || jud_q == "y"){
        jud_qb = true;
        cout << "Enter the new quantity: ";
        int quantity;
        cin >> quantity;
        new_product.set_num(quantity);
    }
    if(!jud_nb && !jud_tb && !jud_pb && !jud_qb){
        cout << "No change!" << endl;
        return false;
    }
    if(servor.root_product_set(index, new_product) == true){
        cout << "Succeed!" << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

bool EShop::root_products_edit_delete(int index){
    if(servor.root_product_delete(index) == true){
        cout << "Succeed!" << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

//管理员函数-用户
bool EShop::root_users(){
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
        case '0':{
            welcome();
            return false;
        }
        case '1':{
            welcome();
            root_users_add();
            break;
        }
        case '2':{
            welcome();
            if(root_users_search() == false){
                break;
            }
            cout << "Edit user? (Y/N)" << endl;
            string jud_eu;
            cin >> jud_eu;
            if(jud_eu == "N" || jud_eu == "n"){
                break;
            }
        }
        case '3':{
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

bool EShop::root_users_add(){
    cout << "Enter the user attribute to add (name password money): ";
    string name, password;
    double money;
    cin >> name >> password >> money;
    if(servor.root_user_add(name, password, money) == true){
        cout << "Succeed!" << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

bool EShop::root_users_search(){
    cout << "Enter the user name to search: ";
    string name;
    cin >> name;
    if(servor.root_user_search(name) == false){
        cout << "User not found!" << endl;
        return false;
    } else{
        return true;
    }
    
}

bool EShop::root_users_edit(){
    cout << "Enter order number of the user to edit: ";
    int index;
    cin >> index;
    if(servor.root_user_get(index).get_name() == "NULL"){
        cout << "User not found!" << endl;
        return false;
    }
    cout << "Set attribute or delete? (S/D)" << endl;
    string jud_sd;
    cin >> jud_sd;
    if(jud_sd == "S" || jud_sd == "s"){
        return root_users_edit_set(index);
    } else if(jud_sd == "D" || jud_sd == "d"){
        return root_users_edit_delete(index);
    } else{
        cout << "Invalid input!" << endl;
        return false;
    }
}

bool EShop::root_users_edit_set(int index){
    User new_user = servor.root_user_get(index);
    cout << "Set name? (Y/N)" << endl;
    string jud_n;
    cin >> jud_n;
    bool jud_nb = false;
    if(jud_n == "Y" || jud_n == "y"){
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
    if(jud_p == "Y" || jud_p == "y"){
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
    if(jud_m == "Y" || jud_m == "y"){
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
    if(jud_c == "Y" || jud_c == "y"){
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
    if(jud_f == "Y" || jud_f == "y"){
        jud_fb = true;
        cout << "Enter the new code flag: ";
        int code_flag;
        cin >> code_flag;
        Cart cart = new_user.get_cart();
        cart.set_code_flag(code_flag == 1 ? true : false);
        new_user.set_cart(cart);
    }
    if(!jud_nb && !jud_pb && !jud_mb && !jud_cb && !jud_fb){
        cout << "No change!" << endl;
        return false;
    }
    if(servor.root_user_set(index, new_user) == true){
        cout << "Succeed!" << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

bool EShop::root_users_edit_delete(int index){
    if(servor.root_user_delete(index) == true){
        cout << "Succeed!" << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

//管理员函数-优惠
bool EShop::root_preferential(){
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
        case '0':{
            welcome();
            return false;
        }
        case '1':{
            root_preferential_coupon();
            break;
        }
        case '2':{
            root_preferential_activity();
            break;
        }
        case '3':{
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

bool EShop::root_preferential_coupon(){
    cout << "Enter the discount range of the coupon (min max): ";
    double min, max;
    cin >> min >> max;
    if(servor.root_coupon_set(min, max) == true){
        cout << "Succeed!" << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

bool EShop::root_preferential_activity(){
    cout << "Enter the discount of the activity: ";
    double discount;
    cin >> discount;
    if(servor.root_activity_set(discount) == true){
        cout << "Succeed!" << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

bool EShop::root_preferential_code(){
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
        case '0':{
            welcome();
            return false;
        }
        case '1':{
            welcome();
            root_preferential_code_add();
            break;
        }
        case '2':{
            welcome();
            if(root_preferential_code_search() == false){
                break;
            }
            cout << "Delete redemption code? (Y/N)" << endl;
            string jud_dc;
            cin >> jud_dc;
            if(jud_dc == "N" || jud_dc == "n"){
                break;
            }
        }
        case '3':{
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

bool EShop::root_preferential_code_add(){
    cout << "Enter the discount of the code: ";
    double discount;
    cin >> discount;
    if(servor.root_code_add(discount) == true){
        cout << "Succeed!" << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

bool EShop::root_preferential_code_search(){
    cout << "Enter the redemption code to search: ";
    string code;
    cin >> code;
    if(servor.code_search(code) == -1){
        cout << "Redemption code not found!" << endl;
        return false;
    } else{
        cout << "Redemption code found!" << endl;
        cout << endl;
        return true;
    }
}

bool EShop::root_preferential_code_delete(){
    cout << "Enter the order number of redemption code to delete: ";
    int index;
    cin >> index;
    if(index < 0 || index >= servor.root_codes_get().size()){
        cout << "Redemption code not found!" << endl;
        return false;
    }
    if(servor.root_code_delete(index) == true){
        cout << "Succeed!" << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

//管理员函数-保存
bool EShop::root_save(){
    if(servor.servor_save() == true){
        cout << "Succeed!" << endl;
        return true;
    } else{
        cout << "Failed!" << endl;
        return false;
    }
}

