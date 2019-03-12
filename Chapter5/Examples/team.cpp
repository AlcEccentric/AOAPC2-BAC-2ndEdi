#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <map>
#include <queue>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");

int main(){
    int teamNum;
    int testId = 0;
    while(cin>>teamNum){
        if(teamNum == 0) break;
        testId++;
        cout<<"Scenario #"<<testId<<endl;
        queue<int> teamQ;
        queue<int> teams[1005];
        map<int, int> personTeamMap;
        for(int i = 0; i < teamNum; i++)
        {
            int pNum;
            cin>>pNum;
            for(int j = 0; j < pNum; j++)
            {
                int pid;
                cin>>pid;
                personTeamMap[pid] = i;
            }
            
        }
        string act;
        cin>>act;
        while(strcmp(act.c_str(), "STOP")!=0){
            if(strcmp(act.c_str(), "ENQUEUE") ==0){
                int pid;
                cin>>pid;
                int tid = personTeamMap[pid];
                if(teams[tid].size()==0){
                    teamQ.push(tid);
                }
                teams[tid].push(pid);
            }else{
                int tid = teamQ.front();
                cout << teams[tid].front() << endl;
                teams[tid].pop();
                if(teams[tid].size()==0){
                    teamQ.pop();
                }
            }
            cin >> act;
        }
        cout<<endl;
        
        
        
    }
}