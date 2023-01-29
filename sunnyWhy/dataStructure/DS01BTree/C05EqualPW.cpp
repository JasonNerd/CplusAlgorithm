/*
给出一棵树，每个节点具有权重，路径被定义为从根节点到某一叶节点的节点序列，【路径权重】
被定义为路径所有节点的权重之和。给定一个数字n，求路径权重等于n的所有路径.
第一行, 表示 节点数m、非叶节点数k、路径权重n,
第二行, 给出编号从00到m-1的节点权重, 以后每行都是非叶节点编号、孩子节点数以及的孩子节点编号
输出每一行都表示一个路径，注意输出路径每个节点权重而非编号，若有多个结果按降序进行输出
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
*/

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



