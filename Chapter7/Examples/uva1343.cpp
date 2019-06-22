#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;
// IDA，剪枝策略比较容易想，其他就是很常规的四会，注意IDA算法不需要状态，BFS才需要状态，
// 书上说也能用BFS，但是需要特殊处理减少状态数，
// 本来是8个1 8个2 8个3组成的排列个数，最大状态数 = 24!/(8!*8!*8!) ~ 90亿
// 改进策略是把问题分为三个子问题：找到中间8块的数字相同的情况 => 找到中间8块全为1、找到中间8块全为2、找到中间8块全为3
// 这样一来每次寻找只需要区分是某个数字或者不是某个数字，每次查找的状态数变为24!/(8!*16!) 几十万的水平，最后从三个次优解里找出最优解即可
// 当然也有的评论说用BFS做还是会超时
// 启发：
// 1. BFS是如果状态是通过计算排列数的方式算出的，并且明显超出正常数据范围，可以尝试通过一些方式减少排序元素的种类减少可能的状态数
// 这道题目里就是将目标分为三个小目标分别求解，从而减少了排序元素种类，减少了可能的最大状态数
// 2. IDA不需要有状态记录这种东西，不需要记录走过的状态
// 3. 写IDA的第一步是确定maxd的最大值，如果没有最大值，就需要注意退出迭代过程的条件（一般是找到需求结果），
// 这道题如果分为子问题来做就无法保证当前子问题一定有解，从而会陷入死循环，因此IDA时不需要分成子问题做
//      1     2
//      3     4
//5  6  7  8  9  10 11
//      12    13 
//14 15 16 17 18 19 20
//      21    22
//      23    24
// ifstream cin("test.in");
// ofstream cout("test.out");
int orim[24];
int maxd;
vector <int> ans;
void printM(const int* m){
    cout << "    "<< m[0] << "   " << m[1] << "\n";
    cout << "    "<< m[2] << "   " << m[3] << "\n";
    for(int i = 0; i < 7; i++)
        cout << m[4+i]<<" ";
    cout << "\n";
    cout << "    "<< m[11] << "   " << m[12] << "\n";
    for(int i = 0; i < 7; i++)
        cout << m[13+i]<<" ";
    cout << "\n";
    cout << "    "<< m[20] << "   " << m[21] << "\n";
    cout << "    "<< m[22] << "   " << m[23] << "\n";
    cout << "\n";
}
int minDiffNum(const int* v){
    int diffs[] = {0, 0, 0};
    int x[] = {6, 7, 8, 11, 12, 15, 16, 17};
    int count = 0;
    for(int i = 0; i < 8; i++)
        if(v[x[i]] != 1) diffs[0]++;

    for(int i = 0; i < 8; i++)
        if(v[x[i]] != 2) diffs[1]++;

    for(int i = 0; i < 8; i++)
        if(v[x[i]] != 3) diffs[2]++;
    
    sort(diffs, diffs+3);
    return diffs[0];
}
void mov(int i1, int i2, int i3, int i4, int i5, int i6, int i7, const int*p, int*v){
    v[i7-1] = p[i1-1];
    v[i1-1] = p[i2-1];
    v[i2-1] = p[i3-1];
    v[i3-1] = p[i4-1];
    v[i4-1] = p[i5-1];
    v[i5-1] = p[i6-1];
    v[i6-1] = p[i7-1];
}
void operateArray(const int* p, int op, int* v){
    
    switch (op)
    {
    case 0:
        mov(1,3,7,12,16,21,23,p,v);
        break;
    case 1:
        mov(2,4,9,13,18,22,24,p,v);
        break;
    case 2:
        mov(11,10,9,8,7,6,5,p,v);
        break;
    case 3:
        mov(20,19,18,17,16,15,14,p,v);
        break;
    case 4:
        mov(24,22,18,13,9,4,2,p,v);
        break;
    case 5:
        mov(23,21,16,12,7,3,1,p,v);
        break;
    case 6:
        mov(14,15,16,17,18,19,20,p,v);
        break;
    case 7:
        mov(5,6,7,8,9,10,11,p,v);
        break;
    }
}
bool dfs(int d, const int* p, int& i, int op){
    int v[24];
    // cout << "maxd = "<< maxd << " d = " << d << " op = " << (char)('A' + op) << "\n";
    memcpy(v, p, 24*sizeof(int));
    if(d){
        operateArray(p, op, v);
        ans.push_back(op);
    }
    // printM(v);
    int restOpNum = maxd - d, zn = minDiffNum(v);//zero num = num != i in center
    // cout << "zn = " << zn << "\n";
    if(zn > restOpNum){
        // cout << "1\n\n";
        if(d) ans.pop_back();
        return false;
    }
    if(d == maxd){
        // cout << "2\n\n";
        if(zn) {
            if(d) ans.pop_back();
            return false;
        }
        else {
            i = v[6];
            return true;
        } 
    }else{
        // cout << "3\n\n";
        if(zn){
            for (int j = 0; j < 8; j++)
                if(dfs(d+1, v, i, j)) return true;
            if(d) ans.pop_back();
            return false;
        }else {
            i = v[6];
            return true;
        }
    }
}
int cindAns(){
    int i;
    ans.clear();
    // printM(orim);
    for(maxd = 0; ; maxd++){
        if(dfs(0, orim, i, 0)) break;
    }
    return i;
}
int main(){
    int x;
    while(cin>>x){
        if(!x) break;
        orim[0] = x;
        for(int i = 1; i < 24; i++)
            cin >> orim[i];
        int n = cindAns();
        // printAns();
        for(int i = 0; i < ans.size(); i++)
            cout << (char)(ans[i] + 'A');
        if(ans.size() == 0) cout << "No moves needed";
        cout << "\n";
        cout << n << "\n";
    }
}