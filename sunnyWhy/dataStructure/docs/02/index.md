---
title: "第01章-二叉树(二)-应用示例"
date: 2023-04-02T21:04:20+08:00
draft: false
tags: ["算法", "二叉树"]
categories: ["学习笔记"]
twemoji: true
lightgallery: true
---

## 1. 权重为W的所有路径
给出一棵树，每个节点具有权重，路径被定义为从根节点到某一叶节点的节点序列，【路径权重】被定义为路径所有节点的权重之和。给定一个数字n，求路径权重等于n的所有路径.
第一行, 表示 节点数m、非叶节点数k、路径权重n,
第二行, 给出编号从0到m-1的节点权重, 以后每行都是非叶节点编号、孩子节点数以及的孩子节点编号
输出每一行都表示一个路径，注意输出路径每个节点权重而非编号，若有多个结果按降序进行输出
```c++
输入样例:
20 9 24
10 2 4 3 5 10 2 18 9 7 2 2 1 3 12 1 8 6 2 2
00 4 01 02 03 04
02 1 05
04 2 06 07
03 3 11 12 13
06 1 09
07 2 08 10
16 1 15
13 3 14 16 17
17 2 18 19
输出:
10 5 2 7
10 4 10
10 3 3 6 2
10 3 3 6 2
```
1. 通过先序遍历或者深度优先搜索， 每遍历到叶节点就计算路径权重并与给定值作比较，若相等则加入到结果中:
```c++
#include <iostream>
#include <vector>
using namespace std;
int m, k, n;    // 节点数、非叶节点数、路径权重
struct Tnode{
    int weight;             // 节点权重
    vector<int> children;   // 子节点编号列表
};
vector<Tnode> wTree;    // 静态存储的树
vector<int> path;       // 存储路径各节点id
vector< vector<int> > result;   // 存储最后的结果序列（可能有多个
// 依据输入构造一棵树
void construct();
// 求取路径和
int getSum();
/* 采用先序遍历（也即深度优先搜索）思路是：碰到叶节点即形成完整序列, 计算序列和 w, 
若 w与n 相等, 则该序列符合要求，予以输出(保存) */
void preTranverse(int root);
// 打印输出结果
void prtRes();

void construct(){
    cin >> m >> k >> n;
    // 创建节点，输入权重
    for(int i=0; i<m; i++){
        Tnode node;
        cin >> node.weight;
        wTree.push_back(node);
    }
    // 创建树结构，添加孩子节点id信息
    for(int i=0; i<k; i++){
        int id, chn;
        cin >> id >> chn;
        for(int j=0; j<chn; j++){
            int cid;
            cin >> cid;
            wTree[id].children.push_back(cid);
        }
    }
}

void preTranverse(int root){
    path.push_back(root);
    int chn = wTree[root].children.size();
    if (chn == 0){
        int w = getSum();
        cout << "Path finished" << endl;
        cout << "path weight = " << w << endl;
        for (int i=0; i<path.size(); i++)
            cout << path[i] << " ";
        cout << endl;
        if (w == n){    // 找到了合适的路径
            vector<int> pthW;
            for(int i=0; i<path.size(); i++)
                pthW.push_back(wTree[path[i]].weight);
            result.push_back(pthW);
        }
    }
    for(int i=0; i<chn; i++){
        preTranverse(wTree[root].children[i]);
        path.pop_back();    // 注意这个pop_back()位置，这是形成正确搜索路径的关键
    }
}

int getSum(){
    int sum = 0;
    for(int i=0; i<path.size(); i++){
        sum += wTree[path[i]].weight;
    }
    return sum;
}

void prtRes(){
    for(int i=0; i<result.size(); i++){
        for(int j=0; j<result[i].size(); j++)
            cout << result[i][j] << " ";
        cout << endl;
    }
}

int main(){
    construct();
    cout << "**************" << endl;
    preTranverse(0);
    prtRes();
    return 0;
}
```
2. 对原程序进行改进，第一是关于路径和的问题，可以看到每次遍历到叶节点都要单独计算一次，不妨设立一个psum，它保存当前遍历过的节点权重和，于是可避免重复计算。其二，原程序并未考虑题目中结果按从大到小的顺序输出，似乎事后排序有些困难？考虑到树中孩子节点的顺序并不影响整棵树的遍历过程，因此这里不妨将孩子按照权重值的降序进行排序，那么先序遍历时自然而然就是先得到孩子节点权重大的路径了。其三还是关于路径和, 假如当前还未遍历到叶节点, 但psum已经不小于给定值了，那么可以立即返回。

```c++
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Tnode{
    int weight;
    vector<int> children;
};
vector<Tnode> wTee; // 树
int m, n, k; // m节点数, n权重, k非叶节点数
vector<int> pathW;
bool cmp(int a, int b);
void construct();
void dfsPre(int root, int csum);

bool cmp(int a, int b){
    return wTee[a].weight > wTee[b].weight;
}

void construct(){
    cin >> m >> k >> n;
    for(int i=0; i<m; i++){
        Tnode nd;
        cin >> nd.weight;
        wTee.push_back(nd);
    }
    for(int i=0; i<k; i++){
        int rt, chn, chid;
        cin >> rt >> chn;
        for(int j=0; j<chn; j++){
            cin >> chid;
            wTee[rt].children.push_back(chid);
        }
        // 对孩子节点按权重从大到小进行排序, 事前排序
        sort(wTee[rt].children.begin(), wTee[rt].children.end(), cmp);
    }
}

void dfsPre(int root, int csum){
    Tnode rt = wTee[root];
    csum += rt.weight;
    pathW.push_back(rt.weight);
    if(csum > n) return ;
    if(csum == n){
        if(rt.children.size()==0){ // 叶子节点
            int pn = pathW.size();
            for(int i=0; i<pn; i++){
                cout << pathW[i];
                if (i<pn-1) cout << " ";
            }
            cout << endl;
        }
        return ;
    }
    for(int i=0; i<rt.children.size(); i++){
        dfsPre(rt.children[i], csum);
        pathW.pop_back();
    }
}

int main(){
    construct();
    cout << "+++++++++++++++" << endl;
    dfsPre(0, 0);
    return 0;
}
```