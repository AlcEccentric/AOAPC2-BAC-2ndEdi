#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <queue>
#define For(i,e) for(i = 0; i < (e); i++)
#define Forr(i,s,e) for(i = (s); i < (e); i++)
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
// 这道题如果只是照搬迭代加深算法，并且不注意效率问题，直接就TLE
// 因此这里用的是带剪枝的迭代加深算法IDA
// 关键点就在于剪枝，即估计余下操作在最好情况下是否有可能达成目标，如果没有可能则递归返回
// 不过这道题的剪枝策略确实不好想，我怀疑网上那些代码都是参考了刘汝佳的提示的。。
// 虽然不是那么好想（至少我这种小白肯定短时间内是想不到）但是还是有所启发
// 1. 刘汝佳的剪枝策略基于这样一个认识：当且仅当数列中每一个数的后继数值为该数的值+1，则数列呈+1递增有序序列（类似链表，可能他能这么想是因为对链表很熟悉）
// 而每次cut+paste操作不论操作的具体细节（从哪剪切，剪切多长，粘贴到哪），最多只能改变序列中三个数的后续值，
// 因此，如果 当前剩余操作数 * 3 < 当前的序列中后续值错误的数的个数，则可以令当前dfs返回完成剪枝
// 结合紫书中提到的埃及分数问题，一个启发是：找到当前状态和目标状态的最乐观步数估计，如果剩余步数小于该估计则剪枝
// 因此如果迭代加深TLE，则大概率需要IDA，则需要找到当前状态与最终状态的差别和步数之间的联系点：
// 这道题是”后继值“：每一次操作都能改变一定数量的后继值，而当前状态的后继值错误个数就是和最终状态的差值
// 后继值既表明了距离终点的距离，又与每一步相关（注意，要找到的关键属性必须是和步数相关，但与该步操作内容无关的）
// 虽然后继值很难想到，但是有了"当前状态与最终状态的区别""每一步所能改变的东西"这两个目标，找到关键属性应该会轻松一些
// 1.1 当然这道题的另一个重要经验就是如何判断一个序列是否是有序序列的方法：后续值错误的数的个数为（所谓错误，指的是和排序之后的序列比较下的错误）
// 2. 使用数组比使用STL要快得多，如果可以不用STL，则尽量别用STL，毕竟STL就是为了编码偷懒，
// 比如这道题剪切粘贴操作用STL辅助处理就会TLE。当然可以先使用STL证明思路的正确，然后再根据需要改写为不带STL的版本
int paras[10];
int maxd, dUpBound, paraNum;
void init(){
    maxd = 0;
    dUpBound = 0;
    int i;
    For(i, 10) paras[i] = 0;
}
void printP(const int *p){
    int i;
    For(i, paraNum) cout << p[i] << " ";
    cout << "\n"; 
}
void getUpBound(){
    int i;
    For(i, paraNum){
        if(i + 1 != paras[i]) dUpBound++;
    }
}
int h(const int* p){
    int i, count = 0;
    For(i, paraNum-1){
        if(p[i+1]!=p[i]+1) count++;
    }
    return count;
}
void cutPaste(int len, int cutS, int pasteS, const int* p, int* v){
    int i, cur = 0;
    For(i, paraNum){
        if(i >= cutS && i < cutS + len)
            v[pasteS + i - cutS] = p[i];
        else{//p[i] is rest
            if(cur == pasteS) cur += len;
            v[cur++] = p[i];
        }
    }
    // printP(p);
    // cout << "->\n";
    // printP(v);
}
bool dfs(int d, const int* p){
    int restOpNum = maxd - d;//已经完成了d次操作，还剩下maxd - d次操作
    if(restOpNum*3 < h(p)) return false;
    if(d == maxd){// d代表已经操作的次数
        int i;
        For(i, paraNum)
            if(p[i] != i+1) return false;
        // cout << "correct ans\n";
        return true;
    }
    // cout << "p:";
    // printP(p);
    int i;// len 1 -> paraNum - 1
    Forr(i, 1, paraNum){
        // cout << "len = " << i << ":\n";
        int j;// startPoint 0 -> paraNum - i
        For(j, paraNum - i + 1){
            // cout << "cut start: " << j <<"\n";
            int k;// insertPoint 0 -> paraNum - i
            For(k, paraNum -i + 1){
                if(k == j) continue;
                // cout << "paste start: " << k <<"\n";
                int v[10];
                cutPaste(i, j, k, p, v);// d+1th op cinish
                if(dfs(d+1, v)) return true;
                
            }
        }
    }
    return false;
}
int main(){
    int caseNum = 0;
    while(cin>>paraNum){
        if(!paraNum) break;
        init();
        caseNum++;
        int i;
        For(i, paraNum) cin >> paras[i];
        getUpBound();
        for(maxd = 0; maxd <= dUpBound; maxd++){
            if(dfs(0, paras)) break;
        }
        cout << "Case " << caseNum <<": " << maxd << "\n";
    }
}