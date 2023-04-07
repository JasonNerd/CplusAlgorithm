---
title: "图算法（一）图的存储和两种遍历方式"
date: 2023-04-07T10:30:40+08:00
draft: false
tags: ["图", "DFS", "BFS"]
categories: ["学习笔记"]
twemoji: true
lightgallery: true
---
# 图的基本概念与存储遍历方式
图由顶点和边构成，顶点之间由边连接，边有方向时称为有向图，否则为无向图。顶点的连接的边数称为度，在有向图中，从顶点出发的边数为出度，指向该顶点的边数为入度。抽象的看，图可表示为G(V, E), V表示顶点集, E表示边集。
## 图的存储
图可以使用**邻接矩阵**, 适用于节点数较少的情况(例如小于1000)
```C++
const int N = 100;
int graph[N][N];    // graph[i]p[j]表示 连接 从 节点i 出发到 节点j 的边的长度或者权重, 如果不存在就是0
```
或者**邻接表**, 节点较多时也适用, 常使用vector数组实现, 他又被称为
```c++
const int N;
struct Node{
    int v;          // 出边的终点为v
    int w;          // 出边权重为w
    Node(int v, int w){
        this->v = v;
        this->w = w;
    }
}

vector<Node> graph[N];

graph[1].push_back(Node(3, 4)); // 表示从节点1出发到节点3的边权重为4
```
## 图的遍历
深度优先遍历或者广度优先遍历, 分别使用递归(或者栈)和队列进行实现

1. 广度优先遍历--借助队列的邻接矩阵实现
```c++
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int MXN = 100;   // N为最大节点数
int graph[MXN][MXN], n, s;     // n为实际节点数 ( 编号 0 到 n-1 ), s为遍历起始节点
bool having_accessed[MXN];      // 记录各个顶点是否 已加入队列
vector<int> tranverse_seq;
// 使用队列实现广度优先
void bfsTranverse(){
    queue<int> q;
    q.push(s);
    having_accessed[s] = true;
    while (!q.empty()){
        int rt = q.front();
        q.pop();
        tranverse_seq.push_back(rt);
        // 对所有未被访问的邻居进行访问
        for(int i=0; i<n; i++){
            if(graph[rt][i] > 0 && !having_accessed[i]){
                q.push(i);
                having_accessed[i] = true;
            }
        }
    }
}

void init_grah(){
    n = 5;
    graph[0][1] = graph[1][0] = 2;
    graph[0][4] = graph[4][0] = 1;
    graph[1][2] = graph[2][1] = 2;
    graph[1][4] = graph[4][1] = 2;
    graph[2][3] = graph[3][2] = 1;
    graph[3][4] = graph[4][3] = 1;
}

void prt_res(int start){
    s = start;
    init_grah();
    bfsTranverse();
    for(auto i: tranverse_seq){
        cout << i << " ";
    }
    cout << endl;
}

int main(){
    // prt_res(1); // 1 0 2 4 3
    prt_res(0); // 0 1 4 2 3
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
```

2. 深度优先遍历--借助栈的邻接表实现
```c++
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
```


## 基于图的遍历的题目练习
### 题目1. 博客的最大转发数
> PAT A1076 Forwards on Weibo
> 在微博上一个用户(root)可能拥有很多粉丝(follower), 同时也会关注许多用户. 这就构成了一个社交网络. 假设 root 发表了一条微博, 那么他的 follower 就可以看到并转发, 同时也可以继续被 follower 的粉丝继续转发.  现在给出一个社交网络, 你需要计算指定用户的微博可能的最大转发数(每个用户只转发一次), 并且限制 间接粉丝的层级至多为L

```git
输入格式:
N, L    // N是用户数(<=1000), L为间接粉丝最大层数(<=6)
n, f[n] // 接下来的N行, 每行第一个数表示用户粉丝数n, 后面跟着n个数表示 关注的用户id列表
...
...
query_n, query_list // 最后一行是查询列表, 第一个数是要查询的用户数量, 后面跟着用户ID
```
题解:

```c++
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct gnode{
    int id, layer;
    gnode(int id){
        this->id=id;
        this->layer=0;
    }
    gnode(int id, int layer){
        this->id=id;
        this->layer=layer;
    }
};
const int MAX_NUM = 1000;
int user_n, mx_layers;
vector<gnode> usrgraph[MAX_NUM];  // 邻接表
vector<int> queries;            // 待查节点id
bool hav_visited[MAX_NUM];      // 访问标记位数组
// 清空标记位
void clear_access();

void init_graph(){
    cin >> user_n >> mx_layers;
    for(int i=1; i<=user_n; i++){   // id 从 1 开始
        int tmpn, bufi;
        cin >> tmpn;
        for(int j=0; j<tmpn; j++){
            cin >> bufi;
            usrgraph[bufi].push_back(i);    // 表示 i 是 bufi 的粉丝, 
            // 注意这里直接传入了一个整数, 并未出错, 这与构造器有关, 似乎这种行为是合理的
        }
    }
    int tmpqn, bufq;
    cin >> tmpqn;
    for(int i=0; i< tmpqn; i++){
        cin >> bufq;
        queries.push_back(bufq);
    }
}

// 计算以root为中心半径为mx_layers的散播人数num
int bfs_tranverse(int root){
    int res = 0;    // 不包含root本身
    queue<gnode> workQ;
    workQ.push(root);
    hav_visited[root] = true;
    while (!workQ.empty()){
        gnode r = workQ.front();
        if(r.layer >= mx_layers)
            break;
        workQ.pop();
        for(auto n: usrgraph[r.id]){
            if(!hav_visited[n.id]){
                workQ.push(gnode(n.id, r.layer+1));
                res++;
                hav_visited[n.id] = true;
            }
        }
    }
    return res;
}


void clear_access(){
    for(int i=1; i<=user_n; i++)
        hav_visited[i] = false;     // 清空访问标志位
}

void prt_info(){
    for(int i=1; i<=user_n; i++){
        cout << i << " - ";
        for(auto fs: usrgraph[i]){
            cout << "(" << fs.id << "," << fs.layer << ")";
        }
        cout << endl;
    }
}

int main(){
    init_graph();
    for(int q: queries){
        clear_access();
        cout << bfs_tranverse(q) << endl;
    }
    return 0;
}
/*
输入样例
7 3
3 2 3 4
0
2 5 6
2 3 1
2 3 4
1 4
1 5
2 2 6
输出样例
4
5
*/
```

### 题目2. 犯罪团伙头目
> PAT A1034 Head of Gang
> 警方寻找一个犯罪团伙(gang)的头目(head)的一个方法是检查他们的通话时长。假设A和B之间有通话, 则称A和B具有联系(边), 边权被定义为双方通话总时长, gang被定义为一个相互之间具有联系的多于2人的团伙, 且该团伙的纵通话时长超过 阈值K. 同时在每一个 gang 中, 权重最大的节点即为 头目head. 现在要求找到所有的gang及其head

```git
输入格式
N K // N, K <= 1000, N表示通话记录数, K表示阈值
(A, B, t)   // 一共N行, A和B表示成员名, t是两者通话时长
// 注意成员名由三个大写的字母构成
输出:
m       // m为犯罪团伙数量, 以下接上m行
A ka    // (头目名, 所在团伙成员数)
B kb
...
// 输出顺序为团伙头目名的升序
```
题解:

```c++
#include<iostream>
#include<map>
#include<string>
#include<vector>
using namespace std;
struct gnode{
    string v;   // 出边终点顶点id
    int w;      // 出边边权
    gnode(string v, int w){
        this->v = v;
        this->w = w;
    }
};
const int MAX_REC = 1000;       // 最大值
int num_records, k_threshold;   // 通话记录数, 总边权阈值, 均不大于1000
map<string, vector<gnode>> graph;   // 邻接表
vector<string> nids, brids;        // 所有的节点编号, 某一分量的所有节点编号
map<string, bool> hav_visted;   // 标记节点是否已被划分到某个团伙中
map<string, int> pweights; // 顶点编号, 点权
void info();    // 测试函数
// 1. 输入数据, 构造邻接表
// 2. 累计顶点权值
// 3. 记录节点id
// 4. 标记所有节点为未访问
void input_init(){
    cin >> num_records >> k_threshold;
    string nm1, nm2;
    int tlen;
    for(int i=0; i<num_records; i++){
        cin >> nm1 >> nm2 >> tlen;
        graph[nm1].push_back(gnode(nm2, tlen));
        pweights[nm1] += tlen;  // 输入时即可记录各点点权
        pweights[nm2] += tlen;
    }
    // 将节点 id 单独构成 vector
    for(auto pw: pweights){
        nids.push_back(pw.first);
        hav_visted[pw.first] = false;
    }
}
// 找出 nid 所在的连通分量的所有节点id(包括nid)
void dfs_tranverse(string nid){
    hav_visted[nid] = true;
    brids.push_back(nid);
    for(auto ov: graph[nid]){
        if(!hav_visted[ov.v]){  // 出边顶点未访问
            dfs_tranverse(ov.v);
        }
    }
}
// brach包含了一个连通分量(团伙)所有的成员id
string getGang(vector<string> branch){
    string gang = branch[0];
    int mxg = pweights[gang];
    for(auto s: branch){
        if(pweights[s]>=mxg){
            gang = s;
            mxg = pweights[s];
        }
    }
    return gang;
}
// 判断团伙总通话时长是否超过阈值
bool ifExcessK(vector<string> branch){
    int k = 0;
    for(auto b: branch){
        k += pweights[b];
    }
    return k > 2*k_threshold;
}

int main(){
    // 初始化
    input_init();
    // 遍历所有节点, 找到所有团伙
    vector<gnode> branch;   // 记录已确认是gang的团伙信息, 包括 头目名称v 和 团伙大小w
    for(auto p: nids){
        if(!hav_visted[p]){ // 节点p未访问, 说明有一个新的连通分量
            brids.clear();      // 先清空已有连通分量节点序列
            dfs_tranverse(p);   // 遍历p所在的连通分量, 并把途经节点加入到 brids
            // 判断 brids 符不符合 gang 的要求
            if(brids.size() > 2 && ifExcessK(brids)){
                string g = getGang(brids);
                branch.push_back(gnode(g, brids.size()));
            }
        }
    }
    // 打印得到团伙信息
    int info = branch.size();
    cout << info << endl;
    for(int i=0; i<info; i++){
        cout << branch[i].v << " " << branch[i].w;
        if( i<info-1 )
            cout << endl;
    }
    return 0;
}

void info(){
    cout << endl;
    for(auto i: graph){
        cout << i.first << "-> ";
        for(auto j: i.second){
            cout << "(" <<j.v << ", "<<j.w<<") ";
        }
        cout << endl;
    }
    cout << endl;
    for(auto v: pweights)
        cout << v.first << ": " << v.second << endl;
    cout << endl;
}
/*
样例1
输入:
8 59
AAA BBB 10
BBB AAA 20
AAA CCC 40
DDD EEE 5
EEE DDD 70
FFF GGG 30
GGG HHH 20
HHH FFF 10
输出:
2
AAA 3
GGG 3
样例2
输入: 
8 70
AAA BBB 10
BBB AAA 20
AAA CCC 40
DDD EEE 5
EEE DDD 70
FFF GGG 30
GGG HHH 20
HHH FFF 10
输出:
0
*/
```
