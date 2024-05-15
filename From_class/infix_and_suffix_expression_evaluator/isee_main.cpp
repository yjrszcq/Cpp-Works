#include<bits/stdc++.h>
#include "infix_and_suffix_expression_evaluator.cpp"

int main() {
    cout << "Infix and Suffix Expression Evaluator" << endl;
    cout << endl;
    cout << "Please select a function: " << endl;
    cout << "1. Evaluate a infix expression" << endl;
    cout << "2. Evaluate a suffix expression" << endl;
    cout << "0. Exit" << endl;
    int choice;
    cin >> choice;
    cout << endl;
    cin.get();
    if(choice == 0){
        system("cls");
        cout << "Goodbye!" << endl;
        cout << endl;
        system("pause");
        return 0;
    }
    system("cls");
    cout << "Infix and Suffix Expression Evaluator" << endl;
    cout << endl;
    cout << "Enter a "<< (choice == 1 ? "infix" : "suffix") << " expression: ";
    string str;
    getline(cin, str);
    cout << endl;
    Expr expr(str);
    if(choice == 1){
        string suffix = expr.suffixExpr();
        cout << "Suffix expression: ";
        expr.print(suffix);
        cout << endl;
        cout << "Result: ";
        cout << expr.eval(suffix) << endl;
    }
    if(choice == 2){
        cout << "Result: ";
        cout << expr.eval(str) << endl;
    }
    cout << endl;
    system("pause");
    return 0;
}
/*
2 + ( 9.2 * 5.7 - 3 + ( p + 1 ) * e ) / 6.4

2 9.2 5.7 * 3 - p 1 + e * + 6.4 / +
11.4841
*/