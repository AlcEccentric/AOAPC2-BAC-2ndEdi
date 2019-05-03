#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <set>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
void init(int G[26][26], int count = 26){
    for(int i = 0; i < count; i++)
        for(int j = 0; j < count; j++)
            G[i][j] = 0;
    
}
void dfs(int cur, const int G[26][26], int vs[26][26], set<int> & dfsRes){
    dfsRes.insert(cur);
    // cout << cur << endl;
    for(int i = 0; i < 26; i++)
    {
        if(i != cur && ( G[i][cur] || G[cur][i]) && !vs[cur][i]){
            vs[cur][i] = vs[i][cur] = 1;
            dfs(i, G, vs, dfsRes);
        }
    }
}
bool qualified(const int G[26][26], const set<char>& alphas){
    int in1 = 0, out1 = 0, other = 0, equal = 0;
    for(set<char>::iterator ii = alphas.begin(); ii != alphas.end(); ii++)
    {
        int outD = 0, inD = 0;
        int cur = *ii - 'a';
        for(int i = 0; i < 26; i++)
            if(G[cur][i]) outD+=G[cur][i];
        for(int i = 0; i < 26; i++)
            if(G[i][cur]) inD+=G[i][cur];
        
        switch (outD-inD)
        {
            case 1:
                out1++;
                break;
            case -1:
                in1++;
                break;
            case 0:
                equal++;
                break;
            default:
                other++;
                break;
        }
    }
    // cout << in1 << " " << out1 << " " << equal << " " << other << endl;
    if(in1 == 1 && out1 == 1 && equal == alphas.size()-2) return true;
    else if(equal == alphas.size()) return true;
    else return false;
}
int main(){
    int caseNum;
    cin >> caseNum;
    while(caseNum){
        int n;
        cin >> n;
        set<char> alphas;
        int G[26][26];
        int vs[26][26];
        init(G);
        init(vs);
        while(n){
            string word;
            cin >> word;
            char start = word[0];
            char end = word[strlen(word.c_str())-1];
            alphas.insert(start);
            alphas.insert(end);
            // cout << start << " "  << end <<endl;
            G[start-'a'][end-'a'] += 1;
            n--;
        }
        set<int> dfsRes;
        dfs(*alphas.begin()-'a', G, vs, dfsRes);
        if(dfsRes.size() != alphas.size()){// not connected
            cout << "The door cannot be opened." << endl;
        }else{
            if(qualified(G, alphas)){
                cout << "Ordering is possible." << endl;
            }else{
                cout << "The door cannot be opened." << endl;
            }
        }
        
        caseNum--;
    }
}