#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <queue>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
// 方法：数洞判断
// 类似的题目也是要区分几个东西，这类题目每个东西必定能够和某个具体指关联，在这道题中每个字符和一个数字（即洞的个数关）一一对应
// 具体：
// 1. 首先把外部0全部标-1(代表无效)
// 2. 遍历所有点，找到为1的点深度优先开始
// 3. 深度优先搜索的时候，对周围的点判断两类情况，一个是待探索点为1，另一个是待探索点为0
// 如果为0，洞数加一，调用另一个递归函数，对这个0进行DFS，每次只找周围的0，并将当前的0变成-1
// 如果为1，标为-1，递归调用DFS函数本身
// 一个启发：即深度优先搜索时，下一个要探索的点可以不只有一种情况，一些情况需要递归调用自身，另一些情况则不需要
priority_queue<char, vector<char>, greater<char> > allAlphas;
void DFSSet0(int map[205][205], int x, int y, int xr, int yr, int value){
    map[x][y] = value;
    if(x-1 > -1 && map[x-1][y] == 0) DFSSet0(map, x-1, y, xr, yr, value);
    if(x+1 < xr && map[x+1][y] == 0) DFSSet0(map, x+1, y, xr, yr, value);
    if(y-1 > -1 && map[x][y-1] == 0) DFSSet0(map, x, y-1, xr, yr, value);
    if(y+1 < yr && map[x][y+1] == 0) DFSSet0(map, x, y+1, xr, yr, value);
}
void DFSSearch(int map[205][205], const int x, const int y, const int xr, const int yr, int &holeNum){
    // assert(map[x][y] == 1);
    map[x][y] = -1; // 由于在程序中，所有调用DFSSearch的点的值都是1，因此这里直接标当前点为-1，而不用判断当前是什么值
    if(x-1 > -1){
        if(map[x-1][y] == 0){
            holeNum++;
            DFSSet0(map, x-1, y, xr, yr, -1);
        }else if(map[x-1][y] == 1){
            DFSSearch(map, x-1, y, xr, yr, holeNum);
        }
    }
    if(x+1 < xr){
        if(map[x+1][y] == 0){
            holeNum++;
            DFSSet0(map, x+1, y, xr, yr, -1);
        }else if(map[x+1][y] == 1){
            DFSSearch(map, x+1, y, xr, yr, holeNum);
        }
    }
    if(y-1 > -1){
        if(map[x][y-1] == 0){
            holeNum++;
            DFSSet0(map, x, y-1, xr, yr, -1);
        }else if(map[x][y-1] == 1){
            DFSSearch(map, x, y-1, xr, yr, holeNum);
        }
    }
    if(y+1 < yr){
        if(map[x][y+1] == 0){
            holeNum++;
            DFSSet0(map, x, y+1, xr, yr, -1);
        }else if(map[x][y+1] == 1){
            DFSSearch(map, x, y+1, xr, yr, holeNum);
        }
    }
}
int countHoles(int map[205][205], const int i, const int j, const int xr, const int yr){
    // cout << "countHoles is called" << endl;
    int holeNum = 0;
    DFSSearch(map, i, j, xr, yr, holeNum);
    
    return holeNum;
}
void putAlpha(int holeNum){
    switch (holeNum)
    {
        case 0:
            allAlphas.push('W');
            break;
        case 1:
            allAlphas.push('A');
            break;
        case 2:
            allAlphas.push('K');
            break;
        case 3:
            allAlphas.push('J');
            break;
        case 4:
            allAlphas.push('S');
            break;
        case 5:
            allAlphas.push('D');
            break;
        default:
            break;
    }
}
void cindAll(int map[205][205], const int xr, const int yr){
    for(int i = 0; i < xr; i++){
        for(int j = 0; j < yr; j++){
            if(map[i][j] == 1){
                int holeNum = countHoles(map, i, j, xr, yr);
                // cout << holeNum << endl;
                putAlpha(holeNum);
            }
        }
    }

}
void setNegAround(int map[205][205], const int h, const int w){
    for(int i = 0; i < h; i++)
    {
        if(i == 0 || i == h-1){
            for(int j = 0; j < w; j++)
            {
                for(int k = 0; k < 4; k++)
                {
                    if(map[i][j*4+k] == 0) {
                        DFSSet0(map, i, j*4+k, h, w*4, -1);
                    }
                }
                
            }
            
        }else{
            if(map[i][0] == 0)
                DFSSet0(map, i, 0, h, w*4, -1);
            if(map[i][(w-1)*4+3] == 0)
                DFSSet0(map, i, (w-1)*4+3, h, w*4, -1);
        }
    }
    
}
void printMap(const int map[205][205], const int h, const int w){
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            for(int k = 0; k < 4; k++)
            {
                cout << map[i][j*4+k] << " ";
            }
            
        }
        cout << endl;
    }
    
}
int main(){
    int casenum = 0;
    while(1){
        int h = 0, w = 0;
        cin >> h >> w;
        if(h == 0 || w == 0) break;
        casenum++;
        int map[205][205];
        for(int i = 0; i < h; i++)
        {
            for(int j = 0; j < w; j++)
            {
                char in; int num;
                cin >> in;
                if(in - '0' > 9 || in - '0' < 0)
                    num = in - 'a' + 10;
                else
                    num = in - '0';
                for(int k = 0; k < 4; k++){
                    map[i][j*4+k] = (num >> (3-k))%2;
                }
            }
            
        }
        // printMap(map, h, w);
        setNegAround(map, h, w);
        // printMap(map, h, w);
        while(allAlphas.size()){
            allAlphas.pop();
        }
        cindAll(map, h, 4*w);
        // cout << allAlphas.size() << endl;
        cout << "Case " << casenum << ": ";
        while(allAlphas.size()){
            cout << allAlphas.top();
            allAlphas.pop();
        }
        cout << endl;
    }
}