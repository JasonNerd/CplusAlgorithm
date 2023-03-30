// @FileName:     msss.cpp
// @CreateTime:   2023/03/29 10:27:50
// @Author:       Rainbow River
/*
给定一个数字序列A1, A2, ..., An; 求i, j(1 <= i, j <= n), 
使得Ai+...+Aj最大, 输出这个最大和sum和i, j.
*/
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