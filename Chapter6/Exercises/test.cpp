#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
const int MAXENUM = 500000;
const int MAXVNUM = 1002;
struct edge{
    int to;
    int next;
};
int eno = 0;
edge edges[MAXENUM];
int main(){

}