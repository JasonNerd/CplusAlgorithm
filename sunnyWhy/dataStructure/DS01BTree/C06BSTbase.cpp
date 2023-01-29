/*
二叉查找树(binary search tree)
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

*/
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
