#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
// NOTE:
// 1. 用next数组可以表示单向链表，如果要实现双向链表，则需要在next数组基础上再加一个prev数组，朝反方向指
// 2. 对于遍历加和的结果，即使每个数不溢出，也要判断最后的和是否会导致溢出
const int maxn = 100000 + 5;

void exch(int *next, int* prev, int x, int y){
    if(next[x] == y){
        int px = prev[x];
        int ny = next[y];
        next[px] = y;
        next[y] = x;
        next[x] = ny;
        prev[ny] = x;
        prev[x] = y;
        prev[y] = px;
    }else if(prev[x] == y){
        int py = prev[y];
        int nx = next[x];
        next[py] = x;
        next[x] = y;
        next[y] = nx;
        prev[nx] = y;
        prev[y] = x;
        prev[x] = py;
    }else{
        int px = prev[x];
        int py = prev[y];
        int nx = next[x];
        int ny = next[y];
        next[px] = y;
        next[y] = nx;
        next[py] = x;
        next[x] = ny;
        prev[nx] = y;
        prev[y] = px;
        prev[ny] = x;
        prev[x] = py;
    }

}

void del(int *next, int* prev, int t){
    int p = prev[t];
    int n = next[t];
    next[p] = n;
    prev[n] = p;
}

void insertRight(int *next, int* prev, int i, int t){
    int tn = next[t];
    next[t] = i;
    next[i] = tn;
    prev[tn] = i;
    prev[i] = t;
}

void insertLeft(int *next, int* prev, int i, int t){
    int tp = prev[t];
    prev[t] = i;
    prev[i] = tp;
    next[tp] = i;
    next[i] = t;
}
void print(int *next){
    for(int j = next[0]; j != 0; j = next[j])
        cout << j << " ";
    cout << endl;
}
void printSum(int *next){
    long long sum = 0, ind = 1;
    for(int i = next[0]; i != 0; i = next[i])
    {
        if(ind%2 == 1) sum += i;
        ind++;
    }
    cout << sum << endl;
}
void init(int * x, int count){
    for(int i = 0; i < count; i++)
        x[i] = 0;
}
int main(){
    int n;
    int caseNo = 1;
    while(cin >> n){
        // cout << endl;
        cout << "Case " << caseNo++ << ": ";
        // cout << "n = " << n << endl;
        int next[maxn];
        init(next, maxn);
        next[n] = 0;
        for(int i = 0; i < n; i++)
            next[i] = i+1;
        
        int prev[maxn];
        init(prev, maxn);
        prev[0] = n;
        for(int i = 1; i < n+1; i++)
            prev[i] = i - 1;
        
        int m;
        cin >> m;
        bool normal = true;
        // print(next);
        for(int i = 0; i < m; i++)
        {
            int c, x, y;
            cin >> c;
            switch (c)
            {
                case 1:
                    /* move x to y left */
                    cin >> x >> y;
                    del(next, prev, x);
                    if(normal){
                        insertLeft(next, prev, x, y);
                    }else{
                        insertLeft(prev, next, x, y);
                    }
                    break;
                
                case 2:
                    /* move x to y right */
                    cin >> x >> y;
                    del(next, prev, x);
                    if(normal){
                        insertRight(next, prev, x, y);
                    }else{
                        insertRight(prev, next, x, y);
                    }
                    break;
                
                case 3:
                    /* exch x and y */
                    cin >> x >> y;
                    exch(next, prev, x ,y);
                    break;
                
                case 4:
                    normal = !normal;
                    break;
            
                default:
                    break;
            }
            // if(normal){
            //     print(next);
            // }
            // else{
            //     print(prev);
            // }
        }
        if(normal){
            // print(next);
            printSum(next);
        }
        else{
            // print(prev);
            printSum(prev);
        }
        
    }
}