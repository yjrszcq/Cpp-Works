#include <bits/stdc++.h>
using namespace std;

bool isInteger(const std::string& str) {
    try {
        std::stoi(str);
        return true;
    } catch (std::invalid_argument const& e) {
        return false;
    } catch (std::out_of_range const& e) {
        return false;
    }
}

bool isFloat(const std::string& str) {
    try {
        std::stof(str);
        return true;
    } catch (std::invalid_argument const& e) {
        return false;
    } catch (std::out_of_range const& e) {
        return false;
    }
}

void generator(){
    cout << "请输入表的名字: ";
    string table_name;
    cin >> table_name;
    cout << "请输入表的属性数目: ";
    int n = 0;
    cin >> n;
    cout << "请输入表的行数: ";
    int m = 0;
    cin >> m;
    m += 1;
    cout << "请按列输入表的属性名和属性: "<< endl;
    getchar();
    vector<string> data;
    for(int i = 0; i < n; i ++){
        cout << endl << "请输入第" << i + 1 << "列: " << endl;
        for(int j = 0; j < m; j ++){
            string temp;
            getline(cin, temp);
            data.push_back(temp);
        }
    }
    cout << endl << "表的属性如下: " << endl;
    for(int i = 0; i < m; i ++){
        if(i == 0){
            cout << "insert into " << table_name << " ";
        }
        cout << "(";
        for(int j = i; j < n * m; j += m){
            if(j != i){
                cout << ", ";
            }
            if(!isInteger(data[j]) && !isFloat(data[j]) && i != 0){
                cout << "'" << data[j] << "'";
            } else{
                cout << data[j];
            }
        }
        cout << ")";
        if(i == 0){
            cout << " values ";
        } else{
            if(i != m - 1){
                cout << ", ";
            } else{
                cout << ";";
            }
        }
        cout << endl;
    }
    cout << endl;
}

int main(){
    cout << "数据库表<批量插入数据>代码生成器 (竖式填入)" << endl << endl;
    while(1){
        generator();
        cout << "是否继续生成代码? (y/n): ";
        string temp;
        cin >> temp;
        if(temp == "n" || temp == "N"){
            break;
        }
    }
}