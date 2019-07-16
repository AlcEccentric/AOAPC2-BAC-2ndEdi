#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <vector>
#define For(i, n) for(i=0; i<n; i++)
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
int testCaseNum, n;

int main(){
    fin >> testCaseNum;
    while(testCaseNum--){
        fin >> n;
        fin.ignore();
        char line[200];
        int i, j;
        For(i, 200) line[i] = '\0';
        fin.getline(line, 200);
        char num[3] = "\0\0";
        i = 0, j = 0;
        vector<int> nums;
        while(i != strlen(line)+1){
            if(line[i] == ' ' || i == strlen(line)){
                nums.push_back(atoi(num));
                j = 0;
                strcpy(num, "\0\0\0");
                i++;
            }else{
                num[j++] = line[i++];
            }
        }
        int size = nums.size();
        For(i, size){
            fout << nums[i] << " ";
        }
        fout << "\n";

    }
}