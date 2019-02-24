#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");

enum {UP, DOWN, LEFT, RIGHT};
struct dot{
    bool udlrHas[4];
    int udlrLen[4];
};

void initDot(dot dots[9][9]){
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            for(int k = 0; k < 4; k++){
                dots[i][j].udlrHas[k] = false;
                dots[i][j].udlrLen[k] = 0;
            }
}
void initCounter(int * counter){
    for(int i = 0; i < 8; i++)
        counter[i] = 0;
}

void getEdge(dot dots[9][9], int m){
    for(int i = 0; i < m; i++){
        char hv;
        fin>>hv;
        int hn, vn;
        if(hv == 'H'){
            fin>>hn>>vn;
            hn--; vn--;
            dots[hn][vn].udlrHas[RIGHT] = true;
            dots[hn][vn+1].udlrHas[LEFT] = true;

        }else{
            fin>>vn>>hn;
            hn--; vn--;
            dots[hn][vn].udlrHas[DOWN] = true;
            dots[hn+1][vn].udlrHas[UP] = true;
        }

    }
}

int countRight(dot dots[9][9], int h, int v, int n){
    if(dots[h][v].udlrHas[RIGHT]){
        if(dots[h][v+1].udlrLen[RIGHT])
            return 1+dots[h][v+1].udlrLen[RIGHT];
        else 
            return 1+countRight(dots, h, v+1, n);
    }
    else
        return 0;
}   
int countLeft(dot dots[9][9], int h, int v, int n){
    if(dots[h][v].udlrHas[LEFT]){
        if(dots[h][v-1].udlrLen[LEFT])
            return 1+dots[h][v-1].udlrLen[LEFT];
        else 
            return 1+countLeft(dots, h, v-1, n);
    }
    else
        return 0;
} 
int countUp(dot dots[9][9], int h, int v, int n){
    if(dots[h][v].udlrHas[UP]){
        if(dots[h-1][v].udlrLen[UP])
            return 1+dots[h-1][v].udlrLen[UP];
        else
            return 1+countUp(dots, h-1, v, n);
    }
    else
        return 0;
} 
int countDown(dot dots[9][9], int h, int v, int n){
    if(dots[h][v].udlrHas[DOWN]){
        if(dots[h+1][v].udlrLen[DOWN])
            return 1+dots[h+1][v].udlrLen[DOWN];
        else
            return 1+countDown(dots, h+1, v, n);
    }
    else
        return 0;
} 

void countEdgeLen(dot dots[9][9], int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            dots[i][j].udlrLen[RIGHT] = countRight(dots, i, j, n);
            dots[i][j].udlrLen[LEFT] = countLeft(dots, i, j, n);
            dots[i][j].udlrLen[UP] = countUp(dots, i, j, n);
            dots[i][j].udlrLen[DOWN] = countDown(dots, i, j, n);
        }
    }
}

void analyzeDots(int*counter, dot dots[9][9], int n){
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(dots[i][j].udlrHas[RIGHT]&&dots[i][j].udlrHas[DOWN]){
                int scanRange = dots[i][j].udlrLen[DOWN]<dots[i][j].udlrLen[RIGHT] ? dots[i][j].udlrLen[DOWN]:dots[i][j].udlrLen[RIGHT];
                for(int k = 1; k <= scanRange; k++){
                    if(dots[i+k][j+k].udlrLen[UP]>=k && dots[i+k][j+k].udlrLen[LEFT]>=k)
                        counter[k]++;
                }
            }
        }
        
    }
    
}
int main(){
    int n,m;
    int proNo = 0;
    while(fin>>n){
        fin>>m;
        dot dots[9][9];
        initDot(dots);
        getEdge(dots, m);
        countEdgeLen(dots, n);
        int counter[9];//counter[0] is useless
        initCounter(counter);
        analyzeDots(counter, dots, n);
        if(proNo != 0){
            fout<<endl;
            fout<<"**********************************";
            fout<<endl;
        }
        fout<<"Problem #"<<proNo+1<<"\n\n";
        bool hassquare = false;
        for(int i = 1; i <= n-1; i++)
        {
            if(counter[i]){
                fout<<counter[i]<<" square (s) of size "<<i<<endl;
                hassquare = hassquare || true;
            }
            
        }
        if (!hassquare) {
            fout<<"No completed squares can be found."<<endl;
        }
        proNo++;
    }
}