/*
使用 SPFA 算法解决 急救物资问题，跟随动态更新更易实现
尝试是否可以先找到全部路径
输出路径数, 急救物资最大数
*/

#include <vector>
#include <set>
#include <iostream>
#include <queue>
using namespace std;
struct gnode{
   int v, dis;  // 出边顶点
   gnode(int v, int dis){
    this->v = v;
    this->dis = dis;
   }
};
const int MAXN = 101;
int ver_n, edg_n, st_p, ed_p;   // 点数、边数、始点、终点
vector<gnode> graph[MAXN];  // 邻接表
int ver_weights[MAXN], opt_plen[MAXN];  // 点权, 最短路径长
bool inq[MAXN];     // 是否在队列中
int res_pn=0, res_mxpw=0;   // 最短路径数、最大累积点权
set<int> prev_nodes[MAXN];  // 前驱节点表
vector<int> tmp_path, opt_path;

void input_graph(){
    cin >> ver_n >> edg_n >> st_p >> ed_p;
    for(int i=0; i<ver_n; i++)
        cin >> ver_weights[i];
    for(int i=0; i<edg_n; i++){
        int f, t, w;
        cin >> f >> t >> w;
        graph[f].push_back(gnode(t, w));
        graph[t].push_back(gnode(f, w));
    }
    for(int i=0; i<ver_n; i++){
        opt_plen[i] = MAXN;
        inq[i] = false;
    }
    opt_plen[st_p] = 0;
}

void spfa(){
    queue<int> workQ;
    workQ.push(st_p);
    inq[st_p] = true;
    while (!workQ.empty()){
        int rid = workQ.front();
        inq[rid] = false;
        workQ.pop();
        for(auto nd: graph[rid]){
            int rm = opt_plen[rid] + nd.dis;
            if (rm < opt_plen[nd.v]){
                opt_plen[nd.v] = rm;
                if (!inq[nd.v]){    // 不在队列才入队
                    workQ.push(nd.v);
                    inq[nd.v] = true;
                }
                prev_nodes[nd.v].clear();
                prev_nodes[nd.v].insert(rid);   // 更新前驱
            }else if(rm == opt_plen[nd.v]){
                if (!inq[nd.v]){    // 不在队列才入队
                    workQ.push(nd.v);
                    inq[nd.v] = true;
                }
                prev_nodes[nd.v].insert(rid);
            }
        }
    }
}

void find_path(int rid){
    if(rid == st_p){
        tmp_path.push_back(rid);
        res_pn++;
        // 计算救援物资
        int pws = 0;
        for(int i: tmp_path)
            pws += ver_weights[i];
        if (pws > res_mxpw){
            res_mxpw = pws;
            opt_path = tmp_path;
        }
        tmp_path.pop_back();
    }
    tmp_path.push_back(rid);
    for(int i: prev_nodes[rid])
        find_path(i);
    tmp_path.pop_back();
}

int main(){
    input_graph();
    spfa();
    find_path(ed_p);
    for(auto i: opt_path)
        cout << i << " ";
    cout << endl;
    cout << res_pn << " " << res_mxpw;
    return 0;
}

/*
5 9 0 3
1 3 5 4 7
0 1 3
0 2 1
0 4 4
1 2 2
1 4 1
1 3 2
2 3 4
2 4 3
3 4 1

3 4 1 2 0
7 20
*/