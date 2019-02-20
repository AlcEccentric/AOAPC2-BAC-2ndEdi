#include <iostream>
#include <fstream>
using namespace std;

enum {A, C, G, T};
int main(){
    int total = 0;
    cin >> total;
    for(int i = 0; i < total; i++){
        int m, n;
        cin >> m >> n;
        int counter[4];
    
        char arr[55][1005]; 
        for(int j = 0; j < m; j++)
            for(int k = 0; k < n; k++)
                cin >> arr[j][k];

        int hamming = 0;
        for(int k = 0; k < n; k++){
            for(int j = 0; j < 4; j++)
                counter[j] = 0; 
            for(int j = 0; j < m; j++){
                switch (arr[j][k])
                {
                    case 'T':
                        counter[T]++;
                        break;
                    case 'A':
                        counter[A]++;
                        break;
                    case 'G':
                        counter[G]++;
                        break;
                    case 'C':
                        counter[C]++;
                        break;
                    default:
                        break;
                }
            }
            char maxCh = '\0';
            int max = -1;
            for(int i = 0; i < 4; i++){
                if(counter[i]>max){
                    max = counter[i];
                    switch (i){
                        case T:
                            maxCh = 'T';
                            break;
                        case A:
                            maxCh = 'A';
                            break;
                        case G:
                            maxCh = 'G';
                            break;
                        case C:
                            maxCh = 'C';
                            break;
                        default:
                            break;
                    }
                }
            }
            hamming = hamming + (m - max);
            cout<<maxCh;
        }
        if(i != total - 1)
            cout<< '\n' << hamming << endl;
        else
            cout<< '\n' << hamming << endl;
  
    }
       
}