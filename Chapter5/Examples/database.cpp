#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include <map>
using namespace std;
// ifstream cin("test.in");
// ofstream cout("test.out");
// NOTE:
// 1. 直接做法(复杂度n*n*m)
// 每次选出不同的两行，两行从前往后比较，数相同的数据列的个数，如果为2则输出
// 缺点，由于n最大值为10000，m的最大值为100，该方法的复杂度可能为100亿次比较
// 2. 改进
// 改进之处有二：1是任选两列，2为每一行的两个元素生成一个key，value为其所在的行数，利用map将线性查找时间减为logn，
// 描述：任选2列，每一行的这两列值组成2元组构成key，在一个map中记录这个2元组第一次出现的行数，每次看该2元组在map中是否已经有对应的值，如果有则找到
// 示例：
// a b c
// c b a
// c b c
// 选择1,2列，则map依次记录ab, cb, cb的行，由于cb已经记录过因此我们知道cb这个二元对在当前行和过去的某一行出现过，map的值就记录了”过去的某一行“
// 因此可以输出结果
// 完整的做法是对1,2列,1,3列,2,3列都做上述操作去发现某个二元组是否在当前行和过去某一行出现过，
// 这样一来复杂度就变成了m*m*n*logn，由于m的最大值远小于n，因此该方法实际上比上一种方法快几百倍(当n很大接近10000时)
// 我的解题过程
// 1. 一开始被lrj对这道题的评价————”map的妙用“误导，以为不需要用brute force循环，仅用map和set的性质就能解决问题
// 结果想了很久，无解，想来想去觉得肯定还是得brute force但是可以用map和set辅助加速一点
// 2. 于是放弃了只用map的性质解决问题的思路，决定用brute force
// 很快就想到，按行brute force肯定不行，因为行数会很大，毕竟是一个值对相等的问题，所有应该可以尝试对列brute force
// 之后就想到了上面的方法，但是却不知如何用一个二元组来作为map的key：
// 2.1 一开始是自定义了一个结构，结构中有两个字符串，之后重载了小于符号，但是发现这样的比较是错误的，两个不相等的对也会被判断为相等
// 2.2 后来选择连接两个字符串为一个字符串，然后重载小于，该方法在实现的时候就觉得很怪异，总感觉单纯连接两个字符串就判断两两各自相等肯定不行
// （仔细想想确实不行，比如a bc和ab c这俩对会被判断为相等的key），但是udebug上的样例居然都通过了。。但是提交发现WA
// 2.3 到这的时候还以为自己的想法又错了，就去搜了搜这道题，一些题解标题就是”如何用二元组作map的key UVA1592 ....“。。。大呼自己沙雕
// 于是去查了查怎么用二元数据作key，答案是对二元数据生成pair<type1, type2>作为key。。于是就AC了
void init(char * x, int count){
    for(int i = 0; i < count; i++)
    {
        x[i] = '\0';
    }
    
}

int main(){
    int rowN, colN;
    while(cin>>rowN>>colN){
        cin.ignore();
        // cout << rowN << " " << colN << endl;
        vector<string> rows[10010];
        for(int i = 0; i < rowN; i++)
        {
            char line[100];
            init(line, 100);
            //get a line
            cin.getline(line, 100);
            char ele[100];
            init(ele, 100);
            // cout << "len of line " << strlen(line) << endl; 
            for(int j = 0; j < strlen(line); j++)
            {
                if(line[j]==','){
                    string x = ele;
                    rows[i].push_back(x);
                    // cout<<x<<endl;
                    init(ele, 100);
                }else{
                    ele[strlen(ele)] = line[j];
                    if(j == strlen(line) - 1){
                        string x = ele;
                        rows[i].push_back(x);
                        // cout<<x<<endl;
                    }
                    
                }
            }
            
        }

        int col1, col2, row1, row2;
        bool found = false;
        for(int i = 0; i < colN; i++)
        {
            for(int j = i+1; j < colN; j++)
            {
                map<pair<string, string>, int> mymap;
                for(int k = 0; k < rowN; k++)
                {
                    pair<string, string> mk = make_pair(rows[k][i],rows[k][j]);
                    // cout << "row no:" << k << " " << "xy = " << xy <<endl;
                    if(mymap.count(mk)){
                        col1 = i;
                        col2 = j;
                        row1 = mymap[mk];
                        // cout << "mk.xy" << mk.xy << endl;
                        row2 = k;
                        found = true;
                        break;
                    }else{
                        mymap[mk] = k;
                    }
                }
                if(found) break;
            }
            if(found) break;
        }

        if(found){
            cout << "NO" << endl;
            cout << row1+1 << " " << row2+1 <<endl;
            cout << col1+1 << " " << col2+1 <<endl;
        }else{
            cout << "YES" << endl;
        }

        // cout << "end this" <<endl;
        
        

        
    }
}