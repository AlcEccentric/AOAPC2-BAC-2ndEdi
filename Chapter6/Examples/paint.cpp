#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <stdlib.h>
#include <queue>
#include <math.h>
#include <set>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
// 这题的题意比较模糊，实际上的意思是，只要有路可以从东边到西边不碰到圈就行，
// 至于路是否是直线都没有要求，只要能画出一条从西边走到东边的任意次弯曲的曲线即可
// 因此只要没有一串圈相互交界从南贯穿到北，就能画出这样的曲线
// 找联通可以用并查集，假设南北边界是两个圈，
// 但是这里并查集的话，每读入一个圈都要找交界的圈，这个复杂度就一下子上到n^2，
// 因此这里应该是用BFS/DFS判断联通的
// 后记：
// lrj总结这道题为对偶图问题，我感觉更像是逆向思维
// 大概基本思路是找到连续的空白块，能从西边通道东边
// 逆向思路是，无法找到连续的障碍从南通到北边
// 关于起点和终点：
// 一开始以为起点和BFS过程无关，只要能判断走得通，之后在边界找到最上面的非障碍点即可
// 事实上是起始点和BFS找的障碍路径是存在关系的，即使不存在一个完全从南通到北的障碍路径
// 一旦这个障碍路径碰到左右边界就会导致起始点的变化
// 因此在走路径的时候，当遇到路径和左右边界交叉时，说明角落有一块空白区域被堵死，
// 即使这个角落的西边或者东部边界是无障碍的，但是由于被这条路径封死，因此是无效的空白边界
// 因此在走障碍路径的时候，当遇到和左右边界的交错且交错部位（相切也算）的下方交点的纵坐标小于已有的起始点纵坐标
// 要更新起始点
struct ball{
    int x, y, r, i;
};
ball balls[1005];
int vis[1005];
void init(int * x, int count){
    for (int i = 0; i < count; i++)
        x[i] = 0;
}
bool touchNorth(const ball& b){
    return 1000 - b.y <= b.r; 
}
bool touchSouth(const ball& b){
    return b.y - 0 <= b.r;
}
bool touchEast(const ball& b, double &bp1, double &bp2, bool & tang){
    bool touch = 1000 - b.x <= b.r;
    tang = b.r == (1000 - b.x);
    if(touch){
        bp1 = b.y + sqrt(b.r * b.r - (1000 - b.x) * (1000 - b.x));
        bp2 = b.y - sqrt(b.r * b.r - (1000 - b.x) * (1000 - b.x));
    }
    return touch; 
}
bool touchWest(const ball& b, double &bp1, double &bp2, bool & tang){
    bool touch = b.x - 0 <= b.r;
    tang = b.r == b.x;
    if(touch){
        bp1 = b.y + sqrt(b.r * b.r - b.x * b.x);
        bp2 = b.y - sqrt(b.r * b.r - b.x * b.x);
    }
    return touch; 
}
bool touch(const ball& b1, const ball& b2){
    int deltax = b1.x - b2.x;
    int deltay = b1.y - b2.y;
    int r = b1.r + b2.r;
    return deltax * deltax + deltay * deltay <= r * r;
}
int main(){
    int n;
    while(cin >> n){
        queue<int> q;
        while(q.size()) q.pop();
        init(vis, 1005);
        for (int i = 0; i < n; i++)
        {
            int x, y, r;
            cin >> x >> y >> r;
            balls[i].x = x;
            balls[i].y = y;
            balls[i].r = r;
            balls[i].i = i;
            if(touchNorth(balls[i])){
                q.push(i);
                vis[i] = 1;
            } 
        }
        bool touchS = false; double wn = 1000, en = 1000;
        while(q.size()){// 注意q一开始就为空的情况
            ball curBall = balls[q.front()];
            q.pop();
            if(touchSouth(curBall)){
                touchS = true;
                break; 
            }
            double bp1 = 0, bp2 = 0; bool tang = false;
            if(touchWest(curBall, bp1, bp2, tang)){
                wn = bp2 < wn ? bp2 : wn;
            }
            if(touchEast(curBall, bp1, bp2, tang)){
                en = bp2 < en ? bp2 : en;
            }
            for (int i = 0; i < n; i++)
            {
                if(!vis[i] && touch(balls[i], curBall)){
                    q.push(i);
                    vis[i] = 1;
                }
            }
            
        }
        if(touchS) cout << "IMPOSSIBLE" << endl;
        else{
            cout << "0.00 ";
            cout << fixed << setprecision(2) << wn;
            cout << " ";
            cout << "1000.00 ";
            cout << fixed << setprecision(2) << en;
            cout << endl;
        }
    }
}