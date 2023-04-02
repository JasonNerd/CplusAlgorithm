// @FileName:     palindrome.cpp
// @CreateTime:   2023/04/02 10:55:47
// @Author:       Rainbow River

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