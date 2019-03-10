#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");

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