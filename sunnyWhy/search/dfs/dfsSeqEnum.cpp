// 枚举所有子序列
#include <iostream>
#include <vector>
using namespace std;
vector<int> seq = {1, 3, 5}, res;
int n = 3;

void enumSubSeq(int i){
    if (i>=n){
        for(int j=0; j<res.size(); j++)
            cout << res[j] << " ";
        cout << endl;
        return ;
    }
    enumSubSeq(i+1);
    res.push_back(seq[i]);
    enumSubSeq(i+1);
    res.pop_back();
}

int main(){
    enumSubSeq(0);
    return 0;
}
/*
enumSubSeq(0)
    enumSubSeq(1)
        enumSubSeq(2)
            enumSubSeq(3)
                cout;
                return ;
            (5)
            enumSubSeq(3)
                cout 5;
                return ;
            ()
        (3)
        enumSubSeq(2)
            enumSubSeq(3)
                cout 3;
                return ;
            (3, 5)
            enumSubSeq(3)
                cout 3, 5;
                return ;
            (3)
        ()
    (1)
    enumSubSeq(1)
        enumSubSeq(2)
            enumSubSeq(3)
                cout 1;
                return ;
            (1, 5)
            enumSubSeq(3)
                cout  1, 5;
                return ;
            (1)
        (1, 3)
        enumSubSeq(2)
            enumSubSeq(3)
                cout 1, 3;
                return ;
            (1, 3, 5)
            enumSubSeq(3)
                cout 1, 3, 5;
                return ;
            (1, 3)
        (1)
    ()
return ;
*/