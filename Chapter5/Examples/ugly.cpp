#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <set>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
// NOTE:
// 1. 方法一：遍历
// 从1开始每次+1得到下一个数，模2/3/5，那个模为0则除，除完的结果再去模2/3/5，直到三次取模都不能得0则退出，判断结果是否为1
// 如果为1，则说明是丑数，加入Set，直到set的大小为1500，则退出，输出最大的数
// 问题：第1500个丑数已经上亿，用+ 1的方法去遍历判断，非常慢，到最后需要大约3分钟才能找到第1500个丑数
// 这个复杂度有点难算，1500是8亿，斜率已经40000，而一开始的斜率只有1左右，从结果来看，时间复杂度应该类似一个指数级别的增长
// 2. 方法二：
// 在计算丑数的过程中发现，下一个新的丑数必然是已经得到的某个丑数的2/3/5倍（反证法可以证明），因此目标找到这个数
// 也就是目的是在已有的丑数集合中找到这样一个丑数，这个丑数*2/3/5大于已经找到的最大丑数，并且是所有这样的丑数中最小的
// 举个例子已经找到当前最大丑数72，对于2，40就是这样的一个丑数(40, 45...*2都能大于72而40是这些丑数中最小的)，对于5，15就是这样的一个丑数
// 对2、3、5分别找到这样的丑数后，分别乘2/3/5，这三个数中较小的那一个就是下一个丑数
// 因此接下来要做的是用高效的方法找到这样的丑数
// 2.1 找到上述的丑数，线性方法
// 从最大丑数/x(x=2/3/5)+1这个数开始，每次判断是否在已有的丑数集合中，不在，则加1直到找到那个丑数，
// 依然是很昂贵的，因为第1500个丑数已经上亿，平均每个丑数之间间隔都已经大于一万，如果/x+1的结果正好比某个丑数大1，则找到下一个丑数平均就得走几万步
// 2.2 由于Set的实现基于二叉排序树，因此在树中找到大于某个值的最小元素其实只需要log的时间复杂度
// 因此正确的方法是使用set的lower_bound函数，找到丑数堆中大于等于最大丑数/x+1的那个元素，这样寻找的时间复杂度就变成log
// 对每个数都要进行常数(3)次的查找，因此时间复杂度是c*n*logn，比指数降了不少
// PS：自己想的结果，虽然想了很久如何实现，但是是自己想出来的哦
long smallest(long x, long y, long z){
    long min = x < y ? x : y;
    min = z < min ? z : min;
    return min;
}

int main(){
    set<long> nums;
    nums.insert(1);
    while(nums.size()!=1500){
        long maxNum = *(nums.rbegin());
        long t2 = maxNum/2 + 1;
        long t3 = maxNum/3 + 1;
        long t5 = maxNum/5 + 1;
        set<long>::iterator i2 = nums.lower_bound(t2);
        set<long>::iterator i3 = nums.lower_bound(t3);
        set<long>::iterator i5 = nums.lower_bound(t5);
        nums.insert(smallest(2*(*i2), 3*(*i3), 5*(*i5)));
    }
    cout << "The 1500'th ugly number is " << *(nums.rbegin())<<"." << endl;

}