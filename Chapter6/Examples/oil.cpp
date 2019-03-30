#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");

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