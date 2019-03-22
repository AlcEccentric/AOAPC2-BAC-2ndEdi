#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
// NOTE:
// 1.链表的数组表示，注意lrj这里给出的代码给出了一种新的、实现非常方便的链表表示，
// 对要放入链表中的每个元素赋予一个编号，比如在这道题的代码中，字符串的第一个字符编号为1，其他字符类推
// 用一个大的int数组存放链表的link信息，这个数组的index值代表了对应的元素编号，数组中的每个数代表当前这个位置index对应的元素在链表中的下一个元素
// 比如array[i] = j;说明编号i的元素在链表中的下一个元素是编号j的元素
// 为了方便操作头结点和判断最后一个节点，令index值为0代表伪头结点编号，数组值为0代表空指针
// 因此，array[0]的值指向链表中第一个有意义的元素（真正的头结点），当array[i] == 0则可以判断i号元素是链表的最后一个元素
// 2. getline的第二个参数
// getline的第二个参数代表的是读一行中的几个字符，想要getline返回非空值，必须将第二个参数设置得足够大
// 即第二个参数的值应该大于该行中可能出现的最大字符数，注意是大于不是大于等于，因为getline必须读到行尾的\n才能返回非空值
// 比如某一行是xxx，而getline的第二个参数为3，则返回值为空，因为getline没有读到这一行最后的\n，因此想要正确读入这一行
// 第二个参数至少为4，同时，保险起见，存放这一行内容的char数组大小也应该开得比这一行所能含有的字符数要大一点
// 3. 注意固定从头插入会导致顺序颠倒（如果插入的位置是当前访问链表元素的next）
// 这道题遇到[的操作是把游标设置为链表头，但是每次在头部插入一个元素，就要将该游标指向最新插入的元素，这样元素顺序才不会与插入顺序相反
//  abcd从左到右固定插入链表头之后的话，结果是dcba，如果每次将游标锁定为新插入的元素，则结果为abcd

void init(char *x, int count){
    for(int i = 0; i < count; i++)
    {
        x[i] = '\0';
    }
    
}

void init(int *x, int count){
    for(int i = 0; i < count; i++)
    {
        x[i] = 0;
    }
    
}
const int maxn = 100000 + 5;
int main(){
    char line[maxn];
    init(line, maxn);
    
    while(cin.getline(line + 1, 100004)){
        int next[maxn];
        init(next, maxn);
        int cur = 0, last = 0;
        for(int i = 1; line[i] != '\0'; i++){
            if(line[i] == '[') cur = 0;
            else if(line[i] == ']') cur = last;
            else {
                int tmp = next[cur];
                next[cur] = i;
                next[i] = tmp;
                if(cur == last) {
                    last = next[cur];
                    cur = last;
                }else{
                    cur = next[cur];
                }
            }
        }
        // for(int i = 0; i != 30; i++)
        // {
        //     cout << next[i] << " ";
        // }
        // cout << endl;
        
        for(int i = next[0]; i != next[last]; i = next[i])
            cout << line[i];
        cout << endl;

        init(line, maxn);
    }
}