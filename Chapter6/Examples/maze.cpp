#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <map>
#include <queue>
#include <stack>
#include <set>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
// 代码写的比较丑陋，尤其是分情况讨论的时候，应该有更美观的写法
// 思路是将每个点根据离开方向的不同看做四个不同的点，对这些待方向的点进行宽度优先搜索
// 边界情况其实有点多，比如终点有无中转可能、起点终点是否一样等等
// 当然或许有统一的处理，比如遍历的时候，当下一个节点为终点时就退出，而不是当前节点为终点时退出，退出时标记parent的出向和位置
// 输出路径的时候，先单独输出终点，再向回输出点，直到到达起点且方向相同
// 总之复杂的代码一定有问题，这个代码还有要优化的地方
// 此外，发现为之前的输入样例构造的map尽管被重新声明了，但是还是保留了原来的内容。。
// 这一点很奇怪，所以说重新声明并不改变变量在内存中的位置？未定义的变量依然会保持之前的值
// 总之注意：对一个变量进行定义，再进行重新声明后，如果该变量没有被重写，则该变量指向的内容还是之前定义的内容
// 建议做习题之前看一遍lrj写的代码
const char compass[5] = "ESWN";
map <char, int> oriToInd;
struct pos{
    int x;
    int y;
    bool operator == (const pos &p) const{
        return x == p.x && y == p.y;
    }
    pos(int x, int y):x(x), y(y){};
    pos(){};
};
struct subNode{
    char ori;
    pos myPos;
    pos parent;
    char parentOri;
};
struct node{
    map<char, set<char> > oriToOris;
    pos myPos;
    subNode subs[4];
    bool decined[4];
};
void init(char *x, int count){
    for(int i = 0; i < count; i++){
        x[i] = '\0';
    }
}
void init(node map[15][15]){
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 15; j++){
            for(int k = 0; k < 4; k++)
            {
                map[i][j].decined[k] = false;
            }
            
        }
    }
    
}
pos getNextPos(char ori, pos curPos){
    if(ori == 'N') return pos(curPos.x-1, curPos.y);
    else if(ori == 'S') return pos(curPos.x+1, curPos.y);
    else if(ori == 'W') return pos(curPos.x, curPos.y-1);
    else return pos(curPos.x, curPos.y+1);
}

bool BFSRush(node map[15][15], char startOri, pos startPos, pos endPos){
    queue<subNode> subNodes;
    // subNode startCopy = map[startPos.x][startPos.y].subs[oriToInd[startOri]];
    subNodes.push(map[startPos.x][startPos.y].subs[oriToInd[startOri]]);
    map[startPos.x][startPos.y].decined[oriToInd[startOri]] = false;
    // cout << "BFS: (" << map[startPos.x][startPos.y].subs[oriToInd[startOri]].myPos.x << "," << map[startPos.x][startPos.y].subs[oriToInd[startOri]].myPos.y << ") go " << startOri << "\n";
    bool hasStart = false;
    bool found = false;
    while(subNodes.size()){
        subNode cur = subNodes.front();
        subNodes.pop();
        // cout << "BFS: (" << cur.myPos.x << "," << cur.myPos.y << ") go " << cur.ori << "\n";
        if(cur.myPos == endPos && hasStart) {
            break;
        }
        char curOutOri = cur.ori;
        pos nextPos = getNextPos(curOutOri, cur.myPos);
        if(nextPos == endPos) found = true;
        hasStart = true;
        set<char> nextOutOris = map[nextPos.x][nextPos.y].oriToOris[curOutOri];
        if(nextOutOris.size() == 0 && nextPos == endPos && !map[nextPos.x][nextPos.y].decined[oriToInd[startOri]]){
            // cout << "here we go" << endl;
            map[nextPos.x][nextPos.y].subs[oriToInd[startOri]].myPos = nextPos;
            map[nextPos.x][nextPos.y].subs[oriToInd[startOri]].parent = cur.myPos;
            map[nextPos.x][nextPos.y].subs[oriToInd[startOri]].parentOri = cur.ori;
            map[nextPos.x][nextPos.y].subs[oriToInd[startOri]].ori = ' ';
            map[nextPos.x][nextPos.y].decined[oriToInd[startOri]] = true;
            subNodes.push(map[nextPos.x][nextPos.y].subs[oriToInd[startOri]]);
        }
        for(auto nextOutOri : nextOutOris){
            if(map[nextPos.x][nextPos.y].decined[oriToInd[nextOutOri]]) continue; // if this subNode has decined by a shorter route
            map[nextPos.x][nextPos.y].subs[oriToInd[nextOutOri]].ori = nextOutOri;
            map[nextPos.x][nextPos.y].subs[oriToInd[nextOutOri]].myPos = nextPos;
            map[nextPos.x][nextPos.y].subs[oriToInd[nextOutOri]].parent = cur.myPos;
            map[nextPos.x][nextPos.y].subs[oriToInd[nextOutOri]].parentOri = cur.ori;
            map[nextPos.x][nextPos.y].decined[oriToInd[nextOutOri]] = true;
            subNodes.push(map[nextPos.x][nextPos.y].subs[oriToInd[nextOutOri]]);
        }
    }
    return found;
}
void printRoute(node map[15][15], char startOri, pos startPos, pos endPos){
    // cout << "printRoute called" << endl;
    stack<subNode> route;
    int endSubNodeInd = oriToInd[startOri];
    for(int i = 0; i < 4; i++)
    {
        if(map[endPos.x][endPos.y].decined[i]){
            // cout << "found i = " << i << endl;
            endSubNodeInd = i;
            break;
        }
    }
    subNode cur = map[endPos.x][endPos.y].subs[endSubNodeInd];
    // cout << "(" << cur.myPos.x << "," << cur.myPos.y << ")" << cur.ori << "\n"; 
    if(cur.ori == ' ' && endPos == startPos){
        // cout << "终点非中转点，且和起点一样" << endl;
        route.push(cur);
        cur = map[cur.parent.x][cur.parent.y].subs[oriToInd[cur.parentOri]];
        while(!(cur.myPos == startPos)){
            route.push(cur);
            // cout << "(" << cur.myPos.x << "," << cur.myPos.y << ")" << cur.ori << "\n"; 
            cur = map[cur.parent.x][cur.parent.y].subs[oriToInd[cur.parentOri]];
        }
        // cout << "(" << cur.myPos.x << "," << cur.myPos.y << ")\n"; 
        route.push(cur);
    }else{
        // cout << "非 终点非中转点，且和起点一样 stupid" << endl;
        // cout << "stupid \n";
        // cout << "(" << cur.myPos.x << "," << cur.myPos.y << ")" << cur.ori << "\n"; 
        while(!(cur.myPos == startPos && cur.ori == startOri)){
            route.push(cur);
            // cout << "(" << cur.myPos.x << "," << cur.myPos.y << ")" << cur.ori << "\n"; 
            cur = map[cur.parent.x][cur.parent.y].subs[oriToInd[cur.parentOri]];
        }
        // cout << "(" << cur.myPos.x << "," << cur.myPos.y << ")\n"; 
        route.push(cur);
    }
    int count = 0;
    while(route.size()){
        count++;
        cout << "(" << route.top().myPos.x << "," << route.top().myPos.y << ")"; 
        if(count%10 == 0 && route.size()!=1) cout << "\n  ";
        else {
            if(route.size()!=1) cout << " ";
            else cout << endl;
        }
        route.pop();
    }
}
int main(){
    oriToInd['E'] = 0;
    oriToInd['S'] = 1;
    oriToInd['W'] = 2;
    oriToInd['N'] = 3;
    while(1){
        char name[40];
        init(name, 40);
        cin >> name;
        if(strcmp(name, "END") == 0) break;
        node map[15][15];
        int startX, startY, endX, endY;
        char startOri;
        cin >> startX >> startY >> startOri >> endX >> endY;
        pos startPos(startX, startY);
        pos endPos(endX, endY);
        
        init(map);
        // cout << startX << " " << startY << " " << map[startX][startY].subs[oriToInd[startOri]].myPos.x << " " <<  map[startX][startY].subs[oriToInd[startOri]].myPos.y << endl;
        while(1){
            int x, y;
            cin >> x;
            if(x == 0) break;
            cin >> y;
            char clot[5];
            node n;
            n.myPos.x = x;
            n.myPos.y = y;
            while(1){
                init(clot, 5);
                cin >> clot;
                if(strcmp(clot,"*") == 0) break;
                set<char> outOris;
                for(int i = 1; i < strlen(clot); i++)
                {
                    switch (clot[i])
                    {
                        case 'L':
                            if(oriToInd[clot[0]] - 1 < 0)  outOris.insert(compass[(oriToInd[clot[0]] - 1)+4]);
                            else outOris.insert(compass[oriToInd[clot[0]] - 1]);
                            break;
                        case 'R':
                            if(oriToInd[clot[0]] + 1 > 3)  outOris.insert(compass[(oriToInd[clot[0]] + 1)-4]);
                            else outOris.insert(compass[oriToInd[clot[0]] + 1]);
                            break;
                        case 'F':
                            outOris.insert(clot[0]);
                            break;
                    }
                }
                n.oriToOris[clot[0]] = outOris;    
            }
            for(int i = 0; i < 4; i++)
                n.decined[i] = false;
            map[x][y] = n;
        }
        map[endX][endY].myPos = endPos;
        map[startX][startY].myPos = startPos;
        map[startX][startY].subs[oriToInd[startOri]].myPos = startPos;
        map[startX][startY].subs[oriToInd[startOri]].ori = startOri;
        for(int i = 0; i < 4; i++)
        {
            if(i == oriToInd[startOri]) map[startX][startY].decined[i] = true;
            else map[startX][startY].decined[i] = false;
        }
        // cout << startX << " " << startY << " " << map[startX][startY].subs[oriToInd[startOri]].myPos.x << " " <<  map[startX][startY].subs[oriToInd[startOri]].myPos.y << endl;
        
        bool found = BFSRush(map, startOri, startPos, endPos);
        cout << name << endl;
        cout << "  ";
        // cout << map[2][cur.parent.y].subs[oriToInd[cur.parentOri]]
        if(found)
            printRoute(map, startOri, startPos, endPos);
        else
            cout << "No Solution Possible" << endl;

    }
}