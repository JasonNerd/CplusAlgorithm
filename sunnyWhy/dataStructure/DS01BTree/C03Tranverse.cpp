/*
二叉树遍历
前序遍历：总是按 根节点-左孩子-右孩子 的顺序访问二叉树的节点
中序遍历：总是按 左孩子-根节点-右孩子 的顺序访问二叉树的节点
后序遍历：总是按 左孩子-右孩子-根节点 的顺序访问二叉树的节点
层序遍历：指从上到下、从左到右地按层一层层地访问二叉树的节点
*/
// 给定二叉树节点数 n 、后序序列 post[n] 和中序序列 mid[n] ，求层序遍历序列 layer[n]，n<=30

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