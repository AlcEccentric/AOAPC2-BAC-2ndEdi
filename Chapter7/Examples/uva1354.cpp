#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include <stack>
#include <iomanip>
#define For(i, e) for(i = 0; i < (e); i++)
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
// 这道题我是比较服气的
// 1. 一开始按刘汝佳说的自底向上每次任选两个重量组成节点进行枚举生成树，之后自顶向下统计每个节点的位置，计算每棵树的最大宽度，但是TLE，
// 对于6个节点的情况 ，能生成8万棵树，每棵树要遍历11个节点，如果有100个输入，计算量接近亿，实际运行要十几秒
// 2. 后来按照刘汝佳说的，自顶向下用子集补集的方法生成树，用记录节点位置的方式，计算宽度
// 发现一来还是超时，二来如果是用记录节点位置的方法计算宽度，很难一边生成一边计算宽度，如果生成所有的树之后再遍历每一棵树统计节点位置
// 那么运算量并不比第一种方法少
// 3. 后来查了网上的做法，一种好像是相互抄袭的做法是，枚举二叉树数组（不是二叉树）的每个点，但是读了代码觉得完全是歪门邪道，
// 递归函数复杂且难理解，很难想象一群人能不约而同想到这么tricky的算法，严重怀疑这些人是相互借鉴，而且该方法还是自顶向下
// 遍历每一棵树确定节点位置计算宽度
// 4. 最后在网上找到一种算法，想法是很自然，就是枚举子集，但是人家怎么没有超时呢，看了之后发现最关键的在于计算宽度的方法
// 该方法用的并不是记录每个节点的位置，而是记录每个生成的子树的对应向左向右能延伸的可能的距离，
// 注意这俩方法的区别，记录每个节点的位置，需要上层节点位置确定之后才能确定，而记录子树左右可能延伸距离并不需要上层节点信息
// 有了这个区别，如果一颗子树和另一颗枚举子树所用到的挂坠完全一样，那么可以跳过后面这次枚举，因为已经处理过该子树
// 5. 不过刘汝佳的代码里写着是确定每棵树和每个节点的位置，如果是确定树之后计算每棵树的宽度，我很好奇他是如何缩减树的个数的
// 于是去看了刘汝佳的代码。。。发现人家根本用的也不是记录位置，也是计算左右延伸距离，所以他书上所谓的对于每一棵确定的树，
// 每个节点的位置就能确定是在逗我吗。。。

// 启发1：减少解答树节点的关键可能不仅仅取决于枚举过程本身，对枚举结果的处理方式也会影响枚举量的多少，比如这道题，如果是确定所有
// 节点位置计算宽度这样的方法，那么解答树就需要走到底，除非使用非常tricky的方法才能减少解答树大小，但依然需要枚举所有可能的树，
// 而如果使用统计左右可能延伸长度的方法计算宽度，则一些子树就不会被重复枚举。。
// 当然刘汝佳说的简单枚举所有的树再自顶向下计算位置显然是他自己想了想觉得每个输入最多8万个树不算多，但是如果测试输入样例很多，还是会超时，严重怀疑刘没有尝试这种简单方法

// 启发2：两种位运算技巧，一种是求二进制1的个数，一种是如何求二进制子集的子集(注意位运算符的优先级较小，保险起见位运算时加括号)
// 2.1 n&(n-1) 的作用是消去n最右侧的1，若令n=n&(n-1)，重复进行该运算到n=0，统计次数即可知道n的二进制表达有几个零
// 2.2 i = n; i !=0; i = (i-1)&n 可以计算n的二进制集合中的所有子集，枚举子集n的子集就需要忽略0，对n中的1进行消去保留的操作：
//     i-1的作用是使i最后一个1变为0，该1右边的0（如果有的话）都变成1，这样第一次与操作消掉了n的最右侧0，
//     第二次，i为n消掉了最右侧1的结果，i-1使得最右第二个位置的1变为0，右侧全为1，这样与操作得到的结果消掉n的最右第二个0，但恢复了n最右侧的0
//     第三次，i为n消掉了最右第二个1的结果，i-1使得原来n的最右侧1再次变为0，其右侧全1， 与操作结果就成了n消掉最右侧第一个和第二个1的结果
//     第四次，就会消掉最右第三个1，恢复最右侧两个1，以此类推

// 注意：一开始写的时候默认根节点不为叶节点了（全集有多个个挂坠）
// 107行处理了非叶节点为根节点时对maxWid的更新，
// 因此在递归函数的开始，处理叶子节点的部分也应该有对叶子节点为根节点时对maxWid的处理
const int maxSubNum = 70;
double rwid, maxWid;
int wNum, vis[maxSubNum], uniset;
int wOfSub[maxSubNum], weights[8], count1[maxSubNum];
vector<double> leftLens[maxSubNum];//存放每个子树左侧可能延伸长度
vector<double> rightLens[maxSubNum];//同上
void init(){
    int i;
    maxWid = -1;
    For(i, maxSubNum){
        wOfSub[i] = 0;
        count1[i] = 0;
        vis[i] = 0;
        leftLens[i].clear();
        rightLens[i].clear();
    }
}
void printBin(int b){
    stack<int> x;
    while(b){
        x.push(b%2);
        b/=2;
    }
    while(x.size()){
        cout << x.top();
        x.pop();
    }
    cout << "\n";
};
void dfs(int subset){
    // cout << "cur sub set: ";
    // printBin(subset);
    // cout << "cur subset = " << subset << "\n";
    if(vis[subset]) return; // 如果该subset对应的子树已经计算过左右延伸，返回
    vis[subset] = 1;//标记该节点已经处理过或正在处理，没有必要再次处理
    if(count1[subset] == 1){ // 如果当前子集代表的是叶子节点
        leftLens[subset].push_back(0);
        rightLens[subset].push_back(0);
        if(subset == uniset) //注意，别漏了叶子节点为全集时对maxWid的处理
            maxWid = 0;
        return;
    }
    // 如果当前子集代表非叶节点
    for(int l = subset; l; l = (l-1) & subset){
        if(l == subset || l == 0) continue;
        int r = subset ^ l;
        dfs(l); dfs(r); // 如果左/右没有处理，则处理并获取左右延伸长度;
        double cL = (double)wOfSub[r]/wOfSub[subset], cR = (double)wOfSub[l]/wOfSub[subset];
        int i, j;
        For(i, leftLens[l].size()){//遍历左侧节点的可能延伸长度对
            For(j, leftLens[r].size()){//遍历右侧节点的可能延伸长度对
                double lL = leftLens[l][i], lR = rightLens[l][i];
                double rL = leftLens[r][j], rR = rightLens[r][j];
                double tL = max(-cR + rL, cL + lL);
                double tR = max(cR + rR, -cL + lR);
                // printBin(subset);
                // cout <<"tL(" << tL << ") + tR(" << tR << ") = " << tL+tR << " rwid: " << rwid <<"\n";
                if(tL + tR > rwid) continue;
                // 否则，为当前子集找到范围内的一个左右延长长度对（tL, tR）
                leftLens[subset].push_back(tL);
                rightLens[subset].push_back(tR);
                if(subset == uniset){//如果非叶节点是全集，更新maxWid（根部）
                    if(tL + tR > maxWid) maxWid = tL + tR;
                }
            }
        }
    }
}
int main(){
    int i, t;// 用宏表达循环头时，由于需要新的循环变量时需要在循环外声明，因此容易忘记在内部使用和外循环不同的循环变量
    cin >> t;
    For(i, t) {
        cin >> rwid >> wNum;
        init();
        int j;
        For(j, wNum){
            cin >> weights[j];
        }
        
        For(j, (1<<wNum)){
            int k;
            For(k, wNum){
                if((1<<k) & j) wOfSub[j] += weights[k];
            }
            int count = 0, n = j;
            while(n){
                n = (n-1)&n;
                count++;
            }
            count1[j] = count;
        }
        uniset = (1<<wNum)-1;
        dfs(uniset);// 调用该函数后，该子树的向左向右的可能延伸对都在leftLens和rightLens的对应向量里
        if(maxWid < 0)
            cout << maxWid << "\n";
        else
            cout << fixed << setprecision(12) << maxWid << "\n";
    }
}