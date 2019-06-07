#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
using namespace std;
// uva 11059 commit 注释写错了懒得改了
// ifstream cin("test.in");
// ofstream cout("test.out");
long long nums[20];
int main(){
    int n;
    int caseNum = 0;
    while(cin>>n){
        long long maxp = 0;
        for (int i = 0; i < n; i++){
            cin >> nums[i];
        }
        caseNum++;
        for (int sublen = 1; sublen <= n; sublen++){
            for (int startp = 0; startp <= n - sublen ; startp++){
                long long res = nums[startp];
                for (int i = 1; i < sublen; i++){
                    res *= nums[startp + i];
                } 
                if(res > maxp) maxp = res; 
            }  
        }
        cout << "Case #"<< caseNum << ": The maximum product is "<< maxp << ".\n\n";
        
    }
}