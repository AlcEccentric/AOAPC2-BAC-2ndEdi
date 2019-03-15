#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include <set>
using namespace std;
// ifstream  cin("test.in");
// ofstream  cout("test.out");

int main(){
    int testCaseNum;
     cin >> testCaseNum;
    for(int i = 0; i < testCaseNum; i++)
    {
        int n;
         cin >> n;
        vector<int> nums;
        for(int j = 0; j < n; j++)
        {
            int num;
             cin >> num;
            //  cout << num << " ";
            nums.push_back(num);
        }
        //  cout << endl;

        bool allZero = false;
        for(int i = 0; i < 1000; i++)
        {
            int firstNum = nums[0];
            set<int> remains;
            for(vector<int>::iterator ii = nums.begin(); ii != nums.end(); ii++)
            {   

                if(ii != nums.end() - 1){
                    int diff = abs(*(ii + 1) - *(ii));
                    nums[ii - nums.begin()] = diff;
                    remains.insert(diff);
                }
                else{
                    int diff = abs(firstNum - *(ii));
                    nums[ii - nums.begin()] = diff;
                    remains.insert(diff);
                }

            }
            if(remains.size() == 1 && *remains.begin() == 0){
                allZero = true;
                break;
            }
        }
        if(allZero)
             cout << "ZERO" << endl;
        else
             cout << "LOOP" << endl;
    }
    
}