// @FileName:     bagpack2.cpp
// @CreateTime:   2023/04/05 15:13:44
// @Author:       Rainbow River
#include <iostream>
using namespace std;
const int MAXN = 101;
int w[MAXN], c[MAXN];   // w[] 物品质量数组, c[] 物品价值数组
int n, bag;     // n 物品数量, bag 背包容量
// 滚动数组: dp[v] = max(dp[v], dp[v-w[i]]+c[i])
int dp[MAXN];     // dp[v] 状态数组

void info(int a[]){
    for(int i=1; i<=bag; i++)
        cout << a[i] << " ";
    cout << endl;
}

void init_problem(){
    cin >> n >> bag;
    for(int i=1; i<=n; i++)
        cin >> w[i];
    for(int i=1; i<=n; i++)
        cin >> c[i];
}

void solve_probem(){
    for(int i=1; i<=n; i++){
        for(int v=bag; v>=w[i]; v--)    // 逆序, 保证dp[v-w[i]]是未被更新过的(i-1的状态)
            dp[v] = max(dp[v-w[i]]+c[i], dp[v]);
    }
}

int main(){
    init_problem();
    solve_probem();
    cout << dp[bag] << endl;
    return 0;
}