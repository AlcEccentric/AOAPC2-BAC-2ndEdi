#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <queue>
#include <stack>
#include <vector>
using namespace std;
const int MAXN = 1005;
ifstream fin("test.in");
ofstream fout("test.out");
// 这道题差不多是刷题到现在卡得最久的题目了。。。
// 这道题的关键在于确定怎样的情况dfs前后两个节点是只能看成父子关系的（即那些只能被算作父子关系的情况）
// 算法使用栈模拟了dfs的过程：
// 1. 根节点入栈
// 2. 当前节点是栈顶节点的孩子则入栈（向下探索）
// 3. 当前节点不是栈顶节点的孩子，则栈弹出（向上回溯）直到栈顶再次是当前节点的父亲，入栈
// 然后轮到下一个节点

// 以下是关于“确定怎样的情况dfs前后两个节点只能看成父子节点”的分析
// 设dfs(x)代表x在dfs里的次序，bfs(x)代表x在bfs里的次序
// if bfs(y) = bfs(x) + 1 则y 1：是x的孩子节点 2：是x的第一个后兄弟 3：是x的前兄弟的孩子
// if dfs(y) = dfs(x) + 1 则y 1:是x的孩子节点 2：是x的第一个后兄弟 3：什么都不是（父亲级别之上的关系）
// 
// 所以当dfs(y) = dfs(x) + 1根据bfs()值可将节点分为以下几种
// if bfs(y) < bfs(x) y在父亲及以上的层，忽略
// if bfs(y) = bfs(x) + 1 and y > x 有两种可能：只能当成x的兄弟处理，既可以当成x的孩子处理又可以当成兄弟处理（注意不存在只能当成孩子处理的情况）因此在这种情况下，可以全部当成兄弟处理
// if bfs(y) = bfs(x) + 1 and y < x则只能当成x的孩子处理（不可能是x的后兄弟，后兄弟的话，y应该比x先bfs到，与bfs(y)>bfs(x)相悖）
// if bfs(y) > bfs(x) + 1 很容易证明y只能是x的孩子（另外两种情况可以证得不成立）

// 总结下来，假设y是dfs中x的下一个节点(dfs(y) = dfs(x) + 1)，则满足以下条件能够当成x孩子处理
// 1. x是根节点（根节点不存在父亲或兄弟，所以一定是孩子）
// 2. bfs(y) = bfs(x) + 1 && y < x
// 3. bfs(y) > bfs(x) + 1
// 其他情况都不能算孩子
// 而如果dfs(y) > dfs(x) + 1用类似的分析方法，也可以得出满足上述三个条件能够当成x孩子处理
int n;
int bfs[MAXN], dfs[MAXN];
vector<int> childs[MAXN];
queue<int> d;
void init(){
    while(d.size()){
        d.pop();
    }
    for(int i = 0; i < MAXN; i++){
        childs[i].clear();
    }
}
bool isChild(int root, int y, int x){
    return  x == root || 
            (bfs[y] == bfs[x] + 1 && y < x) ||
            bfs[y] > bfs[x] + 1;
}
int main(){
    while(fin>>n){
        init();
        for (int i = 0; i < n; i++){
            int num;
            fin >> num;
            bfs[num] = i;
        }
        for (int i = 0; i < n; i++){
            int num;
            fin >> num;
            d.push(num);
            dfs[num] = i;
        }
        stack<int> workspace;
        int root = d.front();
        workspace.push(d.front());
        d.pop();
        while(d.size()){
            // fout << d.front() << "\n";
            if(isChild(root, d.front(), workspace.top())){
                childs[workspace.top()].push_back(d.front());// y is x's child
                workspace.push(d.front());
                d.pop();
            }else{
                while(!isChild(root, d.front(), workspace.top())){
                    workspace.pop();
                }
                childs[workspace.top()].push_back(d.front());// y is x's child
                workspace.push(d.front());
                d.pop();
            }
        }
        for(int i = 1; i <= n; i++){
            fout << i << ":";
            for(vector<int>::iterator ii = childs[i].begin(); ii != childs[i].end(); ii++){
                fout << " " << *ii;
            }
            fout << "\n";
        }
    }
}