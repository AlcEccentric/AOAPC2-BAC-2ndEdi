#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <stack>
#include <map>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");

struct posInfo{
    int pileNo;
    int sizeNo;
};

void clearPos(stack<int>* piles, int no, map<int, posInfo> &posInfoMap){
    int thisPile = posInfoMap[no].pileNo;
    // cout << "\tpile "<< no <<" size " << posInfoMap[no].sizeNo<<endl;
    while(piles[thisPile].size() > posInfoMap[no].sizeNo + 1){
        int blockno = piles[thisPile].top();
        piles[thisPile].pop();
        // assert(piles[blockno].empty());
        // cout<<"clear block "<<blockno<<endl;
        posInfoMap[blockno].pileNo = blockno;
        posInfoMap[blockno].sizeNo = piles[blockno].size();
        piles[blockno].push(blockno);
    }
    // cout<<piles[thisPile].size()<<endl;
}


void initPiles(stack<int>* piles, map<int, posInfo> &posInfoMap, int size){
    for(int i = 0; i < size; i++)
    {
        piles[i].push(i);
        posInfo info;
        info.pileNo = i;
        info.sizeNo = 0;
        posInfoMap[i] = info;
    }
    
}

void printPiles(stack<int> *piles, int blockNum){
    for(int i = 0; i < blockNum; i++)
    {
        cout << i << ":";
        if(!piles[i].empty()){
            stack<int> temp;
            while(!piles[i].empty()){
                temp.push(piles[i].top());
                piles[i].pop();
            }
            while(!temp.empty()){
                cout << " ";
                cout << temp.top();
                piles[i].push(temp.top());
                temp.pop();
            }
            cout<<endl;
        }else{
            cout << endl;
        }
    }
}

int main(){
    stack<int> piles[30];
    map<int, posInfo> posInfoMap;
    initPiles(piles, posInfoMap, 30);
    int blockNum;
    cin>>blockNum;
    while(1){   
        string act, type;
        int src, dst;
        cin>>act;
        if(strcmp(act.c_str(), "quit") == 0) break;
        cin>>src>>type>>dst;
        // cout<<act<<" "<<src<<" "<<type<<" "<<dst<<endl;
        if(src == dst || posInfoMap[src].pileNo == posInfoMap[dst].pileNo) continue;
        
        if(strcmp(act.c_str(), "move") == 0){
            clearPos(piles, src, posInfoMap);
            // printPiles(piles, blockNum);
            if(strcmp(type.c_str(), "onto") == 0){
                clearPos(piles, dst, posInfoMap);
            }
            int srcpile = posInfoMap[src].pileNo;
            // cout<<"before: src pile no = " << posInfoMap[src].pileNo<<endl;
            posInfoMap[src].pileNo = posInfoMap[dst].pileNo;
            // cout<<"after: src pile no = " << posInfoMap[src].pileNo<<endl;

            // cout<<"before: src size no = " << posInfoMap[src].sizeNo<<endl;
            posInfoMap[src].sizeNo = piles[posInfoMap[dst].pileNo].size();
            // cout<<"after: src size no = " << posInfoMap[src].sizeNo<<endl;
            
            piles[posInfoMap[dst].pileNo].push(piles[srcpile].top());
            piles[srcpile].pop();
        }else if(strcmp(act.c_str(), "pile") == 0){
            if(strcmp(type.c_str(), "onto") == 0){
                clearPos(piles, dst, posInfoMap);
            }
            stack<int> temp;
            while(piles[posInfoMap[src].pileNo].size() != posInfoMap[src].sizeNo){
                temp.push(piles[posInfoMap[src].pileNo].top());
                piles[posInfoMap[src].pileNo].pop();
            }
            while(!temp.empty()){
                posInfoMap[temp.top()].pileNo = posInfoMap[dst].pileNo;
                posInfoMap[temp.top()].sizeNo = piles[posInfoMap[dst].pileNo].size();
                piles[posInfoMap[dst].pileNo].push(temp.top());
                temp.pop();
            }
        }
        // printPiles(piles, blockNum);
        // cout<<endl;
        // cout<<"23 pile no: "<<posInfoMap[23].pileNo<<endl;
        // cout<<"23 size no: "<<posInfoMap[23].sizeNo;
        // cout << endl;
    }
    printPiles(piles, blockNum);
    
}