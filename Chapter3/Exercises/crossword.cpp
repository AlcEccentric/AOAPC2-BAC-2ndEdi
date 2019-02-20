#include <iostream>
#include <fstream>
using namespace std;
struct pos{
    char ch;
    int id;
    bool dhasout;
    bool chasout;
};

void printCross(pos puzzle[10][10], int x, int y){
    printf("Across");
    for(int i = 0; i < x; i++){
        int j = 0;
        while(j < y){
            if(puzzle[i][j].id != -1 && !puzzle[i][j].chasout){
                printf("\n%3d.", puzzle[i][j].id);
                int k = j;
                while(k < y && puzzle[i][k].ch != '*'){
                    cout<<puzzle[i][k].ch;
                    puzzle[i][k].chasout = true;
                    k++;
                }
            }
            j++;
        }
    }
    
}
void printDown(pos puzzle[10][10], int x, int y){
    printf("\nDown");
    for(int i = 0; i < x; i++){
        int j = 0;
        while(j < y){
            if(puzzle[i][j].id != -1 && !puzzle[i][j].dhasout){
                printf("\n%3d.", puzzle[i][j].id);
                int k = i;
                while(k < x && puzzle[k][j].ch != '*'){
                    cout<<puzzle[k][j].ch;
                    puzzle[k][j].dhasout = true;
                    k++;
                }
            }
            j++;
        }
    }
}
int main(){
    int x, y;
    pos puzzle[10][10];
    int pid = 0;
    while(1){
        cin >> x;
        if(x == 0){
            return 0;
        }
        cin >> y;
        pid ++;
        int id = 0;

        for(int i = 0; i < x; i++){
            for(int j = 0; j < y; j++)
            {
                puzzle[i][j].dhasout = false;
                puzzle[i][j].chasout = false;
            }
        }

        for(int i = 0; i < x; i++){
            for(int j = 0; j < y; j++)
            {
                char inchar;
                cin >> inchar;
                puzzle[i][j].ch = inchar;
                if((i == 0 || j == 0 || puzzle[i-1][j].ch == '*' || puzzle[i][j-1].ch == '*') && inchar != '*'){
                    id++;
                    puzzle[i][j].id = id;
                }else{
                    puzzle[i][j].id = -1;
                }
            }
            
        }
        if(pid != 1)
            cout << "\n\npuzzle #" << pid <<":\n";
        else
            cout << "puzzle #" << pid <<":\n";
        printCross(puzzle, x, y);
        printDown(puzzle, x, y);
        // cout<<endl;
    }

}