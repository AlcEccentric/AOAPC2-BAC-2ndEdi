#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <set>
using namespace std;
// ifstream  cin("test.in");
// ofstream  cout("test.out");

int main(){
    string x;
    set<string> dictionary;
    while( cin>>x){
        dictionary.insert(x);
    }
    for(auto word : dictionary){
        int len = strlen(word.c_str());
        if(len <= 1) continue;
        for(int i = 1; i < strlen(word.c_str()); i++)
        {
            if(dictionary.count(word.substr(0,i)) && dictionary.count(word.substr(i, len-i))){
                 cout << word << endl;
                break;
            }
        }
        
    }
}