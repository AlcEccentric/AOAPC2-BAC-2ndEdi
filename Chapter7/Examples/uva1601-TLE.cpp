#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <algorithm>
#include <stack>
#include <vector>
#define For(i,e) for(i = 0; i < (e); i++)
#define Forr(i,s,e) for(i = (s); i < (e); i++)
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
// 该代码一直TLE，原因包括转移可能太多：这个代码中的逻辑是几个鬼按先后顺序走，每个鬼有五种走法，而鬼的先后顺序又有3!种
// 因此如果依然单向bfs改进之处应该为：三个鬼同时移动（避免尝试所有排序），记录移动可能（避免不必要的判断）
// 由于不是依次移动，同时移动后的相互位置可能不合法，要判断当前移动组合是否合法
const int maxStateNum = 192*192*192, maxHashNum = 20000000;
typedef int State[6];// ar ac br bc cr cc
State st[maxStateNum], goal;
int step[maxStateNum], fa[maxStateNum];
vector<int> canGo[256];// 1up 2down 3left 4right
int w, h, tryNum;
int head[maxHashNum], nexts[maxStateNum];
char m[16][16], line[20];
void init(){
    int i;
    For(i, maxHashNum) head[i] = 0;
    For(i, maxStateNum) step[i] = 0;
    For(i, maxStateNum) fa[i] = 0;
    For(i, 256) canGo[i].clear();
    tryNum = 0;
}
void printMap(int s, int n){
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
int myhash(int s){
    int a = st[s][0]*100 + st[s][1];
    int b = st[s][2]*100 + st[s][3];
    int c = st[s][4]*100 + st[s][5];
    int v = a*10000 + b*100 + c;
    return v%maxHashNum;
}
bool tryInsert(int s){
    int h = myhash(s);
    int u = head[h];
    while(u){
        if( st[u][0] == st[s][0] && st[u][1] == st[s][1] &&
            st[u][2] == st[s][2] && st[u][3] == st[s][3] &&
            st[u][4] == st[s][4] && st[u][5] == st[s][5] )  return false;
        u = nexts[u];
    }
    nexts[s] = head[h];
    head[h] = s;
    return true;
}
bool noStepOver(int fs, int ns, int* p, int curp, int n, int nr, int nc){
    bool notStepOver = true;
    int i;
    For(i, curp){//后面走的不能踩前面走到的新位置
        int crid = p[i] * 2, ccid = p[i] * 2 + 1;
        if(st[ns][crid] == nr && st[ns][ccid] == nc){
            notStepOver = false;
            break;
        }
    }
    if(notStepOver){
        Forr(i, curp+1, n){//前面走的不能踩后面的原来的位置
            int crid = p[i] * 2, ccid = p[i] * 2 + 1;
            if(st[fs][crid] == nr && st[fs][ccid] == nc){
                notStepOver = false;
                break;
            }
        }
    }
    return notStepOver;
}
void mov(int curs, int& ns, int n, int curp, int* p){
    if(!n) {//到达底端，n个点都已移动结束，st[ns]已完毕
        step[ns] = step[curs]+1;
        if(tryInsert(ns)){ 
            fa[ns] = curs;
            ns++;
            int i;
            For(i, curp) {
                st[ns][2*i] = st[ns-1][2*i];
                st[ns][2*i+1] = st[ns-1][2*i+1];
            }
        }
        return;
    }
    int crid = p[curp] * 2, ccid = p[curp] * 2 + 1;
    int cr = st[curs][crid], cc = st[curs][ccid];
    int spaceNum = cr * w + cc;
    for(auto i : canGo[spaceNum]){
        tryNum++;
        switch (i){
            case 0:// stay
                // fout << (char)('a'+p[curp]) << " stay @ " << cr << " " << cc <<"\n";
                st[ns][crid] = cr;
                st[ns][ccid] = cc;
                break;
            case 1:// up
                if(cr-1 >= 0 && m[cr-1][cc] != '#'&& noStepOver(curs, ns, p, curp, curp+n, cr-1, cc)){
                    // fout << (char)('a'+p[curp]) << " up to " << cr-1 << " " << cc <<"\n";
                    st[ns][crid] = cr-1;
                    st[ns][ccid] = cc;
                }else
                    continue;
                break;
            case 2:// down
                if(cr+1 <= h-1 && m[cr+1][cc] != '#'&& noStepOver(curs, ns, p, curp, curp+n, cr+1, cc)){
                    // fout << (char)('a'+p[curp]) << " down to " << cr+1 << " " << cc <<"\n";
                    st[ns][crid] = cr+1;
                    st[ns][ccid] = cc;
                }else
                    continue;
                break;
            case 3:// left
                if(cc-1 >= 0 && m[cr][cc-1] != '#' && noStepOver(curs, ns, p, curp, curp+n, cr, cc-1)){
                    // fout << (char)('a'+p[curp]) << " left to " << cr << " " << cc-1<<"\n";
                    st[ns][crid] = cr;
                    st[ns][ccid] = cc-1;
                }else
                    continue;
                break;
            case 4:// right
                if(cc+1 <= w-1 && m[cr][cc+1] != '#'&& noStepOver(curs, ns, p, curp, curp+n, cr, cc+1)){
                    // fout << (char)('a'+p[curp]) << " right to " << cr << " " << cc+1 <<"\n";
                    st[ns][crid] = cr;
                    st[ns][ccid] = cc+1;
                }else
                    continue;
                break;
        }
        mov(curs, ns, n-1, curp+1, p);//递归调用的参数不要出现自增自减号，就直接x-1即可，如果非要用，也要用++x而不是x++
    }
}
void backtrace(int s, int n){
    stack<int> ss;
    while(s){
        ss.push(s);
        s=fa[s];
    }
    while(ss.size()){
        printMap(ss.top(), n);
        ss.pop();
    }
}
int bfs(int n){
    int front = 1, rear = 2;
    while(front < rear){
        int p[3], i;
        For(i, n) p[i] = i;
        if( st[front][0] == goal[0] && st[front][1] == goal[1] &&
            st[front][2] == goal[2] && st[front][3] == goal[3] &&
            st[front][4] == goal[4] && st[front][5] == goal[5] ) {
                // backtrace(front, n);
                break;
            }
        
        do{// 对于所有的可能移动顺序 初始为a, b, c（如果有b和c）
            mov(front, rear, n, 0, p);
        } while (next_permutation(p, p+n));
        front++;
    }
    fout << "tryNum = " << tryNum << "\n";
    return step[front];
}
void getGoOris(int w, int h){
    int i;
    For(i, h){
        int j;
        For(j, w){
            if(m[i][j] != '#'){
                int num = w*i + j;
                canGo[num].push_back(0);
                if(i-1 >= 0 && m[i-1][j] != '#'){//up
                    canGo[num].push_back(1);
                }
                if(i+1 <= h-1 && m[i+1][j] != '#'){//down
                    canGo[num].push_back(2);
                }
                if(j-1 >= 0 && m[i][j-1] != '#'){//left
                    canGo[num].push_back(3);
                }
                if(j+1 <= w-1 && m[i][j+1] != '#'){//right
                    canGo[num].push_back(4);
                }    
            }
        }
    }
}
int main(){
    int n;
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
        int ans = bfs(n);
        fout << ans << "\n";
    }
}