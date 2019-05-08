#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <climits>
#include <queue>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
// 方法是两次bfs，一次从终点到起点，另一次从起点到终点
// 这里说一下学到的一些东西
// 1. 链式前向星表示图
// 2. 为什么要从终点开始bfs：由于目标是找到字典序最小的最短路，如何比较字典序呢，要从第一步的权值开始比较
// 如果是正着bfs，最后打印路径是从终点往回走，只能从最后一步开始比较，这样是没法找到最小字典序的
// 因此思路是逆向bfs找最短路，正向bfs找字典序最小的最短路
// 3. 为什么正着找路要用bfs而不是直接打印路径：因为允许多条边颜色相同，因此存在当前这一步有多个字典序相同的走法，
// 因此需要记录相同字典序边走到的节点，然后下一步比较这些节点的出边的权值，再找最小
// 4. 找回路的方法：如果要找一条从a到b的最短路，如果是从a开始bfs，则每次走一步都要记录父亲节点，当走到b点时，
// 得一步步靠找父亲节点的方法走回a并记录路径；如果是从b开始bfs，则每次走一步都可以只记录走到当前节点的步数，当
// 走到a时，一步步往回找步数-1的节点即可打印出路径。
//（当然逆向bfs也可以靠记录父亲节点来找寻路径，但是找步数-1的节点这种方法只适用逆向bfs后打印最短路径，正向bfs无法后用这种方法打印出正确的最短路）
// 1，这题虽然改了方法还是依然疯狂超时，原因是从起点向终点bfs时，在把下一层的节点放入队列时没有考虑到重边，由于有重边的存在
// 下一层会有相同的节点被放到待访问节点队列，这样就导致时间复杂度呈指数级上升
// 2. 其实这道题本应该早就ac，但是由于main函数里的while循环写的有问题，一直WA，
// 与链式前向星数据结构无关，而是由于while读入循环写的不对，其中if(自环) continue
// 这里在continue之前没有对循环变量-1操作，会导致无法正常读入输入数据
// 这件事告诉我们，如果要用continue请仅在for循环里用
const int MAXN = 400020;
int edgeID = 0;
struct Edge{
    int to;
    int next;
    int c;
};
Edge edges[MAXN];
int head[MAXN]; // -1 means single vertex
int dist[MAXN]; // -1 means not visited
int vis[MAXN]; //
void init(int * h, int v){
    for(int i = 0; i < MAXN; i++)
        h[i] = v;
}
inline void addEdge(int s, int e, int c, int id){
    edges[id].c = c;
    edges[id].to = e;
    edges[id].next = head[s];
    head[s] = id;
}
void bfs(int n){
    init(dist, -1);
    queue<int> q;
    q.push(n);
    dist[n] = 0;// first point
    while(q.size()){
        int cur = q.front();
        q.pop();  
        if(cur == 1) break;
        for(int eid = head[cur]; eid != -1; eid = edges[eid].next){
            int nextV = edges[eid].to;
            if(dist[nextV] == -1){
                dist[nextV] = dist[cur] + 1;
                q.push(nextV);
            }
        }
    }
}
void clear(queue<int> q){
    while(q.size()){
        q.pop();
    }
}
void printPath(int n){
    init(vis, 0);
    fout << dist[1] << endl;
    // queue<int> curs, nextes, ans;
    // clear(curs);
    // clear(nextes);
    // clear(ans);
    // curs.push(1);
    // vis[1] = 1;
    // while(1){
    //     int small = INT_MAX;
    //     while(curs.size()){
    //         int cur = curs.front(); curs.pop();
    //         for(int eid = head[cur]; eid != -1; eid = edges[eid].next){
    //             if(dist[cur] - dist[edges[eid].to] == 1 && edges[eid].c <= small){
    //                 small = edges[eid].c;
    //                 nextes.push(eid);
    //             }
    //         }
    //     }
    //     // fout << small << endl;
    //     ans.push(small);
    //     if(ans.size() == dist[1]) break;
    //     assert(curs.empty());
    //     while(nextes.size()){
    //         int ne = nextes.front(); nextes.pop();
    //         int nv = edges[ne].to;
    //         if(vis[nv] == 0 && edges[ne].c == small){
    //             curs.push(nv);
    //             vis[nv] = 1;
    //         }
    //     }
    // }
    // while(ans.size()){
    //     fout << ans.front();
    //     ans.pop();
    //     if(ans.size()) fout << " ";
    //     else fout << endl;
    // }
    queue<int> q;///复杂度写高了 没有给结点判断重复 指数级
    int u = 1, v, i;
    q.push(u);
    int c = INT_MAX;//最小color
    vector<int> vec;//保存下一个层次的点
    while(!q.empty()||!vec.empty()) {
        if(q.empty()) { //保证队列里只有一个层次的点，如果队列空了，说明上一层的点都跑完了，这时候c一定是最小的
            for(i = 0;i < vec.size();i++) {
                int k = vec[i], v = edges[k].to;
                if(edges[k].c == c && !vis[v] ) {//vis[v] 重边
                    if(edges[k].to == n) { printf("%d\n",c); return ;}
                    q.push(edges[vec[i]].to); vis[v] = 1;
                }
            }
            vec.clear();
            printf("%d ",c); c = INT_MAX;
        }

        u = q.front(); q.pop();

        for(i = head[u]; ~i ; i = edges[i].next ) {
            v = edges[i].to;
            if(dist[u] - dist[v] == 1 && edges[i].c <= c) {
                vec.push_back(i);
                c = edges[i].c;
            }
        }
    }

}
int main(){
    int n, m;
    while(fin >> n >> m){
        cout << "m = " << m << endl;
        edgeID = 0;
        init(head, -1);
        while(m){
            int s, e, c;
            fin >> s >> e >> c;
            // fout << s << e << c << endl;
            if(s == e) {
                // m--;
                continue;
            }
            cout << s << " "<< e << " m = " << m << endl;
            addEdge(s, e, c, edgeID++);
            addEdge(e, s, c, edgeID++);
            m--;
        }
        cout << "m = " << m << endl;
        // fout << "bfs ing" << endl;
        bfs(n);
        printPath(n);

    }

}