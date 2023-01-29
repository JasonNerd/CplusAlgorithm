/*6
PAT-A-1403 Is it a binary tree?
给定一个序列，判断它是否为一棵二叉查找树（或其镜像）的先序序列
输入包括第一行的数字N(<=1000)表示节点数，第二行为先序遍历序列
注意：左子树节点严格小于根节点，右节点不小于根节点
输出为两行
YES(是)或者NO(不是)
后序遍历序列
*/
// 
//
//

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


/* 原始的依据先序序列和中序序列重构bst的程序
这里主要考虑中序序列有两种情况，并判断是否可以重构
void preCreate(binTree& root, int preA, int preB, int midA, int midB){
    // preSeq[preA, preB]为子树前序序列, inSeq[midA, midB]为中序序列
    if (preA > preB || midA > midB)
        return ;
    // 前序序列 preSeq[preA] 根节点
    root = new btNode;
    root->weight = preSeq[preA];
    root->lch = root->rch = nullptr;
    // 中序序列寻找根节点序号，区分左右子树
    int rID, lsubN;  // 根节点在中序序列的序号， 左子树节点数
    for (rID=midA; rID<=midB; rID++){
        if (inSeq[rID] == root->weight)
            break; 
    }
    lsubN = rID-midA; 
    // 分别构建左右子树
    preCreate(root->lch, preA+1, preA+lsubN, midA, rID-1);
    preCreate(root->rch, preA+lsubN+1, preB, rID+1, midB);
}
*/

/*
7
8 6 5 7 10 8 11
YES
5 6 7 8 11 10 8

7
8 10 11 8 6 7 5
YES
11 8 10 7 5 6 8

7
8 6 8 5 10 9 11
NO

***************************
--树结构示例------------
    8
 4    12
2  6    14
--其镜像示例------------
     8
  12   4
14    6 2
***************************
成功的序列构造1，构造出一棵二叉排序树
8 6 5 7 10 8 11
5 6 7 8 8 10 11
     8
  6     10
5  7   8  11
成功的序列构造2
8 10 11 8 6 7 5
5 6 7 8 8 10 11
问题在于：
第一步，在第一个序列中第一个元素为 8
第二步，在第二个序列中遇到8，左边3个左子树，右边3个右子树
第三步，递归左子树，根为10，在【5 6 7】中寻找，发现没有
    ===> 构建失败(找不到根节点)
因此考虑可能是镜像序列，采取倒序
11 10 8 8 7 6 5
[11, 10] 8 [8, 7, 6, 5]
[11, [10]] 8 [8, [7, [6], 5]]
      8
  10    8
11         6
         7   5
11 10 7 5 6 8 8 (后序)
不太一样？
所以构建方法稍有区别

失败的案例
8 6 8 5 10 9 11
5 6 8 8 9 10 11
[[5 6] 8 [8 9 10 11]]
[[5 [6]] 8 [8 9 10 11]]
右子树找不到根节点5
*/
