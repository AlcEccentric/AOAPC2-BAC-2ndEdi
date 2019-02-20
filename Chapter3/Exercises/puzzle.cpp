#include <iostream>
#include <fstream>
using namespace std;
void init(char x[5][5]) {
    for(int i = 0; i < 5; i ++)
        for(int j = 0; j < 5; j ++)
            x[i][j] = '\0';
}

void swap(char &x, char &y){
    int tempy = y;
    y = x;
    x = tempy;
}

struct pos{
    int i;
    int j;
};

bool move(char p[5][5], pos &blank, const char command){
    bool succeed = false;
    pos square;
    switch (command){
        case 'A':
            /* code */
            square.i = blank.i - 1;
            square.j = blank.j;
            if(square.i < 0) break;
            succeed = true;
            swap(p[square.i][square.j], p[blank.i][blank.j]);
            break;
        
        case 'B':
            /* code */
            square.i = blank.i + 1;
            square.j = blank.j;
            if(square.i > 4) break;
            succeed = true;
            swap(p[square.i][square.j], p[blank.i][blank.j]);
            break;

        case 'L':
            /* code */
            square.i = blank.i;
            square.j = blank.j - 1;
            if(square.j < 0) break;
            succeed = true;
            swap(p[square.i][square.j], p[blank.i][blank.j]);
            break;

        case 'R':
            /* code */
            square.i = blank.i;
            square.j = blank.j + 1;
            if(square.j > 4) break;
            succeed = true;
            swap(p[square.i][square.j], p[blank.i][blank.j]);
            break;
    
        default:
            break;
    }
    if(succeed){
        blank.i = square.i;
        blank.j = square.j;
    }
    return succeed;
    
}

void printP(char puzzle[5][5]){
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(j != 4)
                cout << puzzle[i][j] << " ";
            else{
                if(i != 4){
                    cout << puzzle[i][j] << "\n";
                }
                else{
                    cout << puzzle[i][j];
                }
            }
        }
    }
}

int main(){
   
    char next = '\0';
    char puzzle[5][5];
    init(puzzle);
    int pId = 0;
    bool first = true;
    while(1){
        cin.get(next);
        if(next == 'Z'){
            // cout << "exit" << endl;
            exit(0);
        }else{
            if(!first)
                cout << endl;
        }
        first = false;
        
        pId ++;

        while(1){
            // cout << "next: " << next << endl;
            if(next == '0'){
                cin.get(next);
                if(next == 'Z'){
                    exit(0);
                }else{
                    if(next != '\n')
                    cout <<  endl;
                }
                break;
            }
            
            pos blank;
            for(int i = 0; i < 5; i++){
                for(int j = 0; j < 5; j++){
                    if(i == 0 && j == 0)
                        puzzle[i][j] = next; 
                    else if(j == 4){
                        cin.get(next);
                        puzzle[i][j] = next;
                        cin.get(next);
                    }  
                    else{
                        cin.get(next); 
                        puzzle[i][j] = next;
                    }
                    
                    if(puzzle[i][j] == ' '){
                        blank.i = i;
                        blank.j = j;
                    }
                }
            }

            cin.get(next);
            bool succeed = true;
            // fout << "blank:" << blank.i << " " << blank.j << endl;
            // fout << "before move:\n";
            // printP(puzzle);
            while(next != '0'){
                if(next == '\n'){
                    cin.get(next);
                    continue;
                }
                // fout << next << " move:\n";
                succeed = move(puzzle, blank, next) && succeed;
                // printP(puzzle);
                cin.get(next);
            }
           
            // if(pId != 1) cout << "\n";
            cout << "Puzzle #" << pId <<":\n";
            
            if (succeed) {
                for(int i = 0; i < 5; i++){
                    for(int j = 0; j < 5; j++){
                        if(j != 4)
                            cout << puzzle[i][j] << " ";
                        else
                            cout << puzzle[i][j] << "\n";
                    }
                    
                }
            }else{
                cout << "This puzzle has no final configuration.\n";
            }   
            // cout << "next: " << next << endl;
        }
        
    }
    return 0;
}
