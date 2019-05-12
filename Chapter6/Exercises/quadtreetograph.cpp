#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <stack>
#include <set>
#include <queue>
using namespace std;
// 注意全黑的情况/即根节点是黑的的情况，这种情况下，输出值为0，而不是没有输出
// lrj书上题目的意思似乎是根节点是没有标号的，只有从第一层开始才有1234的标号
// 所以误以为根节点不管是白是黑都不输出值，英文题说明了根节点为黑时输出0
// ifstream cin("test.in");
// ofstream cout("test.out");
int graph[70][70];
set<int> resNodes;
stack<int> curRoute;
void init(){
    for (int i = 0; i < 70; i++)
        for (int j = 0; j < 70; j++)
            graph[i][j] = -1;
    resNodes.clear();
    while(curRoute.size())
        curRoute.pop();
}
bool allBlack(int a, int b, int c, int d){
    return a == 1 && b == 1 && c == 1 && d == 1;
}
bool allWhite(int a, int b, int c, int d){
    return a == -1 && b == -1 && c == -1 && d == -1;
}
int genNode(stack<int> curRoute, int first){
    int num = first;
    // cout << first << " ";
    while(curRoute.size()){
        // cout << curRoute.top() << " ";
        num = num * 5 + curRoute.top();
        curRoute.pop();
    }
    // cout << endl;
    return num;
}
int toNodes(int hs, int he, int vs, int ve, int curPos){
    if(curPos) curRoute.push(curPos);
    if(he - hs == 1){
        // cout << "" << vs << "," << hs << " ";
        if(graph[vs][hs]) {
            // cout << "is Black" << endl;
            return 1; // 1
        }
        else {
            // cout << "is White" << endl;
            return -1; // 0
        }
    }
    int nw = toNodes(hs, (hs+he)/2, vs, (vs+ve)/2, 1); // NW
    curRoute.pop();
    int ne = toNodes((hs+he)/2, he, vs, (vs+ve)/2, 2); // NE
    curRoute.pop();
    int sw = toNodes(hs, (hs+he)/2, (vs+ve)/2, ve, 3); // SW
    curRoute.pop();
    int se = toNodes((hs+he)/2, he, (vs+ve)/2, ve, 4); // SE
    curRoute.pop();
    // cout << "[" << vs << "," << hs << "] to [" << ve-1 << "," << he-1 << "]:" << endl;
    if(allBlack(nw, ne, sw, se)){
        // cout << "is Black" << endl;
        return 1;
    }else if(allWhite(nw, ne, sw, se)){
        // cout << "is White" << endl;
        return -1;
    }else{
        // cout << "is Grey" << endl;
        // cout << "cur pos " << curPos << endl;
        if(se == 1){
            int SE = genNode(curRoute, 4);
            resNodes.insert(SE);
        }
        // assert(curRoute.size());
        if(sw == 1){
            int SW = genNode(curRoute, 3);
            resNodes.insert(SW);
        }
        if(ne == 1){
            int NE = genNode(curRoute, 2);
            resNodes.insert(NE);
        }
        if(nw == 1){
            int NW = genNode(curRoute, 1);
            // cout << "NW node = " << NW << endl; 
            resNodes.insert(NW);
        }
        return 0;
    }

}
void printNodes(int imgNo){
    cout << "Image " << imgNo << endl;
    if(resNodes.size() >= 12){
        vector<int> nodes;
        for(set<int>::iterator ii = resNodes.begin(); ii != resNodes.end(); ii++){
            nodes.push_back(*ii);
        }
        int count = 0;
        for(vector<int>::iterator ii = nodes.begin(); ii != nodes.end(); ii++){
            if(((count%11 == 0 && count) || ii + 1 == nodes.end())){
                cout << *ii << endl;
                count = 0;
            }else {
                cout << *ii << " ";
                count++;
            }
        }
    }else{
        int count = 0;
        for(set<int>::iterator ii = resNodes.begin(); ii != resNodes.end(); ii++){
            cout << *ii;
            if(count == resNodes.size()-1) cout << endl;
            else cout << " ";
            count++;
        }
    }
    cout << "Total number of black nodes = " << resNodes.size() << "\n";
}
void fillSquare(queue<int>& route, int hs, int he, int vs, int ve){
    //这里是填，当route没数字，说明当前方块不需再切割，是一个黑色整块
    if(route.size() == 0){
        for(int i = vs; i < ve; i++)
            for(int j = hs; j < he; j++)
                graph[i][j] = 1;
        return;
    }
    //下面是切,当route还有数字就需要切割得到目标所在子方块的范围
    int pos = route.front();
    route.pop();
    if(pos == 1){//NW
        fillSquare(route, hs, (hs+he)/2, vs, (vs+ve)/2);
    }else if(pos == 2){//NE
        fillSquare(route, (hs+he)/2, he, vs, (vs+ve)/2);
    }else if(pos == 3){//SW
        fillSquare(route, hs, (hs+he)/2, (vs+ve)/2, ve);
    }else{//SE
        fillSquare(route, (hs+he)/2, he, (vs+ve)/2, ve);
    }

}
void printGraph(int n, int imgNo){
    cout << "Image " << imgNo << endl;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++)
        {
            if(graph[i][j]) cout << "*";
            else cout << ".";
        }
        cout << endl;
    }   
}
int main(){
    int n;
    int imgNo = 1;
    while(cin >> n && n != 0){
        if(imgNo != 1 && n != 0) cout << endl;
        if(n > 0){
            // graph to tree
            init();
            cin.ignore();
            for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                    char c;
                    cin.get(c);
                    graph[i][j] = c - '0';
                }
                cin.ignore();
            } 
            bool foundWhite = false;
            for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                    if(graph[i][j] == 0){
                        foundWhite = true;
                    }
                }
            }
            if(foundWhite)
                toNodes(0, n, 0, n, 0);
            else
                resNodes.insert(0);
            printNodes(imgNo);
        }else{
            // tree to graph
            init();
            for (int i = 0; i < -n; i++)
                for (int j = 0; j < -n; j++)
                    graph[i][j] = 0;
            n = -n;
            int num;
            while(cin >> num && num != -1){
                queue<int> route;
                while(num){
                    route.push(num % 5);
                    num = num / 5;
                }
                fillSquare(route, 0, n, 0, n);
                while(route.size()) route.pop();
            }
            printGraph(n, imgNo);
        }
        imgNo++;
    }
}