#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
// first submission failed because I forget to replace fin&fout with cin&cout
void init(bool* isOut, int count){
    for(int i = 0; i < count; i++)
    {
        /* code */
        isOut[i] = false;
    }
    
}
int main(){
    int N,k,m;
    while(cin>>N>>k>>m){
        if(N == 0 && k == 0 && m == 0) break;
        // cout<<N<<" "<<k<<" "<<m<<endl;
        bool isOut[19];
        int remain = N;
        init(isOut, 19);
        int kCur = 0, mCur = N-1;
        while(remain){
            
            int kstep, mstep;
            if(remain == N){
                kstep = 1;
                mstep = 1;
            }else{
                kstep = mstep = 0;
            }
            while(kstep < k){
                kCur = (kCur+1)%N;
                if(!isOut[kCur]) kstep++;   
            }
            while(mstep < m){
                if(mCur == 0){
                    mCur = N-1;
                }else{
                    mCur = (mCur-1)%N;
                }
                if(!isOut[mCur]) mstep++; 
            }
            // now mCur and kCur point to the people will leave
            if(kCur == mCur){
                // printf("%3d,", kCur+1);
                cout<< fixed << setw(3)<<kCur+1;
                isOut[kCur] = true;
                remain--;
            }else{
                // printf("%3d%3d,", kCur+1, mCur+1);
                cout<< fixed << setw(3) <<kCur+1<< fixed << setw(3)<<mCur+1;
                isOut[kCur] = true;
                isOut[mCur] = true;
                remain-=2;
            }
            if(remain == 0){
                cout<<endl;
            }else{
                cout<<",";
            }
        }
    }
 }