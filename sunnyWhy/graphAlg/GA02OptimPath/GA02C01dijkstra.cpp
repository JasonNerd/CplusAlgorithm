/*
Diikstra算法
使用场景: 解决单源路径最短问题, 给定图G和起点s, 通过算法得到s到其他任一顶点的最短距离
假定图的顶点编号为整数, 0~N-1, 只考虑有向图
输入
M N s
n1 n2 w12
...
M是总边数, N是总的节点数, s为出发顶点, 下接M行, 表示每条边的入点、出点、边权

*/
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 101;   // 顶点数, 边数, 权重 均小于该值
// 图节点定义
struct gnode{
    int v, w;   // 出边顶点, 边权
    gnode(int v, int w){
        this->v = v;
        this->w = w;
    }
};
vector<gnode> graph[MAXN];  // 邻接表
int edge_n, vertex_n, v_start;  // 边数, 顶点数, 起始节点编号
bool having_disposed[MAXN]; // 记录哪些节点已经收敛
int opt_plen[MAXN];     // 记录源点s到其他节点的最短路径长度
int opt_path[MAXN];     // 记录某节点最短路径的前驱节点编号
void init_graph();
void slacken();
int find_minw_v();
void info();
void prt_path(int p);

void init_graph(){
    cin >> edge_n >> vertex_n >> v_start;
    for (int i=0; i<edge_n; i++){
        int v_from, v_to, w_ft;
        cin >> v_from >> v_to >> w_ft;
        graph[v_from].push_back(gnode(v_to, w_ft));
    }
    for (int i=0; i<vertex_n; i++){
        opt_plen[i] = MAXN; // 初始时假定所有(除s)节点距离s无限远
        opt_path[i] = -1;   // 初始时前驱均为-1表示处于未收敛状态
        having_disposed[i] = false; // 同理
    }
    opt_plen[v_start] = 0;  // 初始节点与自己距离为0
}

// 进行一次松弛操作
void slacken(){
    // 1. 从所有未收敛的节点选一个与初始节点最近的节点
    int p = find_minw_v();
    // 2. 以p为中介对p的邻接点进行松弛
    for(auto nd: graph[p]){
        if(opt_plen[nd.v] > (opt_plen[p]+nd.w)){
            // 如果当前邻居可以通过p进行优化(也即路径长变小)
            opt_plen[nd.v] = opt_plen[p]+nd.w;  // 那么进行松弛
            opt_path[nd.v] = p;     // 说明当前 p 是 nd.v 最短路径的 前驱
        }
    }
    // 3. 将p标记为已收敛
    having_disposed[p] = true;
}
// 从所有未收敛的节点选一个与初始节点最近的节点
int find_minw_v(){
    // int mid = 0, mw = opt_plen[0];  // 默认第一个节点
    int mid = -1, mw = MAXN;  // 默认第一个节点
    for (int i=0; i<vertex_n; i++){
        if(opt_plen[i] < mw && !having_disposed[i]){
            mid = i;
            mw = opt_plen[i];
        }
    }
    return mid;
}

void info(){
    cout << endl;
    for(int i=0; i<vertex_n; i++){
        cout << i << " - ";
        for(auto j : graph[i]){
            cout << "(" << j.v << ", " << j.w << ") ";
        }
        cout << endl;
    }
}

void res(){
    for(int i=0; i<vertex_n; i++){
        cout << opt_plen[i] << " ";
    }
    cout << endl;
}

// 打印指定节点的最短路径
void prt_path(int p){
    vector<int> path;
    while (true){
        if (p != -1)
            path.push_back(p);
        else break;
        p = opt_path[p];
    }
    for(int i=path.size()-1; i>=0; i--){
        cout << path[i];
        if(i>0)cout << "->";
    }
}
void prt_path2(int p){
    if(p == -1)
        return ;
    prt_path2(opt_path[p]);     // 先打印前驱
    cout << p << " ";
}

int main(){
    init_graph();
    // 进行n次松弛(n个节点就都收敛)
    // info();
    for(int i=0; i<vertex_n; i++)
        slacken();
    // res();
    prt_path2(5);
    return 0;
}

/*
// 输入
8 6 0
0 1 1
0 3 4
0 4 4
1 3 2
2 5 1
3 2 2
3 4 3
4 5 3
// 邻接表结构
0 - (1, 1) (3, 4) (4, 4)
1 - (3, 2)
2 - (5, 1)
3 - (2, 2) (4, 3)
4 - (5, 3)
5 -
// 最短路数组
0 1 5 3 4 6

*/

