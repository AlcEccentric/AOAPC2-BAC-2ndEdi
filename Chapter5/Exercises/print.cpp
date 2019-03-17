#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <queue>
#include <map>
#include <set>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");

int main(){
    int testCaseNum;
    cin >> testCaseNum;
    for(int i = 0; i < testCaseNum; i++)
    {
        int totalPrintNum;
        int indOfMine;
        cin >> totalPrintNum >> indOfMine;
        int highestPri = 0;
        queue<int> commands;
        set<int> allPris;
        map<int, int> priToNum;
        for(int j = 0; j < totalPrintNum; j++)
        {
            int pri;
            cin >> pri;
            commands.push(pri);
            allPris.insert(pri);
            if(!priToNum.count(pri)) priToNum[pri] = 1;
            else priToNum[pri] ++;
        }
        highestPri = *allPris.rbegin();
        // cout << "indOfMine: " << indOfMine << endl;
        // cout << "highest pri: "<< highestPri << endl;

        int costTime = 0;
        while(commands.size()){
            int firstReq = commands.front();
            commands.pop();
            if(firstReq < highestPri){
                if(indOfMine != 0){
                    indOfMine --;
                }else{
                    indOfMine = commands.size();
                }
                commands.push(firstReq);
            }else{
                costTime++;
                if(indOfMine != 0){
                    indOfMine --;
                }else{
                    // cout << "break" << endl;
                    break;
                }
                if(--priToNum[firstReq] == 0){
                    allPris.erase(firstReq);
                    highestPri = *allPris.rbegin();
                }

            }
            

        }

        cout << costTime << endl;

        
    }
    
}