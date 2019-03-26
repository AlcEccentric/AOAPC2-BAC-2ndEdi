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
// 和之前那道题一样，这道题看上去像是模拟题，实际上无法模拟，但是无法模拟的原因不是计算量过大，而是无法表示
// 假设树有256个节点，除了叶子节点，每个节点只有左子树，则树高256，如果要用数组表示这棵树，则数组的size应为2^256-1
// 即使内存放得下这么大的数组，更严重的是无法用下标取元素，比如叶子节点的下标是2^255，即使是用long long也无法表示这个数
// 因此不应该用模拟的方法
// 以下方法是自己想的，并不是很难想：按照路径排序，然后检查每条根到叶子的路径
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