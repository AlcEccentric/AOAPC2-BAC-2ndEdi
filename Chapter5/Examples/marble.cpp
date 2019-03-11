#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <algorithm>
#include <vector>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");

int searchMarble(vector<int>& marbles, int q){
    int ind = 0;
    for(vector<int>::iterator i = marbles.begin(); i != marbles.end(); i++)
    {
        if(*i == q){
            return ind;
        }
        ind++;
    }
    return ind;
    
}
int main(){
    int N, Q;
    int id = 0;
    cin >> N >> Q;
    while(N != 0 && Q != 0){
        id++;
        cout<<"CASE# "<<id<<":\n";
        // cout << "N:"<<N<<"Q:"<<Q<<endl;
        vector<int> marbles;
        
        for(int i = 0; i < N; i++){
            int m;
            cin >> m;
            marbles.push_back(m);
        }
        sort(marbles.begin(), marbles.end());
        for(int i = 0; i < Q; i++)
        {
            int q;
            cin >> q;
            int ind = searchMarble(marbles, q);
            if(ind == marbles.size()){
                cout<< q <<" not found\n";
            }else{
                cout<< q <<" found at "<<ind+1<<endl;
            }
        }
        marbles.clear();
        cin >> N >> Q;
        
    }
}