#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <stack>
#include <queue>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
void init(queue<int> &q, int N){
    for(int i = 1; i <= N; i++)
        q.push(i);
}
int main(){
    int N;
    while(1){
        cin >> N;
        if(N == 0) break;
        while(1){
            queue<int>q1, q2;
            // cout << "N = " << N <<endl;
            init(q1, N);
            int e;
            cin >> e;
            if(e == 0){
                cout << endl;
                break;
            }
            q2.push(e);
            // cout << e << " ";
            for(int i = 1; i < N; i++)
            {
                cin >> e; 
                // cout << e << " ";
                q2.push(e);
            }
            // cout << endl;
            stack<int> station;
            bool hasError = false;
            while(1){
                if(q2.front() > q1.front()){
                    station.push(q1.front());
                    q1.pop();
                }else if(q2.front() == q1.front()){
                    q1.pop();
                    q2.pop();
                }else if(q2.front() < q1.front()){
                    int s1 = station.top();
                    int q21 = q2.front();
                    station.pop();
                    q2.pop();
                    if(s1 != q21){
                        hasError = true; 
                        cout << "No" << endl;
                        break;
                    }
                }
                if(hasError) break;
                if(q1.empty() || q2.empty()) break;
            }
            if(hasError) continue;
            if(q1.empty() && !q2.empty()){
                if(station.size() != q2.size()){
                    cout << "No" << endl;
                    continue;
                }
                while(!q2.empty()){
                    int s1 = station.top();
                    int q21 = q2.front();
                    station.pop();
                    q2.pop();
                    if(s1 != q21){
                        cout << "No" << endl;
                        hasError = true;
                        break;
                    }
                }
                if(hasError) continue;
            }else if(!q1.empty() && q2.empty()){
                cout << "No" << endl;
                continue;
            }

            if(q1.empty() && q2.empty()){
                cout << "Yes" << endl;
            }
        }
    }
}