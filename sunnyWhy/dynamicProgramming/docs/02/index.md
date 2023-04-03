---
title: "动态规划专题-经典问题集（一）"
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
例如，现有序列`A={1, 2, 3, -1, -2, 7, 9}`(下标从1开始), 它的最长不下降子序列是`[1, 2, 3, 7, 9]`，长度为5。另外，还有一些子序列是不下降子序列，比如`[-1, 7, 9]` 和 `[-2, 7, 9]`等,但都不是最长的。

```c++
// @FileName:     lis.cpp
// @CreateTime:   2023/03/31 10:43:06
// @Author:       Rainbow River

#include<iostream>
using namespace std;
const int MAXN = 101;
int nums[MAXN], n;  // 输入数组及其长度
int dp[MAXN], pt[MAXN]; // dp状态数组, 路径追踪数组
// dp[i] 表示以 A[i]结尾的LIS长度
// pt[i] 表示 在[0, ..., i)中选择尾随哪一个编号 或者自成一派
void init_arr(){
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> nums[i];
        pt[i] = -1;
    }
}

void solve(){
    // 外层移动 i 指针
    for(int i=0; i<n; i++){
        int mx = 0, pti = -1;
        // 内层访问 A[0, ..., i)
        for(int j=0; j<i; j++){
            if(nums[i] >= nums[j] && dp[j] > mx){
                mx = dp[j];
                pti = j;    // 寻找其中可继承的LIS最长的编号
            }
        }
        // 进行决策
        if(mx == 0){
            dp[i] = 1;  // 没找到
            pt[i] = i;
        }else{
            dp[i] = mx+1;
            pt[i] = pti;    // 附在 pti 后
        }
    }
}

void result(int i, int step){
    if(pt[i] == i)  // 这是路径的开头
        cout << "Length of LIS is " << step << endl;
    else
        result(pt[i], step+1);  // 先打印前面的
    cout << i+1 << " ";
}

void _info(){
    cout << "------------" << endl;
    for(int i=0; i<n; i++){
        cout << "i: " << i << ", LIS: " << dp[i] << ", prev id: " << pt[i] << endl;
    }
    cout << "------------" << endl;
}
int main(){
    init_arr();
    solve();
    _info();
    result(n-1, 1);
    return 0;
}

/*
最长不下降子序列(LongestIncreasing Sequence，LIS)是这样一个问题:
在一个数字序列中，找到一个最长的子序列(可以不连续)，使得这个子序列是不下降(非递减)的
例如，现有序列A={1, 2, 3, -1, -2, 7, 9}(下标从1开始), 它的最长不下降子序列是[1, 2, 3, 7, 9]，长度为5。
*/

/*
8
1 2 3 -9 3 9 0 11

7
1 2 3 -1 -2 7 9
*/

```

## 例题3. 最长公共子序列(LCS)
最长公共子序列(`Longest Common Subsequence，LCS`)的问题描述为:给定两个字符串(或数字序列)A和B，求一个字符串，使得这个字符串是A和B的**最长公共部分**(子序列可以不连续)。如样例所示，字符串“`sadstory`”与“`adminsorry`”的最长公共子序列为“`adsory`”，长度为`6`。
```c++
// @FileName:     mxcommon.cpp
// @CreateTime:   2023/04/01 09:55:57
// @Author:       Rainbow River

/*
最长公共子序列(`Longest Common Subsequence，LCS`)的问题描述为:
    给定两个字符串(或数字序列)A和B，求一个字符串，使得这个字符串是A和B的最长公共部分(子序列可以不连续)。
input: sadstory与 adminsorry 的最长公共子序列为 adsory，长度为 6 。
*/

#include<iostream>
#include<string>
using namespace std;
const int MAXN = 101;
string strA, strB;
int dpAB[MAXN][MAXN], path_trace[MAXN][MAXN];

void initial_input(){
    cin >> strA >> strB;
    // 初始化 dp 数组
    for (int i=0; i<strA.length(); i++){
        if(strA[i] == strB[0]){
            dpAB[i][0] = 1;
            path_trace[i][0] = 1;
        }
    }
    for (int j=0; j<strB.length(); j++){
        if (strB[j] == strA[0]){
            dpAB[0][j] = 1;
            path_trace[0][j] = 1;
        }
    }
}

void solve_dp(){
    for(int i=1; i<strA.length(); i++){
        for(int j=1; j<strB.length(); j++){
            if(strA[i]==strB[j]){
                dpAB[i][j] = dpAB[i-1][j-1]+1;
                path_trace[i][j] = 1;
            }else{
                if(dpAB[i-1][j] > dpAB[i][j-1]){// 继承上方
                    dpAB[i][j] = dpAB[i-1][j];
                    path_trace[i][j] = 2;
                }else{
                    dpAB[i][j] = dpAB[i][j-1];
                    path_trace[i][j] = 3;
                }
            }
        }
    }
}

void trace_path(int i, int j){
    if(i==0 || j==0)   // trace 到了起点
        cout << "Longest common substring: ";
    else{
        switch (path_trace[i][j]){
            case 1: trace_path(i-1, j-1);break;
            case 2: trace_path(i-1, j);break;
            case 3: trace_path(i, j-1);break;
        }
    }
    if (path_trace[i][j] == 1)
        cout << strA[i];
}
int main(){
    initial_input();
    solve_dp();
    trace_path(strA.length()-1, strB.length()-1);
    cout << endl;
    cout << dpAB[strA.length()-1][strB.length()-1];
    return 0;
}

/*
A: adminsorry
B: sadstory
回想 LSS, LIS, 这里不妨设立:
dp[i][j] 表示 A[0, ... i] 与 B[0, ..., j] 的最大公共子序列的长度
  s  a  d  s  t  o  r  y
a 0  1  0  0  0  0  0  0
d 0  1  2  2  2  2  2  2
m 0  1  2  2  2  2  2  2
i 0  1  2  2  2  2  2  2
n 0  1  2  2  2  2  2  2
s 1  1  2  3  3  3  3  3
o 0  1  2  3  3  4  4  4
r 0  1  2  3  3  4  5  5
r 0  1  2  3  3  4  5  5
y 0  1  2  3  3  4  5  6

dp[i+1][j+1] = (a[i]==b[j])? dp[i][j]+1 : max(dp[i][j+1], dp[i+1][j])
*/
```

## 例题4. 最长回文子串(LPS)
最长回文子串(`Longest Palindrome Sequence, LPS`)的问题描述:
给出一个字符串S，求S的最长回文子串的长度。
样例: 字符串"PATZJUJZTACCBCC"的最长回文子串为"ATZJUJZTA"，长度为9.

还是先看暴力解法:枚举子串的两个端点i和j，判断在[i, j]区间内的子串是否回文。从复杂度上来看，枚举端点需要 O(n^2)，判断回文需要 O(n)，因此总复杂度是 O(n^3)。可能会有读者想把这个问题转换为最长公共子序列(LCS)问题来求解:把字符串 S 倒过来变成字符串 T，然后对S和T进行LCS 模型求解，得到的结果就是需要的答案。而事实上这种做法是错误的，因为一旦 S中同时存在一个子串和它的倒序，那么答案就会出错。例如字符串S="ABCDZJUDCBA”，将其倒过来之后会变成T="ABCDUJZDCBA"，这样得到最长公共子串为"ABCD”，长度为4，而事实上S 的最长回文子长度为 1。因此这样的做法是不行的。

1. 暴力搜索
```c++
#include <iostream>
#include <string>
using namespace std;
bool judge_ok(int i, int j);
void palindrome(int& mxl);
string iptstr;
// 暴力搜索
void palindrome(int& mxl){
    for(int i=0; i<iptstr.length(); i++){
        for(int j=i; j<iptstr.length(); j++){
            if(judge_ok(i, j))
                mxl = (j-i+1) > mxl ? (j-i+1) : mxl;
        }
        cout << "i = " << i << ", mxl = " << mxl << endl;
    }
}

// if a string is a palindrome
bool judge_ok(int i, int j){
    while(i<=j){
        if(iptstr[i]==iptstr[j]){
            ++i;
            --j;
        }else return false;
    }
    return true;
}

int main(){
    cin >> iptstr;
    int mxl = 0;
    palindrome(mxl);
    cout << mxl;
    return 0;
}

```
2. 使用dp数组
```c++
// 给出一个字符串S，求S的最长回文子串的长度
// 定义状态数组dp[][], dp[i][j]表示S[i, ...,j]是否为回文字符串, i<=j
// 于是: dp[i][j] = (S[i] == S[j]) ? dp[i+1][j-1]: false;
#include <iostream>
#include <string>
using namespace std;
string iptstr, substr;

void palindrome(){
    int n = iptstr.length();
    // 定义一个上三角布尔数组
    bool **dp = new bool* [n];
    for(int i=0; i<n; i++)
        dp[i] = new bool [n-i];
    substr = iptstr[0];
    // 初始化: 从左上[0, 0]到右下[n-1, n-1]的两条对角线
    for(int i=0; i<n; i++)
        dp[i][i] = true;
    for(int i=0; i<n-1; i++)
        if(iptstr[i]==iptstr[i+1]){
            dp[i][i+1] = true;
            substr = iptstr.substr(i, 2);
        }else dp[i][i+1]=false;
    // 接着 fill the rest slope
    for(int layer=3; layer<=n; layer++){
        for(int i=0; i<=n-layer; i++){
            if(iptstr[i] == iptstr[layer+i-1]){
                dp[i][layer-1+i] = dp[i+1][layer-2+i];
                if(dp[i][layer-1+i]) substr = iptstr.substr(i, layer);
            }else dp[i][layer-1+i] = false;
        }
    }
}

int main(){
    while(true){
        cin >> iptstr;
        palindrome();
        cout << substr << endl;
        if(substr.length()==1)break;
    }
    return 0;
}
```

