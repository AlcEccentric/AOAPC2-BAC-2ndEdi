#include <iostream>
#include <fstream>
int MAXN = 3005;
using namespace std;
void init(int *mods){
    for(int i = 0; i < MAXN; i++)
        mods[i] = -1;
}
int main(){
    int mods[MAXN];
    int res[MAXN];
    // init mods with minus one
    init(mods);
    int x, y;
    while(cin>>x>>y){
        
        int tempx = x;
        bool getSame = false;
        int beginInd = -1, endInd = -1;
        for(int i = 0; i < y+1; i++){
            res[i] = tempx/y;
            mods[i] = tempx%y;
            // cind same mod
            for(int j = i - 1; j > i - y - 1; j--){
                if(j < 0)
                    break;
                if(mods[j] == mods[i]){
                    getSame = true;
                    beginInd = j + 1;
                    endInd = i;
                    break;
                }
            }
            if(getSame)
                break;
            tempx = mods[i] * 10;
        }

        cout << x << "/" << y << " = ";
        for(int i = 0; i <= endInd; i++){
            if(i == 51) {
                cout<<"...)"<<endl;
                break;
            }
            if(i == 0)
                cout<<res[i]<<".";
            if(i == beginInd){
                cout<<"("<<res[i];
            }
            if(i == endInd){
                if(endInd != beginInd)
                    cout<<res[i]<<")"<<endl;
                else
                    cout<<")"<<endl;
            }
            if(i != 0 && i != beginInd && i != endInd){
                cout<<res[i];
            }
            
        }
        cout << "   " << endInd - beginInd + 1 << " = number of digits in repeating cycle\n\n";
    }   
    return 0;
}