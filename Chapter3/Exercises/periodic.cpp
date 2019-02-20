#include <iostream>
#include <cstring>
using namespace std;

void init(char * x) {
    for(int i = 0; i < 85; i ++)
        x[i] = '\0';
}

int findP(const char * x, const int len) {
    for(int i = 1; i < len; i++){
        bool succeed = true;
        if(len%i != 0) continue;
        for(int k = 0; k < i; k++){
            for(int j = k; j < len - i; j += i){
                if( x[j] != x[j + i]){
                    succeed = false;
                    break;
                }
            }
            if(!succeed) break;
        }
        if(succeed)
            return i;
    }
    return len;
}

int main() {
    int count = 0;
    char a[85];
    init(a);
    cin >> count;
    for(int i = 0; i < count; i++){
        cin >> a;
        int period = findP(a, strlen(a));
        if(i != count - 1)
            cout << period << endl <<endl;
        else
            cout << period << "\n";
        
    }
    return 0;

}