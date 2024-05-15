 #include<bits/stdc++.h>

 using namespace std;
 
class Expr {
public:
    Expr(string); //构造函数
    string suffixExpr(); //中缀表达式转后缀
    double eval(string suffixExpression); //计算后缀表达式
    void print(string suffixExpression); //输出后缀表达式
private:
    int priority(char); //优先级
    string expression; //表达式
};

Expr::Expr(string str) { //构造函数
    for(int i = 0; i < str.length(); i++){ //去除空格
        if(str[i] != ' '){
            expression += str[i];
        }
    }
}

int Expr::priority(char ch){ //优先级
    if (ch == '*' || ch == '/'){
        return 1;
    }
    if (ch == '+' || ch == '-'){
        return 0;
    }
    if (ch == '('){
        return -1;
    }
}

string Expr::suffixExpr(){ //中缀表达式转后缀
    stack<char> st;
    string suffixExpression;
    for(int i = 0; i < expression.length(); i++){ //遍历表达式
        if(expression[i] == '('){ //左括号直接入栈
            st.push(expression[i]);
        } else if(expression[i] == ')'){ //右括号弹出直到遇到左括号
            while(st.top() != '('){ 
                suffixExpression += st.top();
                suffixExpression += ' ';
                st.pop();
            }
            st.pop();
        } else if(expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/'){ //运算符
            while(!st.empty() && priority(st.top()) >= priority(expression[i])){ //弹出优先级大于等于当前运算符的运算符
                suffixExpression += st.top();
                suffixExpression += ' ';
                st.pop();
            }
            st.push(expression[i]); //当前运算符入栈
        } else{ //数字
            double n = 0;
            while(i < expression.length() && (expression[i] >= '0' && expression[i] <= '9' || expression[i] == '.')){ //获取数字
                suffixExpression += expression[i];
                i ++;
            }
            if(expression[i] == 'p' || expression[i] == 'e'){ //pi和e
                suffixExpression += expression[i];
                i ++;
            }
            suffixExpression += ' ';
            i --;
        }
    }
    while(!st.empty()){ //弹出剩余运算符
        suffixExpression += st.top();
        suffixExpression += ' ';
        st.pop();
    }
    return suffixExpression; //返回后缀表达式
}

double Expr::eval(string suffixExpression){ //计算后缀表达式
    stack<double> num;
    for(int i = 0; i < suffixExpression.length(); i ++){ //遍历后缀表达式
        if(suffixExpression[i] == ' '){
            continue;
        }
        if(suffixExpression[i] >= '0' && suffixExpression[i] <= '9'){ //数字
            string number;
            while(i < suffixExpression.length() && (suffixExpression[i] >= '0' && suffixExpression[i] <= '9' || suffixExpression[i] == '.')){
                number += suffixExpression[i];
                i ++;
            };
            num.push(stod(number));
            i --;
        } else if(suffixExpression[i] == 'p'){ //pi
            num.push(3.14159265358979323846);
        } else if(suffixExpression[i] == 'e'){ //e
            num.push(2.71828182845904523536);
        } else{ //运算符
            double b = num.top(); //弹出两个数进行运算
            num.pop();
            double a = num.top();
            num.pop();
            if(suffixExpression[i] == '+'){
                num.push(a + b);
            } else if(suffixExpression[i] == '-'){
                num.push(a - b);
            } else if(suffixExpression[i] == '*'){
                num.push(a * b);
            } else if(suffixExpression[i] == '/'){
                num.push(a / b);
            }
        }
    }
    return num.top(); //返回结果
}

void Expr::print(string suffixExpression){ //输出后缀表达式
    cout << suffixExpression << endl;
}
