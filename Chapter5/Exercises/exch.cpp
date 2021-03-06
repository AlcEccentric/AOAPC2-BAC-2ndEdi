#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <map>
#include <set>
#include <vector>
using namespace std;
// ifstream  cin("test.in");
// ofstream  cout("test.out");

struct stu{
    unsigned int from;
    unsigned int to;
};

int main(){
    int n;
    while( cin>>n){
        if(!n) break;
        map<pair<unsigned int, unsigned int>, unsigned int > mymap;
        set<pair<unsigned int, unsigned int> > info;
        for(int i = 0; i < n; i++)
        {
            unsigned int from, to;
             cin >> from >> to;
            if(mymap.count(make_pair(from, to))) mymap[make_pair(from, to)] ++;
            else mymap[make_pair(from, to)] = 1;
            
            info.insert(make_pair(from, to));
        }
        bool allFoundPair = true;
        for(auto s : info){
            if(mymap[s] != mymap[make_pair(s.second, s.first)]){
                allFoundPair = false;
                break;
            }
                
        }
        if(allFoundPair)  cout << "YES" << endl;
        else  cout << "NO" << endl;
    }
}