#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
// 一直WA的原因是initCounter数组中没有对counter[8]进行初始化
// 而输出的结果是从counter[1]到counter[8]
// 两个启发：
// 一、如果可以不让含数据的数组元素下标从1开始就尽可能让其从0开始，比如这道题边长为1的正方形数量可以就放在counter[0]里
// 二、数组可以尽可能开的大一点，初始化函数的循环次数和数组的长度保持一致
// 三、如果让含数据的数组元素下标从1开始，则应该好好检查代码中所有关于该数组的代码，看是否有Access越界等访问未初始化的数据的行为

enum {UP, DOWN, LEFT, RIGHT};
struct dot{
    bool udlrHas[4];
    int udlrLen[4];
};

void initDot(dot dots[15][15]){
    for(int i = 0; i < 15; i++)
        for(int j = 0; j < 15; j++)
            for(int k = 0; k < 4; k++){
                dots[i][j].udlrHas[k] = false;
                dots[i][j].udlrLen[k] = 0;
            }
}
void initCounter(int * counter){
    for(int i = 0; i < 15; i++)
        counter[i] = 0;
}

void getEdge(dot dots[15][15], int m){
    for(int i = 0; i < m; i++){
        char hv;
        cin>>hv;
        int hn, vn;
        if(hv == 'H'){
            cin>>hn>>vn;
            hn--; vn--;
            dots[hn][vn].udlrHas[RIGHT] = true;
            dots[hn][vn+1].udlrHas[LEFT] = true;

        }else{
            cin>>vn>>hn;
            hn--; vn--;
            dots[hn][vn].udlrHas[DOWN] = true;
            dots[hn+1][vn].udlrHas[UP] = true;
        }

    }
}

int countRight(dot dots[15][15], int h, int v, int n){
    if(dots[h][v].udlrHas[RIGHT]){
        if(dots[h][v+1].udlrLen[RIGHT])
            return 1+dots[h][v+1].udlrLen[RIGHT];
        else 
            return 1+countRight(dots, h, v+1, n);
    }
    else
        return 0;
}   
int countLeft(dot dots[15][15], int h, int v, int n){
    if(dots[h][v].udlrHas[LEFT]){
        if(dots[h][v-1].udlrLen[LEFT])
            return 1+dots[h][v-1].udlrLen[LEFT];
        else 
            return 1+countLeft(dots, h, v-1, n);
    }
    else
        return 0;
} 
int countUp(dot dots[15][15], int h, int v, int n){
    if(dots[h][v].udlrHas[UP]){
        if(dots[h-1][v].udlrLen[UP])
            return 1+dots[h-1][v].udlrLen[UP];
        else
            return 1+countUp(dots, h-1, v, n);
    }
    else
        return 0;
} 
int countDown(dot dots[15][15], int h, int v, int n){
    if(dots[h][v].udlrHas[DOWN]){
        if(dots[h+1][v].udlrLen[DOWN])
            return 1+dots[h+1][v].udlrLen[DOWN];
        else
            return 1+countDown(dots, h+1, v, n);
    }
    else
        return 0;
} 

void countEdgeLen(dot dots[15][15], int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            dots[i][j].udlrLen[RIGHT] = countRight(dots, i, j, n);
            dots[i][j].udlrLen[LEFT] = countLeft(dots, i, j, n);
            dots[i][j].udlrLen[UP] = countUp(dots, i, j, n);
            dots[i][j].udlrLen[DOWN] = countDown(dots, i, j, n);
        }
    }

    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < n; j++){
    //         cout<<"dot("<<i+1<<","<<j+1<<"):\n"<<"up:"<< dots[i][j].udlrLen[UP]<<endl;
    //         cout<<"down:"<< dots[i][j].udlrLen[DOWN]<<endl;
    //         cout<<"left:"<< dots[i][j].udlrLen[LEFT]<<endl;
    //         cout<<"right:"<< dots[i][j].udlrLen[RIGHT]<<endl<<endl;
    //     }
    // }
}

void analyzeDots(int*counter, dot dots[15][15], int n){
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
    while(cin>>n){
        cin>>m;
        dot dots[15][15];
        initDot(dots);
        getEdge(dots, m);
        countEdgeLen(dots, n);
        int counter[15];//counter[0] is useless
        initCounter(counter);
        analyzeDots(counter, dots, n);
        if(proNo != 0){
            cout<<endl;
            cout<<"**********************************\n";
            cout<<endl;
        }
        cout<<"Problem #"<<proNo+1<<"\n\n";
        bool hassquare = false;
        for(int i = 1; i <= n-1; i++)
        {
            if(counter[i]){
                cout<<counter[i]<<" square (s) of size "<<i<<endl;
                hassquare = hassquare || true;
            }
            
        }
        if (!hassquare) {
            cout<<"No completed squares can be found."<<endl;
        }
        proNo++;
    }
}