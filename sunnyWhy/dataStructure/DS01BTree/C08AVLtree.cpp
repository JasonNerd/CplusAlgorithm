/*
平衡二叉树( AVL树, 前苏联两位数学家提出 ), 也即平衡的二叉查找树。
也即左右子树的高度差不超过1。
定义【平衡因子】为左子树高度减去右子树高度，则AVL树平衡因子绝对值不超过1

基本操作是:
1. 生成一个新节点
2. 获取节点高度
3. 计算节点平衡因子
4. 更新根节点高度
5. 查找、插入、删除
// 二叉树查找, 实际和二叉排序树一样, 期望复杂度O(h) = o(lg N)
// void search(avlT root, int x);   // 鸡肋

// 删除节点
使用递归的方法，对于非叶节点总是寻找到前驱（后继）替换并删除
因此主要考虑叶节点的删除，核心在于节点高度的更新

*/
#include<iostream>
#include<vector>
using namespace std;
// 二叉树节点，包含权重和节点高度
struct avlNode{
    int weight, height;
    avlNode *lch, *rch;
};
typedef avlNode* avlT;
// 生成一个新节点
avlNode* newNode(int w);
// 获取节点高度
int getHeight(avlNode* root);
// 计算节点平衡因子
int getBalanceFactor(avlNode* root);
// 更新节点高度
void updateHeight(avlNode* root);
// 左旋: 使左孩子成为根节点, 这同时也相当于LL调整
// 也即由于在左孩子的左子树上插入了新节点导致根节点不平衡
void leftRotate(avlT &root);
// 右旋: 使右孩子成为根节点, 这同时也相当于RR调整
// 也即由于在右孩子的右子树上插入了新节点导致根节点不平衡
void rightRotate(avlT &root);
// LR调整, 左孩子的右子树插入了新节点导致根节点不平衡
// 做法是先对左孩子进行右旋，也即使得左孩子的右孩子成为新的左孩子
// 再对根节点进行左旋，也即使得新的左孩子成为根节点
// RL调整, 右孩子的左子树插入了新节点导致根节点不平衡
// 做法是先对右孩子进行左旋，也即使得右孩子的左孩子成为新的右孩子
// 再对根节点进行右旋，也即使得新的右孩子成为根节点
void insert(avlT &root, int w);

// 删除节点
void delNode(avlT &root, int w);

void preTranverse(avlT t){
    if(t){
        cout << t->weight << " ";
        preTranverse(t->lch);
        preTranverse(t->rch);
    }
}

void midTranverse(avlT t){
    if(t){
        midTranverse(t->lch);
        cout << t->weight << " ";
        midTranverse(t->rch);
    }
}


int main(){
    vector<int> inputseq = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int n = inputseq.size();
    avlT t = nullptr;
    for(int i=0; i<n; i++){
        insert(t, inputseq[i]);
    }
    preTranverse(t);
    cout << endl;
    midTranverse(t);
/*
7 3 2 1 5 4 6 9 8 10
1 2 3 4 5 6 7 8 9 10
       7
  3        9
2   5    8  10 
  4  6
*/
    return 0;
}

avlNode* newNode(int w){
    avlNode* n = new avlNode;
    n->height = 1;
    n->weight = w;
    n->lch = n->rch = nullptr;
    return n;
}

int getHeight(avlNode* root){
    if(!root)return 0;
    else return root->height;
} 

int getBalanceFactor(avlNode* root){
    return getHeight(root->lch)-getHeight(root->rch);
}

void updateHeight(avlNode* root){
    root->height = max(getHeight(root->lch), getHeight(root->rch))+1;
}

void leftRotate(avlT &root){
    avlNode* rrch = root->rch;
    root->rch = rrch->lch;
    rrch->lch = root;       // 更改指针指向
    updateHeight(root);     // 注意及时更新节点高度
    updateHeight(rrch);
    root = rrch;            // 最后记得使rrch成为根节点
}

void rightRotate(avlT &root){
    avlNode* rlch = root->lch;
    root->lch = rlch->rch;
    rlch->rch = root;
    updateHeight(root);
    updateHeight(rlch);
    root = rlch;
}

void insert(avlT &root, int w){
    if (!root){
        root = new avlNode;
        root->weight = w;
        root->lch = root->rch = nullptr;
        updateHeight(root);
    } else {
        if(w < root->weight){
            insert(root->lch, w);   // 插入到左孩子
            updateHeight(root);     // 插入后更新根节点高度
            int f = getBalanceFactor(root);     // 计算根节点平衡因子
            int fl = getBalanceFactor(root->lch);   // 计算左孩子的因子
            // 首先判断根节点是否平衡
            if(f > 1){
                if(fl>0){
                    rightRotate(root);
                }else{
                    leftRotate(root->lch);
                    rightRotate(root);
                }
            }
        } else {
            insert(root->rch, w);
            updateHeight(root);
            int f = getBalanceFactor(root);
            int fr = getBalanceFactor(root->rch);
            if(f < -1){
                if(fr>0){   // RL
                    rightRotate(root->rch);
                    leftRotate(root);
                }else{      // RR
                    leftRotate(root);
                }
            }
        }
    }
}

void delNode(avlT &root, int w){
    
}

/*
AVL树的插入操作，核心是要动态的保持avl树的特性，也即平衡
第一步，按照权重大小找到插入位置进行插入
第二步，更新节点高度
第三步，计算节点平衡因子
第四步，若绝对值不大于1则结束，否则第五步
第五步，对左子树或右子树进行左旋、右旋以达到平衡

1. 左旋：使右孩子成为根节点而自己成为原右孩子的左孩子
    A
Al    B
    Bl Br
a. 使A的右孩子指针指向Bl ===>
  A  B
Al Bl Br
b. 使B的左孩子指针指向A ===>
      B
  A     Br
Al Bl

2. 右旋：使左孩子成为根节点而自己成为原左孩子的右孩子
      B
  A     Br
Al Ar
a. 使B的左孩子指针指向Ar ==>
  A  B
Al Ar Br
b. 使A的右孩子指针指向B ==>
    A
Al    B
    Ar Br
*/

/*
插入后导致根节点不平衡的4种情况
1. RL型, 在右孩子的左子树上插入新节点导致根节点不平衡, f=-2
    A
Al     C
    D    Cr
  Dl Dr
Al, Dl, Cr, Dr高均为h, H(D)=h+2, f(A)=-2
==> 对根节点右孩子左旋(成为RR型)
    A
Al     D
    Dl   C
       Dr Cr
==> 对根节点左旋(恢复平衡)
      D
  A      C
Al Dl  Dr Cr

2. LR型
       A
   B      Ar
Bl   C
   Cl Cr
=======> 左孩子右旋
          A
     C      Ar
  B    Cr
Bl Cl
======> 根节点左旋
      C
  B      A
Bl Cl  Cr Ar

          A
      B      (h)
  C     (h)
 (h-1) (h-1)
*/

/*
那么插入节点后如何知道是哪个节点（最靠近新插入的节点）不平衡了呢
首先这一节点必然存在于从根节点到该节点的访问路径中，或者查找路径中
需要我们主动找到这个（最近）不平衡的节点吗？
假设不考虑调整问题，那么对于权重为w的节点查找失败也就得到插入位置，
插入后递归返回到父节点，检查平衡因子，由于递归返回的性质，它必然是
离
*/

