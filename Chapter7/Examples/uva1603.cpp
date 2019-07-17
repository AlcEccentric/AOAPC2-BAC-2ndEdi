#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <set>
#define For(i, n) for(i=0; i<n; i++)
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
int testCaseNum, m, n, ans;
bool completeSquare(set<int>& rest, int startX, int startY, int len){
    
}
bool noSquare(set<int>& rest){
    int len, startX, startY;
    For(len, n){
        For(startX, n){
            For(startY, n){
                if(completeSquare(rest, startX, startY, len)){
                    return false;
                }
            }
        }
    }
    return true;
}
bool findAns(set<int>& rest, int restCubeNum, int maxd, int d){
    int restStepNum = maxd - d;
    if(restStepNum * 2 < restCubeNum) return false;
    for(set<int>::iterator ii = rest.begin(); ii != rest.end(); ii++){
        int takenM = *ii, restSquareNum;
        rest.erase(takenM);
        if(noSquare(rest, restSquareNum)){
            ans = n * n - m - rest.size();
            return true;
        }else{
            if(findAns(rest, restSquareNum, maxd, d + 1)) return true;
        }
        rest.insert(takenM);
    }
    return false;
}
int main(){
    fin >> testCaseNum;
    while(testCaseNum--){
        fin >> n;
        fin.ignore();
        int i;
        ans = 0;
        set<int> nums, taken;
        fin >> m;
        For(i, m){
            int x;
            fin >> x;
            nums.insert(x); 
        }
        // 1. 数当前火柴图中，各个边长的正方形数，用于估计函数
        int row = 2 * n + 1, desNum, totalMNum = n * (n + 1) * 2, cubeNum = n * n;
        fout << "original square num: " << cubeNum << "\n";
        for(set<int>::iterator ii = nums.begin(); ii != nums.end(); ii++){
            desNum = 2;
            // fout << "take away " << *ii;
            if(*ii % row <= n){//横着
                int up = *ii - row, down = *ii + row;
                int leftD = *ii + n, rightD = *ii + n + 1;
                int leftU = *ii - n - 1, rightU = *ii - n;
                if(up <= 0){
                    desNum--;
                    if(taken.count(down) || taken.count(leftD) || taken.count(rightD)){
                        desNum--;
                    }
                }else if(down > totalMNum){
                    desNum--;
                    if(taken.count(up) || taken.count(leftU) || taken.count(rightU)){
                        desNum--;
                    }
                }else{
                    if(taken.count(up) || taken.count(leftU) || taken.count(rightU) || taken.count(down) || taken.count(leftD) || taken.count(rightD)){
                        desNum--;
                    }
                }
            }else{//竖着
                int left = *ii - 1, right = *ii + 1;
                int leftD = *ii + n, rightD = *ii + n + 1;
                int leftU = *ii - n - 1, rightU = *ii - n;
                if(left <= 0){
                    desNum--;
                    if(taken.count(right) || taken.count(rightD) || taken.count(rightU)){
                        desNum--;
                    }
                }else if(right > totalMNum){
                    desNum--;
                    if(taken.count(left) || taken.count(leftD) || taken.count(leftU)){
                        desNum--;
                    }
                }else{
                    if(taken.count(left) || taken.count(leftU) || taken.count(rightU) || taken.count(right) || taken.count(leftD) || taken.count(rightD)){
                        desNum--;
                    }
                }
            }
            // fout << " destroy " << desNum << " cubes\n";
            cubeNum -= desNum;
            taken.insert(*ii);
        }    
        fout << "cube num = " << cubeNum << "\n";
        // 2. 用迭代加深搜索（深度最多为所有正方形个数和） 
        int maxn = totalMNum;
        set<int> rest;
        For(i, n*n)
            if(!taken.count(i+1)) rest.insert(i+1);
        
        For(i, maxn){
            if(findAns(rest, cubeNum, i, 0)){
                break;
            }
        }
    }
}