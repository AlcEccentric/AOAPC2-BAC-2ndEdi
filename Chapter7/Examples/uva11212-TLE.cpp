#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <queue>
#include "../../define.h"
using namespace std;
// 直接用迭代加深搜索超时了，具体的收获总结见AC版本
ifstream fin("test.in");
ofstream fout("test.out");
int paras[10], paraNum, maxd, dUpBound;
void init(){
    maxd = 0;
    dUpBound = 0;
    int i;
    For(i, 10) paras[i] = 0;
}
void getUpBound(){
    int i;
    For(i, paraNum){
        int j;
        For(j, i){
            if(paras[j] > paras[i]){
                dUpBound++;
                break;
            }
        }
    }
}
int getUnoderNum(const int* v){
    int i, count;
    For(i, paraNum){
        int j;
        For(j, i){
            if(v[j] > v[i]){
                count++;
                break;
            }
        }
    }
    return count;
}
void printP(const int *p){
    int i;
    For(i, paraNum) fout << p[i] << " ";
    fout << "\n"; 
}
void cutPaste(int len, int cutS, int pasteS, const int* p, int* v){
    queue<int> cp, rest;
    int i;
    For(i, paraNum){
        if(i >= cutS && i < cutS + len) cp.push(p[i]);
        else rest.push(p[i]);
    }
    For(i, len){
        v[pasteS + i] = cp.front();
        cp.pop();
    }
    For(i, paraNum){
        if(i < pasteS || i >= pasteS + len){
            v[i] = rest.front();
            rest.pop();
        }
    }
}

bool dfsFindAns(int d, const int* p){
    if(d == maxd){// d代表已经操作的次数
        int i;
        For(i, paraNum)
            if(p[i]!=i+1) return false;
        // fout << "correct ans\n";
        return true;
    }
    // fout << "p:";
    // printP(p);
    int i;// len 1 -> paraNum - 1
    Forr(i, 1, paraNum){
        // fout << "len = " << i << ":\n";
        int j;// startPoint 0 -> paraNum - i
        For(j, paraNum - i + 1){
            int k;// insertPoint 0 -> paraNum - i
            For(k, paraNum -i + 1){
                if(k == j) continue;
                int v[10];
                cutPaste(i, j, k, p, v);
                int aftUnOrder = getUnoderNum(v);
                if(aftUnOrder > dUpBound) continue;
                if(dfsFindAns(d+1, v)) return true;
            }
        }
    }
    return false;
}
int main(){
    int caseNum = 0;
    while(fin >> paraNum){
        caseNum++;
        if(paraNum == 0) break;
        init();
        int i;
        For(i, paraNum) {
            fin >> paras[i];
        }
        getUpBound();
        for(maxd = 0; maxd <= dUpBound; maxd++){
            // fout << "maxd = " << maxd << "\n";
            if(dfsFindAns(0, paras)) break;
        }
        fout << "Case " << caseNum <<": " << maxd << "\n";
    }    
    
}