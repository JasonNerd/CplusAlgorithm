// @FileName:     numtower.cpp
// @CreateTime:   2023/03/29 10:18:23
// @Author:       Rainbow River

#include <iostream>
/*
数塔
从顶部走到底部, 路径长最大值是多少?
开辟一个dp[][]数组, dp[i][j] 表示从 (i,j) 出发到底部的路径最大长度
dp[i][j] = max(dp[i+1][j], dp[i+1][j+1]) + num_tower[i][j]
*/
using namespace std;
const int MAXN = 64;
int num_tower[MAXN][MAXN], dp[MAXN][MAXN];

int main(){
    // 1. 输入数塔
    int n;
    cin >> n;
    for(int i=0; i<n; i++){
        for(int j=0; j<=i; j++){
            cin >> num_tower[i][j];
        }
    }
    // 2. 求解dp[][], 从底层开始
    for(int i=n-1; i>=0; i--){
        for(int j=0; j<=i; j++){
            dp[i][j] = (dp[i+1][j]>dp[i+1][j+1]?dp[i+1][j]:dp[i+1][j+1])+num_tower[i][j];
        }
    }
    // 3. dp[0][0]即为解答
    cout << dp[0][0] << endl; // 44
    return 0;
}
/*
         5
       8  3
    12  7  16
  4  10  11  6
9  5   3   9  4
5
5
8 3
12 7 16
4 10 11 6
9 5 3 9 4
*/