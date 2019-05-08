#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <set>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
// well，这道题将问题抽象成图的思想和之前那个顺着单词一笔画的题目类似，
// 尽管将问题抽象成图的思想是类似的，但是在图上进行的算法是不一样的。
// 此题的目标是找到一种拼接方式，这种方式是从某种元素一直拼接下去，在后面的某个位置再次用到那种元素
// 由于每一种元素有无数个，因此只要形成循环拼接序列，就可以无限拼接下去，也即目标是要找到拼接元素形成的环
// 找环的话，之前那个DFS拓扑排序就能找到环
// 思想就是把元素的边界（比如这里离子的正负电荷，单词的首尾字母）看作图中的点，而把元素本身看成是图中的边
// 这道题有个特殊的地方在于，边所连接的是不同元素的边界上的点，而不是同一个元素的边界上的点
// 在单词那道题目中，有向边是单词本身，首字母是边起点，尾字母是边终点
// 在这道题中，当前元素边界的字母是有向边的起点，而潜在的相邻元素的相邻边的字母是终点，即终点不在当前元素，而在相邻元素的相邻边上

void init(int G[60][60]){
    for(int i = 0; i < 60; i++)
        for(int j = 0; j < 60; j++)
            G[i][j] = 0;
}
void init(int * x){
    for(int i = 0; i < 60; i++)
        x[i] = 0;
}
int getInd(char a, char b){
    if(a == '0' && b == '0') return -1;
    int ret = (a - 'A') * 2;
    if(b == '+') ret += 1;
    return ret;
}
bool dfscindLoop(int cur, int G[60][60], int * vs){
    vs[cur] = -1;
    for(int i = 0; i < 52; i++)
    {
        if(G[cur][i]){
            if(vs[i] == -1) return true;
            else{
                if(dfscindLoop(i, G, vs)) return true;
            } 
        }
    }
    vs[cur] = 1;
    return false;
}
bool cindLoop(const set<int>& entries, int G[60][60], int * vs){
    for(set<int>::iterator ii = entries.begin(); ii != entries.end(); ii++){
        if(vs[*ii] == 0){// not visited
            if(dfscindLoop(*ii, G, vs)) return true;
        }
    }
    return false;
}
int main(){
    int molNum;
    while(cin >> molNum){
        int G[60][60];
        init(G);
        set<int> entries;
        while(molNum){
            string mol;
            cin >> mol;
            int oriInd[4];
            int revInd[4];
            for(int i = 0; i < 8; i += 2)
            {
                char a = mol[i];
                char b = mol[i+1];
                int ind = getInd(a, b);
                int rev = 0;
                if(ind >= 0){
                    if(ind%2) rev = ind - 1;
                    else rev = ind + 1;
                    entries.insert(ind);
                }else rev = ind;
                oriInd[i/2] = ind;
                revInd[i/2] = rev;
            }
            // fill graph
            for(int i = 0; i < 4; i++){
                if(oriInd[i] >= 0){
                    for(int j = 0; j < 4; j++)
                    {
                        if(j != i && revInd[j] >= 0){
                            G[oriInd[i]][revInd[j]] = 1;
                        }
                    }
                    
                }
            }
            
            molNum --;
        }
        int vs[60];
        init(vs);
        if(cindLoop(entries, G, vs)) cout << "unbounded" << endl;
        else cout << "bounded" << endl;

    }
}