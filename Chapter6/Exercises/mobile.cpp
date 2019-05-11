#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <queue>
#include <map>
#include <set>
// #decine debug
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
// 注意：
// 遇到那种输入树的可能节点可能上百万乃至过亿的题目，一般是不会先将树静态存储下来的
// 一般是一边递归读入树结构，一边处理计算，因为递归建树也是一个先自顶向下后自底向上的过程
// 因此一般的只需要两侧子树的算法基本都可以递归读树的同时，进行数据处理
// 算法思想：
// 一开始看错条件，以为只能是变成整数值，如果只能用整数替换砝码的话，
// 由于要考虑整除的问题，所以只能是层次浅的子树的叶子重量改变，以平衡层次深的子树的重量
// 如果换成可以是非整数的重量，那么就没有必须那一侧改变去平衡另一侧的选择
// 在叶子可变为任意重量的情况下，
// 当两侧子树重量不同时，可以左边变得和右边一样重，可以右边变得和左边一样重
// 两种情况都要记下，如果左变为右，则需要变化左侧叶子数+右侧传上来的变化数
// 另一种情况相反
// 如果两侧子树的重量一样，则无需变化，直接将右侧传来的变化数和左侧传上来的变化数加和传向上一级
// 每一个传到上一层的变化数对应一个变化后的节点重量，如果左变为右，则重量为两倍的右侧重，反之亦然
// 如果两侧重量一样则上传的重量是两侧重量的和
long doBalance(map<long, long>&wtob){
    if(cin.peek() != '['){// leaf
        long w;
        cin >> w;
        wtob[w] = 0;
        return 1;
    }
    char c;
    cin.get(c);// ignore [
    map<long, long> rightWtoB, leftWtoB;
    long leftLNum = doBalance(leftWtoB);
    cin.get(c);// ignore ,
    long rightLNum = doBalance(rightWtoB);
    cin.get(c);// ignore ]
    #ifdef debug
    cout << "leftWs: ";
    for(auto x : leftWs) cout << x << " "; 
    cout << " rightWs: ";
    for(auto x : rightWs) cout << x << " "; 
    cout << "\nleftD = " << leftLNum << " rightD = "<< rightLNum << endl;
    cout << "leftBNum = " << leftBNum << " rightBNum = "<< rightBNum << endl;
    #endif
    for(map<long, long>::iterator p = rightWtoB.begin(); p != rightWtoB.end(); p++){
        if(leftWtoB.count(p->first)){
            wtob[p->first*2] = p->second + leftWtoB[p->first];
        }else{
            // 左变右不变
            wtob[p->first*2] = p->second + leftLNum;
        }
    }
    for(map<long, long>::iterator p = leftWtoB.begin(); p != leftWtoB.end(); p++){
        if(!rightWtoB.count(p->first)){
            // 右变左不变
            wtob[p->first*2] = p->second + rightLNum;
        }
    }
    return leftLNum + rightLNum;
}

int main(){
    long caseNum = 0;
    cin >> caseNum;
    cin.ignore();
    for (long i = 0; i < caseNum; i++)
    {  
        long minBNum = -1;
        map<long, long> wTob;
        doBalance(wTob);
        cin.ignore();
        for (map<long, long>::iterator p = wTob.begin(); p != wTob.end(); p++){
            if(minBNum == -1) minBNum = p->second;
            else minBNum = p->second < minBNum ? p->second : minBNum;
        }
        cout << minBNum << endl;
    }
    
}