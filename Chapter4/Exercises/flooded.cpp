#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
// 注意一些边界值情况，以这道题为例，边界情况有
// 1. 只有一个square
// 2. 只有一列/行square
// 3. 水完全淹没了所有square
// 4. 没有水
// 5. 水量导致的高度恰好与某个square高度一样
// 6. 水量导致的高度恰好与最高square高度一样
// 7. 有square的海拔高度为负数
// 8. 所有square的海拔高度为负数
// 9. 所有Square的海拔为0
// 在这道题中，由于没考虑情况1导致了一个bug
// 53行的外循环中计算的sum值是水恰好到达squares[i]的高度但是还没有淹没squares[i]时的水量
// 带bug版本的i是从1开始的，即已经默认squares[1]的存在，然而在情况1中，squares[1]并不存在，从而导致了循环变量大于边界值
// 访问了含有未知数据的squares[1]，使得最后的计算的结果错误 
int mycmp(const void* x, const void* y){
    return *(int*)x - *(int*)y;
}
int main(){
    int m,n;
    cin>>m>>n;
    int squares[962];
    int rid = 0;
    while(!(m==0 && n==0)){
        rid++;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                cin >> squares[i*n+j];
            }
        }
        qsort(squares, m*n, sizeof(int), mycmp);
        // for(int i = 0; i < m*n; i++){
        //     cout<<squares[i]<<" ";
        // }
        // cout<<endl;

        unsigned int total;
        cin >> total;
        // cout<<total<<endl;
        // if(rid!=1) cout<<endl;
        cout<<"Region "<<rid<<endl;
        int nextReachInd = -1;
        unsigned int sum;
        for(int i = 0; i < m*n; i++){
            sum = 0;
            for(int j = 0; j < i; j++){
                sum += (squares[i] - squares[j]) * 100;
            }
            if(sum > total){
                nextReachInd = i; 
                break;
            }
        }
        if(nextReachInd == -1){
            double rest = total - sum;
            double height = rest/(m*n*100);
            cout<<setiosflags(ios::fixed)<<setprecision(2);
            cout<< "Water level is " << height+squares[m*n-1]<<" meters."<<endl;
            if(sum != total)
                cout<< "100.00 percent of the region is under water.\n" <<endl; 
            else
                cout<< 100 * (double)(m*n-1)/(m*n)<<" percent of the region is under water.\n\n";
            
        }else{
            sum = 0;
            int alreadyReachInd = nextReachInd - 1;
            for(int i = 0; i < nextReachInd; i++){
                sum += (squares[alreadyReachInd] - squares[i]) * 100;
            }
            double rest = total - sum;
            double height = rest/((alreadyReachInd+1)*100);
            cout<<setiosflags(ios::fixed)<<setprecision(2);
            cout<< "Water level is " << height+squares[alreadyReachInd]<<" meters."<<endl;
            if(total != sum)
                cout<< ((double)alreadyReachInd+1)/(m*n) * 100<<" percent of the region is under water.\n\n";
            else
                cout<< ((double)alreadyReachInd)/(m*n) * 100<<" percent of the region is under water.\n\n";
        }

        cin>>m>>n;
    }
}