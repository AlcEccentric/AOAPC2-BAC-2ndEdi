#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <vector>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
// 根据y < x, k >= 1，显然有0 < 1/x <= 1/2k <= 1/y < 1 
// 1/2k <= 1/y可以得到 y <= 2k
// x = k*y/y-k 而 x > 0 可以得到 y > k
// 因此y的枚举范围是k+1 - 2k(当然枚举题的前提是先判断问题大小可以枚举，比如这道题的k只有10000)
int main(){
    int k;
    while(cin >> k){
        vector<int> ys;
        for (int y = k + 1; y <= 2*k; y++)
        {
            int ky = k * y;
            if(ky%(y-k) == 0){
                ys.push_back(y);
            }
            
        }
        cout << ys.size() << "\n";
        for (auto y : ys){
            cout << "1/" << k << " = 1/" << k*y/(y-k) << " + 1/" << y << "\n";
        }

    }
}