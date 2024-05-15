#include <bits/stdc++.h>
#include <Windows.h>
#include <io.h>
#include <conio.h>

using namespace std;

string sentence[100000];
string config_words[100000];

void getAllFiles(string path, vector<string>& files,string fileType);//获取文件夹下所有文件
void replacement();//批量替换文件内的字符串
void welcome();//程序说明
void batch_replace_words();

int main(int argc, char** argv){
    batch_replace_words();
    return 0;
}

void batch_replace_words(){
    welcome();
    replacement();
}

void welcome(){
    cout << "Batch Replace Words" << endl;
    cout << endl;
    cout << "This program is used to batch replace words in files." << endl;
    cout << endl;
    cout << "Please place the program in the folder where the files to be operated are stored." << endl;
    cout << endl;
    cout << "Please create a 'config' file and open it with Notepad, then fill in the following format:" << endl;
    cout << endl;
    cout << "suffix (Without '.')" << endl;
    cout << "originalWords1 newWords1" << endl;
    cout << "originalWords2 newWords2" << endl;
    cout << "..." << endl;
    cout << "originalWordsN newWordsN" << endl;
    cout << endl;
    cout << "If you want to delete words, please fill in [DELETE]." << endl;
    cout << endl;
    cout << "For example:" << endl;
    cout << endl;
    cout << "txt" << endl;
    cout << "hello hi" << endl;
    cout << "world earth" << endl;
    cout << "wrong [DELETE]" << endl;
    cout << endl;
    cout << "Then save and close the file." << endl;
    cout << endl;
    cout << "Press any key to replace words..." << endl;
    cout << endl;
    getch();
}

void getAllFiles(string path, vector<string>& files,string fileType){
	long hFile = 0;
	struct _finddata_t fileinfo;  
	string p;
	if((hFile = _findfirst(p.assign(path).append("\\*" + fileType).c_str(), &fileinfo)) != -1){
		do{
			files.push_back(p.assign("").append(fileinfo.name));
		} while(_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

void replacement(){
    SetConsoleOutputCP(65001);
    ifstream configFile("config");
    if(!configFile.is_open()){
        cerr << "ERROR: 'config' not found." << endl << endl;
        system("pause");
        return;
    }
    if(!configFile){
        cerr << "ERROR: 'config' not found." << endl << endl;
        system("pause");
        return;
    }
    system("cls");
    int cwn = 0;
    while(configFile >> config_words[cwn]){
        cwn ++;
    }
    configFile.close();

    string suffix = config_words[0];
    int originalWordsNum = (cwn - 1) / 2;
    string originalWords[originalWordsNum];
    string newWords[originalWordsNum];
    for(int i = 0; i < originalWordsNum; i ++){
        originalWords[i] = config_words[2 * i + 1];
        newWords[i] = config_words[2 * i + 2];
    }
    memset(sentence, 0, sizeof(sentence));
    string filePath = "replaced";
    bool flag = CreateDirectoryA(filePath.c_str(), NULL);
    if (!flag){
        if(access("replaced", 0) == 0){
            cout << "The directory already exists." << endl;
        } else{
            cout << "ERROR: Failed to create directory." << endl;
            system("pause");
            return;
        }
    }
    ofstream logFile("log");
    logFile.clear();
    char buff[FILENAME_MAX];
    getcwd( buff, FILENAME_MAX );
    string path(buff);
	vector<string> temp;
	getAllFiles(path, temp,"." + suffix);
    for(int i = 0; i < temp.size(); i ++){
        string fileName = temp[i];
        ifstream fin(fileName);
        if(!fin.is_open()){
            cerr << "ERROR: '" << fileName << "' not found." << endl;
            continue;
        }
        if(!fin){
            cerr << "ERROR: '" << fileName << "' not found." << endl;
            continue;
        }  
        int n = 0;
        char buffer[2048];
        while(fin.getline(buffer, 2048,'\n')){
            sentence[n] = buffer;
            n++;
        }
        fin.close();
        int jud_file = 0;
        int jud_ws[originalWordsNum][n];
        for(int j = 0; j < originalWordsNum; j ++){
            for(int k = 0; k < n; k ++){
                jud_ws[j][k] = 0;
            }
        }
        for(int j = 0; j < n; j ++){
            for(int k = 0; k < originalWordsNum; k ++){
                int index = sentence[j].find(originalWords[k]);
                if (index != string::npos){
                    if(jud_file == 0){
                        logFile << endl << "File: " << fileName;
                        jud_file = 1;
                    }
                    jud_ws[k][j] = 1;
                    if(newWords[k] == "[DELETE]"){
                        sentence[j].replace(index, originalWords[k].length(), "");
                    } else{
                        sentence[j].replace(index, originalWords[k].length(), newWords[k]);
                    }
                    
                }
            }
        }
        string newFileName = filePath + "/" + fileName;
        ofstream fout(newFileName);
        for(int j = 0; j < n; j ++){
            fout << sentence[j] << endl;
        }
        fout.close();
        for(int j = 0; j < originalWordsNum; j ++){
            int jud_words = 0;
            for(int k = 0; k < n; k ++){
                if(jud_ws[j][k] == 1){
                    if(jud_words == 0){
                        logFile << endl << "\tWords " << ": (" << originalWords[j] << " -> " << newWords[j] << ") in lines:";
                    }
                    jud_words = 1;
                    logFile << " " << k + 1;
                }
            }
        }
        cout << "File '" << fileName << "' has been replaced successfully." << endl;
    }
    logFile.close();
    system("pause");
}