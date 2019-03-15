#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <map>
#include <vector>
#include <set>
#include <math.h>
#include <algorithm>
using namespace std;
// ifstream  cin("test.in");
// ofstream  cout("test.out");
// NOTE:
// 1. sort函数的第三个参数和qsort函数的最后一个参数
// 两者都是自定义比较函数的函数指针，但是函数签名不同
// qsort : int mycmp(const void* x, const void* y)
// sort : bool mycmp(<element type> x, <element type> y)
// 2. 这道题有边界条件
// 即所有点的x坐标相同，或者多个点的x坐标相同
// 由于策略是比较“两侧”点和轴的横向绝对值距离
// 因此计算绝对值横向距离时要注意去除在轴上的点
// 注意：当点的个数为奇数和偶数时，中心轴的计算方法以及去除在轴上的点的流程都有一定不同，见52-72行
// 3. 也许还有更好的方法

struct point{
    int x;
    int y;
    point(const int x, const int y): x(x), y(y){};
};

bool mycmp(point a, point b){
    return a.x > b.x;
}

int main(){
    int testCaseNum; 
     cin >> testCaseNum;
    for(int i = 0; i < testCaseNum; i++)
    {
        int dotsNum;
         cin >> dotsNum;
        vector<point> dots;
        for(int j = 0; j < dotsNum; j++)
        {
            int x, y;
             cin >> x >> y;
            dots.push_back(point(x, y));
        }
        sort(dots.begin(),dots.end(),mycmp);
        // for(auto p: dots){
        //      cout << p.x << endl;
        // }
        double midX;
        int midXTwice;
        if(dots.size()%2 == 1){
            int midPosInd = dots.size()/2;
            midX = dots[midPosInd].x;
            midXTwice = dots[midPosInd].x * 2;
            //  cout << "midX: " << midX << endl;
            dots.erase(dots.begin() + midPosInd);
            
        }else{
            int midPosInd = dots.size()/2;
            midX = (dots[midPosInd].x + dots[midPosInd-1].x) / 2.0;
            midXTwice = dots[midPosInd].x + dots[midPosInd-1].x;
        }
        //  cout << "midX: " << midX << endl;
        //  cout<<dots.size()<<endl;
        if(midXTwice%2 == 0){
            for(vector<point>::iterator ii = dots.begin(); ii != dots.end();){
                if(ii->x == (int)midX) ii = dots.erase(ii);
                else ii++;
            }
        }
        //  cout<<dots.size()<<endl;
        map<double, set<int> > absDistMap;
        for(auto p : dots){
            double absDist = fabs(p.x - midX);
            if(absDistMap[absDist].count(p.y)){
                absDistMap[absDist].erase(p.y);
            }else{
                absDistMap[absDist].insert(p.y);
            }
        }
        bool sym = true;
        for(map<double, set<int> >::iterator ii = absDistMap.begin(); ii != absDistMap.end(); ii++)
        {
            if(ii->second.size() != 0){
                sym = false;
                break;
            }
        }
        if(sym)  cout << "YES" << endl;
        else  cout << "NO" << endl;
        
        
        
    }
    
}