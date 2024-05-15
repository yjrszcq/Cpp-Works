#include <bits/stdc++.h>

using namespace std;

void random_password_generator();
void generator();
void generate_password();
void record_password(string password);
void view_password();
void clear_password();

int main() {
    random_password_generator();
    return 0;
}

void random_password_generator(){
    while(true){
        cout << "Random Password Generator" << endl << endl;
        cout << "Please select a function: " << endl;
        cout << "1. Generate a password" << endl;
        cout << "2. View all the passwords generated" << endl;
        cout << "3. Clear all the passwords generated" << endl;
        cout << "0. Exit" << endl;
        int jud;
        cin >> jud;
        system("cls");
        switch(jud){
            case 0: cout << "Goodbye!" << endl << endl; system("pause"); return;
            case 1: generator(); break;
            case 2: view_password(); break;
            case 3: clear_password(); break;
            default: cout << "Invalid input!" << endl << endl; system("pause"); break;
        }
        system("cls");
    }
}

void generator(){
    while(true){
        cout << "Random Password Generator" << endl << endl;
        generate_password();
        cout << "Do you want to generate another password? (Y/N)" << endl;
        char jud;
        cin >> jud;
        if (jud == 'N' || jud == 'n') {
            break;
        }
        system("cls");
    }
}

void clear_password(){
    if (remove("password.txt") != 0) {
        cout << "ERROR: Failed to clear password." << endl << endl;
    } else {
        cout << "All passwords have been cleared." << endl << endl;
    }
    system("pause");
}

void view_password(){
    ifstream infile("password.txt");
    if(!infile){
        cerr << "ERROR: 'password.txt' not found." << endl << endl;
        system("pause");
        return;
    }
    string password;
    while(getline(infile, password)){
        cout << password << endl;
    }
    cout << endl;
    infile.close();
    system("pause");
}

void record_password(string password) {
    ofstream outfile("password.txt", ios::app);
    outfile << password << endl;
    outfile.close();
}

void generate_password(){
    string library1 = "0123456789"; // 数字
    string library2 = "abcdefghijklmnopqrstuvwxyz"; // 小写字母
    string library3 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // 大写字母
    string library4 = "~!@#$%^&*()_+"; // 常用符号
    string library5 = "`~!@#$%^&*()-=[]\\;',./_+{}|:\"<>?"; // 所有符号
    string library = library1 + library2 + library3;
    cout << "Please select the symbol to add:" << endl;
    cout << "1. Do not add symbols" << endl;
    cout << "2. Add common symbols" << endl;
    cout << "3. Add all symbols" << endl;
    cout << "0. Cancel" << endl;
    int jud;
    cin >> jud;
    switch(jud){
        case 0: return;
        case 1: break;
        case 2: library += library4; break;
        case 3: library += library5; break;
        default: {
            cout << endl << "Invalid input!" << endl;
            cout << "No symbols are added by default." << endl;
            break;
        }
    }
    cout << endl << "Please enter the password length: " << endl;
    int n;
    cin >> n;
    if(n <= 0){
        cout << endl << "Invalid input!" << endl << endl;
        system("pause");
        return;
    } else if(n > 1000){
        cout << endl << "The password length is too long!" << endl << endl;
        cout << "Ignore warnings to continue generating password. (Y/N)" << endl;
        char jud_continue;
        cin >> jud_continue;
        if (jud_continue == 'N' || jud_continue == 'n'){
            return;
        }
    }
    srand(time(0));
    string password;
    for (int i = 0; i < n; i++) {
        int key = rand() % library.length();
        password += library[key];
    }
    cout << endl << password << endl << endl;
    record_password(password);
}
