#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <set>
#define testAdd 1
#define testVec 1 
#define testBin 1
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
int A[10], P[10], Pos[10];//这里只考虑无重复的集合的全部子集
int V[10];//向量
// 前两种属于递归法
// 后一种属于直接枚举
// 后两种的思路一样，只是做法不同
void print_subset_add(int n, int cur){
    for (int i = 0; i < cur; i++)
        fout << A[i];
    fout << "\n";
    int s = cur ? Pos[A[cur-1]] + 1 : 0;
    for(int i = s; i < n; i++){
        A[cur] = P[i];
        print_subset_add(n, cur+1);
    }
}
void print_subset_vec(int n, int cur){
    if(cur == n){
        for (int i = 0; i < n; i++)
            if(V[i]) fout << P[i];
        fout << '\n';
        return;
    }
    V[cur] = 0;
    print_subset_vec(n, cur+1);
    V[cur] = 1;
    print_subset_vec(n, cur+1);
}
void print_subset_bin(int n){
    for(int i = 0; i < (1<<n); i++){
        for (int j = 0; j < n; j++){
            if(i&(1<<j)) fout << P[n-1-j];
        }
        fout << "\n";
    }
}
int main(){
    // test add element methods
    srand((unsigned)time(NULL));
    set<int> noRepeat;
    int n = 3;
    for (int i = 0; i < n; i++){
        int r;
        do{
            r = (int)rand()%10;
        }while(noRepeat.count(r));
        noRepeat.insert(r);
        P[i] = r;
    }
    sort(P, P+n);
    for (int i = 0; i < n; i++){
        fout << P[i] << " ";
        Pos[P[i]] = i;
    }
    fout << "\n";
    #if testAdd
    print_subset_add(n, 0);
    #endif

    #if testVec
    print_subset_vec(n, 0);
    #endif

    #if testBin
    print_subset_bin(n);
    #endif
}