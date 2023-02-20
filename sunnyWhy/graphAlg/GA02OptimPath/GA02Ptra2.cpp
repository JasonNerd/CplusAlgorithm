/*
input
4 5 0 3
0 1 1 20
1 3 2 30
0 3 4 10
0 2 2 20
2 3 1 20
output
0 2 3 3 40
题意
有N个城市(编号为0~N-1)、M 条道路(无向边)，并给出 M条道路的距离属性与花费属性。
现在给定起点 S 与终点 D，求从起点到终点的最短路径、最短距离及花费。
注意:如果有多条最短路径，则选择花费最小的那条。
*/
#include <iostream>
#include <vector>
using namespace std;
struct gnode{
    int v, w;
    gnode(int v, int w){
        this->v = v;
        this->w = w;
    }
};
void input_graph();
void init_state();
int select();
void slacken();
bool ok_to_opt();
void find_path(int p);

const int MAXN = 101;
int city_num, road_num, loc_id, sav_id;     // 顶点数, 边数, 始点, 终点
vector<gnode> graph[MAXN], mcost[MAXN];     // 邻接表, 花费表
bool having_visited[MAXN];  // 标记是否已访问
int opt_plen[MAXN];   // 最优路径长度数组

int opt_cost = MAXN*MAXN;               // 最小花费
vector<int> opt_path[MAXN];     // 前驱节点数组
vector<int> tmp_res, opt_res;   // 临时最短路, 最优最短路

void input_graph(){
    cin >> city_num >> road_num >> loc_id >> sav_id;
    for(int i=0; i<road_num; i++){
        int i_id, o_id, e_w, e_c;
        cin >> i_id >> o_id >> e_w >> e_c;
        graph[i_id].push_back(gnode(o_id, e_w));
        graph[o_id].push_back(gnode(i_id, e_w));
        mcost[i_id].push_back(gnode(o_id, e_c));
    }
}

void init_state(){
    for (int i=0; i<city_num; i++){
        having_visited[i] = false;
        opt_plen[i] = MAXN;
    }
    opt_plen[loc_id] = 0;   // 初始时源点最短路为0
}

int select(){
    int min_id=-1, min_pt = MAXN;
    for (int i=0; i<city_num; i++){
        if (!having_visited[i] && opt_plen[i]<min_pt){
            min_id = i;
            min_pt = opt_plen[i];
        }
    }
    return min_id;
}

void slacken(){
    int p = select();
    for(auto nd: graph[p]){
        int curp = opt_plen[p] + nd.w;
        if(curp < opt_plen[nd.v]){
            opt_plen[nd.v] = curp;
            opt_path[nd.v].clear();
            opt_path[nd.v].push_back(p);
        }else if(curp == opt_plen[nd.v]){
            opt_path[nd.v].push_back(p);
        }
    }
    having_visited[p] = true;
}

// dfs获取最短路径
void find_path(int p){
    if (opt_path[p].empty()){
        // 形成了完整路径
        tmp_res.push_back(p);
        if(ok_to_opt()){
            opt_res = tmp_res;  // 更新最优路径
        }
        tmp_res.pop_back();
        return ;
    }
    tmp_res.push_back(p);
    for(auto prv: opt_path[p])
        find_path(prv);
    tmp_res.pop_back();
}

bool ok_to_opt(){
    int ccst = 0;   // 计算 tmp_res 的路径长
    for(int i=tmp_res.size()-1; i>0; i--){
        for (auto nd: mcost[tmp_res[i]]){
            if (nd.v == tmp_res[i-1])
                ccst += nd.w;
        }
    }
    if (ccst < opt_cost){
        opt_cost = ccst;
        return true;
    }
    return false;
}

int main(){
    input_graph();
    init_state();
    for(int i=0; i<city_num; i++)
        slacken();
    // for (int i=0; i<city_num; i++)
    //     cout << opt_plen[i] << " ";
    find_path(sav_id);
    for(int i=opt_res.size()-1; i>=0; i--)
        cout << opt_res[i] << " ";
    cout << opt_plen[sav_id] << " " << opt_cost;
    return 0;
}
/*

for (int i=0; i<city_num; i++){
        cout << i << " - ";
        for(auto j: opt_path[i])
            cout << j << " ";
        cout << endl;
    }

0 - 
1 - 0
2 - 0
3 - 1 2

*/
