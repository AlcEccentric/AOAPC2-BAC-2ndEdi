#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <set>
// 暴力枚举也是需要尽可能想办法减少枚举个数的
// 尝试缩小可能的解空间很重要，
// 比如这道题的解空间的初始界为0-9的所有排列（数量级百万）
// 1. 通过分析，abcde or fghij也得是从0-9中选取的5个不同的数的排列
// 于是解空间从A(9, 9)变成了 A(9, 5)数量级少了两个0，数量级变万
// 同时当fghij * n > 98765后也可以停止枚举
// 2. 网上也有从1000枚举到100000的，这个就是稍微简单思考缩小的解空间，数量级变万
// 3. 这里是考虑到abcde最大98765，因此fghij最大为98765/n,只需枚举1000-98765/n之间的数 
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
int main(){
    int n;
    int casenum = 0;
    while(1){
        cin >> n;
        casenum++;
        if(n == 0) break;
        if(casenum != 1) cout << "\n" ;
        int range = 98765 / n + 1;
        bool hasSolution = false;
        for (int i = 1000; i < range; i++){
            int fghij = i;
            int abcde = fghij * n;
            set<int>nums;
            int cpabcde = abcde, cpfghij = fghij;
            for (int j = 0; j < 5; j++){
                nums.insert(abcde%10);
                abcde /= 10;
            }
            if(nums.size() == 5){
                for (int j = 0; j < 5; j++){
                    nums.insert(fghij%10);
                    fghij /= 10;
                }
                if(nums.size() == 10){
                    hasSolution = true;
                    if(cpabcde < 10000) cout << "0";
                    cout << cpabcde << " / ";
                    if(cpfghij < 10000) cout << "0";
                    cout << cpfghij << " = " << n << "\n";
                }
            }       
        
        }
        if(!hasSolution) cout << "There are no solutions for " << n << ".\n";
    }
    
}