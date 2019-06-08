#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <set>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
// 本来这道题应该很快解决的
// 一个傻逼问题导致一直tle
// 所有的全局变量，每获取一组输入时都要初始化！！
// 所有的全局变量，每获取一组输入时都要初始化！！
// 所有的全局变量，每获取一组输入时都要初始化！！
// 此外，这道题有一个地方需要注意的就是m要备份
// 每次递归的m的含义是当前位置之前的数列的最大带宽值，
// 由于当前位置有多种选择，因此，每个递归里的m必须维护
// 尝试某个位置的某种选择时，需要记录大于m的最大带宽，在这个过程中一定要使用m的备份（potM），进行更新获得最大值，避免改变m的值，
// 这是因为该位置还会有其他选择，而如果前面的选择改变了m的值，则对于后面的选择而言，m的值就不再是"当前位置之前的数列的最大带宽值"
// 
int M[26][26];
int vis[26];
set<char> nodes;
int maxBand;
char A[10], R[10];
void get_permutation(int n, int cur, int m){
    if(cur == n){
        maxBand = m;
        for(int i = 0; i < n; i++)
            R[i] = A[i];
        return;
    }
    // cout << "maxBand = " << maxBand<< " cur = " << cur << " m = " << m <<"\n";
    for (auto c : nodes){
        if(!vis[c-'A']){
            if(!cur){
                A[cur] = c;
                vis[c-'A'] = 1;
                get_permutation(n, cur+1, 0);
                vis[c-'A'] = 0;
            }else{
                A[cur] = c;
                int potM = m;
                for (int j = 0; j < cur-m; j++){
                    if(M[A[j]-'A'][A[cur]-'A'] && cur - j > potM){
                        potM = cur - j;
                    }
                }
                if(potM < maxBand){
                    // cout << "m = " << m << "\n";
                    vis[c-'A'] = 1;
                    get_permutation(n, cur+1, potM);
                    vis[c-'A'] = 0;
                }
                
            }
        }
        
    }
    
}
int main(){
    char line[100];
    while(cin.getline(line, 99)){
        if(line[0] == '#') break;
        for(int i = 0; i < 26; i++)
            for(int j = 0; j < 26; j++)
                M[i][j] = 0;
        for(int i = 0; i < 26; i++)
            vis[i] = 0;
        nodes.clear();
        for(int i = 0; i < strlen(line);){
            char thisC = line[i++];
            i++; // ignore :
            nodes.insert(thisC);
            while(line[i] - 'A' < 26 && line[i] - 'A' >= 0){
                char thatC = line[i];
                nodes.insert(thatC);
                M[thisC - 'A'][thatC - 'A'] = 1;
                M[thatC - 'A'][thisC - 'A'] = 1;
                i++;
            }
            i++;// ignore ; and first /0
        }
        maxBand = 10;
        get_permutation(nodes.size(), 0, 0);
        for(int i = 0; i < nodes.size(); i++){
            cout << R[i] << " ";
        }
        cout << "-> " << maxBand << "\n";
    }
}