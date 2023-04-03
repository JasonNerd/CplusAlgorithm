---
title: "第01章-二叉树"
date: 2023-04-02T20:46:51+08:00
draft: false
tags: ["算法", "二叉树"]
categories: ["学习笔记"]
twemoji: true
lightgallery: true
---
## 二叉树的定义（递归）
* （1）要么二叉树没有根节点，是一个空节点
* （2）要么二叉树由根节点、左子树、右子树组成，且左子树和右子树均为二叉树
## 关于二叉树的几个概念：
* **关于树的基本概念**
1. 【空二叉树】是指没有任何节点的二叉树
2. 【层】，根节点为第1层，其子节点为第2层
3. 【度】，节点的子节点数目，0，1，2
4. 【叶节点】，度为0的节点
5. 【深度】，节点的层次，例如根节点深度为1（或者0），它的左子树的根节点的深度则为2（或1）
6. 【高度】，从最底层叶节点（高度为1或0）算起，节点的高度
7. 【路径】，从根节点向下遍历到某节点经过的节点序列
8. 【父节点】、【左孩子】、【右孩子】、【祖先】
* **关于二叉树的基本概念**
1. 【满二叉树】每一层的节点数都达到了当前层的最大节点数
2. 【完全二叉树】除最下面一层外，其余层均达到最大节点数，且最后一层的节点从左到右连续紧密排列，这些连续节点右侧不存在其他节点

-----
## 二叉树的遍历
先序、中序、后序遍历, 它是递归的。例如先序遍历, 是依次遍历根节点、左子树和右子树。若在遍历过程中记录访问节点，就会得到遍历序列，通过遍历序列还可以反向还原二叉树的结构。同时，从层或者深度、高度的概念上，还有层序遍历，它是指从上到下、从左到右的遍历二叉树的每一个节点，有些时候还需要记录节点的层数，这可以往向节点添加新的层数属性，也可以设定一个last-access指针做到。如下给出了通过中序和后序序列构造还原二叉树的代码实现:
```c++
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct BTnode{
    int data;
    BTnode *lch, *rch;
};
typedef BTnode* BinTree;
const int MXLEN = 39;
int n;
int post[MXLEN], mid[MXLEN];
vector<int> tranverseSeq;

// post[postS, postE]为后序序列, [midS, midE]为中序序列, 返回的是序列构建而成的二叉树的根节点
BinTree postRecover(int postS, int postE, int midS, int midE);
// 对二叉树bt进行层序遍历, 遍历序列存放在tranverseSeq
void layerTranverse(BinTree bt);
// 前序遍历
void prevTranverse(BinTree bt);
// 中序遍历
void midTranverse(BinTree bt);
// 后序遍历
void postTranverse(BinTree bt);
// 打印tranverseSeq数组
void prtTranverse();

int main(){
    cin >> n;
    for (int i=0; i<n; i++)
        cin >> post[i];
    for (int i=0; i<n; i++)
        cin >> mid[i];
    BinTree t = postRecover(0, n-1, 0, n-1);
    cout << "Binary tree created!" << endl;
    layerTranverse(t);
    cout << "layer tranverse sequence generated!" << endl;
    prtTranverse();

    cout << endl;
    tranverseSeq.clear();
    prevTranverse(t);
    cout << "prev tranverse sequence generated!" << endl;
    prtTranverse();

    cout << endl;
    tranverseSeq.clear();
    midTranverse(t);
    cout << "mid tranverse sequence generated!" << endl;
    prtTranverse();
    
    cout << endl;
    tranverseSeq.clear();
    postTranverse(t);
    cout << "post tranverse sequence generated!" << endl;
    prtTranverse();
    return 0;
}

BinTree postRecover(int postS, int postE, int midS, int midE){
    if (postS > postE)
        return nullptr;
    BTnode* root = new BTnode;
    root->data = post[postE];   // 后序序列的最后一个表示根节点
    int k;  // 从mid中序序列查找 root->data 的编号
    for (k=midS; k<=midE; k++)
        if (mid[k] == root->data)
            break;
    int ltNum = k - midS;    // 左子树节点数
    // 后序序列左子树区间[postS, postS+ltNum-1], 右子树区间[postS+ltNum, postE-1]
    root->lch = postRecover(postS, postS+ltNum-1, midS, k-1);
    // 中序序列左子树区间[midS, k-1], 右子树区间[k+1, midE]
    root->rch = postRecover(postS+ltNum, postE-1, k+1, midE);
    return root;
}

void layerTranverse(BinTree bt){
    queue<BinTree> trQ;
    trQ.push(bt);
    while (!trQ.empty()){
        BTnode* r = trQ.front();
        tranverseSeq.push_back(r->data);
        if(r->lch)trQ.push(r->lch);
        if(r->rch)trQ.push(r->rch);
        trQ.pop();
    }
}

void prevTranverse(BinTree bt){
    if(!bt)return;
    tranverseSeq.push_back(bt->data);
    prevTranverse(bt->lch);
    prevTranverse(bt->rch);
}

void midTranverse(BinTree bt){
    if(!bt)return;
    midTranverse(bt->lch);
    tranverseSeq.push_back(bt->data);
    midTranverse(bt->rch);
}

void postTranverse(BinTree bt){
    if(!bt)return;
    postTranverse(bt->lch);
    postTranverse(bt->rch);
    tranverseSeq.push_back(bt->data);
}

void prtTranverse(){
    for (int i = 0; i < n; i++){
        cout << tranverseSeq[i];
        if(i != n-1)
            cout << " ";
    }
    
}
/*
input sample
7
2 3 1 5 7 6 4
1 2 3 4 5 6 7
binary tree
    4
1       6
  3   5  7
2
output
4 1 6 3 5 7 2
*/

/*
progress imitate
(0, 6, 0, 6)
root[4], k=3, ltNum=3
[4]->l = (0, 2, 0, 2)
    [2, 3, 1], [1, 2, 3], postS=0, postE=2, midS=0, midE=2
    k = 0, ltNum = 0-0 = 0
    [1]->l = (0, -1, 0, -1)

*/
```
## 树的表示与遍历
特点是一个节点可能有多个孩子，没有左右之分，遍历方法有先序、层序等.可以用序号表示节点, 节点本身则保存一个权重和孩子节点id.
```c++
/*
【树】的表示与遍历
特点是一个节点可能有多个孩子，没有左右之分，遍历方法有先序、层序等
*/
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
typedef int dataType;
// 节点结构，一个数据位，一个则保存子节点编号
struct TNode{
    dataType d;
    vector<int> children;   // 孩子节点编号
};
int n;  // n为节点数, 节点编号0, 1, 2, ..., n-1
vector<TNode> mTree;
vector<int> tranSeq;


void prtSeq();
// 得到一个固定结构的树, NULL 可以利用 children 判断为空表示, n=7, 节点值分别是 8, 5, 4, 7, 6, 3, 2
void getTree();
// 先序遍历, 每次先访问根节点，再依次访问孩子
void preTranverse(int root);
// 层序遍历, 往往题目给出的节点编号即按此次序
void layerTranverse(int root);
void getTree(){
    // V0 -> V1, V2, V3
    // V1 -> V4, V5
    // V2 -> NULL
    // V3 -> V6
    // V4 -> NULL, V5 -> NULL, V6 -> NULL
    TNode v0, v1, v2, v3, v4, v5, v6;
    v0.d = 8;
    v0.children.push_back(1);
    v0.children.push_back(2);
    v0.children.push_back(3);
    v1.d = 5;
    v1.children.push_back(4);
    v1.children.push_back(5);
    v2.d = 4;
    v3.d = 7;
    v3.children.push_back(6);
    v4.d = 6;
    v5.d = 3;
    v6.d = 2;
    mTree.push_back(v0);
    mTree.push_back(v1);
    mTree.push_back(v2);
    mTree.push_back(v3);
    mTree.push_back(v4);
    mTree.push_back(v5);
    mTree.push_back(v6);
    n = 7;
}

void preTranverse(int root){
    tranSeq.push_back(root);
    for(int i=0; i<mTree[root].children.size(); i++){
        preTranverse(mTree[root].children[i]);
    }
}

void layerTranverse(int root){
    queue<int> workQ;
    workQ.push(root);
    while(!workQ.empty()){
        int f = workQ.front();
        tranSeq.push_back(f);
        workQ.pop();
        for(int i=0; i<mTree[f].children.size(); i++)
            workQ.push(mTree[f].children[i]);
    }
}

void prtSeq(){
    for(int i=0; i<n; i++){
        cout << "V" << tranSeq[i];
        if(i < n-1)cout << " ";
    }
}

int main(){
    getTree();
    // 先根遍历, 这实际相当于 深度优先搜索
    preTranverse(0);
    prtSeq();
    // 层序遍历, 这实际相当于 广度优先搜索
    tranSeq.clear();
    layerTranverse(0);
    prtSeq();
    return 0;
}

```