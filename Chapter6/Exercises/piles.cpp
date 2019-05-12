#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <stack>
#include <vector>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
// 这题没啥好说的
// 就是需要一个vector按序记录所有非空的堆的序号，当一个堆变空时，从其中移除对应的序号
stack<string> piles[52];
void init(vector<int>& nonEmptyNum){
    for (int i = 0; i < 52; i++)
    {
        while(piles[i].size()){
            piles[i].pop();
        }
    }
    nonEmptyNum.clear();
}

int match(int offset, const vector<int>& nonEmptyNum){
    if(offset >= 3 && 
     (piles[nonEmptyNum[offset-3]].top()[0] == piles[nonEmptyNum[offset]].top()[0] || 
      piles[nonEmptyNum[offset-3]].top()[1] == piles[nonEmptyNum[offset]].top()[1]) ){
        return nonEmptyNum[offset-3];
    }else if(offset >= 1 && 
    (piles[nonEmptyNum[offset-1]].top()[0] == piles[nonEmptyNum[offset]].top()[0] ||
     piles[nonEmptyNum[offset-1]].top()[1] == piles[nonEmptyNum[offset]].top()[1])){
        return nonEmptyNum[offset-1];
    }else{
        return -1;
    }
}
void moveCard(int toInd, vector<int>::iterator thisInd, vector<int> & nonEmptyNum){
    // fout << "move "; 
    string thisCard = piles[*thisInd].top();
    // fout << thisCard << " on ";
    piles[*thisInd].pop();
    // fout << piles[toInd].top() << "\n";
    piles[toInd].push(thisCard);
    if(piles[*thisInd].size() == 0){
        nonEmptyNum.erase(thisInd);
    }
}
void printPiles(vector<int>&nonEmptyNum){
    if(nonEmptyNum.size() == 1) fout << nonEmptyNum.size() << " pile remaining:";
    else fout << nonEmptyNum.size() << " piles remaining:";
    for(vector<int>::iterator ii = nonEmptyNum.begin(); ii != nonEmptyNum.end(); ii++){
        // fout << "pile #"<<*ii << " size: ";
        fout << " " << piles[*ii].size();
    }
    fout << endl;
}
void move(vector<int>&nonEmptyNum){
    while(1){
        bool change = false;
        for(vector<int>::iterator ii = nonEmptyNum.begin(); ii != nonEmptyNum.end(); ii++){
            int toInd = match(ii - nonEmptyNum.begin(), nonEmptyNum);
            if(toInd != -1){
                moveCard(toInd, ii, nonEmptyNum);
                change = true;
                break;
            }
        }
        if(!change) break;
    }
    printPiles(nonEmptyNum);
}
int main(){
    while(1){
        if(fin.peek() == '#') break;
        vector<int> nonEmptyNum;
        init(nonEmptyNum);
        for (int i = 0; i < 52; i++){
            string x;
            fin >> x;
            piles[i].push(x);
            nonEmptyNum.push_back(i);
        }
        move(nonEmptyNum);
        fin.ignore();
    }
    
    
}