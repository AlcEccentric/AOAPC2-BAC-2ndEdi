#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <vector>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");

int main(){
    int testCaseNum;
    fin >> testCaseNum;
    for(int i = 0; i < testCaseNum; i++)
    {
        int n;
        fin >> n;
        vector<int> nums;
        for(int j = 0; j < n; j++)
        {
            int num;
            fin >> num;
            fout << num << " ";
            nums.push_back(num);
        }fout << endl;
        
        
    }
    
}