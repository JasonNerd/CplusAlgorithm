/*
As an emergency rescue team leader of a city, you are given a special map of your country.
The map shows several scatered cities connected by some roads. 
Amount of rescue teams in each city and the length of each road between any pair of cities are marked on the map.
When there is anemergency call to you from some other city, your job is to lead your men to the place as quickly aspossible,
and at the mean time, call up as many hands on the way as possible.
输入格式
Each input file contains one test case. For each test case, the first line contains 4 positiveintegers: 
N (<500)-the number of cities (and the cities are numbered from 0 to N-1), 
M--the number of roads, C1 and C2--the cities that you are currently in and that you must save,respectively. 
The next line contains N integers, where the i-th integer is the number of rescue teams in the i-th city
Then M lines follow, each describes a road with three integers cl, c2 and L, 
which are the pair of cities connected by a road and the length of that road, respectively. 
It is guaranteed that there exists at least one path from C1 to C2.
输出格式
For each test case, print in one line two numbers: 
the number of different shortest paths between C1 and C2, and the maximum amount of rescue teams you can possibly gather.
All the numbers in a line must be separated by exactly one space, and there is no extra space allowed at the end of a line.
*/
#include<iostream>
#include<vector>

using namespace std;
const int MAXN = 101;
int city_num, road_num, loc_id, sav_id;     // 顶点数, 边数, 始点, 终点
struct gnode{
    int v,w;    // 出边顶点编号, 出边边权
    gnode(int v, int w){
        this->w = w;
        this->v = v;
    }
};
vector<gnode> graph[MAXN];  // 邻接表
bool having_visited[MAXN];  // 标记是否已访问
int rescue[MAXN], opt_rescue[MAXN], opt_path[MAXN], opt_pnum[MAXN]; // 点权, 最大累积点权, 最短路径长度, 数量

void input_graph();
void init_state();
void slacken();
int select();

void input_graph(){
    cin >> city_num >> road_num >> loc_id >> sav_id;
    for(int i=0; i<city_num; i++)
        cin >> rescue[i];   // 更新点权
    for(int i=0; i<road_num; i++){
        int i_id, o_id, e_w;
        cin >> i_id >> o_id >> e_w;
        graph[i_id].push_back(gnode(o_id, e_w));
    }
}

void init_state(){
    for (int i=0; i<city_num; i++){
        having_visited[i] = false;
        opt_rescue[i] = opt_pnum[i] = 0;
        opt_path[i] = MAXN;
    }
    opt_path[loc_id] = 0;   // 初始时源点最短路为0
    opt_rescue[loc_id] = rescue[loc_id];    // 初始时源点的救援物资均可用
    opt_pnum[loc_id] = 1;
}

void slacken(){
    // 1. 选出一个未被访问 且 距离最短 的节点
    int p = select();
    // 2. 遍历邻居, 查看若经过自己(p), 邻居节点的路径长度是否可以优化
    for(auto nd: graph[p]){
        int acr_p = opt_path[p] + nd.w; // 经过p的路径长
        int acr_pr =  opt_rescue[p] + rescue[nd.v]; // 经过点p累积的救援物资
        if (acr_p < opt_path[nd.v]){    // 邻居节点 nd.v 可以经过 p节点 优化
            opt_path[nd.v] = acr_p;
            opt_rescue[nd.v] = acr_pr; // 更新物资收集情况
            opt_pnum[nd.v] = opt_pnum[p];
        }else if (acr_p == opt_path[nd.v]){ // 若两者路径距离相同
            if (acr_pr > opt_rescue[nd.v]){ // 选择经过 p 可以得到更多物资
                opt_rescue[nd.v] = acr_pr;
                opt_pnum[nd.v] += opt_pnum[p];
            }
        }
    }
    having_visited[p] = true;
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

int main(){
    input_graph();
    init_state();
    // 进行n次松弛
    for (int i=0; i<city_num; i++)
        slacken();
    cout << opt_rescue[sav_id] << " " << opt_pnum[sav_id];
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
// 思路:
在求最短路径时增加一条判断物资的条件, 注意这一条件本身不影响
最短路径的选择, 这里需要设立一个累积物资数组
同时题目还要求最短路径的条数
*/