#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#define For(i, e) for(i = 0; i < (e); i++)
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
const int maxHashNum = 5000;
const int maxStateNum = 8000001;
int d, dx, dxa;
typedef int State[4];
int V[3];
State st[maxStateNum];
int head[maxHashNum], nexts[maxStateNum];
// 几点提示
// 1. 注意看题目的输出要求，输出要求中不只是格式要求，还会有算法约束，比如这道题的题干里没说找到最小倒水量，但是在输出中讲了
// 2. 这道题由于没看到”最小倒水量“，因此误认为到达d的操作步数最少的路径即可（无来由假设）
// 3. 由于bfs的书写只能按照每次操作写，因此先到达d的状态未必是倒水量最小路径，一开始是用三个杯子的水量作为状态的唯一标识
// 也就是三杯水量一致的状态即被拒绝进入bfs队列，实际上，即使三个杯子的水量一致，如果新的状态的倒水量小于旧状态的倒水量，则仍应让
// 新状态进入bfs队列（同时，要更新状态数组中对应状态的倒水量）
// 4. 由于后面尝试的路径可能更优，因此必须等bfs尝试完所有可能后，才能得到正确的结果，而不能中途返回
// 启发：每步含权（此题是倒水量）时，bfs探索路不按照最短路走，因此要允许后尝试的更小权路线踩已经访问过的地方
//（其影响就是，只有到bfs完全结束才能确定最优路径）
void init(){
    int i;
    For(i, maxHashNum){
        head[i] = 0;
    }
    dx = 0;
    dxa = -1;
}
int myhash(int s){
    int v = 0, i;
    For(i, 3){
        v = v * 1000 + st[s][i];
    }
    return v%maxHashNum;
}
bool tryInsert(int s){
    int h = myhash(s);
    int u = head[h];
    bool found = false;
    while(u){
        if(st[u][0] == st[s][0] && st[u][1] == st[s][1] && st[u][2] == st[s][2]) {
            found = true;
            break;
        }
        u = nexts[u];
    }
    if(found){
        if(st[s][3] < st[u][3]){
            st[u][3] = st[s][3];
            return true;
        }else{
            return false;
        }
    }
    nexts[s] = head[h];
    head[h] = s;
    return true;
}
void bfs(){
    int front = 1, rear = 2;//用序号区间内的数组代表队列
    while(front < rear){
        int i;
        // 六种操作方式 i -> j倒
        For(i, 3){
            if(st[front][i] <= d && st[front][i] >= dx){
                // cout << "dx = " << dx << " <- st = " << st[front][i] << " with a = " << st[front][3] << "\n";
                if(st[front][i] > dx){
                    dx = st[front][i];
                    dxa = st[front][3];
                }else if(st[front][i] == dx){
                    if(dxa == -1 || st[front][3] < dxa) dxa = st[front][3];
                }
            }
        }
        
        For(i, 3){
            int j;
            For(j, 3){
                if(i == j) continue;
                int k;
                For(k, 3) st[rear][k] = st[front][k];
                if(st[front][i]){//i只要有水就可以倒
                    if(st[front][i] > V[j] - st[front][j]){//j满
                        st[rear][j] = V[j];
                        st[rear][i] = st[front][i] - (V[j] - st[front][j]);
                        st[rear][3] = st[front][3] + V[j] - st[front][j];
                    }else{//i空
                        st[rear][i] = 0;
                        st[rear][j] = st[front][j] + st[front][i];
                        st[rear][3] = st[front][3] + st[front][i];
                    }
                    if(tryInsert(rear)) rear++;
                }
            }
        }
        front++;
    }
    return;
}
int main(){
    int i, t;
    cin >> t;
    For(i, t){
        init();
        // 由于哈希表中0号状态代表了链表的结束，有效状态编号从1开始
        cin >> V[0] >> V[1] >> V[2] >> d;
        st[1][0] = st[1][1] = 0;
        st[1][2] = V[2];
        st[1][3] = 0;
        tryInsert(1);
        bfs();
        cout << dxa << " " << dx << "\n";
        
    }
}