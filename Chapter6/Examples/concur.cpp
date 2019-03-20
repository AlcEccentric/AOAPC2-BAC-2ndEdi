#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <deque>
#include <vector>
#include <queue>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
enum statType{ASSIGN, PRINT, LOCK, UNLOCK, END};
int typeCostTime[5];
struct Program{
    int nextStatement;
    int Q;
    int id;
    vector <string> stats;
    task(int id, int Q): id(id), Q(Q){
        nextStatement = 0;
    };
    void execute(bool &LockIsOn, deque<Program>& ready, queue<Program>& blocked, int* varValues){
        int costTime = 0;
        while(nextStatement < stats.size()){
            string curStat = stats[nextStatement++];
            if(curStat.strstr("end")){
                costTime += typeCostTime[END];
            }else if(curStat.strstr("print")){
                costTime += typeCostTime[PRINT];
                for(int i = 5; i < strlen(curStat.c_str()); i++)
                {
                    if(curStat.c_str()[i] >= 'a' && curStat.c_str()[i] <= 'z'){
                        fout << id << ": " << varValues[curStat.c_str()[i] - 'a'];
                        break;
                    }
                }
            }else if(curStat.strstr("lock")){
                if(LockIsOn){
                    nextStatement--;
                    blocked.push(*this);
                }else{
                    LockIsOn = true;
                    costTime += typeCostTime[LOCK];
                }
            }else if(curStat.strstr("unlock")){
                costTime += typeCostTime[UNLOCK];
                LockIsOn = false;
                if(!blocked.empty()){
                    ready.push_front(block.front());
                }
            }else{ //TODO: handle assignment
                costTime += typeCostTime[ASSIGN];
                int varind = curStat[0] - 'a';
                for(int i = 1; i < strlen(curStat.c_str()); i++)
                {
                    if(isdigit(curStat.c_str()[i])){
                        
                    }
                }
                
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
    fin >> testCaseNum;
    for(int i = 0; i < testCaseNum; i++){
        int progNum;
        fin >> progNum;
        for(int j = 0; j < 5; j++)
            fin >> typeCostTime[j];
        int Q;
        fin >> Q;
        fin.ignore();
        int varValues[26];
        for(int j = 0; j < 26; j++)
            varValues[j] = -1;

        bool LockOn = false;
        deeue<Program> ready;
        queue<Program> blocked;
        for(int j = 0; j < progNum; j++)
        {
            Program p(j+1, Q);
            string l;
            char line[200];
            init(line, 200);
            do
            {
                fin.getline(line, 200);
                l = line;
                p.stats.push_back(l);
            }while(strcmp(l.substr(0,3).c_str(), "end") != 0);
            ready.push(p);
        }

        while(!ready.empty()){
            Program ex = ready.front();
            ready.pop();
            ex.execute(LockOn, ready, blocked, );
        }
        
        fout << endl;
        
    }
    
}