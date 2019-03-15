#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <queue>
using namespace std;
// ifstream  cin("test.in");
// ofstream  cout("test.out");

int main(){
    int num;
    while( cin>>num){
        if(num == 0) break;
        queue<int> cards;
        for(int i = 0; i < num; i++)
            cards.push(i+1);
         cout << "Discarded cards:" ;
        while(cards.size() >= 2){
             cout << " ";
             cout << cards.front();
            cards.pop();
            if(cards.size()>1)  cout << ",";
            int f = cards.front();
            cards.pop();
            cards.push(f);
        }
         cout << endl;
         cout << "Remaining card: " << cards.front() << endl;
        

        
    }
}