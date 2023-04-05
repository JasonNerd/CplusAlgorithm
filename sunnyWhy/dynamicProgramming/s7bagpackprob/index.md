---
title: "背包问题"
date: 2023-04-03T18:57:23+08:00
draft: false
tags: ["算法", "动态规划"]
categories: ["学习笔记"]
twemoji: true
lightgallery: true
---
背包问题是一类经典的动态规划问题，它非常灵活、变体多样，需要仔细体会。本书只介绍两类最简单的背包问题:01 背包问题和完全背包问题，而这两种背包中，又以01 背包为重。
*01背包问题*
有n件物品，每件物品的重量为 `w[i]`，价值为`c[i]`。现有一个容量为`V`的背包，问如何选取物品放入背包，使得背包内物品的总价值最大。其中每种物品都只有`1`件。
```c++
5 8
3 5 1 2 2
4 5 2 1 3
```
令`dp[i][v]`表示前i件物品`(1<i<n, 0<v<V)`装入容量为v的背包中所能获得的最大价值。
考虑对第i件物品的选择策略，有两种策略：
(1) 不放第件物品那么问题转化为前i-1件物品装入容量为v的背包中所能获得的最大价值，也即dp[i-1][v]。
(2) 放第i件物品，那么问题转化为前`i-1`件物品装入容量为`v-w[i]`的背包中所能获得的最大价值，也即`dp[i-1][v-w[i]]+c[i]`。 
```c++
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
```
可以知道，时间复杂度和空间复杂度都是 `O(nV)`，其中时间复杂度已经无法再优化，但是空间复杂度还可以再优化.
注意到状态转移方程中计算`dp[i][v]`时总是只需要`dp[i-1][v]`左侧部分的数据(即只需要图中正上方与左上方的数据)，且当计算`dp[i+1]`的部分时，`dp[i-1]`的数据又完全用不到了，因此不妨仅设立一维数组 `dp[v]`。每计算出一个`dp[i][v]`，就相当于把 `dp[i-1][v]`抹消，因为在后面的运算中`dp[i-1][]`再也用不到了。我们把这种技巧称为**滚动数组**。
```c++
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
```