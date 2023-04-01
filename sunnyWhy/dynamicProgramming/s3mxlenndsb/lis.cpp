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