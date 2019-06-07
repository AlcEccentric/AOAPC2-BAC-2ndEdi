#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <time.h> 
#include <algorithm>
#include <set>
#define testBasic 0
#define testAdv 1
#define testNext 1
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
// 该文件实现了7.2节的几种产生字典序排列的方法
// 方法一:
// 递归法，该方法又分无重复元素排列算法和重复元素排列
// 方法二：
// algorithm 的 next_permutation
int P[10];//存放待排序元素，假设元素的个数为n(n <= 10)
int A[10];//存放排序
void print_permute_basic(int n, int* P, int* A, int cur){
    if(cur == n){
        for (int i = 0; i < cur; i++)
            fout << A[i];
        fout << "\n";
    }else{
        for (int i = 0; i < n; i++){
            bool hasUsed = false;
            for (int j = 0; j < cur; j++){
                if(P[i] == A[j]){
                    hasUsed = true;
                    break;
                }
            }
            if(!hasUsed){
                A[cur] = P[i];
                print_permute_basic(n, P, A, cur+1);
            }
            
        }
    }

}
void print_permute_adv(int n, int* P, int* A, int cur){
    if(cur == n){
        for (int i = 0; i < cur; i++)
            fout << A[i];
        fout << "\n";
    }else{
        for (int i = 0; i < n; i++){
            if(!i||P[i]!=P[i-1]){
                int hasUsedTime = 0, totalTime = 0;
                for (int j = 0; j < cur; j++)
                    if(P[i] == A[j]) hasUsedTime++;
                for (int j = 0; j < n; j++)
                    if(P[i] == P[j]) totalTime++;
                if(hasUsedTime < totalTime){
                    A[cur] = P[i];
                    print_permute_adv(n, P, A, cur+1);
                }
            }            
        }
    }
}
int main(){
    srand((unsigned)time(NULL));
    int n = 5;
    // 生成无重复元素的待排序集合
    set<int> norepeat;
    for (int i = 0; i < n; i++){
        int r;
        do{
            r = (int)rand() % 10;
        }while(norepeat.count(r));
        norepeat.insert(r);
        P[i] = r;
    }
    // sort to get ordered permutation
    sort(P, P+n);
    #if testBasic
    fout << "nums for basic permutation: \n";
    for (int i = 0; i < n; i++)
        fout << P[i] << " ";
    fout << "\n";
    print_permute_basic(n, P, A, 0);
    #endif
    //生成可能有元素重复的待排序集合
    for (int i = 0; i < n; i++)
        P[i] = (int)rand() % 10;
    // sort to get ordered permutation
    sort(P, P+n);
    #if testAdv
    fout << "nums for adv permutation: \n";
    for (int i = 0; i < n; i++)
        fout << P[i] << " ";
    fout << "\n";
    print_permute_adv(n, P, A, 0);
    #endif
    #if testNext
    fout << "nums for next permutation: \n";
    for (int i = 0; i < n; i++)
        fout << P[i] << " ";
    fout << "\n";
    do{
        for(int i = 0; i < n; i++)
            fout << P[i];
        fout << "\n";
    }while(next_permutation(P, P+n));
    #endif
}