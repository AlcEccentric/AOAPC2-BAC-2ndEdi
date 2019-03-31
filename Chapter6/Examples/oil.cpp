#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
// NOTE:
// 1. 由于对用并查集判断连通性的算法过于熟悉，所以这道题我用的是并查集的方法
// 用数组表示点之间的连通关系，遍历所有点，如果是@，则和周围的是@的点比较，看是否在同一个集合（根据数组找root比较是否相同），
// 如果不在同一个连通集，将其中一个root指向另一个，从而连接两个集合
// 由于只有代表一个连通集的root在数组中对应位置的值为它自己，所以在数组中数有多少ind和value相同的位置，其值就是所求值
// 并查集在实现的时候的缺陷：图用的是二维数组，并查集中每个点存在一维数组，一方面将二维坐标转换到一维数组的坐标很容易出错
// 另一方面，当需要判断一个点是否在图的边界时，用一维数组表示点的方式就很难实现（实现了也容易出错），而用二维数组的表示就很好判断边界
// 2. lrj给的方法很简单，直接从一个没有探索过的@点（未标上序号，说明在新的连通集）的周围八个方向进行DFS搜索，为搜到的所有点标上同一序号（而这些点就位于同一连通集），
// 该序号从0递增，每加一就代表找到一个连通集，最后的标号就说明了图中连通集的数量
// 3. 所以遇到图的连通问题，并查集是一个思路，DFS、BFS搜索又是一个思路，两个各有利弊，但是不应该偏废一方
// 4. 这里lrj表示图的方法就是简单的用input的字符二维数组表示
// 5. 给我感觉数据结构课里的东西只会出现在面试里，并且适合那种工程问题，而解决这种算法题，数据结构课上学的东西并不实用

int cindRoot(int *map, int p){
    while(map[p] != p){
        p = map[p];
    }
    return p;
}

bool isSameSet(int *map, int p1, int p2, int &root1, int &root2){
    root1 = cindRoot(map, p1);
    root2 = cindRoot(map, p2);
    return root1 == root2;
}

void connect(int *map, int r1, int r2){
    if(r1 > r2){
        map[r2] = r1;
    }else{
        map[r1] = r2;
    }
}

void init(int *map, int count){
    for(int i = 0; i < count; i++)
    {
        map[i] = -1;
    }
}

int main(){
    int rowNum, colNum;
    while(cin>>rowNum>>colNum){
        // cout << rowNum << colNum << endl;
        if(rowNum == 0 || colNum == 0) break;
        int map[11000];
        init(map, 11000);
       for(int i = 1; i < rowNum+1; i++)
            for(int j = 1; j < colNum+1; j++){
            int cur = i * (colNum+2) + j;
            char p;
            cin >> p;
            if(p == '@')
                map[cur] = cur;
        }
        // cout << "p1" << endl;
        for(int i = 1; i < rowNum+1; i++){
            for(int j = 1; j < colNum+1; j++){
                int cur = i * (colNum+2) + j;
                if(map[cur]==-1) continue;
                int pos[8] = {
                    cur-colNum-2,
                    cur+1,
                    cur+colNum+2,
                    cur-1,
                    cur-colNum-2+1,
                    cur+colNum+2+1,
                    cur-colNum-2-1,
                    cur+colNum+2-1
                };
                
                int root1, root2;
                for(int k = 0; k < 8; k++){
                    if(map[pos[k]] != -1 && !isSameSet(map, cur, pos[k], root1, root2))
                        connect(map, root1, root2);
                }
                
            }
        }
        int oilCount = 0;
        for(int i = 1; i < rowNum+1; i++)
            for(int j = 1; j < colNum+1; j++){
                int cur = i * (colNum+2) + j;
                if(map[cur] == cur) oilCount++;
            }
        cout << oilCount << endl;
        
    }
}