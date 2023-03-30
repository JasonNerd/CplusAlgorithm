// @FileName:     numtower2.cpp
// @CreateTime:   2023/03/29 10:20:13
// @Author:       Rainbow River

#include <iostream>
using namespace std;
const int MAXN = 64;
int num_tower[MAXN][MAXN], dp[MAXN][MAXN], trace_path[MAXN][MAXN];
int n;  // 数塔层数

void solve_dp(int i, int j){
    dp[i][j] = num_tower[i][j];
    if(i<n-1){
        if(dp[i+1][j]==0) solve_dp(i+1, j); // 如果未求解, 则先求一下
        if(dp[i+1][j+1]==0) solve_dp(i+1, j+1);
        bool flg = dp[i+1][j] > dp[i+1][j+1];
        dp[i][j] += flg? dp[i+1][j] : dp[i+1][j+1];
        trace_path[i][j] = flg? 1: -1;  // 1表示左下, -1表示右下
    }
}

void print_trace(int i, int j){
    cout << "(" <<i <<", " << j << ")";
    if(i < n-1){
        if(trace_path[i][j] == 1) print_trace(i+1, j);
        if(trace_path[i][j] == -1) print_trace(i+1, j+1);
    }
}

int main(){
    // 1. 输入数塔
    cin >> n;
    for(int i=0; i<n; i++){
        for(int j=0; j<=i; j++){
            cin >> num_tower[i][j];
        }
    }
    // 2. 递归的求解dp[][], 并保存路径选择
    solve_dp(0, 0);
    cout << dp[0][0] << endl;
    print_trace(0, 0);
    // 44
    // (0, 0)(1, 1)(2, 2)(3, 2)(4, 3)
    return 0;
}