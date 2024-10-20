#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

string toCamelCase(string str) {
    bool capitalize = true;
    string result = "";
    for (char& c : str) {
        if (c == '_') {
            capitalize = true;
        } else {
            if (capitalize) {
                result += toupper(c);
                capitalize = false;
            } else {
                result += c;
            }
        }
    }
    return result;
}

void generateClass(string className, int numVars, vector<pair<string, string>> vars) {
    cout << endl << "class " << className << "{" << endl;
    cout << "public:" << endl;
    cout << "    " << className << "();" << endl;
    cout << "    " << className << "(";
    for (int i = 0; i < numVars; i++) {
        cout << vars[i].first << " " << vars[i].second;
        if (i < numVars - 1) cout << ", ";
    }
    cout << ");" << endl;
    for (int i = 0; i < numVars; i++) {
        cout << "    void set" << toCamelCase(vars[i].second) << "(" << vars[i].first << " " << vars[i].second << ");" << endl;
    }
    for (int i = 0; i < numVars; i++) {
        cout << "    " << vars[i].first << " get" << toCamelCase(vars[i].second) << "();" << endl;
    }
    cout << endl << "private:" << endl;
    for (int i = 0; i < numVars; i++) {
        cout << "    " << vars[i].first << " " << vars[i].second << ";" << endl;
    }
    cout << "};" << endl << endl;

    cout << className << "::" << className << "(){" << endl;
    for (int i = 0; i < numVars; i++) {
        cout << "    this->" << vars[i].second << " = ";
        if (vars[i].first == "string") {
            cout << "\"\"";
        } else if (vars[i].first == "int") {
            cout << "0";
        }
        cout << ";" << endl;
    }
    cout << "}" << endl << endl;

    cout << className << "::" << className << "(";
    for (int i = 0; i < numVars; i++) {
        cout << vars[i].first << " " << vars[i].second;
        if (i < numVars - 1) cout << ", ";
    }
    cout << "){" << endl;
    for (int i = 0; i < numVars; i++) {
        cout << "    this->" << vars[i].second << " = " << vars[i].second << ";" << endl;
    }
    cout << "}" << endl << endl;

    for (int i = 0; i < numVars; i++) {
        cout << "void " << className << "::set" << toCamelCase(vars[i].second) << "(" << vars[i].first << " " << vars[i].second << "){" << endl;
        cout << "    this->" << vars[i].second << " = " << vars[i].second << ";" << endl;
        cout << "}" << endl << endl;
    }

    for (int i = 0; i < numVars; i++) {
        cout << vars[i].first << " " << className << "::get" << toCamelCase(vars[i].second) << "(){" << endl;
        cout << "    return this->" << vars[i].second << ";" << endl;
        cout << "}" << endl << endl;
    }
}

int main() {
    string className;
    int numVars;
    vector<pair<string, string>> vars;

    cout << "请输入类名：";
    cin >> className;
    cout << "请输入变量数量：";
    cin >> numVars;

    for (int i = 0; i < numVars; i++) {
        string type, varName;
        cout << "请输入第" << i + 1 << "个变量的类型和变量名：";
        cin >> type >> varName;
        vars.push_back(make_pair(type, varName));
    }

    generateClass(className, numVars, vars);
	
	// system("pause");
    return 0;
}
