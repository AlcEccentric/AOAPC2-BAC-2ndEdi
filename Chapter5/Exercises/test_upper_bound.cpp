#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <set>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
// NOTE:
// 关于最小堆set的set::lower_bound(p)和set::upper_bound(p)：
// 查看了c++官方文档后，发现
// 之前对set::lower_bound(p)和set::upper_bound(p)的理解有误
// 其实这俩找到的结果都不会比p"小"
// lower_bound找的是"大于等于"p的最"小"值
// upper_bound找的是"大于"p的的最“小”值
// 因此如果想找到“小于”或者“小于等于”的值
// 需要分别使lower_bound和upper_bound返回的迭代器向前（“小”的方向）移动一位（--）
// 当然在这之前需要检查返回的迭代器是否已经是begin
// 这里所说的“大”和“小”加引号是因为真正的“大”“小”取决于对set中成员的<符号的实现
// c++ 中的set实现是最小堆，即begin()指向最“小”的元素

struct node{
    int a;
    int b;
    node(int a, int b):a(a), b(b) {};
    bool operator < (const node& n) const{
        if(a < n.a) return true;
        else if(a > n.a) return false;
        else{
            if(b < n.b) return true;
            else return false;
        }
    }
    
};
ostream& operator << (ostream& out, const node& n){
    out<<"("<<n.a<<","<<n.b<<")";
    return out;
}
int main(){
    set<int> nums;
    nums.insert(1);
    nums.insert(3);
    nums.insert(5);
    cout << *nums.upper_bound(2) << endl; // should be 3
    cout << *nums.upper_bound(3) << endl; // should be 5
    cout << *nums.lower_bound(2) << endl; // should be 3
    cout << *nums.lower_bound(3) << endl; // should be 3

    
    set<node>nodes;
    nodes.insert(node(1, 2));
    nodes.insert(node(1, 4));
    nodes.insert(node(3, 2));
    nodes.insert(node(3, 4));
    cout << *nodes.upper_bound(node(1,2)) << endl;
    cout << *nodes.upper_bound(node(1,3)) << endl;
    cout << *nodes.upper_bound(node(2,1)) << endl;
    cout << *nodes.lower_bound(node(1,3)) << endl;
    cout << *nodes.lower_bound(node(2,1)) << endl;
    cout << *nodes.lower_bound(node(1,2)) << endl;
    cout << *nodes.upper_bound(node(3,2)) << endl;
    cout << *nodes.upper_bound(node(2,3)) << endl;

}