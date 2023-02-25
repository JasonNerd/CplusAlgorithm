/*
SPFA: short path first algorithm
是 Bellman Ford算法的改进版本, 也即并不是一定要 n-1 轮
每条边都更新, 只更新那些顶点值被修改的地点的邻边, 为此
可以借助于队列进行实现
注: 输入不包含负环， 输出第一行为

*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int MAXN = 101;
struct gnode{
    int v, dis; // 出边顶点, 边权
    gnode(int v, int dis){
        this->dis = dis;
        this->v = v;
    }
};
vector<gnode> graph[MAXN];  // 图, 邻接表
int opt_plen[MAXN];     // 最短路径
int ver_n, edg_n, st_p, ed_p;   // 顶点数, 边数, 始点, 终点
bool in_q[MAXN]; // 表示各顶点是否在队列中

void input_graph(){
    cin >> ver_n >> edg_n >> st_p >> ed_p;
    for(int i=0; i<edg_n; i++){
        int f, t, w;
        cin >> f >> t >> w;
        graph[f].push_back(gnode(t, w));
        graph[t].push_back(gnode(f, w));    // 无向图
    }
    for(int i=0; i<ver_n; i++){
        in_q[i] = false;    // 初始时均不在工作队列
        opt_plen[i] = MAXN; // 初始时均不可达
    }
    opt_plen[st_p] = 0;
}

void spfa_alg(){
    queue<int> workQueue;
    workQueue.push(st_p);
    in_q[st_p] = true;
    while (!workQueue.empty()){
        int r = workQueue.front();
        workQueue.pop();
        in_q[r] = false;    // 已弹出
        for(auto nd: graph[r]){
            int mr = opt_plen[r] + nd.dis;
            if (mr < opt_plen[nd.v]){
                opt_plen[nd.v] = mr;
                if (!in_q[nd.v]){
                    workQueue.push(nd.v);   // nd.v 有更新, 需要重新计算
                    in_q[nd.v] = true;
                }
            }
        }
    }
}

int main(){
    input_graph();
    spfa_alg();
    for(int i=0; i<ver_n; i++)
        cout << opt_plen[i] << " ";
    return 0;
}

/*
5 9 0 4
0 1 3
0 2 1
0 3 6
1 2 1
1 3 3
1 4 1
2 3 2
2 4 4
3 4 1

0 2 1 3 3
*/

