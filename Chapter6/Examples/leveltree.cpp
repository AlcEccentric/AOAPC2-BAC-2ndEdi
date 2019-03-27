#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <cctype>
#include <set>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
// NOTE:
// 1. 和之前那道题一样，这道题看上去像是模拟题，实际上无法模拟，但是无法模拟的原因不是计算量过大，而是无法表示
// 假设树有256个节点，除了叶子节点，每个节点只有左子树，则树高256，如果要用数组表示这棵树，则数组的size应为2^256-1
// 即使内存放得下这么大的数组，更严重的是无法用下标取元素，比如叶子节点的下标是2^255，即使是用long long也无法表示这个数
// 因此不应该用模拟的方法
// 以下方法是自己想的，并不是很难想：按照路径排序，然后检查每条根到叶子的路径
// 2. lrj给出的方法是用动态生成树，即生成树的节点，用指针连接节点生成树.
// 说实话我觉得lrj给的方法其实不够直观简单，而且指针在debug的时候比较容易出现问题
// 不过不失为一种参考
// 3. lrj的代码中还给出了用数组实现动态二叉树的方法（即只对有值的节点分配内存），方法是
// 用序号代表有值的节点，用两个数组left和right数组存放对应节点的两个孩子的序号，用一个数组value存放对应节点的值
// 4. 同时在这一部分lrj还提出了用Node数组作内存池防止内存泄漏的二叉树指针表示法，即静态分配一个大数组，同时准备一个freelist存放所有数组元素的指针
// 当分配新节点时就将freelist的指针给出，当节点不再需要时，就将指向该数组元素的指针放回freelist以备再用
struct node{
    string route;
    int num;
    bool operator < (const node& n) const{
        if(strlen(route.c_str()) > strlen(n.route.c_str())) return false;
        else if(strlen(route.c_str()) < strlen(n.route.c_str())) return true;
        else{
            return strcmp(route.c_str(), n.route.c_str()) < 0;
        }
    };
};

void init(char *x, int count){
    for(int i = 0; i < count; i++)
        x[i] = '\0';
}

int main(){
    
    string x;
    while(cin >> x){
        set<node> tree;
        bool goNextTestCase = false;
        do{
            // cout << x <<endl;
            if(strcmp(x.c_str(), "()") == 0) break;
            char num[11];
            init(num, 11); 
            int i;
            for(i = 1; i < strlen(x.c_str()); i++)
            {
                if(x[i] == ',') {
                    i++;
                    break;
                }
                num[strlen(num)] = x[i];
            }
            char route[260];
            init(route, 260);
            for( ;i < strlen(x.c_str()); i++)
            {
                if(x[i] == ')') break;
                route[strlen(route)] = x[i];
            }
            node n;
            n.route = route;
            n.num = atoi(num);
            // cout << "route: " << route << endl;
            // cout << "num: " << num << endl;
            // cout << endl;
            if(tree.count(n) && !goNextTestCase) {
                goNextTestCase = true;
                // cout << "at (" << n.route << ")" << endl;
                cout << "not complete" << endl;
            }
            tree.insert(n);
        }while(cin >> x);
        if(goNextTestCase) continue;
        // check route complete;
        int leafDepth = strlen(tree.rbegin()->route.c_str());
        bool somewrong = false;
        // cout << "check route complete" << endl;
        for(set<node>::reverse_iterator j = tree.rbegin(); j != tree.rend(); j++)
        {
            if(strlen(j->route.c_str()) != leafDepth) break;
            char route[260];
            init(route, 260);
            strcpy(route, j->route.c_str());
            while(strlen(route)){
                route[strlen(route) - 1] = '\0';
                node tn;
                tn.route = route;
                // cout << route << endl;
                if(tree.count(tn) != 1){
                    somewrong = true;
                    // cout << "at (" << route << ")" << endl;
                    cout << "not complete" << endl;
                    break;
                }
            }
            if(somewrong) break;
        }
        if(somewrong) continue;
        // cout << "size: " << tree.size() << endl;
        for(set<node>::iterator j = tree.begin(); j != tree.end(); j++)
        {
            if(j == tree.begin()) cout << j->num;
            else cout << " " << j->num;
        }
        cout << endl;

        
        
    }
}