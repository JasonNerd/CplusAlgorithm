// @FileName:     kruscal.cpp
// @CreateTime:   2023/03/27 22:09:52
// @Author:       Rainbow River

#include <iostream>
#include <algorithm>
using namespace std;
// 这里图的存储完全基于边
struct node{
    int u, v;
    int cost;
};
const int MAXN = 101;
int ver_n, adj_n;
node egdes[MAXN];
int father[MAXN];
bool cmp(node a, node b);
void init_graph();
int kruscal();
int acq_root(int nid);
bool merge_root(int nid1, int nid2);

// 表示将边表 按权重的升序排序
bool cmp(node a, node b){
    return a.cost < b.cost;
}

void init_graph(){
    cin >> ver_n >> adj_n;
    for(int i=0; i<adj_n; i++)
        cin >> egdes[i].u >> egdes[i].v >> egdes[i].cost;
    sort(egdes, egdes+adj_n, cmp);
    // 初始化并查集
    for(int i=0; i<ver_n; i++)
        father[i] = i;
}

// 并查集操作: 查找--也即获取集合根节点
int acq_root(int nid){
    int tmp = nid;
    while(nid != father[nid])
        nid = father[nid];
    // 此时 nid 就是集合 root, 为优化查找, 
    // 这里可以把查找路径上的节点的 father 均修改为 nid
    while (tmp != father[tmp]) {
        int x = tmp;
        tmp = father[tmp];
        father[x] = nid;
    }
    return nid;
}
// 并查集操作: 合并两个节点所在集合, 指明合并是否成功
bool merge_root(int nid1, int nid2){
    int rt1 = acq_root(nid1), rt2 = acq_root(nid2);
    if(rt1 == rt2) return false;
    else{
        father[rt1] = rt2;
        return true;
    }
}

int kruscal(){
    // 不断地将边的两端点所在集合进行合并, 除非两端点在一个集合
    int res = 0, t_edge_n = 0;
    for(int i=0; i<adj_n; i++){ // 从小到大枚举边
        if(merge_root(egdes[i].u, egdes[i].v)){
            res += egdes[i].cost;
            t_edge_n++;
        }
        if(t_edge_n == ver_n-1)break;
    }
    return res;
}

int main(){
    init_graph();
    cout << kruscal() << endl;
    return 0;
}

/*
5 9
0 1 3
0 2 1
0 3 6
1 2 1
1 3 3
1 4 1
2 3 2
2 4 4
3 4 1
*/

/*
6 10
0 1 4
0 4 1
0 5 2
1 2 6
1 5 3
2 3 6
2 5 5
3 4 4
3 5 5
4 5 3
*/