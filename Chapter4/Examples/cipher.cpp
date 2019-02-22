#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
// need to note(about the compSucceed function)
void init(char * x, int size){
    for(int i = 0; i < size; i++)   
        x[i] = '\0';
}

void init(int * x, int size){
    for(int i = 0; i < size; i++)   
        x[i] = 0;
}

void countFor(char * chars, int * counts){
    for(int i = 0; i < strlen(chars); i++)
        counts[chars[i] - 'A'] ++;
}

int mycmp(const void* x, const void* y){
    return *(int*)x - *(int*)y;
}

bool compSucceed(const int* cntx, const int* cnty){
    for(int i = 0; i < 26; i++)
        if(cntx[i] != cnty[i]) return false;
    return true;
}

int main(){
    char x[105], y[105];
    int cntx[26], cnty[26];
    init(x,105);
    init(y,105);
    
    while(cin>>x>>y){
        init(cntx, 26);
        init(cnty, 26);
        countFor(x, cntx);
        countFor(y, cnty);
        qsort(cntx, 26, sizeof(int), mycmp);
        qsort(cnty, 26, sizeof(int), mycmp);
        if(compSucceed(cntx, cnty))
            cout<<"YES"<<endl;
        else
            cout<<"NO"<<endl;
        init(x,105);
        init(y,105);
    }
}