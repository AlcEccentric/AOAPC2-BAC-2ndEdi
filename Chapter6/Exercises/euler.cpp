#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <set>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
//这道题第一眼看上去是欧拉路径问题
//但是有两点阻碍，一点是存在不连通的情况
//另一点是某个连通分支内的奇点可能大于2个
//对于第一点的反应自然是最后的边数再加上（连通分支数-1）
//但是每个连通分支里不一定存在欧拉路径，每个连通分支里的边数怎么算
//于是就卡在这了，
//但是后来突然想到可以在连通分支里给奇点之间加边（每次连接一个分支的俩奇点都能使奇点数-2），使奇点数减少到2
//然后对于不连通的分支，两两之间加一条边使连通
//两步的加边数和原来的边数相加得到最后的结果
//一开始不成熟的想法是：把每个连通分支的奇点数通过加边的方法减为2，只要剩下所有分支的奇点数为2
//将两个分支各自的两个奇点中的某个奇点两两相连，得到的新分支的奇点数还是2，再去和其他分支用同样的方式相连，
//因此最后在使连通的步骤中，加的边数就是（连通数-1）
//这个想法存在顾虑和问题
//顾虑1：万一有的连通图的奇点数为奇数怎么办？
//  答：这不可能，任何图中不可能存在奇数个奇点，因为如果存在奇数个奇点，奇数个奇数相加为奇数，而剩下的全为偶点，因此总度数为奇数
//     但是图的度数必然是偶数，因为每增加一条边图的度数和会多两度，因此图的度数和必然为偶数
//     因此完全可以忽略这种情况，奇点个数一定为偶数个
//顾虑2：连接两个奇点数为2的连通分支会不会影响最后奇点数为2
//  答：不会，两个连通分别有俩奇点，从每个连通里选一个奇点，将其相连，那么相连后，每个连通里只剩下一个奇点，而此时两个连通已经算一个连通，因此新生成的连通奇点数为2不变
//问题：没有考虑连通的奇点数为0的情况
//  一开始写的是（奇点数-2）/2得到连通需要构成欧拉路所要加的最少边，
//  但是如果奇点数为0，那么这个数就为-1了，然而事实是，奇点数为零和奇点数为2的分支一样不需要加减边就有欧拉路
//  因此如果奇点数为0 or 2则连通不需要加边即可构成欧拉路，当奇点数为≥4的偶数，则需要加（奇点数-2）/2条边使其有欧拉路
//之后又产生了新的顾虑：
//如果剩下的连通的奇点数不全是2，而还可能有0个奇点的连通时，使这几个连通相互连接的最少边是否还是（连通数-1）呢？
//   答：是的，
//   1. 如果有两个奇点数为0的连通分支，各自任选一点相连，两个连通的奇点数各自变为1，但是由于连在了一起，新形成的连通的奇点数变为2
//   2. 如果一个奇点数为0的连通分支，另一个奇点数为2的分支，则从前一个分支里任选一点，后一个分支选一个奇点，两两相连，前一个分支奇点数变为1，后一个连通分支奇点数变为1，新的分支奇点数又成了2
//   3. 如果有两个奇点数为2的连通分支，如前所述，各自选择一个奇点两两相连，新生成的分支奇点数亦为2
//   因此，只要剩下的n个分支全部为奇点数为0或2的分支时，只需要按照上述三点有选择地加入n-1条边，则必定最后会得到一个奇点数为2的连通分支
// 所以算法逻辑如下
// 得到分支数n
// 得到各个分支的奇点数，对于奇点数为0、2的，使该分支出现欧拉路的所需加边数为0，如果奇点数大于等于4的偶数m，则使该分支出现欧拉路的所需加边数为(m-2)/2
// 得到上一步使所有分支成为度数为2/0的分支的加边数之和x
// 结果就为 x + n - 1 + e（其中e是检查员本来要走的边数）

const int MAXENUM = 500000;
const int MAXVNUM = 1002;
struct edge{
    int to;
    int next;
};
int eno = 0;
edge edges[MAXENUM];
int nodes[MAXVNUM], vis[MAXVNUM], deg[MAXVNUM];
set<int> ns;
void init(){
    ns.clear();
    for (int i = 0; i < MAXVNUM; i++){
        nodes[i] = -1;
        vis[i] = 0; 
        deg[i] = 0;
    }
    eno = 0;
}
void add(int from, int to){
    edges[eno].next = nodes[from];
    edges[eno].to = to;
    nodes[from] = eno;
    eno++;
}
void dfs(int cur, int connNum){
    // cout << "visiting " << cur << "\n";
    vis[cur] = connNum;
    for(int eno = nodes[cur]; eno != -1; eno = edges[eno].next){
        if(vis[edges[eno].to] == 0){
            dfs(edges[eno].to, connNum);
        }
    }   
}
int main(){
    int v, e, w;
    int caseNum = 0;
    while(1){
        init();
        cin >> v >> e >> w;
        #if debug
        cout << v << " " << e << " " << w << "\n";
        #endif
        if(v == 0 && e == 0 && w == 0) break;
        caseNum++;
        for (int i = 0; i < e; i++){
            int from, to;
            cin >> from >> to;
            add(from, to);
            add(to, from);
            ns.insert(from);
            ns.insert(to);
            deg[from]++;
            deg[to]++;
        }
        // 算连通数
        int connNum = 0;
        for(auto n : ns){
            if(vis[n] == 0){
                connNum++;
                dfs(n, connNum);
            }
        }
        #if debug
        cout << "connection num = " << connNum << "\n";
        #endif
        // 计算奇点
        int addEdgeNum = 0;
        for (int i = 1; i <= connNum; i++){
            #if debug
            cout << "in conn " << i << " odd points:";
            #endif
            int oddNum = 0;
            for(auto n : ns){
                if(vis[n] == i && deg[n]%2 == 1){
                    #if debug
                    cout << " " << n;
                    #endif
                    oddNum++;
                }
            }
            if(oddNum > 2)
                addEdgeNum += (oddNum-2)/2;
            #if debug
            cout << "(" << oddNum << ")\n";
            #endif
        }
        if(connNum > 1){
            addEdgeNum += connNum - 1;
        }
        cout << "Case "<< caseNum << ": " << (addEdgeNum + e)*w << "\n";
        
    }
}