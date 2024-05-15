#include <bits/stdc++.h>
#include <unistd.h>
#include "es_root.cpp"
#include "es_code.cpp"

using namespace std;

class Servor{
public:
    Servor();
    bool servor_file_check();
    bool servor_start();
    void servor_start_failed();
    bool servor_save();
    bool servor_exit();
    //数据加载
    bool load_product_data();
    bool load_user_data();
    bool lode_code_data();
    //数据保存
    bool save_product_data();
    bool save_user_data();
    bool save_code_data();
    //用户操作
    User* get_current_user();
    bool is_user();
    bool user_signup(string name, string password);
    bool user_login(string name, string password);
    bool user_logout();
    bool user_change_password(string original_password, string password);
    bool user_recharge(double money);
    bool user_ask_for_coupon();
    string user_ask_for_code();
    //商品操作
    Product product_get(int insex);
    Product product_get(string name);
    vector<Product> products_get();
    bool product_show();
    bool product_search(string name);
    //购物车操作
    bool cart_add(Product product, int num);
    bool cart_reduce(Product product, int num);
    bool cart_delete(Product product);
    bool cart_delete(int index);
    double cart_get_total_price(vector<int> index);
    double cart_check(vector<int> index);
    bool cart_payment(vector<int> index, double total_price);
    bool cart_save_history(vector<int> index, Cart original_cart, double total_price);
    bool cart_show_history();
    bool cart_analysis(vector<int> start_time, vector<int> end_time);
    bool cart_analysis(long long seconds_begin, long long seconds_end);
    //兑换码操作
    string code_create(int n, bool publush_flag);
    string code_create(int n, double discount, bool publush_flag);
    int code_search(string code);
    double code_get_discount(string code);
    bool code_delete(int code_index);
    bool code_eligibility_check();
    bool code_eligibility_initialize();
    //活动操作
    double activity_get();
    //管理员操作
    bool is_root();
    bool root_login(string name, string password);
    bool root_logout();
    bool root_coupon_set(double min, double max);
    bool root_activity_set(double discount);
    //管理员-操作兑换码
    vector<Code> root_codes_get();
    bool root_code_add(double discount);
    void root_code_show();
    bool root_code_delete(int code_index);
    bool root_code_delete(string code);
    //管理员-操作用户
    User root_user_get(int index);
    User root_user_get(string name);
    vector<User> root_users_get();
    bool root_user_add(string name, string password, int money);
    bool root_user_set(int user_index, User new_user);
    bool root_user_set(User origin_user, User new_user);
    bool root_user_delete(int user_index);
    bool root_user_delete(User origin_user);
    bool root_user_show();
    bool root_user_search(string name);
    //管理员-操作商品
    bool root_product_add(string name, string type, double price, int num);
    bool root_product_set(int product_index, Product new_product);
    bool root_product_set(Product origin_product, Product new_product);
    bool root_product_delete(int product_index);
    bool root_product_delete(User origin_product);
private:
    vector<User> users;
    vector<Product> products;
    vector<Code> codes;
    User* current_user;
    double coupon_min;
    double coupon_max;
    double activity_discount;
};

Servor::Servor(){
    if(servor_start() == false){
        servor_start_failed();
    }
    current_user = NULL;
    coupon_min = 0.7;
    coupon_max = 0.9;
    activity_discount = 1;
}

bool Servor::servor_file_check(){
    bool jud = true;
    if(access("data_products.txt", F_OK) != 0){
        cout << "ERROR: 'data_products.txt' not found" << endl;
        jud = false;
    }
    if(access("data_user.txt", F_OK) != 0){
        cout << "ERROR: 'data_user.txt' not found" << endl;
        jud = false;
    }
    if(access("data_codes.txt", F_OK) != 0){
        cout << "ERROR: 'data_codes.txt' not found" << endl;
        jud = false;
    }
    return jud;
}

bool Servor::servor_start(){
    if(!servor_file_check()){
        return false;
    }
    if(load_product_data() && load_user_data() && lode_code_data()){
        return true;
    }
    return false;
}

void Servor::servor_start_failed(){
    cout << endl;
    cout << "Please check the documents and restart the system" << endl;
    cout << endl;
    system("pause");
    exit(0);
}

bool Servor::servor_save(){
    if(save_user_data() && save_product_data() && save_code_data()){
        return true;
    }
    return false;
}

bool Servor::servor_exit(){
    if(servor_save()){
        if(current_user != NULL){
            if(current_user->get_permission() == User::USER){
                user_logout();
            } else{
                root_logout();
            }
        }
        return false;
    }
    return true;
}

bool Servor::load_product_data(){
    ifstream ifs("data_products.txt");
    if(!ifs){
        cout << "ERROR: 'data_products.txt' not found" << endl;
        return false;
    }
    string line;
    while (getline(ifs, line)){
        stringstream ss(line);
        string temp;
        int i = 0;
        string name;
        string type;
        double price;
        int num;
        while (getline(ss, temp,' ')){
            if (i == 0){
                name = temp;
            } else if (i == 1){
                type = temp;
            } else if (i == 2){
                price = stod(temp);
            } else if (i == 3){
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

bool Servor::load_user_data(){
    ifstream ifs("data_user.txt");
    if(!ifs){
        cout << "ERROR: 'data_user.txt' not found" << endl;
        return false;
    }
    string line;
    while (getline(ifs, line)){
		stringstream ss(line);
		string temp;
		int i = 0;
        User user(User::USER);
		Cart cart;
        Product product("NULL", "NULL", 0, 0);
		while (getline(ss, temp,' ')){
			if (i == 0){
				user.set_name(temp);
			} else if (i == 1){
				user.set_password(temp);
			} else if (i == 2){
				user.set_money(stod(temp));
			} else if (i == 3){
                cart.set_coupon(stod(temp));
            } else if (i == 4){
                cart.set_code_flag(stoi(temp) == 1 ? true : false);
            } else {
				if(i % 2 == 1){
                    product = product_get(temp);
				} else{
                    if(product.get_name() != "NULL"){
                        cart.load_cart(product, stoi(temp));
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

bool Servor::lode_code_data(){
    ifstream ifs("data_codes.txt");
    if(!ifs){
        cout << "ERROR: 'data_codes.txt' not found" << endl;
        return false;
    }
    string line;
    while (getline(ifs, line)){
        stringstream ss(line);
        string temp;
        int i = 0;
        string code_string;
        double discount;
        bool pubilsh_flag;
        while (getline(ss, temp,' ')){
            if (i == 0){
                code_string = temp;
            } else if (i == 1){
                discount = stod(temp);
            } else if (i == 2){
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

bool Servor::save_product_data(){
    ofstream ofs("data_products.txt");
    for(auto product : products){
        ofs << product.get_name() << " " << product.get_type() << " " << product.get_price() << " " << product.get_num() << endl;
    }
    ofs.close();
    return true;
}

bool Servor::save_user_data(){
    ofstream ofs("data_user.txt");
    if(is_user()){
        for(auto &user : users){
            if(user.get_name() == current_user->get_name()){
                user = *current_user;
                break;
            }
        }
    }
    for(auto user : users){
        ofs << user.get_name() << " " << user.get_password() << " " << user.get_money() << " ";
        Cart cart = user.get_cart();
        ofs << cart.get_coupon() << " " << cart.get_code_flag() << " ";
        vector<Product> user_products = cart.get_products();
        for(auto user_product : user_products){
            ofs << user_product.get_name() << " " << user_product.get_num() << " ";
        }
        ofs << endl;
    }
    ofs.close();
    return true;
}

bool Servor::save_code_data(){
    ofstream ofs("data_codes.txt");
    for(auto code : codes){
        ofs << code.get_code() << " " << code.get_discount() << " " << code.get_pubilsh_flag() << endl;
    }
    ofs.close();
    return true;

}

User* Servor::get_current_user(){
    return current_user;
}

bool Servor::is_user(){
    if(current_user != NULL && current_user->get_permission() == User::USER){
        return true;
    } else{
        return false;
    }
}

bool Servor::user_signup(string name, string password){
    if (password.length() < 6 || password.length() > 16) {
        cout << "ERROR: Password length should be between 6 and 16 characters" << endl;
        return false;
    }
    regex pattern_password("^[A-Za-z0-9_!?@#.]+$");
    if (!regex_match(password, pattern_password)) {
        cout << "ERROR: illegal password" << endl;
        return false;
    }
    regex pattern_name("^[A-Za-z0-9_]+$");
    if (!regex_match(name, pattern_name)) {
        cout << "ERROR: illegal name" << endl;
        return false;
    }
    for(auto user : users){
        if(user.get_name() == name){
            return false;
        }
    }
    User user(User::USER);
    user.set_name(name);
    user.set_password(password);
    user.set_money(0);
    users.push_back(user);
    if(!save_user_data()){
        return false;
    }
    return true;
}

bool Servor::user_login(string name, string password){
    for(auto user : users){
        if(user.get_name() == name && user.get_password() == password){
            if(current_user != NULL){
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

bool Servor::user_logout(){
    for(auto &user : users){
        if(user.get_name() == current_user->get_name()){
            user = *current_user;
            break;
        }
    }
    delete current_user;
    current_user = NULL;
    if(!save_user_data()){
        return false;
    }
    return true;
}

bool Servor::user_change_password(string original_password, string password){
    if(current_user->get_password() != original_password){
        cout << "ERROR: original password is wrong" << endl;
        return false;
    }
    if (password.length() < 6 || password.length() > 16) {
        cout << "ERROR: Password length should be between 6 and 16 characters" << endl;
        return false;
    }
    regex pattern_password("^[A-Za-z0-9_!?@#.]+$");
    if (!regex_match(password, pattern_password)) {
        cout << "ERROR: illegal password" << endl;
        return false;
    }
    current_user->set_password(password);
    string name = current_user->get_name();
    if(user_logout() && user_login(name, password)){
        return true;
    }
    return false;
}

bool Servor::user_recharge(double money){
    current_user->set_money(current_user->get_money() + money);
    for(auto &user : users){
        if(user.get_name() == current_user->get_name()){
            user = *current_user;
            if(!save_user_data()){
                return false;
            }
            return true;
        }
    }
    return false;

}

bool Servor::user_ask_for_coupon(){
    if(current_user->get_cart().get_coupon() != 1){
        cout << "You have had a coupon!" << endl;
        return false;
    }
    srand(time(0));
    double coupon = (double)(rand() % (int)(coupon_max * 100 - coupon_min * 100) + coupon_min * 100) / 100.0;
    Cart cart = current_user->get_cart();
    if(cart.set_coupon(coupon) == false){
        return false;
    }
    current_user->set_cart(cart);
    return save_user_data();
}

string Servor::user_ask_for_code(){
    if(current_user->get_cart().get_coupon() != 1){
        cout << "You have had a coupon. You can't ask for redemption code" << endl;
        return "NULL";
    }
    if(current_user->get_cart().get_code_flag() == true){
        cout << "You have had a redemption code. You can't ask for redemption code" << endl;
        return "NULL";
    }
    current_user->get_cart().set_code_flag(true);
    for(auto &code : codes){
        if(code.get_pubilsh_flag() == false){
            code.set_pubilsh_flag(true);
            save_code_data();
            Cart cart = current_user->get_cart();
            cart.set_code_flag(true);
            current_user->set_cart(cart);
            save_user_data();
            return code.get_code();
        }
    }
    if(code_create(25, true) != "NULL"){
        Cart cart = current_user->get_cart();
        cart.set_code_flag(true);
        current_user->set_cart(cart);
        save_user_data();
        return codes[codes.size() - 1].get_code();
    } else{
        return "NULL";
    }
}

Product Servor::product_get(int index){
    if(index >= 0 && index < products.size()){
        return products[index];
    } else{
        return Product("NULL", "NULL", 0, 0);
    }
}

Product Servor::product_get(string name){
    for(auto product : products){
        if(product.get_name() == name){
            return product;
        }
    }
    return Product("NULL", "NULL", 0, 0);
}

vector<Product> Servor::products_get(){
    return products;
}

bool Servor::product_show(){
    int i = 0;
    for(auto product : products){
        cout << "Order number: " << i << endl;
        product.info();
        cout << endl;
        i ++;
    }
    if(i == 0){
        cout << "ERROR: product is empty" << endl;
        return false;
    }
    return true;
}

bool Servor::product_search(string name){
    bool jud = 0;
    int i = 0;
    for(auto product : products){
        if(product.get_name() == name || product.get_name().find(name) != string::npos){
            cout << "Order number: " << i << endl;
            product.info();
            cout << endl;
            jud = 1;
        }
        i ++;
    }
    if(jud == 1){
        return true;
        
    } else{
        cout << "ERROR: product not found" << endl;
        return false;
    }
}

bool Servor::cart_add(Product product, int num){
    Cart cart = current_user->get_cart();
    if(cart.add(product, num) == false){
        return false;
    }
    current_user->set_cart(cart);
    return save_user_data();
}

bool Servor::cart_reduce(Product product, int num){
    Cart cart = current_user->get_cart();
    if(cart.reduce(product, num) == false){
        return false;
    }
    current_user->set_cart(cart);
    return save_user_data();
}

bool Servor::cart_delete(Product product){
    Cart cart = current_user->get_cart();
    if(cart.del(product.get_name()) == false){
        return false;
    }
    current_user->set_cart(cart);
    return save_user_data();
}

bool Servor::cart_delete(int index){
    Cart cart = current_user->get_cart();
    if(cart.del(index) == false){
        return false;
    }
    current_user->set_cart(cart);
    return save_user_data();

}

double Servor::cart_get_total_price(vector<int> index){
    double total_price = 0;
    vector<Product> cart_products = current_user->get_cart().get_products();
    for(auto i : index){
        total_price += cart_products[i].get_price() * cart_products[i].get_num();
    }
    return total_price;

}

double Servor::cart_check(vector<int> index){
    vector<Product> cart_products = current_user->get_cart().get_products();
    for(auto i : index){
        Product product = product_get(cart_products[i].get_name());
        if(product.get_name() == "NULL"){
            cout << "ERROR: product not found" << endl;
            return -1;
        }
        if(product.get_num() < cart_products[i].get_num()){
            cout << "ERROR: not enough products" << endl;
            return -1;
        }
    }
    double total_price = cart_get_total_price(index);
    if(activity_discount == 1){
        cout << "Total price: $" << total_price << endl;
    } else{
        total_price *= activity_discount;
        cout << "Total price (with activity discount): $" << total_price << endl;
    }
    return total_price;
}

bool Servor::cart_payment(vector<int> index, double total_price){
    if(index.size() == 0){
        cout << "ERROR: cart is empty" << endl;
        return false;
    }
    int code_index = -1;
    int use_coupon = -1;
    cout << "Use coupon? (Y/N): ";
    char jud_coupon;
    cin >> jud_coupon;
    if(jud_coupon == 'y' || jud_coupon == 'Y'){
        if(current_user->get_cart().get_coupon() < 0 || current_user->get_cart().get_coupon() >= 1){
            cout << "You don't have coupon. Do you want to use redemption code? (Y/N): ";
            char jud_code;
            cin >> jud_code;
            if(jud_code == 'y' || jud_code == 'Y'){
                cout << "Enter your redemption code: ";
                string redemption_code;
                cin >> redemption_code;
                code_index = code_search(redemption_code);
                if(code_index == -1 || codes[code_index].get_discount() == 1){
                    cout << "Redemption code is wrong" << endl;
                } else{
                    cout << "Total price (with redemption code " << (activity_discount == 1 ? "" : "and activity discount");
                    total_price *= codes[code_index].get_discount();
                    cout << " ): $" << total_price  << endl;
                    
                }
            }
        } else{
            cout << "Total price (with coupon " << (activity_discount == 1 ? "" : "and activity discount");
            total_price *= current_user->get_cart().get_coupon();
            cout << " ): $" << total_price << endl;
            use_coupon = 1;
        }
    } else{
        cout << "Use redemption code? (Y/N): ";
        char jud_code;
        cin >> jud_code;
        if(jud_code == 'y' || jud_code == 'Y'){
            cout << "Enter your redemption code: ";
            string redemption_code;
            cin >> redemption_code;
            code_index = code_search(redemption_code);
            if(code_index == -1 || codes[code_index].get_discount() == 1){
                cout << "Redemption code is wrong" << endl;
            } else{
                cout << "Total price (with redemption code " << (activity_discount == 1 ? "" : "and activity discount");
                total_price *= codes[code_index].get_discount();
                cout << " ): $" << total_price  << endl;
                
            }
        }
    }
    cout << "Confirm payment (Y/N): ";
    char jud_confirm;
    cin >> jud_confirm;
    if(jud_confirm == 'N' || jud_confirm == 'n'){
        return false;
    } else{
        if(total_price > current_user->get_money()){
            cout << "ERROR: not enough money" << endl;
            return false;
        }
        if(code_index != -1){
            code_delete(code_index);
            current_user->get_cart().set_code_flag(false);
        } else if(use_coupon != -1){
            current_user->get_cart().set_coupon(1);
        }
        Cart original_cart = current_user->get_cart();
        vector<Product> cart_products = original_cart.get_products();
        vector<string> p_names;
        for(auto i : index){
            for(auto &product : products){
                if(product.get_name() == cart_products[i].get_name()){
                    p_names.push_back(cart_products[i].get_name());
                    product.set_num(product.get_num() - cart_products[i].get_num());
                    break;
                }
            }
        }
        if(!save_product_data()){
            return false;
        }
        current_user->set_money(current_user->get_money() - total_price);
        Cart cart = current_user->get_cart();
        for(auto p_name : p_names){
            cart.del(p_name);
        }
        current_user->set_cart(cart);
        for(auto &user : users){
            if(user.get_name() == current_user->get_name()){
                user = *current_user;
                if(!save_user_data()){
                    return false;
                }
                cart_save_history(index, original_cart, total_price);
                return true;
            }
        }
        cart_save_history(index, original_cart, total_price);
        return true;
    }
}

bool Servor::cart_save_history(vector<int> index, Cart original_cart, double total_price){
    ofstream ofs("history_" + current_user->get_name() + ".txt", ios::app);
    long long seconds;
    //int yy, mm, dd;
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
    for(auto i : index){
        int num = cart_products[i].get_num() - current_user->get_cart().get_product(cart_products[i].get_name()).get_num();
        ofs << "Product: " << cart_products[i].get_name() << " Type: " << cart_products[i].get_type();
        ofs << " Price: " << cart_products[i].get_price() << " Num: " << num << endl;
    }
    ofs << "Total price: " << total_price << endl;
    ofs << endl;
    ofs.close();
    return true;
}

bool Servor::cart_show_history(){
    ifstream ifs("history_" + current_user->get_name() + ".txt");
    if(!ifs){
        cout << "ERROR: history not found" << endl;
        return false;
    }
    string line;
    while (getline(ifs, line)){
        cout << line << endl;
    }
    ifs.close();
    return true;
}

bool Servor::cart_analysis(vector<int> start_time, vector<int> end_time){
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

bool Servor::cart_analysis(long long seconds_begin, long long seconds_end){
    ifstream ifs("history_" + current_user->get_name() + ".txt");
    if(!ifs){
        cout << "ERROR: history not found" << endl;
        return false;
    }
    vector<string> lines;
    char buffer[2048];
    while(ifs.getline(buffer, 2048,'\n')){
        lines.push_back(buffer);
    }
    ifs.close();
    vector<Product> products_analysis;
    bool jud = false;
    for(auto line : lines){
        if(line.find("Time") != string::npos){
            long long seconds;
            stringstream ss(line);
            string temp;
            int i = 0;
            while (getline(ss, temp,' ')){
                if(i == 2){
                    seconds = stoll(temp);
                }
                i ++;
            }
            if (seconds >= seconds_begin){
                jud = true;
            }
            if (seconds > seconds_end){
                break;
            }
        }
        if(jud == true && line.find("Product") != string::npos){
            stringstream ss(line);
            string temp;
            int i = 0;
            Product product("NULL", "NULL", 0, 0);
            while (getline(ss, temp,' ')){
                if(i == 1){
                    product.set_name(temp);
                } else if(i == 3){
                    product.set_type(temp);
                } else if(i == 5){
                    product.set_price(stod(temp));
                } else if(i == 7){
                    product.set_num(stoi(temp));
                }
                i ++;
            }
            products_analysis.push_back(product);
        }
    }
    if(jud == false){
        cout << "ERROR: no data" << endl;
        return false;
    }
    sort(products_analysis.begin(), products_analysis.end(), [](const Product& p1, const Product& p2) {
        if (p1.get_type() == p2.get_type()) {
            return p1.get_name() < p2.get_name();
        }
        return p1.get_type() < p2.get_type();
    });
    products_analysis.push_back(Product("NULL", "NULL", 0, 0));
    cout << "Analysis result:" << endl;
    double type_price = 0;
    for(int i = 0; i < products_analysis.size() - 1; i ++){
        if(i == 0 || products_analysis[i].get_type() != products_analysis[i - 1].get_type()){
            cout << endl << "Type: " << products_analysis[i].get_type() << endl;
        }
        cout << "Product: " << products_analysis[i].get_name() << " Price: $" << products_analysis[i].get_price();
        int num = 0;
        while(i < products_analysis.size() - 1){
            num += products_analysis[i].get_num();
            if(products_analysis[i].get_name() != products_analysis[i + 1].get_name()){
                cout << " Num: " << num << endl;
                break;
            }
            i ++;
        }
        type_price += num * products_analysis[i].get_price();
        if(products_analysis[i].get_type() != products_analysis[i + 1].get_type()){
            cout << "Type total price: $" << type_price << endl;
            type_price = 0;
        }
    }
    return true;
}

string Servor::code_create(int n, bool publush_flag){
    string library1 = "0123456789";
    string library2 = "abcdefghijklmnopqrstuvwxyz";
    string library3 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string library = library1 + library2 + library3;
    srand(time(0));
    string code;
    while(1){
        code = "";
        for (int i = 0; i < n; i++) {
            int key = rand() % library.length();
            code += library[key];
        }
        if(code_search(code) == -1){
            break;
        }
    }
    double discount = (double)(rand() % 3 + 7) / 10.0;
    Code new_code(code, discount, publush_flag);
    codes.push_back(new_code);
    save_code_data();
    return code;
}

string Servor::code_create(int n, double discount, bool publush_flag){
    string library1 = "0123456789";
    string library2 = "abcdefghijklmnopqrstuvwxyz";
    string library3 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string library = library1 + library2 + library3;
    srand(time(0));
    string code;
    while(1){
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
    save_code_data();
    return code;
}

int Servor::code_search(string code){
    for(int i = 0; i < codes.size(); i ++){
        if(codes[i].get_code() == code){
            return i;
        }
    }
    return -1;
}

double Servor::code_get_discount(string code){
    int code_index = code_search(code);
    if(code_index != -1){
        return codes[code_index].get_discount();
    } else{
        return 1;
    }
}

bool Servor::code_delete(int code_index){
    if(code_index >=0 && code_index < codes.size()){
        codes.erase(codes.begin() + code_index);
        return save_code_data();
    }
    return false;
}

bool Servor::code_eligibility_check(){
    if(get_current_user()->get_cart().get_code_flag() == false && get_current_user()->get_cart().get_coupon() == 1){
        cout << "You are already eligible to apply for redemption code." << endl;
        return false;
    }
    return true;
}

bool Servor::code_eligibility_initialize(){
    Cart cart = current_user->get_cart();
    cart.set_coupon(1);
    cart.set_code_flag(false);
    current_user->set_cart(cart);
    return save_user_data();
}

double Servor::activity_get(){
    return activity_discount;
}

bool Servor::is_root(){
    if(current_user != NULL && current_user->get_permission() == User::ROOT){
        return true;
    } else{
        return false;
    }
}

bool Servor::root_login(string name, string password){
    Root* root = new Root();
    if(root->get_name() == name && root->get_password() == password){
        if(current_user != NULL){
            if(current_user != NULL){
                if(current_user->get_permission() == User::USER){
                    user_logout();
                } else{
                    root_logout();
                }
            }
        }
        current_user = root;
        return true;
    }
    return false;
}

bool Servor::root_logout(){
    if(servor_save()){
        delete current_user;
        current_user = NULL;
        return true;
    }
    return false;
}

bool Servor::root_coupon_set(double min, double max){
    if(!is_root()){
        return false;
    }
    this->coupon_min = min;
    this->coupon_max = max;
    return true;
}

bool Servor::root_activity_set(double discount){
    if(!is_root()){
        return false;
    }
    this->activity_discount = discount;
    return true;
}

vector<Code> Servor::root_codes_get(){
    if(!is_root()){
        return vector<Code>();
    }
    return codes;
}

bool Servor::root_code_add(double discount){
    if(!is_root()){
        return false;
    }
    code_create(25, discount, false);
    return true;
}

void Servor::root_code_show(){
    if(!is_root()){
        return;
    }
    int i = 0;
    for(auto code : codes){
        cout << "Order number: " << i << endl;
        cout << "Code: " << code.get_code() << endl;
        cout << "Discount: " << code.get_discount() << endl;
        cout << "Pubilsh flag: " << code.get_pubilsh_flag() << endl;
        cout << endl;
        i ++;
    }
    if(i == 0){
        cout << "ERROR: code is empty" << endl;
    }
}

bool Servor::root_code_delete(int code_index){
    if(!is_root()){
        return false;
    }
    codes.erase(codes.begin() + code_index);
    return true;
}

bool Servor::root_code_delete(string code){
    if(!is_root()){
        return false;
    }
    for(auto it = codes.begin(); it != codes.end(); it ++){
        if(it->get_code() == code){
            codes.erase(it);
            return true;
        }
    }
    return false;

}

User Servor::root_user_get(int index){
    if(!is_root()){
        return User(User::USER);
    }
    if(index >= 0 && index < users.size()){
        return users[index];
    } else{
        return User(User::USER);
    }
    
}

User Servor::root_user_get(string name){
    if(!is_root()){
        return User(User::USER);
    }
    for(auto user : users){
        if(user.get_name() == name){
            return user;
        }
    }
    return User(User::USER);
}

vector<User> Servor::root_users_get(){
    if(!is_root()){
        return vector<User>();
    }
    return users;
}

bool Servor::root_user_add(string name, string password, int money){
    if(!is_root()){
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

bool Servor::root_user_set(int user_index, User new_user){
    if(!is_root()){
        return false;
    }
    users[user_index] = new_user;
    return true;
}

bool Servor::root_user_set(User origin_user, User new_user){
    if(!is_root()){
        return false;
    }
    for(auto &user : users){
        if(user.get_name() == origin_user.get_name()){
            user = new_user;
            return true;
        }
    }
    return false;
}

bool Servor::root_user_delete(int user_index){
    if(!is_root()){
        return false;
    }
    users.erase(users.begin() + user_index);
    return true;
}

bool Servor::root_user_delete(User origin_user){
    if(!is_root()){
        return false;
    }
    for(auto it = users.begin(); it != users.end(); it ++){
        if(it->get_name() == origin_user.get_name()){
            users.erase(it);
            return true;
        }
    }
    return false;
}

bool Servor::root_user_show(){
    if(!is_root()){
        return false;
    }
    int i = 0;
    for(auto user : users){
        cout << "Order number: " << i << endl;
        user.info_root();
        cout << endl;
        i ++;
    }
    if(i == 0){
        cout << "ERROR: user is empty" << endl;
        return false;
    }
    return true;
}

bool Servor::root_user_search(string name){
    if(!is_root()){
        return false;
    }
    bool jud = 0;
    int i = 0;
    for(auto user : users){
        if(user.get_name() == name || user.get_name().find(name) != string::npos){
            cout << "Order number: " << i << endl;
            user.info();
            cout << endl;
            jud = 1;
        }
        i ++;
    }
    if(jud == 1){
        return true;
        
    } else{
        cout << "ERROR: user not found" << endl;
        return false;
    }
}

bool Servor::root_product_add(string name, string type, double price, int num){
    if(!is_root()){
        return false;
    }
    for(auto product : products){
        if(product.get_name() == name){
            product.set_num(product.get_num() + num);
            return true;
        }
    }
    Product product(name, type, price, num);
    products.push_back(product);
    return true;
}

bool Servor::root_product_set(int product_index, Product new_product){
    if(!is_root()){
        return false;
    }
    products[product_index] = new_product;
    return true;
}

bool Servor::root_product_set(Product origin_product, Product new_product){
    if(!is_root()){
        return false;
    }
    for(auto &product : products){
        if(product.get_name() == origin_product.get_name()){
            product = new_product;
            return true;
        }
    }
    return false;
}

bool Servor::root_product_delete(int product_index){
    if(!is_root()){
        return false;
    }
    products.erase(products.begin() + product_index);
    return true;
}

bool Servor::root_product_delete(User origin_product){
    if(!is_root()){
        return false;
    }
    for(auto it = products.begin(); it != products.end(); it ++){
        if(it->get_name() == origin_product.get_name()){
            products.erase(it);
            return true;
        }
    }
    return false;
}