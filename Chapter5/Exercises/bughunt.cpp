#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <cctype>
#include <map>
#include <stack>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");

void init(char *x, int count){
    for(int i = 0; i < count; i++)
        x[i] = '\0';
}
int main(){
    char line[85];
    init(line, 85);
    while(1){
        
        cin.getline(line, 80);
        if(line[0] != '.'){
            // get the program
            // cout << "new program:" << endl;
            int lineno = 1;
            map<string, int> arrayToSize;
            map<string, map<int, int> > arrayToContent;
            bool hasError = false;
            do{
                // cout << "clause: "<< line << endl;
                if(hasError) continue;
                if(strstr(line, "=") == NULL){
                    // declaration
                    // cout << "Analyze declaration" << endl;
                    char arrayNameC[80];
                    init(arrayNameC, 80);
                    int i;
                    for(i = 0; i < strlen(line); i++)
                    {
                        if(line[i] == '[') break;
                        arrayNameC[strlen(arrayNameC)] = line[i];
                    }
                    i++;
                    char arraySizeC[10];
                    init(arraySizeC, 10);
                    for(;i < strlen(line); i++){
                        if(line[i] == ']') break;
                        arraySizeC[strlen(arraySizeC)] = line[i];
                    }
                    int arraySize = atoi(arraySizeC);
                    string arrayName = arrayNameC;
                    if(arraySize < 0) arraySize = 0; 
                    arrayToSize[arrayName] = arraySize;
                    // cout << "array: " << arrayName << " with size: " <<arraySize << endl;
                    map<int, int> mymap;
                    arrayToContent[arrayName] = mymap;// a empty map
                }else{
                    // assignment
                    // cout << "Analyze assignment" << endl;
                    stack<string> leftArrayNames;
                    stack<string> rightArrayNames;
                    int i;
                    char arrayNameC[80];
                    init(arrayNameC, 80);
                    // cout << "left array names:" <<endl;
                    for(i = 0; i < strlen(line); i++)
                    {
                        if(isdigit(line[i])) break;
                        while(1){
                            // get array name
                            if(line[i] == '[') break;
                            arrayNameC[strlen(arrayNameC)] = line[i];
                            i++;
                        };
                        string arrayName = arrayNameC;
                        leftArrayNames.push(arrayName);
                        // cout << arrayName << " ";
                        init(arrayNameC, 80);
                    }
                    // cout << endl;
                    char index[10];
                    init(index, 10);
                    for(; i < strlen(line); i++){
                        if(line[i] == ']') break;
                        index[strlen(index)] = line[i];
                    }
                    int leftInd = -1;
                    if(strlen(index)) leftInd = atoi(index);
                    for(; i < strlen(line); i++){
                        if(isalpha(line[i]) || isdigit(line[i])) break;
                    }
                    // cout << "left array ind:" <<leftInd <<endl;
                    // get things on the other side of equal sign
                    // cout << "right array names:" <<endl;
                    // cout << line[i] << endl;
                    for(; i < strlen(line); i++)
                    {
                        if(isdigit(line[i])) break;
                        while(1){
                            // get array name
                            if(line[i] == '[') break;
                            arrayNameC[strlen(arrayNameC)] = line[i];
                            i++;
                        };
                        string arrayName = arrayNameC;
                        rightArrayNames.push(arrayName);
                        // cout << arrayName << " ";
                        init(arrayNameC, 80);
                    }
                    // cout << endl;
                    init(index, 10);
                    for(; i < strlen(line); i++){
                        if(line[i] == ']') break;
                        index[strlen(index)] = line[i];
                    }
                    // cout << "line[i]: " << line[i-1] <<endl;
                    int rightInd = -1;
                    if(strlen(index)) rightInd = atoi(index);

                    // cout << "right array ind:" <<rightInd <<endl;
                    
                    // check error on the right：
                    // array undecined
                    // access invalid memory
                    // pos referred by the ind is undecined
                    // cout << "right access:" <<endl;
                    while(!rightArrayNames.empty()){
                        string name = rightArrayNames.top();
                        rightArrayNames.pop();
                        // cout << name << "[" << rightInd << "]"<<endl ;
                        if(!arrayToSize.count(name)){
                            // the array is undecined
                            hasError = true;
                            break;
                        }

                        if(rightInd >= arrayToSize[name]){
                            // access outside the array
                            hasError = true;
                            break;
                        }

                        if(!arrayToContent[name].count(rightInd)){// this pos of array is undecined
                            hasError = true;
                            break;
                        }else{
                            rightInd = arrayToContent[name][rightInd];
                        }
                    }
                    // now right value equals rightInd
                    // check error on the left
                    // array undecined
                    // access invalid memory
                    // cout << "left access:" <<endl;
                    while(leftArrayNames.size() > 1){
                        string name = leftArrayNames.top();
                        leftArrayNames.pop();
                        // cout << name << "[" << leftInd << "]"<<endl ;
                        if(!arrayToSize.count(name)){
                            // the array is undecined
                            hasError = true;
                            break;
                        }

                        if(leftInd >= arrayToSize[name]){
                            // access outside the array
                            hasError = true;
                            break;
                        }

                        if(!arrayToContent[name].count(leftInd)){// this pos of array is undecined
                            hasError = true;
                            break;
                        }else{
                            leftInd = arrayToContent[name][leftInd];
                        }
                    }
                    if(!arrayToSize.count(leftArrayNames.top())){
                        // the array is undecined
                        hasError = true;
                    }

                    if(leftInd >= arrayToSize[leftArrayNames.top()]){
                        // access outside the array
                        hasError = true;
                    }
                    if(hasError){
                        cout << lineno << endl;
                        continue;
                    }
                    // cout << "cinal: " << leftArrayNames.top() << "[" << leftInd << "]=" <<rightInd<<endl;
                    arrayToContent[leftArrayNames.top()][leftInd] = rightInd;

                }
                lineno++;
            } while(cin.getline(line, 80) && line[0] != '.');
            if(!hasError) cout << 0 << endl;
        }else{
            break;
        }

    }
}