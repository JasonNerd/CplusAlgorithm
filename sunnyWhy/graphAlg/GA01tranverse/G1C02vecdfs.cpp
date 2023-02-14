/*
使用邻接表实现图的存储, 用深度优先遍历方法遍历图
*/

#include <iostream>
#include <vector>
#include <stack>
using namespace std;
const int MXN = 100;   // N为最大节点数
int n;     // n为实际节点数(编号 0 到 n-1 ), s为遍历起始节点
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
// 使用 栈 实现深度优先
void dfsTranverse(int start){
    stack<int> q;
    tranverse_seq.push_back(start); // 访问节点
    q.push(start);                  // 节点入栈
    having_accessed[start] = true;  // 标记为已入栈
    bool founded = false;           // 栈顶节点的邻居是否已被全部访问完毕
    while (!q.empty()){
        int rt = q.top();           // 1. 取栈顶节点
        founded = false;            // 初始假定找不到未访问的邻居
        for (auto nd: graph[rt]){
            if(!having_accessed[nd.v]){     // 2. 找到一个未访问的节点
                tranverse_seq.push_back(nd.v); // 访问该节点
                q.push(nd.v);                   // 入栈
                having_accessed[nd.v] = true;   // 并标记
                founded = true;                 // 找到了未访问的邻居
                break;      // break是第一个关键点, 此时邻居节点位于栈顶, 所以应 break 并立即尝试 访问该邻居的邻居
            }
        }
        if (!founded)
            q.pop();    // 说明 当前节点的所有邻居都访问结束, 可以弹出栈
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
    init_grah();
    dfsTranverse(start);
    for(auto i: tranverse_seq){
        cout << i << " ";
    }
    cout << endl;
}

int main(){
    // prt_res(0);
    prt_res(2);
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