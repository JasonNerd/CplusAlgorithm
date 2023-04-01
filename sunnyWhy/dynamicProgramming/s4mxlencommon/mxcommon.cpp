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