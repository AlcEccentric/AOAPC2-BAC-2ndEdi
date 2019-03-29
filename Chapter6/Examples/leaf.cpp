#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <map>
#include <set>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");

map<int, int> horizonPosToSum;
set<int> poses;
int getInput(int thisPos, int depth){
    int num;
    cin >> num;
    if(depth == 0 && num == -1) return 1;
    if(depth == 0){
        horizonPosToSum.clear();
        poses.clear();
    }
    if(num == -1){
        return 0;
    }
    // cout << "sum of pos before: " << horizonPosToSum[thisPos] <<endl;
    // cout << "num: " << num << " pos: " << thisPos << endl;
    poses.insert(thisPos);
    if(horizonPosToSum.count(thisPos)){
        horizonPosToSum[thisPos] = horizonPosToSum[thisPos] + num;
    }else{
        horizonPosToSum[thisPos] = num;
    }
    // cout << "sum of pos after: " << horizonPosToSum[thisPos] <<endl;
    getInput(thisPos-1, depth + 1);//left
    getInput(thisPos+1, depth + 1);//right
    return 0;
}
int main(){
    int caseNum = 1;
    while(getInput(0, 0) == 0){
        cout << "Case " << caseNum << ":" << endl;
        for(set<int>::iterator i = poses.begin(); i != poses.end(); i++)
        {
            if(i == poses.begin())
                cout << horizonPosToSum[*i];
            else
                cout << " " << horizonPosToSum[*i];
        }
        cout << endl << endl;
        caseNum ++;
    }
}