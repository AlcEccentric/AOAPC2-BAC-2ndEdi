#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
// need to find other's better solution
struct face{
    int wh[2];
    bool paired;
};

void initFaces(face * x){
    for(int i = 0; i < 6; i++){
        x[i].paired = false;
        x[i].wh[0] = 0;
        x[i].wh[1] = 0;
    }   
}
// 总感觉这里应该有更好的方法
// 又想到一个新问题，即如果构成链环的边不止三个，如何最高效地找到这个链环
bool chained(const face * pairs){
    if(pairs[0].wh[0] == pairs[1].wh[0] ) {
        if(pairs[1].wh[1] == pairs[2].wh[0]){
            if(pairs[2].wh[1] == pairs[0].wh[1]){
                return true;
            }else{
                return false;
            }
        }else if(pairs[1].wh[1] == pairs[2].wh[1]){
            if(pairs[2].wh[0] == pairs[0].wh[1]){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }else if(pairs[0].wh[0] == pairs[1].wh[1]){
        if(pairs[1].wh[0] == pairs[2].wh[0]){
            if(pairs[2].wh[1] == pairs[0].wh[1]){
                return true;
            }else{
                return false;
            }

        }else if(pairs[1].wh[0] == pairs[2].wh[1]){
            if(pairs[2].wh[0] == pairs[0].wh[1]){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
    else if(pairs[0].wh[0] == pairs[2].wh[0]){
        if(pairs[2].wh[1] == pairs[1].wh[0]){
            if(pairs[1].wh[1] == pairs[0].wh[1]){
                return true;
            }else return false;
        }else if(pairs[2].wh[1] == pairs[1].wh[1]){
            if(pairs[1].wh[0] == pairs[0].wh[1]){
                return true;
            }else return false;
        }else return false;
    }else if(pairs[0].wh[0] == pairs[2].wh[1]){
        if(pairs[2].wh[0] == pairs[1].wh[0]){
            if(pairs[1].wh[1] == pairs[0].wh[1]){ return true;}
            else return false;
        }
        else if(pairs[2].wh[0] == pairs[1].wh[1]){
            if(pairs[1].wh[0] == pairs[0].wh[1]){ return true;}
            else return false;
        }
        else return false;
    }
    else{
        return false;
    }
}
bool isSame(const face* x, const face* y){
    return (x->wh[0] == y->wh[0]) && (x->wh[1] == y->wh[1]);
}
int main(){
    int w, h;
    while(cin>>w>>h){
        face faces[6];
        initFaces(faces);
        int count = 0;
        do
        {
            /* code */
            if(w<=h){
                faces[count].wh[0] = w;
                faces[count].wh[1] = h;
            }else{
                faces[count].wh[0] = h;
                faces[count].wh[1] = w;
            }
            
            count++;
            if(count != 6)
                cin>>w>>h;
        } while (count<6);
        int pairNum = 0;
        face pairFaces[3];
        for(int i = 0; i < 6; i++){
            if(pairNum == 3) break;
            if(faces[i].paired) continue;
            for(int j = i+1; j < 6; j++){
                if(faces[j].paired) continue;
                if(isSame(&faces[i], &faces[j])){
                    faces[i].paired = faces[j].paired = true;
                    pairFaces[pairNum].wh[0] = faces[i].wh[0];
                    pairFaces[pairNum].wh[1] = faces[i].wh[1];
                    pairNum++;
                    break;
                }
            }
            
        }
        if(pairNum == 3){
            // 不仅仅需要组成三个pair face
            // 同时，三个pair face的wh必须构成链状
            if(chained(pairFaces))
                cout<<"POSSIBLE"<<endl;
            else
                cout<<"IMPOSSIBLE"<<endl;
        }
        else
            cout<<"IMPOSSIBLE"<<endl;
        
        
    }
}