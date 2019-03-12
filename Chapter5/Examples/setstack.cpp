#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <algorithm>
#include <set>
#include <stack>
#include <map>
#include <vector>
// 这道题集合的表示是核心，
// 看了提示，想了半天大概想到集合用set<int>表示，每生成一个集合要去判断这个新生成的集合是否在之前已经生成过
// 问题就在于怎么判断已经生成过，想着用set里的数组合成一个字符串代表这个set，然后和id构成一个map，然而总觉得
// 组合成字符串的方法会出错，看了题解知道了一个很重要的信息：
// STL也可以作为map的key，因此根本没必要尝试用其他形式表达set作为key，直接用set作为key即可
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
typedef set<int> Set;
static int ID = 0;

int getID(Set &thisSet, map <Set, int> &SetIDMap, map<int, Set> &IDSetMap){
    // 如果已生成，返回对应ID
    // 如果未生成，返回新的ID，将新的ID和该set的映射放入map
    if(SetIDMap.count(thisSet)){
        return SetIDMap[thisSet];
    }else{
        int retID = ID;
        ID++;
        SetIDMap[thisSet] = retID;
        IDSetMap[retID] = thisSet;
        return retID;
    }
}
int main(){
    int testCaseNum;
    cin >> testCaseNum;
    while(testCaseNum != 0){
        map <Set, int> SetIDMap;
        map <int, Set> IDSetMap;
        stack<int> setStack;
        int actNum;
        cin >> actNum;
        while(actNum != 0){
            // cout<<actNum<<endl;
            // cout << setStack.size() << endl;
            string s;
            cin >> s;
            // cout << s <<endl;
            if(strcmp(s.c_str(), "PUSH") == 0){
                Set thisSet;
                int id = getID(thisSet, SetIDMap, IDSetMap);
                setStack.push(id);
            }else if(strcmp(s.c_str(), "DUP") == 0){
                int id = setStack.top();
                setStack.push(id);
            }else if(strcmp(s.c_str(), "UNION") == 0){
                int id1 = setStack.top();
                setStack.pop();
                int id2 = setStack.top();
                setStack.pop();
                Set s1 = IDSetMap[id1];
                Set s2 = IDSetMap[id2];
                vector<int> thisSetVec;
                set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), back_inserter(thisSetVec));
                Set thisSet;
                for(auto num : thisSetVec)
                    thisSet.insert(num);
                int id = getID(thisSet, SetIDMap, IDSetMap);
                setStack.push(id);
            }else if(strcmp(s.c_str(), "INTERSECT") == 0){
                int id1 = setStack.top();
                setStack.pop();
                int id2 = setStack.top();
                setStack.pop();
                Set s1 = IDSetMap[id1];
                Set s2 = IDSetMap[id2];
                vector<int> thisSetVec;
                set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), back_inserter(thisSetVec));
                Set thisSet;
                for(auto num : thisSetVec)
                    thisSet.insert(num);
                int id = getID(thisSet, SetIDMap, IDSetMap);
                setStack.push(id);
            }else if(strcmp(s.c_str(), "ADD") == 0){
                int id1 = setStack.top();
                setStack.pop();
                int id2 = setStack.top();
                setStack.pop();
                Set thisSet = IDSetMap[id2];
                thisSet.insert(id1);
                int id = getID(thisSet, SetIDMap, IDSetMap);
                setStack.push(id);
            }
            actNum--;
            cout<<IDSetMap[setStack.top()].size()<<endl;
        }
        testCaseNum--;
        cout<<"***"<<endl;
    }
    

}