#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include <cctype>
#include <iomanip>
using namespace std;
// ifstream  cin("test.in");
// ofstream  cout("test.out");

void init(char*x, int count){
    for(int i = 0; i < count; i++)
    {
        /* code */
        x[i] = '\0';
    }
    
}

void init(int *x, int count){
    for(int i = 0; i < count; i++)
    {
        /* code */
        x[i] = 0;
    }
}

int main(){
    char c;
    vector<string> lines[1005];
    int lineCount = 0;
    while( cin.get(c)){
        char word[85];
        init(word, 85);
        //  cout << c <<endl;
        while(!isspace(c) && c != '\n'&& c != '\t'){
            word[strlen(word)] = c;
            if(! cin.get(c)) break;
        }
        string x = word;
        //  cout << x <<endl;
        if(strlen(x.c_str()) != 0)
            lines[lineCount].push_back(x);
        if(c == '\n'){
            lineCount++;
        }
    }

    // for(int i = 0; i <= lineCount; i++)
    // {
    //     for(auto word : lines[i]){
    //          cout << word << " ";
    //     }
    //      cout << endl;
    // }
    
    int maxColNum = 0;
    for(int i = 0; i <= lineCount; i++)
        maxColNum = maxColNum < lines[i].size() ?  lines[i].size() : maxColNum;
    //  cout << maxColNum << endl;

    int width[180];
    init(width, 180);
    for(int i = 0; i <= lineCount; i++)
    {
        for(vector<string>::iterator ii = lines[i].begin(); ii != lines[i].end(); ii++)
        {
           width[ii - lines[i].begin()] = strlen((*ii).c_str()) > width[ii - lines[i].begin()] ? strlen((*ii).c_str()) : width[ii - lines[i].begin()];
        }
    }
    
    for(int i = 0; i <= lineCount; i++)
    {
        for(vector<string>::iterator ii = lines[i].begin(); ii != lines[i].end(); ii++){
            if(ii != lines[i].end() - 1)
                 cout << left << setw(width[ii - lines[i].begin()]+1) << *ii;
            else
                 cout << left << *ii;
        }
        if(i != lineCount)
             cout<<endl;
    }

    


    
}