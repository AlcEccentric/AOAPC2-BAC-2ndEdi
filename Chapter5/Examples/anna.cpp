#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <map>
#include <set>
#include <cctype>
#include <algorithm>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");

struct word{
    string ori;
    string key;
    bool operator < (const word& w) const{
        if(strcmp(ori.c_str(), w.ori.c_str()) < 0) return true;
        return false;
    }
};

void init(char * x, int count){
    for(int i = 0; i < count; i++)
    {
        x[i] = '\0';
    }
    
}

int main(){
    string s;
    map<string, int> countSame;
    set<word> words;
    while(cin>>s){
        if(strcmp(s.c_str(), "#")==0) break;
        word w;
        w.ori = s;
        char str[25];
        init(str, 25);
        strcpy(str, s.c_str());
        for(int i = 0; i < strlen(str); i++)
            str[i] = tolower(str[i]);
        sort(str, str+strlen(str));
        string ss = str;
        if(countSame.count(ss)){
            countSame[ss]++;
        }else{
            countSame[ss] = 1;
        }
        w.key = ss;
        words.insert(w);
    }
    for(auto w : words)
    {
        if(countSame[w.key] == 1){
            cout << w.ori << endl;
        }
    }
    
}