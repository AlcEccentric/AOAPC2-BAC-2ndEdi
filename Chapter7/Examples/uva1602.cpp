#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include <set>
#include <algorithm>
#define For(i,e) for(i = 0; i < (e); i++)
#define Forr(i,s,e) for(i = (s); i < (e); i++)
using namespace std;
// 这道题的初始思路是正确的，即每次放一个方块，问题在于如果在坐标系内枚举方块
// 如何判重？因为直接比较两个形状的坐标是否一致显然是不行的，题目允许平移、旋转、翻转后比较
// 当时觉得一方面没想到标准化这种思想，另一方面觉得即使实现旋转、翻转耗时应该很可怕
// 事实上由于题目只有十个方块，每一步判重后可以向下的分支所剩不多，所以计算量并没有那么大
// 所以启发就是如何在坐标系里比较形状的相同和不同
// 启发：通过标准化+翻转、旋转后可在坐标系下通过比较坐标比较形状的相同与否

// ifstream cin("test.in");
// ofstream cout("test.out");
struct State{
    pair<int, int> v[12];
    int size;
    State(){
        size = 0;
    };
};
int n, w, h;
int c, cc;
const int maxHashNum = 10000, maxStateNum = 34000;
int heads[maxHashNum], nexts[maxStateNum];
State st[maxStateNum];
void printAnimal(int s){
    int i, size = st[s].size;
    For(i, size){
        cout << st[s].v[i].first << ", " << st[s].v[i].second << "\n";
    }
}
void init(){
    c = 0;
    cc = 0;
    int i;
    For(i, maxHashNum){
        heads[i] = 0;
    }
    For(i, maxStateNum){
        st[i].size = 0;
    }
}
int myhash(int s){
    int i, sum = 0, size = st[s].size;
    For(i, size){
        sum += (st[s].v[i].first * 10 + st[s].v[i].second);
    }
    sum += maxHashNum;
    return sum%maxHashNum;
}
int myhash(State& a){
    int i, sum = 0, size = a.size;
    For(i, size){
        sum += (a.v[i].first * 10 + a.v[i].second);
    }
    sum += maxHashNum;
    return sum%maxHashNum;
}
bool sameAnimal(int a, int b){
    if(st[a].size != st[b].size) return false;
    int i, s = st[a].size;
    For(i, s){
        if(st[a].v[i].first != st[b].v[i].first || st[a].v[i].second != st[b].v[i].second) return false;
    }
    return true;
}
void norm(int s){
    pair<int, int> base = st[s].v[0];
    int i, size = st[s].size;
    For(i, size){
        st[s].v[i].first -= base.first;
        st[s].v[i].second -= base.second;  
    }
    sort(st[s].v, st[s].v + st[s].size);
}
inline bool hasSame(int s, int hs){
    // 对于每种操作后得到的animal看是否和已有的重复，如果重复则直接返回false
    int f = heads[hs];
    while(f){
        if(sameAnimal(f, s)) return true;
        f = nexts[f];
    }  
    return false;
}
void rotate90(int s){
    int i, size = st[s].size;
    For(i, size){
        int ox = st[s].v[i].first, oy = st[s].v[i].second;
        st[s].v[i].first = oy;
        st[s].v[i].second = -ox;
    }
    norm(s);
}
void flipX(int s){
    int i, size = st[s].size;
    For(i, size){
        st[s].v[i].second = -st[s].v[i].second;
    }
    norm(s);
}
bool tryInsert(int s){
    bool foundSame = false;
    int hs;
    // 对当前animal进行各种变换，变换后仍旧存放在s所指的位置
    sort(st[s].v, st[s].v + st[s].size);
    norm(s);//本体
    int i;
    For(i, 4){
        rotate90(s);//转90
        hs = myhash(s);
        if(hasSame(s, hs)) return false;
    }

    flipX(s);//绕x轴翻转
    For(i, 4){
        rotate90(s);//转90
        hs = myhash(s);
        if(hasSame(s, hs)) return false;
    }
    
    // 如果所有变换都没有和任何已有的重复，则插入当前的动物（尽管s指向的动物到这里可能已经改变了方位，但是不影响正确性）
    nexts[s] = heads[hs];
    heads[hs] = s;
    return true;
}
bool exceedWH(int s){
    int minx = 20, miny = 20, maxx = -20, maxy = -20;
    int i, size = st[s].size;
    For(i, size){
        minx = st[s].v[i].first < minx ? st[s].v[i].first : minx;
        maxx = st[s].v[i].first > maxx ? st[s].v[i].first : maxx;
        miny = st[s].v[i].second < miny ? st[s].v[i].second : miny;
        maxy = st[s].v[i].second > maxy ? st[s].v[i].second : maxy;
    }
    if((maxx - minx >= w || maxy - miny >= h)&&(maxx - minx >= h || maxy - miny >= w)) return true;
    return false;
}
bool hasPair(int s, pair<int, int> p){
    int i, size = st[s].size;
    For(i, size){
        if(st[s].v[i].first == p.first && st[s].v[i].second == p.second) return true;
    }
    return false;
}
void cindAns(int rest){
    if(exceedWH(c)) return;
    int thisc = c;
    // cout << rest << "\n";
    if(!tryInsert(c++)) return;
    if(rest == 0) {
        cc++;
        return;
    }
    int i, j, x, y, size = st[thisc].size;
    For(i, size){
        For(j, 4){
            switch (j)
            {
                case 0://up
                    x = st[thisc].v[i].first, y = st[thisc].v[i].second + 1;
                    break;
                case 1://down
                    x = st[thisc].v[i].first, y = st[thisc].v[i].second - 1;
                    break;
                case 2://right
                    x = st[thisc].v[i].first + 1, y = st[thisc].v[i].second;
                    break;
                case 3://left
                    x = st[thisc].v[i].first - 1, y = st[thisc].v[i].second;
                    break;
            }
            if(!hasPair(thisc, make_pair(x, y))){
                int k;
                For(k, size){
                    st[c].v[k] = st[thisc].v[k];
                }
                st[c].size = st[thisc].size;
                st[c].v[st[c].size++] = make_pair(x, y); 
                cindAns(rest-1);
            }
        }
    }
}
int main(){
    while(cin >> n >> w >> h){
        init();
        st[c].v[0] = make_pair(0, 0);
        st[c].size = 1;
        if(n == 1) cout << "1\n";
        else{
            cindAns(n-1);
            cout << cc << "\n";
        }
    }
}