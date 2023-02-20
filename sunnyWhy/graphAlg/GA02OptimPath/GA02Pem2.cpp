/*
使用dijkstra+dfs范式进行编程, 问题同救援物资
输入: 点数、边数、始点、终点
点权序列
边权序列
*/
#include <vector>
#include <iostream>
using namespace std;
struct gnode{
    int w, v;
    gnode(int v, int w){
        this->w = w;
        this->v = v;
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
vector<gnode> graph[MAXN];
bool having_visited[MAXN];  // 标记是否已访问
int rescue[MAXN], opt_path[MAXN];   // 点权数组, 最优路径长度数组
vector<int> prevn[MAXN];     // 前驱节点数组
int pnum=0, mxres=0; // 最短路径数, 最大物资数
vector<int> tmp_res, opt_res;   // 临时最短路, 最优最短路

void input_graph(){
    cin >> city_num >> road_num >> loc_id >> sav_id;
    for(int i=0; i<city_num; i++)
        cin >> rescue[i];   // 更新点权
    for(int i=0; i<road_num; i++){
        int i_id, o_id, e_w;
        cin >> i_id >> o_id >> e_w;
        graph[i_id].push_back(gnode(o_id, e_w));
        graph[o_id].push_back(gnode(i_id, e_w));
    }
}

void init_state(){
    for (int i=0; i<city_num; i++){
        having_visited[i] = false;
        opt_path[i] = MAXN;
    }
    opt_path[loc_id] = 0;   // 初始时源点最短路为0
}

int select(){
    int min_id=-1, min_pt = MAXN;
    for (int i=0; i<city_num; i++){
        if (!having_visited[i] && opt_path[i]<min_pt){
            min_id = i;
            min_pt = opt_path[i];
        }
    }
    return min_id;
}

void slacken(){
    int p = select();
    for(auto nd: graph[p]){
        int curp = opt_path[p] + nd.w;
        if(curp < opt_path[nd.v]){
            opt_path[nd.v] = curp;
            prevn[nd.v].clear();
            prevn[nd.v].push_back(p);
        }else if(curp == opt_path[nd.v]){
            prevn[nd.v].push_back(p);
        }
    }
    having_visited[p] = true;
}

// dfs获取最短路径
void find_path(int p){
    if (prevn[p].empty()){
        // 形成了完整路径
        pnum++;
        tmp_res.push_back(p);
        if(ok_to_opt()){
            opt_res = tmp_res;  // 更新最优路径
        }
        tmp_res.pop_back();
        return ;
    }
    tmp_res.push_back(p);
    for(auto prv: prevn[p])
        find_path(prv);
    tmp_res.pop_back();
}

bool ok_to_opt(){
    int rc = 0;
    for(auto i: tmp_res)
        rc += rescue[i];
    if (rc > mxres){
        mxres = rc;    // 更新第二标尺值
        return true;
    }
    return false;
}

int main(){
    input_graph();
    init_state();
    for(int i=0; i<city_num; i++)
        slacken();
    find_path(sav_id);
    cout << pnum << " " << mxres;
    return 0;
}

/*
input example:
5 6 0 2
1 2 1 5 3
0 1 1
0 2 2
0 3 1
1 2 1
2 4 1
3 4 1
output example:
2 4
*/
/*
0 - ()
1 - (0 )
2 - (0 1 )
3 - (0 )
4 - (3 )
*/