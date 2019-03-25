#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
// NOTE:
// 尽管这道题是例题，也就是看了分析写的，还是记录下收获
// 1. 模拟题的计算量
// 有些题看上去似乎是模拟题（不是那种一眼看上去就能90%确定的模拟题），实际上可能需要一些特殊的算法
// 判断是否应该用模拟的方法去做的方法是，假设输入极大，计算所需的计算量判断用纯模拟的方法是否超时
// 比如这道题，假设输入的树深D为20，I为2^19，
// 则需要一个 size = 2^20-1 的大数组
// 对于每个球要模拟19次移动，一共要模拟19*2^19这么次移动，2^10 = 1024，则对于一个test case最多可能需要10000000次移动
// 一共最多有1000组test case，最多可能需要模拟10000000000（100亿）次移动
// 第一，三秒的时间限制不可能允许这么多次移动的模拟(哪怕是加法，上亿次加法也会超时)
// 第二，根据刷题经验，接近一亿次操作的算法基本上是错误做法
// 基于以上两点可以初步判断模拟几乎不可能
// 2. 二叉树是一种非常有规律可循的数据结构
// 基于数组实现的二叉树有个很有用并且经常被利用的性质就是：当前k号节点的左孩子是2k右孩子是2k+1
// 对于这种暗示做题者要按一定规律自顶向下寻找二叉树中路径的问题，上述性质应该第一个被利用起来
int main(){
    
    
    int n;
    cin >> n;
    while(n){
        int D, I;
        cin >> D >> I;
        int noToThisNode = I;
        int nextNodeNo = 1;
        int judgeTime = 0; // when judge time == D - 1, exit;

        while(judgeTime != D - 1){
            if(noToThisNode%2 == 0){ // right
                nextNodeNo = nextNodeNo * 2 + 1 ;
                noToThisNode = noToThisNode / 2;
            }
            else{ // left
                nextNodeNo = nextNodeNo * 2;
                noToThisNode = noToThisNode / 2 + 1;
            }
            judgeTime ++;
        }

        cout << nextNodeNo << endl;
        n--;
    }

}