#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include <stack>
#include <assert.h>
#define For(i,e) for(i = 0; i < (e); i++)
#define Forr(i,s,e) for(i = (s); i < (e); i++)
// 这道题有不少要说的，虽然想法很直观bfs，但是细节上需要注意很多
// 关于bfs效率有三个收获
// 1. 如果bfs的每一步有多个动作要执行，一个可能的方法是让几个动作在一部中同时执行
// 如果不合法则考虑下一个动作组合，而不是考虑不同的动作次序，后者会无增加很多不必要的尝试
// 在这里有abc三个鬼可以动，那么在bfs的一步中，就尝试让三个鬼同时动，动完之后再去判断是不是一次合法的尝试
// 这样比尝试abc所有的排序要减少不少尝试（1/10），代价是判断合法的函数会比排序法难写一点
// 2. 虽然尝试所有的下一步可能是一种自然的想法，但是在时间要求严格的题目中，尝试很多不必要的非法的下一步是一种浪费
// 如果每一步的尝试方向是有限的，那么可以在读取输入时对输入预处理，记录下每一个可移动位置的合法移动方向，从而
// 避免在bfs中尝试非法方向
// 3. 在空间足够的情况下如果能使用多维数组进行状态相同的判断，则使用之；虽然更高效的方法是编码使用一维数组；
// 几种判断状态重复的方法按效率排应该是 编码 > 多维访问数组 > 多对一哈希 > STL
// 注意了以上几点之后，单向bfs可以通过了
// 一些编码经验：
// 1. 这次又忘了在init函数初始化全局变量，导致WA，所以下次准备提交前一定要检查init函数里是否初始化了所有的全局变量
// 2. 每次写一个函数的逻辑时都要思考这样的逻辑是否适用于所有的情况（有的时候写的代码逻辑，或许只考虑了最复杂和一般的情况，反而是最简单的情况没有考虑）
// 比如validMov函数里面一开始就只考虑了有abc都存在在图中的情况，没有考虑只有两个或者一个字母的逻辑
// 这道题的最高效方法是双向bfs，终点起点同时bfs，当某一步两者走到的状态一致时则可以停止，步数为两者步数相加，
// 待日后尝试这种做法(其实是对这道题感到厌倦= =)
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
const int maxStateNum = 192*192*192;
typedef int State[6];// ar ac br bc cr cc
State st[maxStateNum], goal;
int step[maxStateNum];
int fa[maxStateNum];
vector<pair<int, int> > canGo[16][16];// 1up 2down 3left 4right
int w, h, n, front, rear, vis[240][240][240];
char m[16][16], line[20];
void init(){
    int i;
    For(i, maxStateNum) step[i] = 0;
    For(i, maxStateNum) fa[i] = 0;
    For(i, 240){
        int j;
        For(j, 240){
            int k;
            For(k, 240) vis[i][j][k] = 0;
        }
    }
    For(i, 6){
        st[1][i] = 0;
        goal[i] = 0;//又尼玛忘记初始化全局变量
    }
    For(i, 16){
        int j;
        For(j, 16) {
            canGo[i][j].clear();
            canGo[i][j].push_back(make_pair(0,0));
        }
    }
}
void printMap(int s){
    int i;
    For(i, h){
        int j;
        For(j, w){
            int k;
            bool found = false;
            For(k, n){
                if(i == st[s][k*2] && j == st[s][k*2+1]){
                    fout << (char)('X' + k);
                    found = true;
                    break;
                }
            }
            if(!found) fout << m[i][j];
        }
        fout << "\n";
    }
    fout << "\n";
}
int no(char x, char base){
    return x-base;
}
// int myhash(int s){
//     int a = st[s][0]*100 + st[s][1];
//     int b = st[s][2]*100 + st[s][3];
//     int c = st[s][4]*100 + st[s][5];
//     int v = a*10000 + b*100 + c;
//     return v%maxHashNum;
// }
bool tryInsert(int s){
    if(n==1) assert(st[s][2] == 0 && st[s][3] == 0 && st[s][4] == 0 && st[s][5] == 0);
    if(n==2) assert(st[s][4] == 0 && st[s][5] == 0);
    int a = st[s][0]*w + st[s][1];
    int b = st[s][2]*w + st[s][3];
    int c = st[s][4]*w + st[s][5];
    if(vis[a][b][c]){ return false; }
    vis[a][b][c] = 1;
    return true;
}
void backtrace(int s){
    stack<int> ss;
    while(s){
        ss.push(s);
        s=fa[s];
    }
    while(ss.size()){
        printMap(ss.top());
        ss.pop();
    }
}
void getGoOris(int w, int h){
    int i;
    For(i, h){
        int j;
        For(j, w){
            if(m[i][j] != '#'){
                if(i-1 >= 0 && m[i-1][j] != '#'){//up
                    canGo[i][j].push_back(make_pair(-1, 0));
                }
                if(i+1 <= h-1 && m[i+1][j] != '#'){//down
                    canGo[i][j].push_back(make_pair(1, 0));
                }
                if(j-1 >= 0 && m[i][j-1] != '#'){//left
                    canGo[i][j].push_back(make_pair(0, -1));
                }
                if(j+1 <= w-1 && m[i][j+1] != '#'){//right
                    canGo[i][j].push_back(make_pair(0, 1));
                }    
            }
        }
    }
}
bool validMove(int* nextABC, int* curABC){
    if(n==1) assert(nextABC[2] == 0 && nextABC[3] == 0 && nextABC[4] == 0 && nextABC[5] == 0);
    if(n==2) assert(nextABC[4] == 0 && nextABC[5] == 0);
    int nAr = nextABC[0], nAc = nextABC[1], nBr = nextABC[2], nBc = nextABC[3], nCr = nextABC[4], nCc = nextABC[5];
    int cAr = curABC[0], cAc = curABC[1], cBr = curABC[2], cBc = curABC[3], cCr = curABC[4], cCc = curABC[5];
    // fout << "A from("<< cAr << "," << cAc << ") to (" << nAr << "," << nAc << ")\n";
    // fout << "B from("<< cBr << "," << cBc << ") to (" << nBr << "," << nBc << ")\n";
    // fout << "C from("<< cCr << "," << cCc << ") to (" << nCr << "," << nCc << ")\n\n";
    if((nAr&&nBr&&nAc&&nBc&&nAr == nBr && nAc == nBc)||(nAr&&nCr&&nAc&&nCc&&nAr == nCr && nAc == nCc)||(nBr&&nCr&&nBc&&nCc&&nCr == nBr && nCc == nBc)){
        return false;// overlap
    }
    if( (nAr&&nBr&&nAc&&nBc&&nAr == cBr && nAc == cBc && nBr == cAr && nBc == cAc)||
        (nAr&&nCr&&nAc&&nCc&&nAr == cCr && nAc == cCc && nCr == cAr && nCc == cAc)||
        (nBr&&nCr&&nBc&&nCc&&nCr == cBr && nCc == cBc && nBr == cCr && nBc == cCc)){
        return false;// exchange
    }
    return true;
}
int bfs(){
    int minstep = -1;
    front = 1, rear = 2;
    // fout << "bfs\n";
    while(front < rear){
        if(n==1) assert(st[front][2] == 0 && st[front][3] == 0 && st[front][4] == 0 && st[front][5] == 0);
        if(n==2) assert(st[front][4] == 0 && st[front][5] == 0);
        if( st[front][0] == goal[0] && st[front][1] == goal[1] &&
            st[front][2] == goal[2] && st[front][3] == goal[3] &&
            st[front][4] == goal[4] && st[front][5] == goal[5] ) {
                // backtrace(front);
                // if(minstep == -1 || step[front] < minstep) minstep = step[front];
                // fout << "minstep updated\n";
                break;
            }
        int nextABC[6], curABC[6], i;
        For(i, 6) {
            curABC[i] = st[front][i]; 
        }
        const vector<pair<int, int> > & aCanGo = canGo[curABC[0]][curABC[1]], & bCanGo = canGo[curABC[2]][curABC[3]], & cCanGo = canGo[curABC[4]][curABC[5]];
        int goASize = aCanGo.size(), goBSize = bCanGo.size(), goCSize = cCanGo.size();
        // fout << "goA: " << goASize << " goB: " << goBSize << " goC: " << goCSize << "\n";
        For(i, goASize){
            int j;
            nextABC[0] = curABC[0] + aCanGo[i].first;
            nextABC[1] = curABC[1] + aCanGo[i].second;
            For(j, goBSize){
                int k;
                nextABC[2] = curABC[2] + bCanGo[j].first;
                nextABC[3] = curABC[3] + bCanGo[j].second;
                For(k, goCSize){
                    nextABC[4] = curABC[4] + cCanGo[k].first;
                    nextABC[5] = curABC[5] + cCanGo[k].second;
                    if(validMove(nextABC, curABC)){
                        // fout << "valid move\n";
                        int l;
                        For(l, 6) st[rear][l] = nextABC[l];
                        if(tryInsert(rear)) {
                            step[rear] = step[front]+1;
                            fa[rear] = front;
                            rear++;
                        }
                    }
                }
            }
        }
        front++;
    }
    // return minstep;
    return step[front];
}
int main(){
    while(fin >> w >> h >> n){
        if(!w && !h && !n) break;
        int i;
        init();
        fin.ignore();
        For(i, h){
            fin.getline(line, 20);
            int j;
            For(j, w){
                m[i][j] = line[j];
                char x = m[i][j];
                if(no(x, 'a') < n && no(x, 'a') >= 0){// a b c
                    st[1][2*no(x, 'a')] = i;
                    st[1][2*no(x, 'a')+1] = j;
                }else if(no(x, 'A') < n && no(x, 'A') >= 0){// A B C
                    goal[2*no(x, 'A')] = i;
                    goal[2*no(x, 'A')+1] = j;
                }
            }
        }
        getGoOris(w, h);
        tryInsert(1);
        int ans = bfs();
        fout << ans << "\n";
    }
}