#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
long long nums[20];
int main(){
    int n;
    int caseNum = 0;
    while(fin>>n){
        long long maxp = 0;
        for (int i = 0; i < n; i++){
            fin >> nums[i];
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
        fout << "Case #"<< caseNum << ": The maximum product is "<< maxp << ".\n\n";
        
    }
}