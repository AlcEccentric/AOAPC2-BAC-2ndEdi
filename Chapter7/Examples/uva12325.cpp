#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <algorithm>
#define For(i,e) for(i = 0; i < (e); i++)
#define Forr(i,s,e) for(i = (s); i < (e); i++)
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
// 最近好弱啊，连续三题看了题解，实在是没心情再刷了
// 这道题搞完，我要去搞一会图形学了，目测七月结束也就能刷到120题了，随意了，注意质量比数量重要，心情好了再来认真思考刷题。。
// 看题目显然是枚举，那么既然枚举肯定要枚举量尽可能少
// 显然n/s2 和 n/s1都是可能的枚举次数，刚开始的想法是二者选小的枚举，然而在s1 s2都是很小的数而n为很大的数的时候，枚举量还是很大
// 于是我看了题解...
// 在s1 s2都不足够大时（即s1 * s2 < n），如果v1 * s2 >= v2 * s1意味着如果宝物2选满了s1个，则这s1个宝物2必定可以换成s2个宝物1，并取得更高价值，因此宝物2的个数不可能超过s1，
// 另一种情况同理。此时，枚举量就只是s1或s2
long n, s1, v1, s2, v2, maxv;
void init(){
    maxv = 0;
}
int main(){
    int caseNum;
    cin >> caseNum;
    int i;
    For(i, caseNum){
        init();
        cin >> n >> s1 >> v1 >> s2 >> v2;
        if(s1 * s2 >= n){//s1 or s2 is big enough
            if(n/s1 < n/s2){
                // 枚举1
                long j, e = n/s1;
                For(j, e+1){
                    maxv = max(v1 * j + v2 * ((n - j * s1)/s2), maxv);
                }
            }else{
                long j, e = n/s2;
                For(j, e+1)
                    maxv = max(v2 * j + v1 * ((n - j * s2)/s1), maxv);
            }
        }else{
            if(s1*v2 >= s2*v1){
                // 每s1*s2的容积，每选s2个1都不如选s1个2更划算，因此1的个数不可能超过或等于s2
                // 注意！！！这并不意味着对于s1*s2的体积全选2就是最优解，以上这句话只是证明全选2比全选1好，不代表比他们在该体积限制下的所有组合好
                long j;
                For(j, s2){//枚举1
                    maxv = max(v1 * j + v2 * ((n - j * s1)/s2), maxv);
                }
            }else{
                // 每s1*s2都选1更划算
                long j;
                For(j, s1){//枚举2
                    maxv = max(v2 * j + v1 * ((n - j * s2)/s1), maxv);
                }
            }
        }
        cout << "Case #" << i+1 << ": " << maxv << "\n";
    }
}