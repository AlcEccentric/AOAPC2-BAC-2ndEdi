#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
void init(char *x, int size){
    for(int i = 0; i < size; i++){
        x[i] = '\0';
    }
}
int getLen(char *x, char *y){
    int leny = strlen(y);
    int lenx = strlen(x);
    bool succeed ;
    int cY = 0;
    int cX = 0;
    for(cY = 0; cY < leny; cY++)
    {
        succeed = true;
        for(cX = 0; cX < lenx; cX++)
        {
            if(x[cX] != '2') continue;
            // here x[cX] must be '2'
            if(cY+cX >= leny){
                break;
            }
            if(y[cY+cX] == '2'){
                succeed = false;
                break;
            }
        }
        if(succeed) break;
    }
    
    if(lenx+cY > leny)
        return lenx+cY;
    else
        return leny;
}
int main(){
    char x[105], y[105];
    init(x, 105);
    init(y, 105);
    while(cin.getline(x, 105) && cin.getline(y, 105)){
        // cout<<"x:" << x<<" len:"<< strlen(x) << endl;
        // cout<<"y:" << y<<" len:"<< strlen(y) << endl;
        // 因为我的这个方法是一个子串保持不动另一个移动，然后进行分析
        // 但是发现在一些特殊情况计算出的结果是错的
        // ver1: 移动短的串，固定长的串
        // 但是对于2221和121212这样的例子就会失败
        // 观察这个例子只后就打算移动字典序小的串(121212)
        // ver2: 移动字典序小的串 对于2222和12111失败
        // ver3: 如果长度不等移动短的串，否则移动字典序小的串 对于2222和1211失败
        // 之后又有一些想法，比如如果发现对应位置上x，y各有一个'2'，则往前找'1'
        // 谁先找到'1'谁移动，但是发现对于212和122这样的样例，就会变成无限循环比较
        // 后来定下神来重新思考，当前纠结的是两个串先移动谁的问题，仔细一想发现这个问题没有纠结的必要：
        // 根据已有的算法，不管先移动谁，最后都能"咬合"，两种移动方法给出的长度都是有效的
        // 也就是说，现在有多种求解方法，并且这些方法的想法相似，只是部分条件不同(谁先移动)
        // 1. 方法的选择并不影响结果的有效性(valid)，但是得到结果未必是最优的(optimal)
        // 2. 只有有限多种(2种)求解方法
        // 3. 目的是找到最优解，而任何一种方法都有可能成为最优解
        // 
        // 因此，上述条件保证了，即使将这有限多种方法分别求解，再从中选择得到最优解，也不会造成错误或者过大开销

        int res1 = getLen(x, y);
        int res2 = getLen(y, x);
        if(res1 < res2){
            cout<< res1 <<endl;
        }else{
            cout<< res2 <<endl;
        }
    }
    return 0;
}