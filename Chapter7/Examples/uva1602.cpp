#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#define For(i,e) for(i = 0; i < (e); i++)
#define Forr(i,s,e) for(i = (s); i < (e); i++)
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
typedef vector<pair<int, int> > State;
int n, w, h;
int c;
const int maxHashNum = 10000, maxStateNum = 20000;
int heads[maxHashNum], nexts[maxStateNum];
State st[maxStateNum];
void init(){
    c = 0;
    int i;
    For(i, maxHashNum){
        heads[i] = 0;
    }
}
int myhash(int s){
    int i, sum = 0;
    For(i, st[s].size()){
        sum += (st[s][i].first * 10 + st[s][i].second);
    }
    return sum%maxHashNum;
}
int myhash(State& a){
    int i, sum = 0;
    For(i, a.size()){
        sum += (a[i].first * 10 + a[i].second);
    }
    return sum%maxHashNum;
}
bool sameAnimal(int a, int b){
    if(st[a].size() != st[b].size()) return false;
    int i, s = st[a].size();
    For(i, s){
        if(st[a][i].first != st[b][i].first || st[a][i].second != st[b][i].second) return false;
    }
    return true;
}
void norm(int s){
    sort(st[s].begin(), st[s].begin()+st[s].size());
    pair<int, int> base = *(st[s].begin());
    int i, size = st[s].size();
    For(i, size){
        st[s][i].first -= base.first;
        st[s][i].second -= base.second;  
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
    int i, size = st[s].size();
    For(i, size){
        int ox = st[s][i].first, oy = st[s][i].second;
        st[s][i].first = oy;
        st[s][i].second = -ox;
    }
}
void flipX(int s){
    int i, size = st[s].size();
    For(i, size){
        st[s][i].second = -st[s][i].second;
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
void findAns(int minx, int miny, int maxx, int maxy){
    if(maxx - minx >= w || maxy - miny >= h) return;
    if(!tryInsert(c)) return;
    int i, size = st[c].size();
    For(i, size){
        
    }
        
}
int main(){
    while(fin>>n>>w>>h){
        init();
        st[c].push_back(make_pair(0, 0));
        if(n == 1) fout << "1\n";
        else{
            findAns(0, 0, 0, 0, c);
        }
    }
}