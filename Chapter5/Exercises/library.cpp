#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <set>
#include <map>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
// NOTE: 
// find upper_bound and lower_bound of set dont work for self defined struct
// do some tests in test_upper_bound.cpp with conclusion;
struct book{
    string title;
    string author;
    book(string t, string a):title(t), author(a){};
    bool operator < (const book& b) const{
        if(strcmp(author.c_str(), b.author.c_str()) < 0) return true;
        else if(strcmp(author.c_str(), b.author.c_str()) > 0) return false;
        else//author same
            return strcmp(title.c_str(), b.title.c_str()) < 0;
    };
};

void init(char * x, int count){
    for(int i = 0; i < count; i++)
    {
        x[i] = '\0';
    }
    
}

int main(){
    char c;
    set<book> books;
    map<string, string> titleToAuthor;
    char title[85];
    char author[85];
    init(title, 85);
    init(author, 85);
    while(cin.get(c)){
        if(c == 'E') break;
        title[0] = c;
        while(cin.get(c)){
            title[strlen(title)] = c;
            if(c == '"') 
                break;
        }
        cin.get(c); // get space
        cin.get(c); // get b
        cin.get(c); // get y
        cin.get(c); // get space
        while(cin.get(c)){
            if(c == '\n') 
                break;
            author[strlen(author)] = c;
        }
        string t = title;
        string a = author;
        books.insert(book(t, a));
        titleToAuthor[t] = a;
        init(title, 85);
        init(author, 85);
    }
    // cout << "lower bound for m(by 7): " << lower_bound(books.begin(), books.end(), book("m","7"))->title << endl;
    string com1, t;
    set<book> returned;
    
    while(cin>>com1){
        // cout << "com1:" << com1 << endl;
        if(strcmp(com1.c_str(), "END") == 0) break;
        if(strcmp(com1.c_str(), "BORROW") == 0){
            
            char title[85];
            init(title, 85);
            cin.get(c);
            while(cin.get(c)){
                if(c == '\n') break;
                title[strlen(title)] = c;
            }
            string t = title;
            string a = titleToAuthor[t];
            books.erase(book(t,a));
            continue;
        }
        if(strcmp(com1.c_str(), "RETURN") == 0){
            char title[85];
            init(title, 85);
            cin.get(c);
            while(cin.get(c)){
                if(c == '\n') break;
                title[strlen(title)] = c;
            }
            string t = title;
            string a = titleToAuthor[t];
            // cout << "RETURN: " << t << endl;
            returned.insert(book(t,a));
            continue;
        }
        if(strcmp(com1.c_str(), "SHELVE") == 0){
            // cout << "shelve" << endl;
            
            for(auto rb : returned){
                // cout << "books in shelf now:"<<endl;
                // for(auto b : books){
                //     cout << b.title << endl;
                // }
                // cout << "lower bound : " << books.lower_bound(rb)->title << " by " << books.lower_bound(rb)->author << endl;
                books.insert(rb);
                set<book>::iterator biter = books.lower_bound(rb);
                if(biter != books.begin()){ // have ahead one
                    biter--;
                    cout << "Put "<< rb.title << " after " << biter->title << endl;
                }else{
                    cout << "Put "<< rb.title << " first" << endl;
                }
                
            }
            cout << "END" <<endl;
            returned.clear();
            continue;
        }
    }
}