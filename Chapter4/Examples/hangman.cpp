#include <iostream>
// #include <fstream>
#include <cstring>
#include <stdlib.h>
using namespace std;
//  ifstream cin("test.in");
//  ofstream cout("test.out");
// 1. 第一次直接统计的guess里的每个字母出现的次数，并且根据字典序对guess字母进行了排序
// 该方法忽略了guess字母的序，如cheese和cheeseaaaaaaa就会被判断为lose
// 2. 第二次按照guess的字母出现顺序去判定了，但是忽略了相同正确字符被猜多次导致的猜对次数超过answer不同字母个数的情况
// 如cheese和cccc就会被该方法判断为win实际上是应该判断为放弃
// 而该问题在方法一种没有出现，因为根据字典序对guess字母进行了排序的结果是，多个相同的正确猜测字母被认为是一个正确猜测而不是多个
// 因此，对于方法2，设置一个数组判断该字母是否被猜测过即可，只有没被猜过的才会被继续考虑是否猜中
// 3. 书本题干误导，书本说，如果出现重复多次错误猜测字符，会被认定为多次，
// 比如cheese和zzzzzzzche，根据书中题干，应该输出lose，实际根据oj中的题干应该输出chickened out.
void countFor(char * chars, int * counts){
    for(int i = 0; i < strlen(chars); i++)
        counts[chars[i] - 'a'] ++;
}

void init(char * x, int size){
    for(int i = 0; i < size; i++)   
        x[i] = '\0';
}

void init(int * x, int size){
    for(int i = 0; i < size; i++)   
        x[i] = 0;
}

int comp(int * cntAns, char* guess){
    int wrongNum = 0;
    int correctNum = 0;
    int totalAnsChar = 0;
    for(int i = 0; i < 26; i++){
        if(cntAns[i]) totalAnsChar++;
    }

    bool hasBeenGuessed[26];
    for(int i = 0; i < 26; i++)
    {
        /* code */
        hasBeenGuessed[i] = false;
    }
    
    for(int i = 0; i < strlen(guess); i++){
        int indOfAns = guess[i] - 'a';
        if(!hasBeenGuessed[indOfAns] && cntAns[indOfAns]){
            correctNum++; 
            hasBeenGuessed[indOfAns] = true;     
            if(correctNum == totalAnsChar)
                return 1;     
        }else{
            if(!hasBeenGuessed[indOfAns]){
                wrongNum++; 
                hasBeenGuessed[indOfAns] = true;
                if(wrongNum >= 7)
                return -1;
            }
        }
    }
 
    return 0;
    
}

int main(){
    int n = -1;
    char ans[5000], guess[5000];
    cin >> n;
    while(n!=-1){
        init(ans, 5000);
        init(guess, 5000);
        cin >> ans >> guess;
        int cntAns[26];
        init(cntAns, 26);
        countFor(ans, cntAns);
        int res = comp(cntAns, guess);
        cout<<"Round "<<n<<endl;
        if(res == 1){
            cout<<"You win."<<endl;
        }else if(res == -1){
            cout<<"You lose."<<endl;
        }else{
            cout<<"You chickened out."<<endl;
        }
        cin >> n;
    }
}