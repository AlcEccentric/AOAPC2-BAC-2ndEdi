#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <map>
#include <queue>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
// NOTE:
// 0. 启发: 对输入样例，徒手画一画处理流程，也许可以发现一些解题（简化解法）的关键点
// 1.这道题一开始我的做法用的是vector表示队列,然后每次插入时都需要从前往后找到最后一个队友的位置，
// 导致插入的时候的时间复杂度为n，而题目特意提醒此题的数据量很大，enqueue和dequeue的时间复杂度必须是常数级别，
// 没有看到这个提示，导致第一次虽然结果正确但是超时
// 2.一开始用vector的原因是没有考虑到，根据题目条件同一个队伍的队友在队列中是聚合的而不是分散的，也就是队伍中，
// 如果一些人属于同一个队伍，那么这些人必然是按照插入时间顺序从前到后连续排列，其间不含任何其它队伍的人，
// 这样一来，就可以用对伍编号queue来表示队列，每个队伍是一个queue，队员push到队伍的queue中，如果队伍中没人则将队伍编号push到队列中，
// dequeue时将队员从对应的队伍中pop，如果pop完后队伍没人了，则将队伍编号从队列中pop
// 由于一开始没有想到同一队的队友在队列中是连续排列的这一点，以为他们之间会有其他队的插着，导致队列无法用队伍编号表示，只能用队员编号表示，
// 因此在这种情况下要找到最后一个队友必须得从头到尾search一遍，而且由于得在中间插入，因此只能用vector
//
//
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