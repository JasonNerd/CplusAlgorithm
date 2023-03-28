// @FileName:     prim.cpp
// @CreateTime:   2023/03/27 21:07:35
// @Author:       Rainbow River

#include <iostream>
#include <vector>

using namespace std;
// 例如给一张邻接表图, 求最小生成树边权
struct node{
    int v, w;
    node(int v, int w){
        this->v = v;
        this->w = w;
    }
};

const int MAXN = 101;
bool having_visited[MAXN];  // 已访问节点数组, S
int min_dist[MAXN];         // 存放节点到集合 S 的最短距离
vector<node> graph[MAXN];
int ver_n, adj_n, st_v = 0; // 顶点数, 边数, 假定生成树从节点0开始


void init_graph(){
    cin >> ver_n >> adj_n;
    for (int i=0; i<adj_n; i++){
        int s, e, w;
        cin >> s >> e >> w;
        graph[s].push_back(node(e, w));
        graph[e].push_back(node(s, w));
    }
    for(int i=0; i<ver_n; i++)
        min_dist[i] = MAXN;     // 起始时所有节点均不可达
}

int pick_v(){
    // pick 一个未访问的距离集合 S 最近的 节点 v
    int v, md = MAXN;
    for(int i=0; i<ver_n; i++){
        if(!having_visited[i] && min_dist[i] < md){
            md = min_dist[i];
            v = i;
        }
    }
    return v;
}

int prim(){
    having_visited[st_v] = true; // 将起始节点加入访问集合
    min_dist[st_v] = 0;
    for(node nd: graph[st_v]){// 初始化起始节点的邻居
        min_dist[nd.v] = nd.w;
    }
    // 函数返回最小生成树的边权
    int tree_w = 0;
    for(int i=0; i<ver_n-1; i++){   // 剩余 n-1 个节点依次收敛
        int v = pick_v();
        tree_w += min_dist[v];
        having_visited[v] = true;
        // 松弛节点 v 的邻居
        for(node nd: graph[v]){
            if(min_dist[nd.v] > nd.w)
                min_dist[nd.v] = nd.w;
        }
    }
    return tree_w;
}

int main(){
    init_graph();
    cout << prim() << endl;
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