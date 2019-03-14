#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include <map>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");

void init(char * x, int count){
    for(int i = 0; i < count; i++)
    {
        x[i] = '\0';
    }
    
}

int main(){
    int rowN, colN;
    while(cin>>rowN>>colN){
        cin.ignore();
        // cout << rowN << " " << colN << endl;
        vector<string> rows[10010];
        for(int i = 0; i < rowN; i++)
        {
            char line[100];
            init(line, 100);
            //get a line
            cin.getline(line, 100);
            char ele[100];
            init(ele, 100);
            // cout << "len of line " << strlen(line) << endl; 
            for(int j = 0; j < strlen(line); j++)
            {
                if(line[j]==','){
                    string x = ele;
                    rows[i].push_back(x);
                    // cout<<x<<endl;
                    init(ele, 100);
                }else{
                    ele[strlen(ele)] = line[j];
                    if(j == strlen(line) - 1){
                        string x = ele;
                        rows[i].push_back(x);
                        // cout<<x<<endl;
                    }
                    
                }
            }
            
        }

        int col1, col2, row1, row2;
        bool found = false;
        for(int i = 0; i < colN; i++)
        {
            for(int j = i+1; j < colN; j++)
            {
                map<pair<string, string>, int> mymap;
                for(int k = 0; k < rowN; k++)
                {
                    pair<string, string> mk = make_pair(rows[k][i],rows[k][j]);
                    // cout << "row no:" << k << " " << "xy = " << xy <<endl;
                    if(mymap.count(mk)){
                        col1 = i;
                        col2 = j;
                        row1 = mymap[mk];
                        // cout << "mk.xy" << mk.xy << endl;
                        row2 = k;
                        found = true;
                        break;
                    }else{
                        mymap[mk] = k;
                    }
                }
                if(found) break;
            }
            if(found) break;
        }

        if(found){
            cout << "NO" << endl;
            cout << row1+1 << " " << row2+1 <<endl;
            cout << col1+1 << " " << col2+1 <<endl;
        }else{
            cout << "YES" << endl;
        }

        // cout << "end this" <<endl;
        
        

        
    }
}