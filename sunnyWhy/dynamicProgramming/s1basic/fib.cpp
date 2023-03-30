// @FileName:     fib.cpp
// @CreateTime:   2023/03/29 10:17:32
// @Author:       Rainbow River

#include <iostream>
using namespace std;
// 计算 斐波那契数列 的第 n 项
const int MAXN = 101;
int dp[MAXN];

int fib(int n){
    if(n<=2)return 1;
    else{
        if(dp[n] != 0)
            return dp[n]; // 已经计算过
        else{
            dp[n] = fib(n-1) + fib(n-2);    // 计算并保存
            return dp[n];   // 然后返回
        }
    }
}
int fib2(int n){
    if(n<=2)return 1;
    else return fib2(n-1)+fib2(n-2);
}
int main(){
    for(int i=50; i>0; i--){
        cout << fib(i) << " ";
    }
    return 0;
}