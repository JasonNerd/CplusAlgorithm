---
title: "图算法（二）最短路径算法"
date: 2023-04-07T11:04:03+08:00
draft: false
tags: ["图", "最短路径"]
categories: ["学习笔记"]
twemoji: true
lightgallery: true
---
最短路径是图论中一个很经典的问题:**给定图 G(VE)，求一条从起点到终点的路径，使得这条路径上经过的所有边的边权之和最小**。对任意给出的图G(VE)和起点S终点T，如何求从S到T的最短路径. 解决最短路径问题的常用算法有**Diikstra算法, Bellman-Ford算法, SPFA算法, Floyd算法**。
## Diikstra算法
* 使用场景: 解决单源路径最短问题, 给定图G和起点s, 通过算法得到s到其他任一顶点的最短距离

* **基本思想**: 设置一个已访问的节点集合S, 从顶点集V中取出初始顶点s加入S, 从V中选择一个距离s最近的顶点u加入S, 以u为中介松弛初始顶点与其他顶点的距离, 这样的松弛操作执行到V为空.

* 有效性分析: 每次都选与源点最近的节点, 也即在对于s到中介点u的路径已经最优(否则可以重新选择使其最优), 在此基础上, 松弛所有未访问的邻居节点, 选择其中一个节点k, 条件是距离s最短, 这样最优路径就扩张了一个节点, 这样的扩张一直到包含所有的节点.

* 复杂度分析: 空间复杂度O(V+E), V为节点数, E为边数(能使用邻接表就使用邻接表), 同时还有个bool having_access[N]以及mincost[N]以及prevnid[N]。从复杂度来看，主要是外层循环 O(V)与内层循环 (寻找最小的 d]需要 O(V)、举v需要 O(adj[u].size))产生的。又由于对整个程序来说，枚举v的次数总共为 O(adj[u]size)=O(E)，因此总复杂度为 O(V+ E)。可以注意到，上面的做法都是复杂度 O(V)级别的，其中由于必须把每个顶点都标记为已访问，因此外层循环的 O(V)时间是无法避免的，但是寻找最小 d[u]的过程却可以不必达到O(V)的复杂度，而可以使用堆优化来降低复杂度。最简洁的写法是直接使用 STL 中的优先队列priority_queue，这样使用邻接表实现的 Dikstra算法的时间复杂度可以降为0(VlogV+E)此外，Dijkstra 算法只能应对所有边权都是非负数的情况，如果边权出现负数，那么 Dijkstra算法很可能会出错，这时最好使用SPFA算法。

> Dijkstra 算法题解: 单源路径最短-记录path版
```c++
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

```

* 出题策略:于是，碰到这种**有两条及以上可以达到最短距离的路径**，题目就会给出一个第二标尺(第一标尺是距离)，要求在所有选择第二标尺最优的一条路径。而第二标尺常见的是以下三种出题方法或其组合:
(1) 给每条边**再增加一个边权**(比如说花费)，然后要求在最短路径有多条时要求路径上的花费之和最小(如果边权是其他含义，也可以是最大)。
(2) **给每个点增加一个点权**(例如每个城市能收集到的物资)，然后在最短路径有多条时要求路径上的点权之和最大(如果点权是其他含义的话也可以是最小)。
(3) **直接问有多少条最短路径**
对这三种出题方法，都只需要增加一个数组 **opt_sel[]** 来存放新增的边权或点权或最短路径条数，然后在 Dikstra算法中修改优化opt_sel[]的那个步即可，其他部分不需要改动。

注意, 对于最短路径下一节点的选择, 这是不必改变的, 在更新下一节点同时更新新增的数组即可, 需要考虑的是在`(opt_path[j] == opt_path[p] + graph[p][j])`注意更新新增数组, 例如对于第二边权(花费), 若经过节点p使得花费更小, 那么就更新第二边权(累积数组).
### 例题展示
#### 尽快的收集更多医疗物资
1. 题目说明
```git
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
```
2. 题解(使用 Dijkstra 算法进行求解)
题目大意是有一些个城市, 它们保留有一些个医疗物资, 并且城市之间有一些个路线相联。现在你要在两地之间收集尽可能多的物资，前提是要最快，也就是必须最短路径，而在有多条最短路的时候就选择那个收集到更多物资的那一条。
```c++
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
```
#### 尽可能减少耗材消耗
1. 题目说明
```git
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
```
在已是最短路的情况下求最小花费的。
2. 题解:
```c++
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
```


### 最短路径的最优子结构
通过对dijkstra算法及以上3个变种思想方法的学习, 可以发现, 他们都满足最优子结构, 也即, 如果当前节点最优, 那么路径上的每一个节点也都是最优, 换句话说, 在当前节点最优时, 对于当前节点的所有邻居节点, 一句题意就可以直接选出下一个最优节点, 此时相对于下一个最优节点, 当前节点就是他路径上的节点, 并且是最优的，简单说来, 以上三种情况都存在和、累计的概念。当面对更复杂的、不满足最优子结构的问题时, 就需要一种更通用的方法求解。

思想很简单, 就是试图使用一种方法, 寻找并保存所有的最短路径, 保存之后什么问题就都没问题了，这种方法就是 **Dijkstra+DFS** 。将前面的前驱节点数组扩展到可包含多前驱的情况: `vector<int> pre[MAXN]`. 此时, dijkstra 专心寻找最短路径, 当接入节点p可以使路径更优, 则清空原前驱vector并加入p(这是由于p相对于原来所有的前驱都更优), 而如果与已有最优情况相同时, 那就加入他们(你们都是我的翅膀). 这样以后, dfs负责遍历pre数组, 递归每一条最短路径, 依据第二标尺更新最优值.

## Bellman-Ford算法
Dijkstra算法可以很好地解决无负权图的最短路径问题，但如果出现了**负权边，Dijkstra 算法就会失效**，例如图10-39中设置A为源点时，首先会将点B和点C的dist值变为-1和1，接着由于点B的dist 值最小，因此用点 B去更新其未访问的邻接点(虽然并没有)。在这之后点B标记为已访问，于是将无法被从点C出发的边CB更新，因此最后distB]就是-1，但显然A到B的最短路径长度应当是A一C-B的-4。
![](./image/2023-02-24-22-13-18.png)
现在考虑环，也就是从某个顶点出发、经过若干个不同的顶点之后可以回到该顶点的情况。而根据环中边的边权之和的正负，可以将环分为零环、正环、负环。显然，图中的零环和正环不会影响最短路径的求解，因为零环和正环的存在不能使最短路径更短:而**如果图中有负环，且从源点可以到达，那么就会影响最短路径的求解**:但如果图中的负环无法从源点出发到达，则最短路径的求解不会受到影响。

如下即为BF算法的伪码, 进行n-1轮松弛, 每一轮松弛所有边:
![](./image/2023-02-24-22-20-28.png)
此时，如果图中没有从源点可达的负环，那么数组d中的所有值都应当已经达到最优。因此只需要再对所有边进行一轮操作，**判断是否有某条边(u,v)仍然满足`d[u]+W(u,v)<d[v]`**，如果有，则说明图中有从源点可达的负环，返回false; 否则说明数组d中的所有值都已经达到最优，返回true。

题解:
```c++
/*
BF算法的伪码, 进行n-1轮松弛, 每一轮松弛所有边, 此时，
如果图中没有从源点可达的负环，那么数组d中的所有值都应当已经达到最优。
因此只需要再对所有边进行一轮操作，判断是否有某条边(u,v)仍然满足
d[u]+W(u,v)<d[v]，如果有，则说明图中有从源点可达的负环，返回false; 
否则说明数组d中的所有值都已经达到最优，返回true。
*/

#include <iostream>
#include <vector>
#include <set>
using namespace std;

struct gnode{
    int v, w;
    gnode(int v, int w){
        this->v = v;
        this->w = w;
    }
};

const int MAXN = 101;
int city_num, road_num, loc_id, sav_id;     // 顶点数, 边数, 始点, 终点
vector<gnode> graph[MAXN];
int rescue[MAXN], opt_path[MAXN];   // 点权数组, 最优路径长度数组
set<int> prevn[MAXN];     // 前驱节点数组
int pnum=0, mxres=0; // 最短路径数, 最大物资数
vector<int> tmp_res, opt_res;   // 临时最短路, 最优最短路

void input_graph();
void bell_man_ford();
void find_path(int rid);

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
    for (int i=0; i<city_num; i++){
        opt_path[i] = MAXN;
    }
    opt_path[loc_id] = 0;   // 初始时源点最短路为0
}

void bell_man_ford(){
    for (int i=0; i<city_num-1; i++){
        // 一共 n-1 轮, 每轮遍历所有边
        for (int j=0; j<city_num; j++){
            // 以 j 为中介, 对所有邻边进行松弛
            for (auto nd: graph[j]){
                if(opt_path[j]+nd.w < opt_path[nd.v]){
                    opt_path[nd.v] = opt_path[j]+nd.w;
                    prevn[nd.v].clear();
                    prevn[nd.v].insert(j);
                }else if (opt_path[j]+nd.w == opt_path[nd.v]){
                    // 注意这里可能重复加入
                    prevn[nd.v].insert(j);
                }
            }
        }
    }
}

void find_path(int rid){
    if (rid == loc_id){
        tmp_res.push_back(rid);
        // 遍历 tmp_res, 计算结果
        pnum++;
        int ts = 0;
        for(auto nd: tmp_res){
            ts += rescue[nd];
        }
        if (ts > mxres){
            mxres = ts;
            opt_res = tmp_res;
        }
        tmp_res.pop_back();
        return ;
    }
    tmp_res.push_back(rid);
    for(auto nd: prevn[rid])
        find_path(nd);
    tmp_res.pop_back();
}

int main(){
    input_graph();
    bell_man_ford();
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

```


### BF算法正确性证明
那么，为什么Bellman-Ford 算法是正确的呢?想要了解完整数学证明的读者可以参考算法导论，下面给出一个简洁直观的证明。
首先，如果最短路径存在，那么最短路径上的顶点个数肯定不会超过V个(想一想为什么?)。于是，**如果把源点s作为一棵树的根结点，把其他结点按照最短路径的结点顺序连接就会生成一棵最短路径树**。显然，在最短路径树中，从源点S 到达其余各顶点的路径就是原图中对应的最短路径，且**图和源点一旦确定，最短路径树也就确定了**。另外，由于最短路径上的顶点个数不超过V个，因此最短路径树的层数一定不超过V。由于初始状态下d[s]为0，因此在接下来的步骤中 d[s]不会被改变(也就是说，最短路径树中第一层结点的d值被确定)。接着通过 Bellman-Ford算法的第一轮操作之后，最短路径树中的第二层顶点的d值也会被确定下来;然后进行第二轮操作，于是第三层顶点的d 值也被确定下来。这样计算直到最后一层顶点的d值确定。**由于最短路径树的层数不超过V层因此Bellman-Ford算法的松驰操作不会超过V-1轮**。证毕。请读者使用Bellman-Ford算法重新对[PATA1003]题进行编码，以熟悉Bellman-Ford算法及体会上面给出的思路。

## SPFA算法
虽然Bellman-Ford算法的思路很简洁，但是O(VE)的时间复杂度确实很高，在很多情况下并不尽如人意。仔细思考后会发现，Bellman-Ford 算法的每轮操作都需要操作所有边，显然这其中会有大量无意义的操作，严重影响了算法的性能。于是注意到，只有当某个顶点 u的`d[u]`值改变时，从它出发的边的邻接点V的 `d[v]`值才有可能被改变。由此可以进行一个优化:**建立一个队列**，每次将队首顶点u 取出，然后对从u出发的所有边uv 进行松弛操作,也就是判断 `d[u] +length[u->v]<d[v]`是否成立，如果成立，则用`d[u]+length[u->v]`覆盖`d[v]`,于是 `d[v]`获得更优的值，此时**如果不在队列中**，就把加入队列。**这样操作直到队列为空说明图中没有从源点可达的负环)，或是某个顶点的入队次数超过V-1(说明图中存在从源点可达的负环)。**
![](./image/2023-02-25-17-08-31.png)
这种优化后的算法被称为SPFA(Shortest Path Faster Algorithm)，**它的期望时间复杂度是O(kE)，其中E是图的边数，k 是一个常数，在很多情况下k 不超过 2，可见这个算法在大部分数据时异常高效，并且经常性地优于堆优化的 Diikstra 算法。** 但如果图中有从源点可达的负环，传统 SPFA的时间复杂度就会退化成 O(VE)。

SPFA 十分灵活，其内部的写法可以根据具体场景的不同进行调整。例如上面代码中的FIFO队列可以替换成优先队列(priority_queue)，以加快速度;或者替换成双端队列(deque),使用SLF 优化和 LLL 优化，以使效率提高至少50%。**除此之外，上面给出的代码是 SPFA的BFS 版本，如果将队列替换成栈，则可以实现 DFS 版本的 SPFA，对判环有奇效**对这些内容有兴趣的读者可以去查找资料学习。
最后，请读者使用SPFA算法完成10.4.1节中的几个例题(也就是 Dkstra算法中的例题)以熟练使用SPFA算法。

题解:
```c++
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

```
#### 使用 SPFA 算法解决 急救物资问题
```c++
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

```
## Floyd算法

解决全源最短路径问题

```c++
// @FileName:     GA02C04Floyd.cpp
// @CreateTime:   2023/03/27 19:36:05
// @Author:       Rainbow River

/*
Floyd算法(读者可以将其读作“弗洛伊德算法”用来解决全源最短路问题，即对给定的图G(VE)，求任意两点uv之间的最短路径长度，时间复杂度是 0(n^3)。
由于的复杂度决定了顶点数n的限制约在200以内，因此使用邻接矩阵来实现Flyd 算法是非常合适且方便的。
Floyd算法基于这样一个事实:如果存在顶点k，使得以k作为中介点时顶点i和顶点i的当前最短距离缩短，则使用顶点k作为顶点i和顶点i的中介点，
即当dis[i][k] + dis[k][j] < dis[i]li]时，令dis[i][j]= dis[i][k] + dis[k][j](其中 dis[i][j]表示从顶点i到顶点i的最短距离)。
如图10-42所示，V1 到 V4 的距离为3，而以V2为中介点时可以使V1到V4的距离缩短为2，那么就把V1到V4的距离从3优化为2,
即当dis[1][2]+dis[2][4]<dis[1][4]时，令dis[1][4]= dis[1][2] + dis[2][4]。
基于上面的事实，Floyd算法的流程如下:
枚举顶点 k in [1，n]
    以顶点k作为中介点，枚举所有顶点对i和j(i in [1，n]，j in [1，n])
        如果dis[il[k] +dis[k][j] < dis[il[j]成立
            赋值dis[i][i] = dis[i][k] +dis[k][j]
*/

#include<iostream>
using namespace std;
const int MAXN = 100;
int dis[MAXN][MAXN];
int ver_n, adj_n;

void init_graph(){
    cin >> ver_n >> adj_n;
    int ti, tj, tv;
    for(int i=0; i<ver_n; i++){
        for(int j=0; j<ver_n; j++){
            dis[i][j] = MAXN;
        }
    }
    for(int i=0; i<adj_n; i++){
        cin >> ti >> tj >> tv;
        dis[ti][tj] = dis[tj][ti] = tv;
    }
    for(int i=0; i<ver_n; i++) dis[i][i] = 0;
}

void plot(int a[MAXN][MAXN]){
    for(int i=0; i<ver_n; i++){
        for(int j=0; j<ver_n; j++){
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

void floyd(){
    for(int k=0; k<ver_n; k++){
        for(int i=0; i<ver_n; i++){
            for(int j=0; j<ver_n; j++){
                int m = dis[i][k]+dis[k][j];
                if(m < dis[i][j])
                    dis[i][j] = m;
            }
        }
        // cout << "k = " << k << endl;
        // plot(dis);
        // cout << endl;
        // cout << endl;
    }
}

int main(){
    init_graph();
    cout << endl;
    floyd();
    plot(dis);
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
```

