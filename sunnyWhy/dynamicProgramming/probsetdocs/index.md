---
title: "动态规划专题-经典问题集"
date: 2023-03-30T11:32:13+08:00
draft: false
tags: ["算法", "动态规划"]
categories: ["学习笔记"]
twemoji: true
lightgallery: true
---

## 例题1. 最大连续子序列和
`给定一个数字序列A1, A2, ..., An; 求i, j(1 <= i, j <= n), 使得Ai+...+Aj最大, 输出这个最大和sum和i, j.`

思考: 考虑问题是要求一个序列的连续子序列, 这个连续子序列的数字之和必须是所有子序列里最大的, 一个想法就是遍历所有这样的子序列, 在其中搜索和最大的即可, 此时算法时间复杂度为$O(n^3)$. 此时, 不妨固定i使其为0也即整个序列的开端, 迭代j指针, 观察 [0, ..., j] 内的子序列. 定义这样一个状态数组dp[n], dp[i]表示[0, i]且包含A[i]的子序列的最大和, 那么如何通过dp[i-1]得到dp[i], dp[i-1]表示包括了A[i-1]的连续子序列的最大和, 在加入A[i]后, 这将构成一个新的连续序列, 其和为 dp[i-1]+A[i], 而如果 dp[i-1]<0, 则舍弃 dp[i-1], 使得A[i]成为新的最大子序列的和, 在这一求解过程中得到的最大值即为求解结果
```c++
#include <iostream>
using namespace std;
int n;
const int MAXN = 101;
int dp[MAXN], nums[MAXN];

int main(){
    cin >> n;
    int mxs=0;
    for(int i=0; i<n; i++){
        cin >> nums[i];
        if(nums[i] < mxs)
            mxs = nums[i];
    }
    // 求解 dp 数组
    dp[0] = nums[0];
    for(int i=1; i<n; i++){
        if(dp[i-1]>0)  dp[i] = dp[i-1] + nums[i];
        else dp[i] = nums[i];
        if(dp[i] > mxs) mxs = dp[i];
    }
    cout << mxs << endl;
    return 0;
}
/*
6
-2 11 -4 13 -5 -2
*/
```

## 例题2. 最长不下降子序列(LIS)
最长不下降子序列(LongestIncreasing Sequence，LIS)是这样一个问题:
`在一个数字序列中，找到一个最长的子序列(可以不连续)，使得这个子序列是不下降(非递减)的`
例如，现有序列`A={1, 2, 3, -1, -2, 7, 9}`(下标从1开始), 它的最长不下降子序列是`[1, 2, 3, 7, 9]`，长度为5。另外，还有一些子序列是不下降子序列，比如`[1, 2, 3]` 和 `[1, -2, 7]`等,但都不是最长的。

