#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
char A[85];
int k, n, hardNum;
void print_hard(int cur){
    // cout << "hard num = " << hardNum << " cur = " << cur << "\n";
    if(hardNum == k){
        for(int i = 0; i < cur; i++){
            if(i%4 == 0 && i) {
                if(i == 64) cout << "\n";
                else cout << " ";
            }
            cout << A[i];
        }
        cout << "\n" << cur << "\n";
        return;
    }else if(hardNum > k) return; // 这句话很重要，否则当hardNum大于k则递归还会继续深入，实际上不应该继续，应该直接返回
    for (int i = 0; i < n; i++){
        // A , B, A+n
        char curC = 'A' + i;
        bool ok = true;
        A[cur] = curC;
        for(int j = 1; j <= cur; j += 2){
            int s = cur - j, len = (j+1)/2;
            bool allSame = true;
            for(int k = 0; k < len; k++){
                if(A[s+k] != A[s+len+k]){
                    allSame = false;
                    break;
                }
            }
            if(allSame){
                ok = false;
                break;
            }
        }
        if(ok){
            hardNum++;
            print_hard(cur+1);
        }
    }
    
}
int main(){
    while(cin >> k >> n){
        if(k == 0 && n == 0) break;
        hardNum = 0;
        print_hard(0);
    }
}