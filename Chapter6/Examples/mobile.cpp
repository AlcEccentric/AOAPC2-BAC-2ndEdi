#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
using namespace std;
ifstream cin("test.in");
ofstream cout("test.out");
// NOTE:
// 不要在做题前做任何假设
// 如果做了，如果读完题感觉假设好像是对的，将自己的假设写下来，去实现代码
// 如果WA，则将自己做过的假设一个个确认是否正确（如果不确定，则认定为错误）
// 判断某个之前认定的假设错误后，据此修改代码逻辑，再去debug，如果依然WA，重复上述步骤
// 直到所有假设都被验证
// 如果依然错误再去思考其他的原因
void init(char * x, int count){
    for(int i = 0; i < count; i++)
        x[i] = '\0';
}

bool getInput(int & w){
    int wl, dl, wr, dr;
    cin >> wl >> dl >> wr >> dr;
    // cout << wl << dl << wr << dr << endl;
    if(wl != 0 && wr != 0){
        // leaf
        w = wl + wr;
        return wl*dl == wr*dr;
    }
    // 下面两行写法会导致错误
    // 这样写会导致天平输入数据读取错误
    // 即如果第一个if失败则立刻返回的话，当前节点的右子树内容会被当成右兄弟的内容读取
    // 因此需要用两个变量保存左右的返回值
    // if(!getInput(wl)) return false;
    // if(!getInput(wr)) return false;
    bool leftIsBal = true;
    bool rightIsBal = true;
    // 只有当某端重量为0时才存在子悬臂（做题前做出了一个题目未说明的错误假设：所有有子悬臂的悬臂其两端都是子悬臂，实际上可以是一端有子悬臂(w为0)，另一端为一个重物(w非0)）
    // 才有必要读取子悬臂并更新这一端的重量值
    // 同样这种情况没有在udebug样例中给出
    if(wl == 0)
        leftIsBal = getInput(wl);
    if(wr == 0)
        rightIsBal = getInput(wr);
    // 这个天平平衡的条件是每一个悬臂都要平衡
    // 而不只是最顶端的悬臂保持平衡
    // udebug中的样例没有子悬臂不平衡的情况，因此无法发现这一点
    // 仔细想想这一点很reasonable，如果只要判断最顶端悬臂平衡的话
    // 为啥输入要给你子悬臂的两个力矩呢？直接给两端重量不就行了
    if(leftIsBal == false || rightIsBal == false) return false;

    w = wl + wr;
    return  wl*dl == wr*dr;
}
int main(){
    int testCaseNum = 0;
    cin >> testCaseNum;
    while(testCaseNum){
        int w;
        bool thisTreeIsBal = getInput(w);
        if(thisTreeIsBal){
            cout << "YES\n";
        }else{
            cout << "NO\n";
        }
        if(testCaseNum != 1)  cout << endl;
        testCaseNum--;
    }
}