#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <math.h>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
void init(char *x, int count){
    for(int i = 0; i < count; i++)
    {
        x[i] = '\0';
    }
}
int getOct(char * ip, int lastDotInd, int curDotInd){
    int res = 0;
    for(int i = lastDotInd + 1; i < curDotInd; i++)
        res = res * 10 + (ip[i] - '0');
    return res;
}
void getBinChar(char* binChars, int octNum){
    if(octNum >= 256 || octNum <= -1){
        exit(1);
    }
    binChars[8] = '\0';
    int ind = 7;
    while(octNum != 0){
        binChars[ind] = octNum % 2 + '0';
        octNum /= 2;
        ind--;
    }
    if(ind != -1){
        for(int i = 0; i <= ind; i++)
            binChars[i] = '0';
    }
}
void getOctChar(const char* octChars, const int startInd, int& res){
    res = 0;
    for(int i = 0; i < 8; i++){
        res += (octChars[startInd + i] - '0') * (int)pow(2, 7-i);
    }
}
int main(){
    int num;
    while(cin>>num){
        cin.ignore();
        char IPs[1005][40];
        char ip[20];
        for(int i = 0; i < num; i++){
            init(ip, 20);
            init(IPs[i], 40);
            cin.getline(ip, 20);
            // cout << "IPs["<<i<<"] = "<<IPs[i]<<endl;
            int lastDot = -1;
            int cpDst = 0;
            for(int j = 0; j <= strlen(ip); j++){
                if(ip[j] == '.' || ip[j] == '\0'){
                    int seg = getOct(ip, lastDot, j);
                    char bi[9];
                    getBinChar(bi, seg);
                    strncpy(&IPs[i][cpDst], bi, 8);
                    lastDot = j;
                    cpDst+=8;
                }
            }
            // cout<< IPs[i] << endl;
        }
        int firstNotEqualInd = 32;
        for(int i = 0; i < 32; i++){
            bool equal = true;
            for(int j = 1; j < num; j++){
                if(IPs[j-1][i] != IPs[j][i]){
                    // cout << "unequal i = " <<i<<endl;
                    equal = false;
                    firstNotEqualInd = i;
                    break;
                }
            }
            if(!equal)
                break;
        }
        char subnetIP[40], mask[40];
        init(subnetIP, 40);
        init(mask, 40);
        strncpy(subnetIP, IPs[0], 32);
        for(int i = 0; i < 32; i++)
            mask[i] = '1';
        for(int i = firstNotEqualInd; i < 32; i++){
            mask[i] = '0';
            subnetIP[i] = '0';
        }
        // cout<< "Mask: "<<mask<<endl;
        // cout<< "SubnetIP: "<<subnetIP<<endl;
        int ipSeg[4], maskSeg[4];
        for(int i = 0; i < 4; i++){
            getOctChar(subnetIP, i*8, ipSeg[i]);
            getOctChar(mask, i*8, maskSeg[i]);
        }
        for(int i = 0; i < 4; i++){
            if(i != 3){
                cout<<ipSeg[i] << ".";
            }else{
                cout<<ipSeg[i] << "\n";
            }
        }
        for(int i = 0; i < 4; i++){
            if(i != 3){
                cout<<maskSeg[i] << ".";
            }else{
                cout<<maskSeg[i] << "\n";
            }
        }
        
        
            
        

        
        
    }
}