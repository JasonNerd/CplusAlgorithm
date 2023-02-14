/*
使用邻接表实现图的存储, 用广度优先遍历方法遍历图
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int MXN = 100;   // N为最大节点数
int n, s;     // n为实际节点数(编号 0 到 n-1 ), s为遍历起始节点
vector<int> tranverse_seq;      // 节点编号遍历序列
bool having_accessed[MXN];      // 记录各个顶点是否 已加入队列
struct Node{
    int v;  // 出边顶点编号
    int w;  // 边权重
    Node(int v, int w){
        this->v = v;
        this->w = w;
    }
};
vector<Node> graph[MXN];
// 使用队列实现广度优先
void bfsTranverse(){
    queue<int> q;
    q.push(s);
    having_accessed[s] = true;
    while (!q.empty()){
        int rt = q.front();
        tranverse_seq.push_back(rt);    // 出队后访问
        q.pop();
        for (auto nd: graph[rt]){
            if(!having_accessed[nd.v]){
                q.push(nd.v);
                having_accessed[nd.v] = true;
            }
        }
    }
}

void init_grah(){
    n = 5;
    graph[0].push_back(Node(1, 2));     // 从 节点0 出发到 节点1 的边权重为 2
    graph[0].push_back(Node(4, 1));     // 从 节点0 出发到 节点4 的边权重为 1
    graph[1].push_back(Node(2, 2));     // 从 节点1 出发到 节点2 的边权重为 2
    graph[1].push_back(Node(4, 2));     // 从 节点1 出发到 节点4 的边权重为 2
    graph[2].push_back(Node(3, 1));     // 从 节点2 出发到 节点3 的边权重为 1
    graph[3].push_back(Node(4, 1));     // 从 节点3 出发到 节点4 的边权重为 1
    graph[1].push_back(Node(0, 2));     // 从 节点1 出发到 节点0 的边权重为 2
    graph[4].push_back(Node(0, 1));     // 从 节点4 出发到 节点0 的边权重为 1
    graph[2].push_back(Node(1, 2));     // 从 节点2 出发到 节点1 的边权重为 2
    graph[4].push_back(Node(1, 2));     // 从 节点4 出发到 节点1 的边权重为 2
    graph[3].push_back(Node(2, 1));     // 从 节点3 出发到 节点2 的边权重为 1
    graph[4].push_back(Node(3, 1));     // 从 节点4 出发到 节点3 的边权重为 1
}

void prt_res(int start){
    s = start;
    init_grah();
    bfsTranverse();
    for(auto i: tranverse_seq){
        cout << i << " ";
    }
    cout << endl;
}

int main(){
    // prt_res(0);
    prt_res(1);
    return 0;
}

/*
图示例(无向图):
(V0, V1, 2)
(V0, V4, 1)
(V1, V2, 2)
(V1, V4, 2)
(V2, V3, 1)
(V3, V4, 1)
*/