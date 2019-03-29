#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");

// NOTE:
// 题目说深度不超过5而不是层数不超过5，
// 根节点的深度为0,因此所谓层数不超过5的意思是，算上根节点所在层一共不超过6层
// 因此最多节点数为2047而不是1023
// 所以数组要开得大一点
long sum = 0;
void getInput(char * color, int ind){
    char c;
    cin>>c;
    if(c == 'f'){
        color[ind] = c;
        return;
    }
    if(c == 'e'){
        //leaf
        if(color[ind] == '\0') color[ind] = c;
        return;
    }
    if(c == 'p'){
        if(color[ind] == '\0' || color[ind] == 'e'){
            color[ind] = c;
        }
        int x4 = (ind+1)*4;
        getInput(color, x4-3);
        getInput(color, x4-2);
        getInput(color, x4-1);
        getInput(color, x4);
    }
    return;
}

void count(char * color, int ind, int w){
    if(color[ind] == 'e'){
        return;
    }else if(color[ind] == 'f'){
        sum = sum + w;
        return;
    }else if(color[ind] == 'p'){
        int nextw = w/4;
        int x4 = (ind+1)*4;
        count(color, x4-3, nextw);
        count(color, x4-2, nextw);
        count(color, x4-1, nextw);
        count(color, x4, nextw);
        return;
    }
}

void init(char *x, int count){
    for(int i = 0; i < count; i++)
        x[i] = '\0';   
}

int main(){
    int testCaseNum = 0;
    cin >> testCaseNum;
    while(testCaseNum){
        char color[3000];
        init(color, 3000);
        getInput(color, 0);
        getInput(color, 0);
        sum = 0;
        count(color, 0, 1024);
        cout << "There are " << sum <<" black pixels." << endl;
        testCaseNum--;
    }
}