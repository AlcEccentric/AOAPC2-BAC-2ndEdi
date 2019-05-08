#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <climits>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
int m, n, k;
int minSteps;
int field[25][25], vis[25][25];
// 这道题其实直接用带条件的bfs就行，条件是不能连续穿k个障碍物，这个实现起来比较简单，
// 记录每个点上走过的连续障碍物，如果下一步超过k则不放入队列
// 由于读到一篇面经说dfs也可以求最短路，因此在这里写的是dfs求最短路的方法
// 这里记一下dfs求最短路和bfs求带权最短路的方法
// dfs求最短路：（不论是否带权dfs求最短路的方法一致）
// 用一个值记录已经取得的最短路权值/长度 minw
// 每次走到一个点
// 如果当前步数/权和大于 minw，则返回false（认为这一步没走，并且这条路无法成为最短接）
// 如果符合其他不能走条件，则返回false(意义同上)
// 如果当前节点是终点，如果当前权更小，则更新minw，最终节点直接返回true即可
// 标记当前节点走过，并且试探周围节点是否合法 &&（没走过 || 走过但是之前走过这个节点时的权值/步数大于当前权值/步数相应增加后的值）
// 如果满足条件则递归调用dfs，四个方向的dfs函数返回结果的或作为当前dfs的返回值
// 如果还要求记录路径，除了minw还要加一个minRoute的栈保存路径节点，一个route栈动态记录路径节点的变化
// 则dfs函数的最开始对节点压栈，return前弹出，当minw被更新时，清空已有的minRoute，将route的内容复制到minRoute
// bfs求最短路：
// 如果只是求边数最小的路，就是最基本的bfs
// 如果是要求权值最小的路，在决定是否将下一个节点加入队列时
// 除了没访问过的可以加入队列，访问过的但是之前到达这个节点时的权值比当前权值增加后的对应值大的节点也应该被放进队列
// 如果能访问到终点，则返回true
// 记录路径的话还是一样，每次按照标准选定了下一个节点放进队列前，设置其父亲节点，然后最后从终点向回走即可
struct node{
    int x,y;
};
void init(int x[25][25], int value){
    for (int i = 0; i < 25; i++)
        for (int j = 0; j < 25; j++)
            x[i][j] = value;
}
void dodfs(int nM, int nN, int stepNum, int objNum, bool & res);
bool dfs(int curM, int curN, int stepNum, int objNum){
    if(objNum > k) return false;
    if(stepNum >= minSteps) return false;
    if(field[curM][curN] == -1) return false;
    if(curM == m && curN == n){
        minSteps = stepNum;
        return true;
    }
    vis[curM][curN] = stepNum;
    // cout << "[" << curM << "," << curN << "] obj:"<< objNum <<"\n";
    bool res = false;
    int nM, nN;
    nM = curM+1, nN = curN;
    dodfs(nM, nN, stepNum, objNum, res);
    nM = curM-1, nN = curN;
    dodfs(nM, nN, stepNum, objNum, res);
    nM = curM, nN = curN+1;
    dodfs(nM, nN, stepNum, objNum, res);
    nM = curM, nN = curN-1;
    dodfs(nM, nN, stepNum, objNum, res);
    return res;
}
bool valid(int M, int N){
    return M <= m && M >= 1 && N <= n && N >= 1;
}
void dodfs(int nM, int nN, int stepNum, int objNum, bool & res){
    if(valid(nM, nN) && (!vis[nM][nN] || stepNum < vis[nM][nN])){
        // cout << "nM = " << nM << " nN = " << nN << endl;
        if(field[nM][nN]){
            // cout << "obj wiil add one" << endl;
            res |= dfs(nM, nN, stepNum+1, objNum+1);
        }else{
            // cout << "clear obj" << endl;
            res |= dfs(nM, nN, stepNum+1, 0);
        }
    }
}
int main(){
    int caseNum;
    cin >> caseNum;
    for (int i = 0; i < caseNum; i++)
    {
        minSteps = INT_MAX;
        cin >> m >> n >> k;
        init(field, -1);
        init(vis, 0);
        for (int j = 1; j <= m; j++){
            for (int k = 1; k <= n; k++){
                cin >> field[j][k];
            }
        }
        bool res = false;
        if(field[1][1] == 1)
            res = dfs(1, 1, 1, 1);
        else    
            res = dfs(1, 1, 1, 0);
        
        if(res) cout << minSteps - 1 << endl;
        else cout << -1 << endl;

        

    }
    
}