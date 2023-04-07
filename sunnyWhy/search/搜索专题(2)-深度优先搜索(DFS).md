---
title: "搜索专题(2)-深度优先搜索(DFS)"
date: 2023-04-07T15:06:35+08:00
draft: false
tags: ["搜索", "DFS", "算法"]
categories: ["学习笔记"]
twemoji: true
lightgallery: true
---

例如，以走迷宫为例，我们总是选择岔道口中的一条前进，而如果遇到了新的岔道口，仍选择新岔道口中的一条岔路前进，直到走到死胡同，此时返回上一个岔道口，选择另一条岔路前进。这种策略在深度上进行，不走到死胡同就不回头，称为深度优先遍历.

注意到，深度优先搜素会遍历所有的路径，并且每走到一个死胡同，就代表着一个完整路径的形成。深度优先搜索是一种枚举所有完整路径以遍历所有情况的方法使用栈或者递归可以很好的解决递归问题.

## 1. 背包问题
```git
// 假设有n件物品，已知价格v[i]和w[i]，选取重量不超过W的物品使价格总和最大
```
题解: 对于物品i, 有选或者不选两种情况.
```c++
#include <iostream>
#include <vector>
using namespace std;
const int MXN = 20;
vector<int> v={14, 30, 4, 3, 17, 7, 13, 8, 40, 22};
vector<int> w={3, 7, 1, 1, 4, 2, 3, 2, 9, 5};
int n = 10, mxv = 0, bag=12;
void DFS(int index, int cuV, int cuW){
    if(index >= n){
        if(cuW<=bag && cuV > mxv)
            mxv = cuV;
        return ;
    }
    // cout << "index="<<index << ", current Value = " << cuV << ", current Weight = " << cuW << endl;
    DFS(index+1, cuV, cuW);
    DFS(index+1, cuV+v[index], cuW+w[index]);
}
int main(){
    DFS(0, 0, 0);
    cout << mxv << endl; 
    return 0;
}
```

在上面的代码中, 每次都会进入两个分支, 从而形成了一个完全搜索二叉树, 复杂度很高, 并且每次都会走到路径的尽头, 考虑到如果当前物品的质量之和已经比背包容量大了就可以不往下继续深挖了, 这在搜索树上看起来就像是剪掉了一个枝杈:
```c++
#include <iostream>
#include <vector>
using namespace std;
const int MXN = 20;
vector<int> v={14, 30, 4, 3, 17, 7, 13, 8, 40, 22};
vector<int> w={3, 7, 1, 1, 4, 2, 3, 2, 9, 5};
int n = 10, mxv = 0, bag=12;
void DFS(int index, int cw, int cv){
    if(index >= n){
        if (cw <= bag){
            if(cv >= mxv)
                mxv = cv;
        }
        return ;
    }
    DFS(index+1, cw, cv);
    if (cw + w[index] <= bag){
        if (cw+w[index] > mxv){
            mxv = cw+w[index];
        }
        DFS(index+1, cw+w[index], cv+v[index]);
    }
}
int main(){
    DFS(0, 0, 0);
    cout << mxv << endl;
    return 0;
}
```

## 2. 选数字问题
从s个数中选取k个数使其和为x，若有多个答案选取平方和最大的一组
```c++
#include <iostream>
#include <vector>
using namespace std;
vector<int> seq = {12, -3, 1, 1, 4, -2, 7, 5, 2, 6, 3, -4};
int x = 12, msq = 0, k=3, n=12;
vector<int> res, rea;

int sum_(){
    int rsm = 0;
    for(int j=0; j<res.size(); j++)
        rsm += res[j];
    return rsm;
}

int sq_sum(){
    int sqm = 0;
    for (int j=0; j<res.size(); j++)
        sqm += res[j]*res[j];
    return sqm;
}

void selectK(int i, int ck){
    int rsm = sum_(), sqm = sq_sum();
    if(ck >= k){
        if(rsm == x && sqm >= msq){
            msq = sqm;
            rea = res;
        }
        return ;
    }
    if(i>=n)return ;
    res.push_back(seq[i]);
    selectK(i+1, ck+1);
    res.pop_back();
    selectK(i+1, ck);
}

int main(){
    selectK(0, 0);
    for(int i=0; i<rea.size(); i++)
        cout << rea[i] << " ";
    cout << "max square sum = " << msq << endl;
    return 0;
}
```

修改题目条件:
从n个数中选k个数使其和为x，每个数可重复选，可包含负数，若有多个结果，取平方和最大的

```c++
#include <iostream>
#include <vector>
using namespace std;
vector<int> tmp, ans, seq = {5, -2, 3, 1};
int n = 4, x = 27, k = 9, mxSqsum = 0;
void selectK(int index, int curK, int curSum, int curSq){
    if (curK == k && curSum==x){
        if (curSq >= mxSqsum){
            ans = tmp;
            mxSqsum = curSq;
        }
        return ;
    }
    if(index >= n || curK > k) return ;
    tmp.push_back(seq[index]);
    selectK(index, curK+1, curSum+seq[index], curSq+seq[index]*seq[index]);
    tmp.pop_back();
    selectK(index+1, curK+1, curSum, curSq);
}
int main(){
    selectK(0, 0, 0, 0);
    for(int i=0; i<ans.size(); i++)
        cout << ans[i] << " ";
    cout << "max square sum = " << mxSqsum << endl;
    return 0;
}
```

## 枚举子序列
```c++
// 枚举所有子序列
#include <iostream>
#include <vector>
using namespace std;
vector<int> seq = {1, 3, 5}, res;
int n = 3;

void enumSubSeq(int i){
    if (i>=n){
        for(int j=0; j<res.size(); j++)
            cout << res[j] << " ";
        cout << endl;
        return ;
    }
    enumSubSeq(i+1);
    res.push_back(seq[i]);
    enumSubSeq(i+1);
    res.pop_back();
}

int main(){
    enumSubSeq(0);
    return 0;
}
/*
enumSubSeq(0)
    enumSubSeq(1)
        enumSubSeq(2)
            enumSubSeq(3)
                cout;
                return ;
            (5)
            enumSubSeq(3)
                cout 5;
                return ;
            ()
        (3)
        enumSubSeq(2)
            enumSubSeq(3)
                cout 3;
                return ;
            (3, 5)
            enumSubSeq(3)
                cout 3, 5;
                return ;
            (3)
        ()
    (1)
    enumSubSeq(1)
        enumSubSeq(2)
            enumSubSeq(3)
                cout 1;
                return ;
            (1, 5)
            enumSubSeq(3)
                cout  1, 5;
                return ;
            (1)
        (1, 3)
        enumSubSeq(2)
            enumSubSeq(3)
                cout 1, 3;
                return ;
            (1, 3, 5)
            enumSubSeq(3)
                cout 1, 3, 5;
                return ;
            (1, 3)
        (1)
    ()
return ;
*/
```