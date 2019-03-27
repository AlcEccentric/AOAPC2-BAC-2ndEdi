#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <set>
using namespace std;
// NOTE:
// 对于树这种结构，递归的方法应该作为第一反应之一被想到
// ifstream cin("test.in");
// ofstream cout("test.out");
struct rec{
    int nodeValue;
    int sumValue;
    bool operator < (const rec& r) const{
        if(sumValue < r.sumValue) return true;
        else if(sumValue > r.sumValue) return false;
        else{
            return nodeValue < r.nodeValue;
        }
    };
};
void init(int * x, int count){
    for(int i = 0; i < count; i++)
        x[i] = -1;
}
int intlen(int * x){
    int i;
    for(i = 0; x[i] != -1; i++){

    }
    return i;
}
void init(char * x, int count){
    for(int i = 0; i < count; i++)
        x[i] = '\0';
}
int intcind(int * x, int target){
    for(int i = 0; x[i] != -1; i++){
        if(x[i] == target)
            return i;
    }
    return -1;
}

void printIntArray(int * a){
    for(int i = 0; a[i] != -1; i++){
        cout << a[i] << " ";
    }
    cout << endl;
}
set <rec> recs;
void getTheNode(int * mid, int * post, int sumFromAbove){
    if(intlen(mid) == 0 || intlen(post) == 0)
        return;
    if(intlen(mid) == 1 || intlen(post) == 1){
        // assert(mid[0] == post[0]);
        rec r;
        r.nodeValue = mid[0];
        r.sumValue = sumFromAbove + r.nodeValue;
        recs.insert(r);
        // cout << "r.nodeValue: " << r.nodeValue << endl;
        // cout << "r.sumValue: " << r.sumValue << endl;
        // cout << endl;
        return;
    }
    
    // cout << "mid: ";
    // printIntArray(mid);
    // cout << "post: ";
    // printIntArray(post);

    int thisNodeValue = post[intlen(post) - 1];
    
    // cout << "this node: " << thisNodeValue << endl;
    
    int thisNodeInMidIndex = intcind(mid, thisNodeValue);
    int halfSize = intlen(mid);
    int * leftMid = new int[halfSize];
    int * rightMid = new int[halfSize];
    init(leftMid, halfSize);
    init(rightMid, halfSize);
    // cout << "this node ind in mid: " << thisNodeInMidIndex << " and halfSize: " << halfSize << " and lenMid: " << intlen(mid) << endl;
    // debug
    // assert(halfSize >= thisNodeInMidIndex && halfSize >= intlen(mid) - 1 - thisNodeInMidIndex);
    if(thisNodeInMidIndex)
        memcpy(leftMid, mid, thisNodeInMidIndex * sizeof(int));
    if(thisNodeInMidIndex != intlen(mid) - 1)
        memcpy(rightMid, mid + thisNodeInMidIndex + 1, (intlen(mid) - 1 - thisNodeInMidIndex) * sizeof(int));
    
    // cout << "left mid: ";
    // printIntArray(leftMid);
    // cout << "right mid: ";
    // printIntArray(rightMid);

    int * leftPost = new int[halfSize];
    int * rightPost = new int[halfSize];
    init(leftPost, halfSize);
    init(rightPost, halfSize);
    memcpy(leftPost, post, intlen(leftMid) * sizeof(int));
    memcpy(rightPost, post + intlen(leftMid), intlen(rightMid) * sizeof(int));
    
    // cout << "left post: ";
    // printIntArray(leftPost);
    // cout << "right post: ";
    // printIntArray(rightPost);
    // cout << endl;

    getTheNode(leftMid, leftPost, sumFromAbove + thisNodeValue);
    getTheNode(rightMid, rightPost, sumFromAbove + thisNodeValue);
    // cout << thisNodeValue << " ends" << endl;
    delete[] leftPost;
    delete[] rightPost;
    delete[] leftMid;
    delete[] rightMid;
    // cout << thisNodeValue << " ends" << endl;
}

int main(){
    char line1[50000];
    char line2[50000];
    init(line1, 50000);
    init(line2, 50000);
    while(cin.getline(line1, 50000)){
        cin.getline(line2, 50000);
        int mid[10001];
        int post[10001];
        init(mid, 10001);
        init(post, 10001);
        int ind = 0;
        for(int i = 0; i < strlen(line1); i++)
        {
            char num[6];
            init(num, 6);
            while(i < strlen(line1) && isdigit(line1[i])){
                num[strlen(num)] = line1[i];
                i++;
            }
            // cout << ind << " m: " << num << endl;
            mid[ind] = atoi(num);
            ind++;
        }
        ind = 0;
        for(int i = 0; i < strlen(line2); i++)
        {
            char num[6];
            init(num, 6);
            while(i < strlen(line2) && isdigit(line2[i])){
                num[strlen(num)] = line2[i];
                i++;
            }
            // cout << ind << " p: " << num << endl;
            post[ind] = atoi(num);
            ind++;
        }

        getTheNode(mid, post, 0);
        // cout << "ready to output" << endl;
        
        cout << recs.begin()->nodeValue << endl;
        recs.clear();
    }
}