#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;


void init(char *x, int size){
    for(int i = 0; i < size; i++){
        x[i] = '\0';
    }
}

int main(){
    char s[100000], t[100000];
    init(s, 100000);
    init(t, 100000);
    while(cin>>s>>t){
        int tCursor = 0;
        bool cind = true;
        for(int i = 0; i < strlen(s); i++){
            bool res = false;
            while(tCursor < strlen(t)){
                if(t[tCursor] == s[i]) {
                    res = true;
                    tCursor++;
                    break;
                }
                tCursor++;
            }
            cind = cind && res;
            if(!res) break;
        }
        if(cind)
            cout<<"Yes"<<endl;
        else
            cout<<"No"<<endl;
        
    }
}