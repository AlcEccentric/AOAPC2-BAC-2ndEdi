#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <cctype>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
// NOTE:
// 这道题的前几个版本虽然udebug样例都通过了但是WA
// 于是重新审题，发现题意是文章中凡是非字母的字符都当成空格看待
// 而之前的版本将文章中的*和数字都当做单词的一部分处理了
// 于是在原有的代码将文章中这两种字符当成分隔符处理后就AC了
// 只是由于一开始审题不清，代码逻辑和题意不一样，以至于后来改动后，代码变得非常混乱而且丑陋
// 这题读入文章应该有更优雅的方法，比如每次getline，如果判断不是**********，复制这个line,将副本里面的非字母都变成空格
// 然后去分析这个复制后的line的内容即可，比get应该要优雅易懂不易错的多
// 所以以后有条件还是尽可能不要用get，很容易让代码读入的逻辑变得很恶心
void init(char *x, int count){
    for(int i = 0; i < count; i++)
    {
        x[i] = '\0';
    }
    
}
int main(){
    int articleNum;
    cin >> articleNum;
    cin.ignore();
    string articles[150][1600];
    map<string, set<int> > stringInWhichArticle;
    map<string, set<int> > stringInWhichLine[150];
    for(int i = 0; i < articleNum; i++)
    {   
        char c;
        int lineno = 0;
        char line[100];
        init(line, 100);
        while(cin.get(c)){
            // cout << c << endl;
            if(!isalpha(c) && !(c == '*' && strlen(line)==0)) {
                // cout << c << endl;
                line[strlen(line)] = c;
                if(c == '\n') {
                    if(line[0] != '*')articles[i][lineno] = line;
                    // cout<< "full2: " << line;
                    init(line, 100);
                    lineno++;
                }
                continue;
            }
            char word[100];
            init(word, 100);
            // cout << c << endl;
            line[strlen(line)] = c;
            while(isalpha(c) || (c == '*'  && strlen(line)==1)){
                if(isalpha(c)) c = tolower(c);
                word[strlen(word)] = c;
                cin.get(c);
                // cout << c << endl;
                line[strlen(line)] = c;
            }
           
            string w = word;
            // cout <<"w: "<< w << endl;
            if(strcmp(w.c_str(), "*") == 0) {
                for(int iii = 0; iii < 9; iii++)
                {
                    cin.get(c);
                }
                break;
            }
            stringInWhichArticle[w].insert(i);
            stringInWhichLine[i][w].insert(lineno);
             if(c == '\n') {
                if(line[0] != '*')articles[i][lineno] = line;
                // cout << "full1: "<< line;
                init(line, 100);
                lineno++;
            }
        }
    }
    int queryNum;
    cin >> queryNum;
    // cout << "query num " << queryNum << endl;
    cin.ignore();
    for(int i = 0; i < queryNum; i++)
    {
        char line[100];
        init(line, 100);
        cin.getline(line, 80);
        // cout << line;
        vector<string> query;
        char word[100];
        init(word, 100);
        for(int j = 0; j < strlen(line); j++)
        {
            if(isalpha(line[j])) line[j] = tolower(line[j]);
            word[strlen(word)] = line[j];
            if( j >= strlen(line) - 1 || line[j+1] == ' '){
                string w = word;
                query.push_back(w);
                init(word, 100);
                if(j < strlen(line) - 1&&line[j+1] == ' ') j++;
            }
        }
        bool found = false;
        vector<int> resArts;
        int resNo = 0;
        // for(auto q : query){
        //     cout << q << "endl" <<endl;
        // }
        switch(query.size())
        {
            case 1:// term

                for(set<int>::iterator it = stringInWhichArticle[query[0]].begin(); it != stringInWhichArticle[query[0]].end(); it++){
                    found = true;
                    if(it != stringInWhichArticle[query[0]].begin()){
                        cout << "----------"<<endl;
                    }
                    int artInd = *it;
                    for(auto lineno : stringInWhichLine[artInd][query[0]]){
                        cout << articles[artInd][lineno];
                    }

                }   
                break;

            case 2:// NOT
                
                for(int j = 0; j < articleNum; j++){
                    if(stringInWhichArticle[query[1]].count(j)) continue;
                    found = true;
                    if(resNo != 0){
                        cout << "----------"<<endl;
                    }
                    resNo++;
                    for(int k = 0; strlen(articles[j][k].c_str())!=0; k++){
                        cout << articles[j][k];
                    }
                }
                break;
            
            case 3:
                
                if(strcmp(query[1].c_str(), "and") == 0){
                    set_intersection(stringInWhichArticle[query[0]].begin(), stringInWhichArticle[query[0]].end(), stringInWhichArticle[query[2]].begin(), stringInWhichArticle[query[2]].end(), back_inserter(resArts));
                }else if(strcmp(query[1].c_str(), "or") == 0){
                    set_union(stringInWhichArticle[query[0]].begin(), stringInWhichArticle[query[0]].end(), stringInWhichArticle[query[2]].begin(), stringInWhichArticle[query[2]].end(), back_inserter(resArts));
                }
                // cout << query[0] << " " << query[2] << endl;
                // cout << stringInWhichArticle[query[0]].size() << endl;
                // cout << stringInWhichArticle[query[2]].size() << endl;
                // cout << "res arts size " << resArts.size() << endl;
                if(resArts.size()) found = true;
                for(vector<int>::iterator it = resArts.begin(); it != resArts.end(); it++){
                    if(it != resArts.begin()) cout << "----------"<<endl;
                    int artInd = *it;
                    set<int> resLineNo;
                    for(auto lineno : stringInWhichLine[artInd][query[0]]){
                        resLineNo.insert(lineno);
                    }
                    for(auto lineno : stringInWhichLine[artInd][query[2]]){
                        resLineNo.insert(lineno);
                    }
                    for(auto lineno : resLineNo){
                        cout << articles[artInd][lineno];
                    }
                }
                break;
        
            default:
                break;
        }
        if(!found) cout << "Sorry, I found nothing." << endl;
        cout << "==========" << endl;
        
    }
    
    
}