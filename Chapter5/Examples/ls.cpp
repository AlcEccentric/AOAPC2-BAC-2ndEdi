#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");

int main(){
    int num;
    while(cin>>num){
        vector<string> files;
        int maxLen = 0;
        for(int i = 0; i < num; i++)
        {
            string file;
            cin >> file;
            maxLen = (int)file.length() > maxLen ? (int)file.length() : maxLen;
            files.push_back(file);
        }
        sort(files.begin(), files.end());
        // for(auto f : files){
        //     cout << f << endl;
        // }
        int colNum = 62/(maxLen+2);
        int rowNum = num%colNum==0 ? num/colNum : num/colNum + 1;
        int filenum = 0;
        cout << "------------------------------------------------------------" <<endl;
        for(vector<string>::iterator iter = files.begin(); iter < files.begin()+rowNum; iter++){
            int countColNum = 0;
            while(countColNum < colNum){
                if(iter+countColNum*rowNum-files.begin()>=num) break;
                if(countColNum != colNum - 1){
                    if(iter+(countColNum+1)*rowNum-files.begin()>=num)
                        cout << left << setw(maxLen) << *(iter+countColNum*rowNum);
                    else
                        cout << left << setw(maxLen+2) << *(iter+countColNum*rowNum);

                }
                else
                    cout << left << setw(maxLen) << *(iter+countColNum*rowNum);
                countColNum++;
            }
            cout << endl;
        }
    }
}