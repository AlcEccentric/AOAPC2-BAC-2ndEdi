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
ifstream fin("test.in");
ofstream fout("test.out");
struct State{
    vector<pair<int, int> > v;
    set<pair<int, int> > s;
};
int n, w, h;
int c, cc;
const int maxHashNum = 10000, maxStateNum = 20000;
int heads[maxHashNum], nexts[maxStateNum];
State st[maxStateNum];
void printAnimal(int s){
    int i, size = st[s].v.size();
    For(i, size){
        fout << st[s].v[i].first << ", " << st[s].v[i].second << "\n";
    }
}
void init(){
    c = 0;
    int i;
    For(i, maxHashNum){
        heads[i] = 0;
    }
}
int myhash(int s){
    int i, sum = 0, size = st[s].v.size();
    // For(i, size){
    //     sum += (st[s].v[i].first * 10 + st[s].v[i].second);
    // }
    return sum%maxHashNum;
}
int myhash(vector<pair<int, int> >& a){
    int i, sum = 0, size = a.size();
    For(i, size){
        sum += (a[i].first * 10 + a[i].second);
    }
    return sum%maxHashNum;
}
bool sameAnimal(int a, int b){
    if(st[a].v.size() != st[b].v.size()) return false;
    int i, s = st[a].v.size();
    For(i, s){
        if(st[a].v[i].first != st[b].v[i].first || st[a].v[i].second != st[b].v[i].second) return false;
    }
    return true;
}
void norm(int s){
    sort(st[s].v.begin(), st[s].v.begin()+st[s].v.size());
    pair<int, int> base = *(st[s].v.begin());
    int i, size = st[s].v.size();
    For(i, size){
        st[s].v[i].first -= base.first;
        st[s].v[i].second -= base.second;  
    }
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
    int i, size = st[s].v.size();
    For(i, size){
        int ox = st[s].v[i].first, oy = st[s].v[i].second;
        st[s].v[i].first = oy;
        st[s].v[i].second = -ox;
    }
}
void flipX(int s){
    int i, size = st[s].v.size();
    For(i, size){
        st[s].v[i].second = -st[s].v[i].second;
    }
}
bool tryInsert(int s){
    bool foundSame = false;
    int hs = myhash(s);
    // 对当前animal进行各种变换，变换后仍旧存放在s所指的位置
    norm(s);//本体
    int i;
    For(i, 4){
        rotate90(s);//转90
        if(hasSame(s, hs)) return false;
    }

    flipX(s);//绕x轴翻转
    For(i, 4){
        rotate90(s);//转90
        if(hasSame(s, hs)) return false;
    }
    
    // 如果所有变换都没有和任何已有的重复，则插入当前的动物（尽管s指向的动物到这里可能已经改变了方位，但是不影响正确性）
    nexts[s] = heads[hs];
    heads[hs] = s;
    return true;
}
void findAns(int minx, int miny, int maxx, int maxy, int rest){
    if(maxx - minx >= w || maxy - miny >= h) return;
    int thisc = c;
    fout << rest << "\n";
    if(!tryInsert(c++)) return;
    if(rest == 0) {
        cc++;
        return;
    }
    int i, j, x, y, size = st[thisc].v.size();
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
            if(!st[thisc].s.count(make_pair(x, y))){
                int tmaxx = x > maxx ? x : maxx, tmaxy = y > maxy ? y : maxy;
                int tminx = x < minx ? x : minx, tminy = y < miny ? y : miny; 
                int k;
                For(k, size){
                    st[c].v.push_back(st[thisc].v[k]);
                    st[c].s.insert(st[thisc].v[k]);
                }
                st[c].v.push_back(make_pair(x, y));
                st[c].s.insert(make_pair(x, y));
                findAns(tminx, tminy, tmaxx, tmaxy, rest-1);
            }
        }
    }
}
int main(){
    while(fin >> n >> w >> h){
        init();
        st[c].v.push_back(make_pair(0, 0));
        st[c].s.insert(make_pair(0, 0));
        // fout << "fuck\n";
        if(n == 1) fout << "1\n";
        else{
            findAns(0, 0, 0, 0, n-1);
            fout << cc << "\n";
        }
    }
}