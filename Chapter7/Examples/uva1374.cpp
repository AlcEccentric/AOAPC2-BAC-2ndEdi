#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <stdlib.h>
#define For(i,e) for(i = 0; i < (e); i++)
#define Forr(i,s,e) for(i = (s); i < (e); i++)
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
// IDA
// 剪枝策略很简单，上一层传下来的最大幂指数x，如果剩余操作次数为y，则如果有x * 2 ^ y < target，则剪枝
// 意思是:假使当前及之后的每一步都让最大的幂指数与自身相加(2*x, 4*x, 8*x...)，
// 最后得到的最大可能加和仍然比目标指数值小时，说明无论如何加减都没法达到目标值，因此当前这步没有继续前进必要
int maxd, ans;
void printInfo(const int* nums, const int len, const int d, const int m){
    cout << "maxd: " << maxd << " depth: " << d << "\n";
    int i;
    For(i, len){
        cout << nums[i] << " ";
    }
    cout << "\nlast level largest: " << m << "\n";

};
bool dfs(const int target, const int d, int* nums, int* vis, const int len, const int m){
    // printInfo(nums, len, d, m);
    if(d == maxd){
        if(vis[target]) {
            ans = d;
            // printInfo(nums, len, d, m);
            return true;
        }
        else return false;
    }else{
        if(vis[target]) {
            ans = d;
            // printInfo(nums, len, d, m);
            return true;
        }
        else{
            if(m*pow(2, maxd-d) < target) return false;// 剪枝
            // cout << "here " << m*pow(2, maxd-d) << "\n";
            // nums[len-1] - nums[len-1-i] i = 0...
            for(int i = 0; i <= len-1; i++){
                if(nums[len-1]>nums[i]){
                    int x = nums[len-1] - nums[i];
                    if(!vis[x]){
                        nums[len] = x;
                        vis[x] = 1;
                        int nm = x > m ? x : m;
                        if(dfs(target, d+1, nums, vis, len+1, nm)) return true;
                        vis[x] = 0;
                    }
                }
                if(nums[len-1] <= target && nums[i] <= target){
                    int x = nums[len-1] + nums[i];
                    if(!vis[x]){
                        nums[len] = x;
                        vis[x] = 1;
                        int nm = x > m ? x : m;
                        if(dfs(target, d+1, nums, vis, len+1, nm)) return true;
                        vis[x] = 0;
                    }
                }
                
            }
            return false;
        }
       
    }
}
int main(){
    int n;
    while(cin>>n){
        if(!n) break;
        int nums[1000], vis[1025], len = 0;
        nums[len++] = 1;
        for(int i = 0; i < 1025; i++)
            vis[i] = 0;
        vis[1] = 1;
        for(maxd = 0; maxd < n; maxd++){
            if(dfs(n, 0, nums, vis, len, 1)) break;
        }
        cout << ans << "\n";
    }
}