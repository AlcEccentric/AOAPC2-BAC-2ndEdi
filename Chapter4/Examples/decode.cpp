#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
int decodeForChar(const char* dict, const int len, const int octNum){
    int ind = (int)(pow(2, len) - len - 1) + octNum;
    return ind;
}
void init(char * x, int count){
    for(int i = 0; i < count; i++)
    {
        /* code */
        x[i] = '\0';
    }
    
}
bool isAllOne(char* charcode, int len){
    for(int i = 0; i < len; i++)
        if(charcode[i] == '0') return false;
    return true;
}
int main(){
    char dict[1000];
    // char code[10000];
    init(dict, 1000);
    // init(code, 10000);
    while(cin.getline(dict, 1000)){
        // cout<<"dict:"<<dict<<endl;
        char ch[4];
        init(ch, 4);
        while(1){  
            //  cout<<ch<<endl;
            // get len of each char code unit
            for(int i = 0; i < 3;){
                cin.get(ch[i]);
                // cout<<"lenC["<<i<<"]="<<ch[i]<<endl;
                if(ch[i] == '\n'){
                    ch[i] = '\0';
                    continue;
                }else{
                    i++;
                }
            }
            // cout<<"lenC:"<<ch<<endl;
            int len = 0;
            for(int i = 0; i < 3; i++){
                len += pow(2, 2-i)*(ch[i]-'0');
            }
            if(len == 0) {
                char useless;
                cin.get(useless);
                break;
            }
            // cout<<"len:"<<len<<endl;
            char charcode[15];
            init(charcode, 15);
            while(1){
                // get each char code unit's octnum
                int octNum = 0;
                for(int i = 0; i < len;){
                    char x;
                    cin.get(x);
                    // cout<<"x:"<<x<<" ";
                    if(x == '\n'){
                        continue;
                    }else{
                        charcode[i] = x;
                        octNum += (x-'0')*pow(2,len-i-1);
                        i++;
                    }
                }
                
                if(isAllOne(charcode, len)) {
                    break;
                }
                // cout<<"charcode:"<<charcode<<" oct:"<<octNum<<endl;
                cout<<dict[decodeForChar(dict, len, octNum)];
                init(charcode, 15);
            }
            init(ch, 4);
        }
        cout<<endl;
        init(dict, 1000);
        // init(code, 10000);
    }
}