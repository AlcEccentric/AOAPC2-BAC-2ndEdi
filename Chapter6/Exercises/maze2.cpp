#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <queue>
#include <stack>
// #define deb÷ug
using namespace std;
// 带状态的图遍历，和6-14 uva 816（Chapter6/Examples/maze.cpp）很像
// 一般的图遍历仅以位置作为访问与否的唯一标识
// 那道题是位置+当前朝向（状态）作为唯一的标识，即使位置一样，只要到当前点的朝向不一样，就认为该点还有探索的意义（原因是当前朝向不同，后一步不同）
// 这道题是位置+骰子的顶面+骰子的下面(注意是下面不是底面，底面是顶面的对面）作为唯一标识
// 一开始只考虑了位置，导致一些情况没有解，因为一些应该探索的路没有探索
// 后来考虑加入状态，但是只考虑了把顶面加入，然而事实是：即使位置&顶面一样，由于顶面周围的四个面不确定，之后依然有可能存在不同的路径可以探索
// 因此需要将位置+顶面+下面（顶面周围四个面任意一个面）一同考虑作为唯一的访问标识
// 经验：
// 如果走下一步需要依据当前的某个条件（这道题里是顶面），则访问标识除了位置可能还需要另一个状态（顶面）
// 如果当下一步确定后发现走下下步需要依据当前的某个条件（这道题里是下面），则可能访问标识可能需要再加入新的状态（下面）
// 以此类推...
ifstream fin("test.in");
ofstream fout("test.out");

enum ori{U, D, L, R};
stack<pair<int, int> > res;
int rowNum, colNum, startRow, startCol;
bool hasStep = false;
int maze[15][15];
bool vis[12][12][6][6];
void init(){
    while(res.size())
        res.pop();
    hasStep = false;
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 15; j++)
            maze[i][j] = 0;
    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 12; j++)
            for (int k = 0; k < 6; k++)
                for (int l = 0; l < 6; l++)
                    vis[i][j][k][l] = false;
}
int nextTop(int curT, int curD, ori o, int & nextD){
    int curB = 7 - curT, curU = 7 - curD;
    int curL, curR;
    if((curT == 1 && curD == 5)||(curT == 2 && curD == 1)||(curT == 6 && curD == 2)||(curT == 5 && curD == 6)){
        curL = 3;
    }else if((curT == 1 && curD == 2)||(curT == 5 && curD == 1)||(curT == 6 && curD == 5)||(curT == 2 && curD == 6)){
        curL = 4;
    }else if((curT == 6 && curD == 3)||(curT == 4 && curD == 6)||(curT == 1 && curD == 4)||(curT == 3 && curD == 1)){
        curL = 5;
    }else if((curT == 3 && curD == 6)||(curT == 6 && curD == 4)||(curT == 4 && curD == 1)||(curT == 1 && curD == 3)){
        curL = 2;
    }else if((curT == 3 && curD == 2)||(curT == 5 && curD == 3)||(curT == 4 && curD == 5)||(curT == 2 && curD == 4)){
        curL = 1;
    }else if((curT == 2 && curD == 3)||(curT == 3 && curD == 5)||(curT == 5 && curD == 4)||(curT == 4 && curD == 2)){
        curL = 6;
    }
    curR = 7 - curL;
    int ret = 0;
    switch(o){
        case U:
            ret = 7 - curU;
            nextD = curB;
            break;
        case D:
            ret = 7 - curD;
            nextD = curT;
            break;
        case L:
            ret = 7 - curL;
            nextD = curD;
            break;
        case R:
            ret = 7 - curR;
            nextD = curD;
            break;        
    }
    return ret;
}
bool go(int curRow, int curCol, int curT, int curD){
    // 之后的逻辑确保每次这里的都是合法的位置，
    #ifdef debug
    fout << "visiting (" << curRow << "," << curCol << ") curT:"<<curT <<" curD:" <<curD << endl;
    #endif
    if(curRow == startRow && curCol == startCol){
        if(hasStep){
            res.push(make_pair(curRow, curCol));
            return true;
        }else{
            res.push(make_pair(curRow, curCol));
            hasStep = true;
        }
    }else{
        res.push(make_pair(curRow, curCol));
        
    }
    vis[curRow][curCol][curT][curD] = true;
    int nextRow, nextCol, nextT, nextD;
    // see whether can go up
    nextRow = curRow - 1; nextCol = curCol;
    nextT = nextTop(curT, curD, U, nextD);
    if(maze[nextRow][nextCol] != 0 && !vis[nextRow][nextCol][nextT][nextD] && (maze[nextRow][nextCol] == -1 || maze[nextRow][nextCol] == curT)){
        #ifdef debug
        fout << "go up\n";
        #endif
        if (go(nextRow, nextCol, nextT, nextD)){
            return true;
        }
    }
    // see whether can go down
    nextRow = curRow + 1; nextCol = curCol;
    nextT = nextTop(curT, curD, D, nextD);
    if(maze[nextRow][nextCol] != 0 && !vis[nextRow][nextCol][nextT][nextD] && (maze[nextRow][nextCol] == -1 || maze[nextRow][nextCol] == curT)){
        #ifdef debug
        fout << "go down\n";
        #endif
        if (go(nextRow, nextCol, nextT, nextD)){
            return true;
        }
    }
    // see whether can go left
    nextRow = curRow; nextCol = curCol - 1;
    nextT = nextTop(curT, curD, L, nextD);
    if(maze[nextRow][nextCol] != 0 && !vis[nextRow][nextCol][nextT][nextD] && (maze[nextRow][nextCol] == -1 || maze[nextRow][nextCol] == curT)){
        #ifdef debug
        fout << "go left\n";
        #endif
        if (go(nextRow, nextCol, nextT, nextD)){
            return true;
        }
        
    }
    // see whether can go right
    nextRow = curRow; nextCol = curCol + 1;
    nextT = nextTop(curT, curD, R, nextD);
    if(maze[nextRow][nextCol] != 0 && !vis[nextRow][nextCol][nextT][nextD] && (maze[nextRow][nextCol] == -1 || maze[nextRow][nextCol] == curT)){
        #ifdef debug
        fout << "go right\n";
        #endif
        if (go(nextRow, nextCol, nextT, nextD)){
            return true;
        }
    }
    #ifdef debug
    fout << "dead end\n";
    #endif
    res.pop();
    return false;
}
void print(stack<pair<int, int> >& r){
    int s = r.size();
    int count = 0;
    while(r.size()){
        if(count%9 == 0) fout << "  ";
        fout << "(" << r.top().first << "," << r.top().second << ")";
        r.pop();
        count++;
        if(count != s){
            fout << ",";
        }
        if(count%9 == 0 && count != s){
            fout << "\n";
        }
    }
    fout << endl;
}
int main(){
    string name;
    while(1){
        fin >> name;
        if(strcmp(name.c_str(), "END") == 0) break;
        fin >> rowNum >> colNum >> startRow >> startCol;
        int curT, curD;
        fin >> curT >> curD;
        init();
        for(int i = 1; i <= rowNum; i++)
            for(int j = 1; j <= colNum; j++)
                fin >> maze[i][j];
        
        
        stack<pair<int, int> > revRes;
        if(go(startRow, startCol, curT, curD)){
            while(res.size()){
                revRes.push(res.top());
                res.pop();
            }
            fout << name << "\n";
            print(revRes);
        }else{
            fout << name << "\n";
            fout << "  " << "No Solution Possible\n";
        }
    }
    
}