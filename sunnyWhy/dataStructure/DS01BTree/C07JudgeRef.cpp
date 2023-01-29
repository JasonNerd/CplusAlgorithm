/*
仍然是判断某序列是否为二叉排序树（或镜像）的先序遍历序列
但换一种思路：
也即将给定序列依据题意依次插入从而形成bst，再对其进行先序（镜像）遍历
得到遍历序列，观察是否与给定序列相同，是则输出yes并给出后序序列，否则
输出NO
*/

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

