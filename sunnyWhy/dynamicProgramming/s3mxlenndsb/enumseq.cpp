// @FileName:     enumseq.cpp
// @CreateTime:   2023/03/31 10:19:15
// @Author:       Rainbow River
// 枚举一个序列的所有子序列
// 序列A的子序列是指:
// 1. 是序列A的子集
// 2. 元素间相对顺序不变
// 3. 相邻元素在原始序列中不必相邻

#include<iostream>
#include<vector>
using namespace std;
const int MAXN = 5;
int a[MAXN] = {2, -1, 1, 3, 4};
vector<int> seq;
void prt_seq();
void enum_seq(int i);
int main(){
    enum_seq(0);
    return 0;
}

void prt_seq(){
    cout << "[";
    for(int a: seq)
        cout << a << " ";
    cout << "]" << endl;
}

void enum_seq(int i){
    if(i == MAXN)
        prt_seq();
    else{
        enum_seq(i+1);  // 不选择 i 号元素, 直接进入 i+1 号元素
        seq.push_back(a[i]);
        enum_seq(i+1);  // 选择 i 号元素
        seq.pop_back();
    }
}