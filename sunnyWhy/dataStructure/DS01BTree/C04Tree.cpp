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