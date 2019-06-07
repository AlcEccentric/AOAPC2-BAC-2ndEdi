#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
// 这里的代码还是复杂了些,
// 刘汝佳的代码用了两个辅助数组vis和isp，空间换时间（计算量）的方法将代码减少了很多
// 在本代码的print_circle中，通过遍历32以内的素数与前一个数的差，并判断这个差是否在[1, n]之间，其目的就是找到和前一个数相加能得到素数的数
// 而刘汝佳实现该目的的方法则是建立一个isp数组，由于n最大16，可能的和都在[1,31]之间，因此isp是一个32个整数数组，i如果是素数，则isp[i]为1
// 遍历1-n，和前一个数求和。看isp[和]是否为1即可判断枚举的数是否能和前一个数相加为负数，其代码逻辑看上去更加自然，而不像这里的比较hack
// 而vis数组则是判断当前枚举数是否在前面已经枚举，而这个数组能够确实地减少程序的复杂度（从O(n)的循环变为O(1)直接访问）
int primenum = 11;
int C[17];
int primes[11] = {2,3,5,7,11,13,17,19,23,29,31};
void print_circle(int n, int* C, int cur){// assume cur start from 1
    if(cur == n){
        bool ok = false;
        for(int i = 0; i < primenum; i++){
            if(C[cur-1]+1 == primes[i]){ 
                ok = true;
                break;
            } 
        }
        if(ok) 
            for(int i = 0; i < cur; i++) {
                if(i != cur-1) cout << C[i] << " ";
                else cout << C[i] << "\n";
            }
        return;
    }
    for(int i = 0; i < primenum; i++){
        int curNum = primes[i] - C[cur-1];
        if(curNum > 0 && curNum <= n){
            bool foundSame = false;
            for(int j = 0; j < cur; j++)
                if(curNum == C[j]) {
                    foundSame = true;
                    break;
                }
            if(!foundSame){
                C[cur] = curNum;
                print_circle(n, C, cur+1);
            }
        }
    }
}
int main(){
    int n, caseNum = 0;
    while(cin >> n){
        caseNum++;
        C[0] = 1;
        if(caseNum > 1) cout << "\n";
        cout << "Case " << caseNum << ":\n";
        print_circle(n, C, 1);
        // cout << "\n";
    }
}