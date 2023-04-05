// @FileName:     bagpack1.cpp
// @CreateTime:   2023/04/05 10:17:33
// @Author:       Rainbow River

#include <iostream>
using namespace std;
/*
0-1背包问题: 先看如何设置状态, 需要考察状态的维度, 例如本题中有两个维度
分别是 物品质量和背包容量, 具体的dp[i][v]是指仅考虑前i个物品且背包质量
为 v 的情况下获得的最大价值
*/

const int MAXN = 101;
int w[MAXN], c[MAXN];   // w[] 物品质量数组, v[] 物品价值数组
int n, bag;     // n 物品数量, bag 背包容量
int dp[MAXN][MAXN];     // dp[i][v] 状态数组
int p[MAXN][MAXN];     // 回溯数组

void init_problem(){
    cin >> n >> bag;
    for(int i=1; i<=n; i++)
        cin >> w[i];
    for(int i=1; i<=n; i++)
        cin >> c[i];
}

void solve_probem(){
    // dp[0][]=0, dp[][0]=0
    for(int i=1; i<=n; i++){
        for(int v=1; v<=bag; v++){
            if(v >= w[i] && (dp[i-1][v-w[i]]+c[i]) > dp[i-1][v]){
                dp[i][v] = dp[i-1][v-w[i]]+c[i];
                p[i][v] = 1;   // 表示选择第 i 件物品
            }else{ // v容量太小, 无法装入 w[i] 或者 装入物品i后得不到更大的价值
                dp[i][v] = dp[i-1][v];    
                p[i][v] = -1;  // 表示不选第 i 件物品
            }
        }
    }
}

void path_tracing(int i, int v){
    // 从[n, bag] 开始回溯
    if(i<=0 || bag<=0){
        cout << "Get it: " << endl;
    }else{
        if(p[i][v] == -1)
            path_tracing(i-1, v);
        if(p[i][v] == 1){
            path_tracing(i-1, v-w[i]);
            cout << "Put object " << i << ", ("<< w[i] << ", " << c[i] << ")" << endl;
        }
    }
}

int main(){
    init_problem();
    solve_probem();
    path_tracing(n, bag);
    cout << dp[n][bag] << endl;
    return 0;
}
/*
5 8
3 5 1 2 2
4 5 2 1 3

*/