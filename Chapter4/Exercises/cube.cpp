#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
// NOTE:
// 1. 模拟题先思考最直接的（不基于理论而基于实际操作）解法，比如筛子这道题，直接思考如果手上有两个骰子，自己会怎么判断相等，
// 2.由于模拟题的题目数据规模不是很大，甚至可以通过蛮力搜索来简化直接解法
// 3. strcpy的第二个参数中必须含有\0，因为strcpy函数遇到\0才停止复制，如果不含\0则应该用strncpy选择复制特定多的字符数
// 4. 注意哪些数据不应该被修改，在这道题中first和second两个代表初始骰子的数组就不应该修改，不能修改的原因是，oppo1和oppo2中的颜色一致的面标号是为first和second的记录的
// 一旦修改了first和second，oppo1和oppo2中存储的数据就无效了，但实际上下一次循环还是要用oppo1和oppo2的。因此，如果想要转动骰子，则应该将两个骰子的数据
// 复制到一个新数组，对新数组进行修改操作。
void init(char* x, int size){
    for(int i = 0; i < size; i++)
    {
        x[i] = '\0';
    }
    
}

bool hasSameOppo(const char * c1, const char * c2, int* oppo1, int* oppo2, int& sameNum){
    sameNum = 0;
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            
            if(c1[i] == c2[j]){
                // cout << "In has same oppo i = " <<i << " j = " << j << "\n";
                oppo1[sameNum] = i;
                oppo2[sameNum] = j;
                sameNum++;
            }
        }
    }
    return sameNum != 0;
}

void exch(char * cube, int ind1, int ind2){
    char tmp = cube[ind1];
    cube[ind1] = cube[ind2];
    cube[ind2] = tmp;
}

void makeUpNormal(char * cube, int upInd){
    char tmp = cube[0];
    switch (upInd)
    {
        case 0:
            break;
    
        case 1:
            cube[0] = cube[1];
            cube[1] = cube[5];
            cube[5] = cube[4];
            cube[4] = tmp;
            break;
        case 2:
            cube[0] = cube[2];
            cube[2] = cube[5];
            cube[5] = cube[3];
            cube[3] = tmp;
            break;
        
        case 3:
            cube[0] = cube[3];
            cube[3] = cube[5];
            cube[5] = cube[2];
            cube[2] = tmp;
            break;
        
        case 4:
            cube[0] = cube[4];
            cube[4] = cube[5];
            cube[5] = cube[1];
            cube[1] = tmp;
            break;

        case 5:
            exch(cube, 0, 5);
            exch(cube, 2, 3);
            break;

        default:
            cout << "index is wrong\n";
            exit(1);
            break;
    }
    return;
}

void makeFrontNormal(const char * cube, char * frontCube, const int frontInd){
    strncpy(frontCube, cube, 6);
    switch (frontInd)
    {
        case 1:
            break;
        
        case 2:
            frontCube[1] = frontCube[2];
            frontCube[2] = frontCube[4];
            frontCube[4] = frontCube[3];
            frontCube[3] = cube[1];
            break;
        
        case 3:
            frontCube[1] = frontCube[3];
            frontCube[3] = frontCube[4];
            frontCube[4] = frontCube[2];
            frontCube[2] = cube[1];
            break;

        case 4:
            exch(frontCube, 1, 4);
            exch(frontCube, 2, 3);
            break;
    
        default:
            cout << "index is wrong\n";
            exit(1);
            break;
    }
    // cout << "Make front\n";
}
bool compRotate(const char* c1, const char* c2){
    if(c1[5] != c2[5]) return false;
    for(int j = 1; j < 5; j++){
        char frontCube2[6];
        makeFrontNormal(c2, frontCube2, j);
        for(int i = 1; i < 5; i+=1){
            char frontCube1[6];
            // cout << "Inner loop " << i << "\n"; 
            makeFrontNormal(c1, frontCube1, i);
            if(frontCube2[1] == frontCube1[1] && 
               frontCube2[2] == frontCube1[2] && 
               frontCube2[3] == frontCube1[3] && 
               frontCube2[4] == frontCube1[4]){
                   return true;
            }
            // cout << "Inner loop " << i << "\n";
        }
    }
    
    return false;
}

int main(){
    char twoCubes[15];
    init(twoCubes, 15);
    while(cin.getline(twoCubes, 15)){
        // cout << twoCubes << "\n";
        char first[7] = {twoCubes[0],
                         twoCubes[1],
                         twoCubes[2],
                         twoCubes[3],
                         twoCubes[4],
                         twoCubes[5]};
        char second[7] = {twoCubes[6],
                         twoCubes[7],
                         twoCubes[8],
                         twoCubes[9],
                         twoCubes[10],
                         twoCubes[11]};
        int oppo1[40], oppo2[40];
        int sameNum;
        bool res = false;
        if(hasSameOppo(first, second, oppo1, oppo2, sameNum)){
            // cout << "Same num " << sameNum << "\n" ;
            // cout << first << " " << second <<"\n";
            for(int i = 0; i < sameNum; i++){
                // cout << first << " " << second <<"\n";
                // cout << "oppo1 = "<< oppo1[i] << " " << first[oppo1[i]];
                // cout << " oppo2 = "<< oppo2[i] << " " << second[oppo2[i]]<<"\n";
                char cpFirst[6], cpSecond[6];
                strncpy(cpFirst, first, 6);
                strncpy(cpSecond, second, 6);
                makeUpNormal(cpFirst, oppo1[i]);
                makeUpNormal(cpSecond, oppo2[i]);
                res = compRotate(cpFirst, cpSecond);
                if(res)
                    break;
            }    
        }else{
            res = false;
        }
        if(res) cout<<"TRUE"<<endl;
        else cout<<"FALSE"<<endl;
        // cout << "Reach bottom" <<endl;
    }
}