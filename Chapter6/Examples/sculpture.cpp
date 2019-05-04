#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <queue>
#include <set>
#include <map>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
// 这道题的启发是图不仅可以是二维的，还可以是n维的，比如这道题就是在三维的图中进行DFS
// 这道题值得参考的地方还有坐标的离散化 以及 求补的思想
int maxxInd, maxyInd, maxzInd;
enum ori{X, Y, Z};
struct slot{
    int x;
    int y;
    int z;
    int xl;
    int yl;
    int zl;
    slot(int x, int y, int z, int xl, int yl, int zl):x(x),y(y),z(z),xl(xl),yl(yl),zl(zl){};
};
void initSpace(int space[105][105][105]){
    for(int i = 0; i < 105; i++)
        for(int j = 0; j < 105; j++)
            for(int k = 0; k < 105; k++)
                space[i][j][k] = 0;
}
bool invalid(int x, int y, int z){
    if(x < 0 || x > maxxInd+1 || y < 0 || y > maxyInd+1 || z < 0 || z > maxzInd + 1) return true;
    return false;
}

int getSize(int i, int j, int k, map<int,int>& xIndtox, map<int,int>& yIndtoy, map<int,int>& zIndtoz){
    // for 8 vertex
    if((i <= 0|| i >= maxxInd) && (j <= 0|| j >= maxyInd) && (k <= 0|| k >= maxzInd)){
        return 1;
    }else if((i <= 0|| i >= maxxInd) && (j <= 0|| j >= maxyInd) && (k > 0 && k < maxzInd)){
        // for 4 edges paralleling to z axis
        return zIndtoz[k+1] - zIndtoz[k];
    }else if((i <= 0|| i >= maxxInd) && (j > 0 && j < maxyInd) && (k <= 0 || k >= maxzInd)){
        // for 4 edges paralleling to y axis
        return yIndtoy[j+1] - yIndtoy[j];
    }else if((i > 0 && i < maxxInd) && (j <= 0|| j >= maxyInd) && (k <= 0 || k >= maxzInd)){
        // for 4 edges paralleling to x axis
        return xIndtox[i+1] - xIndtox[i];
    }else if((i <= 0|| i >= maxxInd) && (j > 0 && j < maxyInd) && (k > 0 && k < maxzInd)){
        return (zIndtoz[k+1] - zIndtoz[k]) * (yIndtoy[j+1] - yIndtoy[j]);
    }else if((i > 0 && i < maxxInd) && (j <= 0 || j >= maxyInd) && (k > 0 && k < maxzInd)){
        return (zIndtoz[k+1] - zIndtoz[k]) * (xIndtox[i+1] - xIndtox[i]);
    }else if((i > 0 && i < maxxInd) && (j > 0 && j < maxyInd) && (k <= 0 || k >= maxzInd)){
        return (yIndtoy[j+1] - yIndtoy[j]) * (xIndtox[i+1] - xIndtox[i]);
    }else{
        return (yIndtoy[j+1] - yIndtoy[j]) * (xIndtox[i+1] - xIndtox[i]) * (zIndtoz[k+1] - zIndtoz[k]);
    }
    
}
int handle(int ret, int i, int j, int k, ori o, map<int,int>& xIndtox, map<int,int>& yIndtoy, map<int,int>& zIndtoz){
    if(ret == -2){
        switch (o)
        {
            case X:
                return (yIndtoy[j+1] - yIndtoy[j]) * (zIndtoz[k+1] - zIndtoz[k]);
            case Y:
                return (xIndtox[i+1] - xIndtox[i]) * (zIndtoz[k+1] - zIndtoz[k]);
            case Z:
                return (yIndtoy[j+1] - yIndtoy[j]) * (xIndtox[i+1] - xIndtox[i]);
            default:
                return 0;
        }
        
    }else return 0;
}
int dfs(int x, int y, int z, int space[105][105][105], map<int,int>& xIndtox, map<int,int>& yIndtoy, map<int,int>& zIndtoz, int& face, int& volume){
    // cout << "try to visit " << x << " " << y << " " << z << endl;
    // if we want to compute face we should distinguish visited and the slot cubes
    if(invalid(x, y, z) || space[x][y][z] == -1){// invalid or visited
        face = 0;
        volume = 0;
        return -1;
    }
    if(space[x][y][z] == 1) {
        face = 0;
        volume = 0;
        return -2;
    } // touch slot
    space[x][y][z] = -1;
    volume = getSize(x, y, z, xIndtox, yIndtoy, zIndtoz);
    face = 0;
    int addVolume = 0, addFace = 0, handledFace = 0;
    handledFace = handle(dfs(x+1, y, z, space, xIndtox, yIndtoy, zIndtoz, addFace, addVolume), x, y, z, X, xIndtox, yIndtoy, zIndtoz);
    face += addFace;
    face += handledFace;
    volume += addVolume;
    handledFace = handle(dfs(x-1, y, z, space, xIndtox, yIndtoy, zIndtoz, addFace, addVolume), x, y, z, X, xIndtox, yIndtoy, zIndtoz);
    face += addFace;
    face += handledFace;
    volume += addVolume;
    handledFace = handle(dfs(x, y+1, z, space, xIndtox, yIndtoy, zIndtoz, addFace, addVolume), x, y, z, Y, xIndtox, yIndtoy, zIndtoz);
    face += addFace;
    face += handledFace;
    volume += addVolume;
    handledFace = handle(dfs(x, y-1, z, space, xIndtox, yIndtoy, zIndtoz, addFace, addVolume), x, y, z, Y, xIndtox, yIndtoy, zIndtoz);
    face += addFace;
    face += handledFace;
    volume += addVolume;
    handledFace = handle(dfs(x, y, z+1, space, xIndtox, yIndtoy, zIndtoz, addFace, addVolume), x, y, z, Z, xIndtox, yIndtoy, zIndtoz);
    face += addFace;
    face += handledFace;
    volume += addVolume;
    handledFace = handle(dfs(x, y, z-1, space, xIndtox, yIndtoy, zIndtoz, addFace, addVolume), x, y, z, Z, xIndtox, yIndtoy, zIndtoz);
    face += addFace;
    face += handledFace;
    volume += addVolume;
    return 0; 
}
int total(int space[105][105][105], map<int,int>& xIndtox, map<int,int>& yIndtoy, map<int,int>& zIndtoz){
    int totalvol = 0; 
     for(int i = 0; i <= maxxInd+1; i++)
        for(int j = 0; j <= maxyInd+1; j++)
            for(int k = 0; k <= maxzInd+1; k++){
                totalvol += getSize(i, j, k, xIndtox, yIndtoy, zIndtoz);
            }
    return totalvol;
}
int main(){
    int caseNum;
    cin >> caseNum;
    // cout << "case num " << caseNum << endl;
    while(caseNum){
        int slotNum;
        cin >> slotNum;
        // cout << "slot num " << slotNum << endl;
        set<int> xs, ys, zs;
        queue<slot> slots;
        while(slotNum){
            int x, y, z, xlen, ylen, zlen;
            cin >> x >> y >> z >> xlen >> ylen >> zlen;
            slot s(x, y, z, xlen, ylen, zlen);
            slots.push(s);
            xs.insert(x);
            xs.insert(x+xlen);
            ys.insert(y);
            ys.insert(y+ylen);
            zs.insert(z);
            zs.insert(z+zlen);
            slotNum--;
        }
        // cout << "fill maps" << endl;
        map<int,int> xtoxI, ytoyI, ztozI, xItox, yItoy, zItoz;
        int maxx = 0, maxy = 0, maxz = 0;
        // cout << "\n x: ";
        int xc = 0;
        for(set<int>::iterator ii = xs.begin(); ii != xs.end(); ii++)
        {
            maxx = maxx > *ii ? maxx : *ii;
            // cout << *ii << " ";
            xtoxI[*ii] = xc + 1;
            xItox[xc + 1] = *ii;
            xc++;
        }
        // cout << "\n y: ";
        int yc = 0;
        for(set<int>::iterator ii = ys.begin(); ii != ys.end(); ii++)
        {
            maxy = maxy > *ii ? maxy : *ii;
            // cout << *ii << " ";
            ytoyI[*ii] = yc + 1;
            yItoy[yc + 1] = *ii;
            yc++;
        }
        // cout << "\n z: ";
        int zc = 0;
        for(set<int>::iterator ii = zs.begin(); ii != zs.end(); ii++)
        {
            maxz = maxz > *ii ? maxz : *ii;
            // cout << *ii << " ";
            ztozI[*ii] = zc + 1;
            zItoz[zc + 1] = *ii;
            zc++;
        }
        // cout << endl;
        // cout << "init size" << endl;
        maxxInd = xtoxI[maxx];
        maxyInd = ytoyI[maxy]; 
        maxzInd = ztozI[maxz];
        // cout << maxxInd << " " << maxyInd << " " << maxzInd << endl;
        // cout << "init space" << endl;
        int space[105][105][105];
        initSpace(space);
        // cout << "fill the space" << endl;
        while(slots.size()){
            slot curs = slots.front();
            slots.pop();
            // cout << curs.x << " " << curs.x + curs.xl << endl;
            // cout << curs.y << " " << curs.y + curs.yl << endl;
            // cout << curs.z << " " << curs.z + curs.zl << endl;
            int xlInd = xtoxI[curs.x], xhInd = xtoxI[curs.x + curs.xl];
            int ylInd = ytoyI[curs.y], yhInd = ytoyI[curs.y + curs.yl];
            int zlInd = ztozI[curs.z], zhInd = ztozI[curs.z + curs.zl];
            // cout << xlInd << " " << xhInd << endl;
            // cout << ylInd << " " << yhInd << endl;
            // cout << zlInd << " " << zhInd << endl;
            for(int i = xlInd; i < xhInd; i++)
                for(int j = ylInd; j < yhInd; j++)
                    for(int k = zlInd; k < zhInd; k++)
                        space[i][j][k] = 1;
        }
        // cout << "dfs and compute the outer size" <<  endl;
        int outerVol, face;
        dfs(0, 0, 0, space, xItox, yItoy, zItoz, face, outerVol);
        // cout << "outer vol: " << outerVol << endl;
        // compute total size;
        int totalVol = total(space, xItox, yItoy, zItoz);
        // cout << "total vol: " << totalVol << endl;
        cout << face << " " << totalVol - outerVol << endl;
       
        caseNum--;
    }
}