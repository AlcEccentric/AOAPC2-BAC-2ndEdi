#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <deque>
#include <vector>
#include <queue>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
enum statType{ASSIGN, PRINT, LOCK, UNLOCK, END};
int typeCostTime[5];
struct Program{
    int nextStatement;
    int Q;
    int id;
    vector <string> stats;
    Program(int id, int Q): id(id), Q(Q){
        nextStatement = 0;
    };
    void execute(bool &LockIsOn, deque<Program>& ready, queue<Program>& blocked, int* varValues){
        // cout << "\npro "<<id << " is executing" << endl;
        // cout << "next state is " << stats[nextStatement] << endl;
        int costTime = 0;
        while(nextStatement < stats.size()){
            string curStat = stats[nextStatement++];
            // cout << curStat << " ";
            // if(strstr(curStat.c_str(), "unlock")) cout << "this is unlock" << endl;
            if(strstr(curStat.c_str(), "end")){
                costTime += typeCostTime[END];
            }else if(strstr(curStat.c_str(), "print")){
                costTime += typeCostTime[PRINT];
                for(int i = 5; i < strlen(curStat.c_str()); i++)
                {
                    if(curStat.c_str()[i] >= 'a' && curStat.c_str()[i] <= 'z'){
                        cout << id << ": " << varValues[curStat.c_str()[i] - 'a'] << endl;
                        break;
                    }
                }
            }else if(strstr(curStat.c_str(), "lock") && curStat.c_str()[0] != 'u'){
                if(LockIsOn){
                    nextStatement--;
                    blocked.push(*this);
                    break;
                }else{
                    LockIsOn = true;
                    costTime += typeCostTime[LOCK];
                }
            }else if(strstr(curStat.c_str(), "unlock")){
                // cout << "this is unlock" << endl;
                costTime += typeCostTime[UNLOCK];
                LockIsOn = false;
                if(!blocked.empty()){
                    ready.push_front(blocked.front());
                    blocked.pop();
                }
                // cout << "unlock block into ready, ready size: " << ready.size() << endl;
            }else{ //TODO: handle assignment
                // cout << "assign: " << curStat[0] << " = ";
                costTime += typeCostTime[ASSIGN];
                int varind = curStat[0] - 'a';
                int sum = 0;
                for(int k = 1; k < strlen(curStat.c_str()); k++)
                {
                    if(isdigit(curStat.c_str()[k])){
                        sum = 10 * sum + curStat.c_str()[k] - '0';
                    }
                }
                // cout << sum << endl;
                varValues[varind] = sum;
            }
            // cout << "cost: " << costTime << endl;
            if(costTime >= Q && nextStatement < stats.size()){
                ready.push_back(*this);
                // cout << "time ran out ready size: " << ready.size() << endl;
                break;
            }
        }
    };
};

void init(char * x, int count){
    for(int i = 0; i < count; i++)
    {
        x[i] = '\0';
    }
    
}
int main(){
    int testCaseNum;
    cin >> testCaseNum;
    for(int i = 0; i < testCaseNum; i++){
        int progNum;
        cin >> progNum;
        // cout << "Prog num: " << progNum << endl;
        for(int j = 0; j < 5; j++){
            cin >> typeCostTime[j];
            // cout << "type " << j << " cost " << typeCostTime[j] << endl;
        }
        

        int Q;
        cin >> Q;
        // cout << "Q: " << Q << endl;
        cin.ignore();
        int varValues[26];
        for(int j = 0; j < 26; j++)
            varValues[j] = 0;

        bool LockOn = false;
        deque<Program> ready;
        queue<Program> blocked;
        for(int j = 0; j < progNum; j++)
        {
            Program p(j+1, Q);
            string l;
            char line[200];
            init(line, 200);
            // cout << "pro " << j << ":\n";
            do
            {
                cin.getline(line, 200);
                l = line;
                p.stats.push_back(l);
                // cout << strcmp(l.substr(0,3).c_str(), "end") << endl;
            }while(strcmp(l.substr(0,3).c_str(), "end") != 0);
            ready.push_back(p);
        }
        // cout <<"initial ready size: "<< ready.size() << endl;
        while(!ready.empty()){
            Program ex = ready.front();
            ready.pop_front();
            // cout << "\nready size: " << ready.size() << endl;
            ex.execute(LockOn, ready, blocked, varValues);
        }
        if(i != testCaseNum - 1)
        cout << endl;
        
    }
    
}