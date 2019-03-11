#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <cctype>
#include <set>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");


struct word{
    string thisWord;
    bool operator < (const struct word& w) const{
        if(strcmp(thisWord.c_str(), w.thisWord.c_str()) < 0)
            return true;
        return false;
    };
};

ostream& operator << (ostream& out, const word& w){
    out<<w.thisWord;
    return out;
}

void init(char* s, int count){
    for(int i = 0; i < count; i++)
    {
        s[i] = '\0';
    }
    
}
void getRidOfNonAlpha(char* s){
    for(int i = 0; i < strlen(s); i++)
    {
        if(!isalpha(s[i]))
            s[i] = '\0';
    }
}
void strToLower(char *s){
    for(int i = 0; i < strlen(s); i++)
    {
        s[i] = (char)tolower((int)s[i]);
    }
    
}

int main(){
    char s[205];
    set<word> words;
    init(s, 205);
    char c;
    while(cin.get(c)){

        while(isalpha(c)){
            c = (char)tolower((int)c);
            s[strlen(s)] = c;
            cin.get(c);
        }
        if(strlen(s)!=0){
            string x = s;
            word w;
            w.thisWord = x;
            words.insert(w);
        }
        init(s, 205);
    }
    for(auto witer: words){
        cout << witer << endl;
    }

}