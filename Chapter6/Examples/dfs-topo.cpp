#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <queue>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
int vs[105];
int pre[105][105];
void init(int * x, int count, int v = 0){
    for(int i = 0; i < count; i++)
        x[i] = v;
}
void init(int x[105][105], int count){
    for(int i = 0; i < count; i++)
        for(int j = 0; j < count; j++)
            x[i][j] = 0;
}
bool dfs(queue<int>& res, int i, int n){
    vs[i] = -1;
    // cout << "visiting " << i << endl;
    for(int j = 1; j <= n; j++)
    {
        if(pre[j][i]){
            if(vs[j] == -1){
                // there is a circle
                return false;
            }else if(vs[j] == 0){
                if(!dfs(res, j, n)) return false;
            }
        }
    }
    // cout << "push " << i << endl;
    res.push(i);           
    vs[i] = 1;
    return true;
}
bool topo(queue<int>& res, int n){
    for(int i = 1; i <= n; i++)
    {
        if(vs[i] == 0){
            // cout << "dfs called for " << i << endl;
            if(!dfs(res, i, n)) return false;
        }
    }
    return true;
}
void printOrder(queue<int>& res){
    while(res.size()){
        cout << res.front();
        res.pop();
        if(res.size() == 0) cout << endl;
        else cout << " ";
    }
}
int main(){
    int n,m;
    while(1){
        cin >> n >> m;
        if(n == 0 && m == 0) break;
        init(pre, 105);
        init(vs, 105);
        for(int i = 0; i < m; i++)
        {
            int pr, po;
            cin >> pr >> po;
            pre[pr][po] = 1;
        }
        queue<int> res;
        if(topo(res, n)){
            printOrder(res);
        }else{
            cout << "This is impossible." << endl;
        }

    }
}