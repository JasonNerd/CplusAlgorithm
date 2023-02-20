/*
题目描述
A traveler's map gives the distances between cities along the highways, together with the cost of each highway.
Now you are supposed to write a program to help a traveler to decide the shortest path between his/her /
starting city and the destination. If such a shortest path is not unique, you aresupposed to output the one /
with the minimum cost, which is guaranteed to be unique.
输入格式
Each input file contains one test case. Each case starts with a line containing 4 positive integers N,M, S, and D, 
where N (<500) is the number of cities (and hence the cities are numbered from 0to N-1); 
M is the number of highways; S and D are the starting and the destination cities.respectively. 
Then M lines follow, each provides the information of a highway, in the format:
City1 City2 Distance Cost
where the numbers are all integers no more than 500, and are separated by a space.
输出格式
For each test case, print in one line the cities along the shortest path from the starting point tothe destination,
followed by the total distance and the total cost of the path. T
he numbers must be separated by a space and there must be no extra space at the end of output.
*/
#include <iostream>
#include <vector>

using namespace std;
struct gnode{
    int v, dis, cst;    // dis距离, cos花费
    gnode(int v, int dis, int cst){
        this->dis = dis;
        this->cst = cst;
        this->v = v;
    }
};
const int MAXN = 101;
vector<gnode> graph[MAXN];  // 邻接表
int city_num, road_num, loc_id, dest_id;    // 点数, 边数, 所在城市编号, 目的城市编号
bool having_visted[MAXN];   // 记录是否收敛
int opt_prev[MAXN], opt_path[MAXN], opt_cost[MAXN]; // 前向顶点, 最短路径长度, 最小花费
vector<int> resp;   // 存放最短路径

void input_graph();     // 输入图信息
void init_state();      // 状态初始化
int select();           // 选点
void slacken();         // 松弛
void get_path(int p);   // 获取路径

void input_graph(){
    cin >> city_num >> road_num >> loc_id >> dest_id;
    int ft, tf, dis, cst; // 注意是无向边
    for(int i=0; i<road_num; i++){
        cin >> ft >> tf >> dis >> cst;
        graph[ft].push_back(gnode(tf, dis, cst));
        graph[tf].push_back(gnode(ft, dis, cst));
    }
}

void init_state(){
    for (int i=0; i<city_num; i++){
        opt_path[i] = MAXN;
        opt_cost[i] = MAXN;
        opt_prev[i] = -1;
        having_visted[i] = false;
    }
    opt_cost[loc_id] = opt_path[loc_id] = 0;
}

void slacken(){
    // 1. 寻找未访问的最近节点
    int p = select();
    // 2. 遍历邻居
    for (auto nd: graph[p]){
        int acr_dis = opt_path[p] + nd.dis; // 经过p得到的路径长
        int acr_cst = opt_cost[p] + nd.cst; // 经过p得到的花费
        if (acr_dis < opt_path[nd.v]){  // 进行一个松弛
            opt_cost[nd.v] = acr_cst;
            opt_path[nd.v] = acr_dis;
            opt_prev[nd.v] = p;
        }else if (acr_dis == opt_path[nd.v]){   // 依据花费更新
            if(acr_cst < opt_cost[nd.v]){   // 经过p可以得到更小的花费
                opt_cost[nd.v] = acr_cst;   // 更新花费
                opt_prev[nd.v] = p;         // 更新路径
            }
        }
    }
    having_visted[p] = true;    // 标记为已处理
}

int select(){
    int mid=-1, mw=MAXN;
    for(int i=0; i<city_num; i++){
        if(!having_visted[i] && (opt_path[i] < mw)){
            mid = i;
            mw = opt_path[i];
        }
    }
    return mid;
}

void get_path(int p){
    if(p == -1)
        return ;
    get_path(opt_prev[p]);
    resp.push_back(p);
}

int main(){
    input_graph();
    init_state();
    for(int i=0; i<city_num; i++)
        slacken();
    get_path(dest_id);
     for(auto nd: resp)
        cout << nd << " ";
    cout << opt_path[dest_id] << " " << opt_cost[dest_id];
    return 0;
}

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
