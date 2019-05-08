#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <math.h>
using namespace std;
// 这题如果理解清楚会发现连模拟题都算不上啊。。
// 再加上这数据量少得可怜，硬找规律就ez解决
ifstream cin("test.in");
ofstream cout("test.out");
void init(int * x, int v){
    for(int i = 0; i < 7; i++)
        x[i] = v;
}
void init(char * x, int count){
    for(int i = 0; i < count; i++)
        x[i] = '\0';
}
int toInd(const char *x){
    int l = strlen(x), ret = 0;
    for(int i = 0; i < l; i++){
        ret = ret + (x[i] - '0') * (int)pow(2, l - 1 - i);
    }
    return ret;
}
int main(){
    int n;
    int caseNum = 1;
    while(cin >> n){
        if(n == 0) break;
        cout << "S-Tree #" << caseNum << ":\n";
        int pos[7];
        init(pos, -1);
        for (int i = 0; i < n; i++){
            char x;
            cin >> x;
            cin >> x;
            pos[x - '1'] = i;
        }
        char leaves[130];
        init(leaves, 130);
        cin >> leaves;
        int m;
        cin >> m;
        char x[8];
        init(x, 8);
        for (int i = 0; i < m; i++){    
            cin >> x;
            char key[8];
            init(key, 8);
            for(int j = 0; j < strlen(x); j++){
                key[pos[j]] = x[j];
            }
            // cout << "key = " << key << endl;
            cout << leaves[toInd(key)];
        }
        cout << "\n" << endl;
        caseNum ++;
    }
}