#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <stack>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");

struct matrix{
    int rowNum;
    int colNum;
};

void init(char * line, int count){
    for(int i = 0; i < count; i++)
    {
        line[i] = '\0';
    }
    
}
int main(){
    int matrixNum;
    cin >> matrixNum;
    matrix mats[26];
    for(int i = 0; i < matrixNum; i++)
    {
        char name;
        int rn, cn;
        cin >> name >> rn >> cn;
        mats[name - 'A'].colNum = cn;
        mats[name - 'A'].rowNum = rn;
    }

    cin.ignore();
    char line[200];
    init(line, 200);
    while(cin.getline(line, 200)){
        // analyze the multiplication expression
        stack<matrix> matStack;
        int eleMulNum = 0;
        bool hasError = false;
        for(int i = 0; i < strlen(line); i++)
        {
            if(line[i] == '(') continue;
            if(line[i] <= 'Z' & line[i] >= 'A'){
                matStack.push(mats[line[i] - 'A']);
                continue;
            }
            if(line[i] == ')'){
                matrix matRight = matStack.top();
                matStack.pop();
                matrix matLeft = matStack.top();
                matStack.pop();
                if(matLeft.colNum == matRight.rowNum){
                    matrix tmpMat;
                    tmpMat.rowNum = matLeft.rowNum;
                    tmpMat.colNum = matRight.colNum;
                    eleMulNum += matLeft.rowNum * matLeft.colNum * matRight.colNum;
                    matStack.push(tmpMat);
                }else{
                    hasError = true;
                    cout << "error" << endl;
                    break;
                }
            }
        }
        if(hasError) continue;
        cout << eleMulNum << endl;
    }
    
}