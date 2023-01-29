/*
二叉树的定义（递归）
（1）要么二叉树没有根节点，是一个空节点
（2）要么二叉树由根节点、左子树、右子树组成，且左子树和右子树均为二叉树
*/
#include <iostream>
using namespace std;
typedef int dtType;
struct BTnode{
    BTnode *lch, *rch;
    dtType data;
    BTnode() {}
    BTnode(dtType d){
        this->lch = nullptr;
        this->rch = nullptr;
        this->data = d;
    }
};
typedef struct BTnode* BTree;

BTnode* newBTnode(dtType d){
    BTnode * pn = new BTnode;
    pn->data = d;
    pn->lch = nullptr;
    pn->rch = nullptr;
    return pn;
}

BTnode* search(BTree root, dtType x){
    if (root == nullptr){
        return nullptr;
    }
    if (root->data == x) return root;  // 查找值为x的节点并返回
    search(root->lch, x);
    search(root->rch, x);
}

BTnode* update(BTree& root, dtType x, dtType m){
    // 查找值为x的节点，修改为m，将修改后的节点指针返回
    BTnode* n = search(root, x);
    if (n)
        n->data = m;
    return n;
}

int main(){
    BTree btr = newBTnode(10);
    btr->lch = newBTnode(12);
    btr->rch = newBTnode(23);
    update(btr, 23, 25);
    cout << btr->rch->data << endl;
    return 0;
}

/*
关于二叉树的几个概念：
a. 关于树的基本概念
（1）【空二叉树】是指没有任何节点的二叉树
（2）【层】，根节点为第1层，其子节点为第2层
（3）【度】，节点的子节点数目，0，1，2
（4）【叶节点】，度为0的节点
（5）【深度】，节点的层次，例如根节点深度为1（或者0），它的左子树的根节点的深度则为2（或1）
（6）【高度】，从最底层叶节点（高度为1或0）算起，节点的高度
（7）【路径】，从根节点向下遍历到某节点经过的节点序列
（8）【父节点】、【左孩子】、【右孩子】、【祖先】
b. 关于二叉树的基本概念
（1）【满二叉树】每一层的节点数都达到了当前层的最大节点数
（2）【完全二叉树】除最下面一层外，其余层均达到最大节点数，且最后一层的节点从左到右连续紧密排列，这些连续节点右侧不存在其他节点
*/