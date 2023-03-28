// @FileName:     toposort.cpp
// @CreateTime:   2023/03/28 10:42:57
// @Author:       Rainbow River
/*
拓扑排序完整程序示例: 它输出一个拓扑排序序列, 若不存在, 则打印
错误提示
*/
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
const int MAXN = 101;
struct node{
    int v, w;
    node(int v, int w){
        this->v = v;
        this->w = w;
    }
};
vector<node> graph[MAXN];
int in_deg[MAXN];   // 入度表
int ver_n, adj_n;   // 顶点数, 边数
vector<int> topo_seq; // 拓扑序列

void init_graph(){
    cin >> ver_n >> adj_n;
    for(int i=0; i<adj_n; i++){
        int v0, v1;
        cin >> v0 >> v1;
        graph[v0].push_back(node(v1, 0));   // the weight info is useless here
        in_deg[v1]++;   // 更新入度
    }
}

bool topology_sort(){
    queue<int> wrkq;
    // 将所有入度为0的节点加入 wrkq
    for(int i=0; i<ver_n; i++)
        if(in_deg[i] == 0)
            wrkq.push(i);
    while (!wrkq.empty()){
        int rt = wrkq.front();
        for(node nd: graph[rt]){
            if(--in_deg[nd.v]==0)     // 遍历 rt 指向节点, 将它们的入度减1
                wrkq.push(nd.v);    // 若为0加入队列
        }
        wrkq.pop();
        topo_seq.push_back(rt);
    }
    return topo_seq.size() == ver_n;
}

int main(){
    init_graph();
    bool sort_ok = topology_sort();
    if(sort_ok){
        for(int nid: topo_seq)
            cout << nid << " ";
        cout << endl;
    }else{
        cout << "It's not a DAG, so doesn't have topo-seq." << endl;
    }
}
/*
negtive example:
5 7
0 1
0 2
1 2
3 0
3 2
1 4
4 3
*//*
positive example:
5 8
0 1
0 2
0 3
3 1
1 4
3 2
2 4
3 4
*/