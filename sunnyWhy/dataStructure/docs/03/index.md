---
title: "第01章-二叉树(三)-二叉查找树BST"
date: 2023-04-02T21:57:02+08:00
draft: false
tags: ["算法", "二叉树"]
categories: ["学习笔记"]
twemoji: true
lightgallery: true
---

## 二叉查找树(binary search tree)
定义:
(1) 要么二叉查找树是一棵空树
(2) 要么它由根节点、左子树、右子树组成，左子树和右子树均为二叉查找树，且左子树的
    所有节点的权重均小于等于右子树的；
操作：
（1）查找: btn* search(bst root, int x);   // 查找值为x的节点并返回节点指针
（2）插入: bst insert(bst root, int x);    // 创建节点x，插入x（原地修改）
（3）建立: bst create(int a[]);     // 建立一棵bst
（4）删除: bst delnode(bst root, int x);
特点：
中序遍历得到的权重序列是升序有序的

```c++
#include <iostream>
#include <vector>

using namespace std;
struct btn{
    int weight;
    btn *lch, *rch;
};
typedef btn* bst;
// 查找值为x的节点并返回节点指针
btn* search(bst root, int x);
// 创建节点x，插入x（原地修改）
void insert(bst& root, int x);
// 建立一棵bst
bst create(int a[], int n);
bst create(vector<int> a);
// 删除值为x的节点, 若节点x有两个子树，应当找到节点的前驱prev或者后继post作为替代
void delnodeA(bst& root, int x);
// 使用prev代替待删节点后删除prev
btn* getPrev(btn* bnd);
// 使用post代替待删节点后删除post
btn* getPost(btn* bnd);
// 删除节点的递归优雅方式
void delnodeB(bst &root, int x);
// 中序遍历
void tranverse(bst root);

// 测试函数
void test(bst mbst);
void delTest(bst mbst, void (*delFunc)(bst&, int));

btn* search(bst root, int x){
    if (!root) return nullptr;  // 查找失败
    if(root->weight == x) return root;  // 查找成功
    else if (root->weight < x){     // 在右子树
        return search(root->rch, x);
    }else{                          // 在左子树
        return search(root->lch, x);
    }
}

void insert(bst& root, int x){
    if(root){
        if(root->weight == x) return ;  // 相同值, 不予插入
        else if(root->weight < x){      // x应该插入到右子树
            insert(root->rch, x);
        }else{
            insert(root->lch, x);
        }
    }else{
        // 此即为插入位置
        root = new btn;
        root->weight = x;
        root->lch = root->rch = nullptr;
    }
}

bst create(int a[], int n){
    bst t = nullptr;
    for(int i=0; i<n; i++){
        insert(t, a[i]);
    }
    return t;
}

bst create(vector<int> a){
    bst t = nullptr;
    for(int i=0; i<a.size(); i++){
        insert(t, a[i]);
    }
    return t;
}

void delnodeA(bst& root, int x){
    // 非递归删除，第一步查找x结点
    btn *p = root, *q = root;   // 采用双指针方法，q为遍历指针, p指示q的双亲
    bool search_ok = false;     // 查找成功的标志
    while (q){
        if (q->weight == x){
            search_ok = true;
            break;
        }else if (q->weight < x){   // x在右子树
            p = q;
            q = q->rch;
        }else{
            p = q;
            q = q->lch;
        }
    }
    if(!search_ok)  return ;     // 不存在该节点, 直接返回
    btn* ready = q;     // ready指向待删节点指针(保存下来)
    // 存在该节点为q，当q不是根节点时p指向双亲
    if(q->lch && q->rch){   // q有左右子树, 以找后继为例
        p = q;
        q = q->rch;
        while(q->lch){
            p = q;
            q = q->lch;
        }
    }
    ready->weight = q->weight;
    // 以下情况可能出现 q是根节点, 
    if(!q->lch && !q->rch){     // 叶节点
        if(q == root){
            root = nullptr;
            return ;
        }
        else{
            if(q == p->lch)
                p->lch = nullptr;
            else
                p->rch = nullptr;
        }
    }else if(q->lch && !q->rch){    // 只有左孩子
        if (q == root){
            root = root->lch;
            delete q;
        }else{
            if(q == p->lch) // q是p的左孩子
                p->lch = q->lch;
            else
                p->rch = q->lch;
            delete q;
        }
    }else if(!q->lch && q->rch){    // 只有右孩子
        if (q==root){
            root = root->rch;
            delete q;
        }else{
            if(q == p->lch) // q是p的左孩子
                p->lch = q->rch;
            else
                p->rch = q->rch;
            delete q;
        }
    }
    // return root;
} 

btn* getPrev(btn* bnd){
    // 左子树的最右节点, 注意bnd有左右两个孩子
    btn *lp = bnd->lch, *rp = lp->rch;
    while(rp){
        lp = rp;
        rp = lp->rch;
    }
    return lp;
}

btn* getPost(btn* bnd){
    // 右子树的最左节点, 注意bnd有左右两个孩子
    btn *rp = bnd->rch, *lp = rp->lch;
    while(lp){
        rp = lp;
        lp = rp->lch;
    }
    return rp;
}
// 递归删除节点的写法
void delnodeB(bst &root, int x){
    if(!root) return ;
    if(root->weight == x){
        if(!root->lch && !root->rch){
            root = nullptr;
        }else if(root->lch != nullptr){ // 包含左子树
            btn* nd = getPrev(root);
            root->weight = nd->weight;
            delnodeB(root->lch, nd->weight);
        }else{  // 仅包含右子树
            btn* nd = getPost(root);
            root->weight = nd->weight;
            delnodeB(root->rch, nd->weight);
        }
    }else if (root->weight < x){
        delnodeB(root->rch, x);
    }else{
        delnodeB(root->lch, x);
    }
}

void tranverse(bst root){
    if(root){
        tranverse(root->lch);
        cout << root->weight << " ";
        tranverse(root->rch);
    }
}
void test(bst mbst){
    cout << "+++++++++++++++" << endl;
    tranverse(mbst);
    cout << endl;
}

void delTest(bst mbst, void (*delFunc)(bst&, int)){
    delFunc(mbst, 2);
    test(mbst);
    delFunc(mbst, 2);
    test(mbst);    
    delFunc(mbst, 4);
    test(mbst);
    delFunc(mbst, 6);
    test(mbst);
    delFunc(mbst, 5);
    test(mbst);
    delFunc(mbst, 8);
    test(mbst);
    delFunc(mbst, 15);
    test(mbst);
    delFunc(mbst, 11);
    test(mbst);
    delFunc(mbst, 10);
    test(mbst);
    delFunc(mbst, 23);
    test(mbst);
    delFunc(mbst, 28);
    test(mbst);
    delFunc(mbst, 17);
    test(mbst);
    delFunc(mbst, 12);
    test(mbst);
}

int main(){
    vector<int> lseq = {8, 4, 15, 2, 6, 11, 23, 5, 10, 12, 17, 28};
    bst mbst = create(lseq);
    // delTest(mbst, delnodeA);
    delTest(mbst, delnodeB);
    
}

/*
        8
  4          15
2   6     11     23
   5    10 12  17  28

*/

```

## 例题. If it a bst
PAT-A-1403 Is it a binary tree?
给定一个序列，判断它是否为一棵二叉查找树（或其镜像）的先序序列, 输入包括第一行的数字N(<=1000)表示节点数，第二行为先序遍历序列. 注意：左子树节点严格小于根节点，右节点不小于根节点. 输出为两行
YES(是)或者NO(不是)
后序遍历序列
```c++
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
// 定义树节点 
struct btNode{
    int weight;
    btNode *lch, *rch;
};
typedef struct btNode* binTree;
// 存储遍历序列
vector<int> preSeq, inSeq, posSeq;
// 节点数量 numNodes
int numNodes;
// ok是结果标志，初值为true, 若遇到矛盾则置为false
// mirror是指示标志，表示是否考虑镜像可能
bool ok=true, mirror=false;     // 
void preTranverse(binTree t);   // 先序遍历
void midTranverse(binTree t);   // 中序遍历
void posTranverse(binTree t);   // 后序遍历
void prtSeq(vector<int> seq);   // 打印序列
// 通过前序序列和中序序列构建二叉树
// void preCreate(binTree& root, int preA, int preB, int midA, int midB);
void judgeIfBst(binTree& root, int preA, int preB, int midA, int midB);

int main(){
    int buf;
    cin >> numNodes;    // 节点序列
    for (int i = 0; i < numNodes; i++){
        cin >> buf;
        preSeq.push_back(buf);      // 先序序列
    }
    // 主要函数: assign()深复制, sort()排序, reverse()倒序
    // 头文件: <algorithm>
    inSeq.assign(preSeq.begin(), preSeq.end());
    sort(inSeq.begin(), inSeq.end());   // 升序序列
    binTree root=nullptr;
    // preCreate(root, 0, numNodes-1, 0, numNodes-1);
    judgeIfBst(root, 0, numNodes-1, 0, numNodes-1);
    if(ok){
        posSeq.clear();
        posTranverse(root);
        prtSeq(posSeq);
        cout << endl;
        cout << "YES";
    }else{
        ok = true;
        mirror = true;  // 说明可能是镜像
        reverse(inSeq.begin(), inSeq.end());    // 中序序列变了
        judgeIfBst(root, 0, numNodes-1, 0, numNodes-1);
        if(ok){
            posSeq.clear();
            posTranverse(root);
            prtSeq(posSeq);
            cout << endl;
            cout << "YES";
        }else{
            cout << "NO";
        }
    }
    return 0;
}

void preTranverse(binTree t){
    if(t){
        preSeq.push_back(t->weight);
        preTranverse(t->lch);
        preTranverse(t->rch);
    }
}

void midTranverse(binTree t){
    if(t){
        midTranverse(t->lch);
        inSeq.push_back(t->weight);
        midTranverse(t->rch);
    }
}

void posTranverse(binTree t){
    if(t){
        posTranverse(t->lch);
        posTranverse(t->rch);
        posSeq.push_back(t->weight);
    }
}

void prtSeq(vector<int> seq){
    int n = seq.size();
    for (int i=0; i<n; i++){
        cout << seq[i];
        if (i < n-1){
            cout << " ";
        }
    }
}

void judgeIfBst(binTree& root, int preA, int preB, int midA, int midB){
    if (!ok) return ;   // 创建失败就直接返回
    if (preA > preB || midA > midB) return ;
    root = new btNode;
    root->weight = preSeq[preA];
    root->lch = root->rch = nullptr;
    // 中序序列寻找根节点
    int rID, lsubN, flag=-1;  // 根节点在中序序列的序号， 左子树节点数
    if (!mirror)
        for (rID=midA; rID<= midB; rID++){
            if(inSeq[rID] == root->weight){
                flag = 1;
                break;
            }
        }
    else
        for (rID=midB; rID>= midA; rID--){
            if(inSeq[rID] == root->weight){
                flag = 1;
                break;
            }
        }
    if (flag == -1){
        ok = false; // 没找到根节点，构建失败哦
        return ;
    }
    lsubN = rID - midA;
    judgeIfBst(root->lch, preA+1, preA+lsubN, midA, rID-1);
    judgeIfBst(root->rch, preA+lsubN+1,preB, rID+1, midB);
}
```
仍然是判断某序列是否为二叉排序树（或镜像）的先序遍历序列, 但换一种思路：
也即将给定序列依据题意依次插入从而形成bst，再对其进行先序（镜像）遍历得到遍历序列，观察是否与给定序列相同，是则输出yes并给出后序序列，否则输出NO
```c++
#include<iostream>
#include<vector>
using namespace std;
struct binNode{
    int weight;
    binNode *lch, *rch;
};
typedef binNode* binTree;
int n;                      // 节点数
vector<int> inputSeq, transSeq;     // 遍历序列
void insert(binTree &t, int d);     // 插入节点
void prevTranverse(binTree t);      // 前序遍历
void postTranverse(binTree t);      // 后序遍历
void mirrorPrev(binTree t);         // 镜像前序遍历
void mirrorPost(binTree t);         // 镜像后序遍历
void prtSeq();                      // 打印遍历序列

int main(){
    int tmp;
    cin >> n;
    binTree t = nullptr;
    for (int i=0; i<n; i++){
        cin >> tmp;
        inputSeq.push_back(tmp);
        insert(t, tmp);
    }
    transSeq.clear();
    prevTranverse(t);
    if (inputSeq == transSeq){
        cout << "YES" << endl;
        transSeq.clear();
        postTranverse(t);
        prtSeq();
    }else{
        transSeq.clear();
        mirrorPrev(t);
        if(transSeq == inputSeq){
            cout << "YES" << endl;
            transSeq.clear();
            mirrorPost(t);
            prtSeq();
        }else{
            cout << "NO";
        }
    }
    return 0;
}

void prtSeq(){
    for (int i = 0; i < n; i++){
        cout << transSeq[i];
        if (i != n-1)cout << " ";
    }
}

void insert(binTree &t, int d){
    if(t){
        if(d < t->weight)
            insert(t->lch, d);
        else
            insert(t->rch, d);
    }else{
        t = new binNode;
        t->weight = d;
        t->lch = t->rch = nullptr;
    }
}

void prevTranverse(binTree t){
    if(t){
        transSeq.push_back(t->weight);
        prevTranverse(t->lch);
        prevTranverse(t->rch);
    }
}

void postTranverse(binTree t){
    if(t){
        postTranverse(t->lch);
        postTranverse(t->rch);
        transSeq.push_back(t->weight);
    }
}

void mirrorPrev(binTree t){
    if(t){
        transSeq.push_back(t->weight);
        mirrorPrev(t->rch);
        mirrorPrev(t->lch);
    }
}

void mirrorPost(binTree t){
    if(t){
        mirrorPost(t->rch);
        mirrorPost(t->lch);
        transSeq.push_back(t->weight);
    }
}

```
