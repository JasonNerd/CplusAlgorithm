// @FileName:     criticalpath.cpp
// @CreateTime:   2023/03/28 16:24:44
// @Author:       Rainbow River

#include<iostream>
#include<iostream>
#include<queue>
#include<stack>

using namespace std;
struct node{
    int v, w;
    node(int v, int w){
        this->v = v;
        this->w = w;
    }
};
const int MAXN = 101;   // 各种意义的上限, 例如边权、顶点数、边数都不超过该值
vector<node> graph[MAXN];   // 邻接表
int ver_n, adj_n;   // 顶点数, 边数
int e[MAXN], l[MAXN], ve[MAXN], vl[MAXN], indeg[MAXN];
stack<int> topo_seq;

void fill(int a[], int n, int val);
void init_graph();
bool topo();
void fill_vl(int vle);
void critical_path();

void fill(int a[], int n, int val){
    for(int i=0; i<n; i++)
        a[i] = val;
}

void init_graph(){
    cin >> ver_n >> adj_n;
    for(int i=0; i<adj_n; i++){
        int v1, v2, w;
        cin >> v1 >> v2 >> w;
        graph[v1].push_back(node(v2, w));
        indeg[v2]++;
    }
}

bool topo(){
    queue<int> wrkq;
    for(int i=0; i<ver_n; i++)
        if(indeg[i] == 0)
            wrkq.push(i);
    while (!wrkq.empty()){
        int rt = wrkq.front();
        for(node nd: graph[rt]){
            if(ve[nd.v] < ve[rt]+nd.w)
                ve[nd.v] = ve[rt]+nd.w; // 更新 邻居事件的 最早发生时间
            if(--indeg[nd.v] == 0)
                wrkq.push(nd.v);
        }
        wrkq.pop();
        topo_seq.push(rt);  // 加入拓扑序列
    }
    return topo_seq.size() == ver_n;
}

// 计算 vl[], vle是 ve[l], l是拓扑排序的最后一位
void fill_vl(int vle){
    fill(vl, ver_n, vle);
    while (!topo_seq.empty()){
        int v = topo_seq.top();
        for(node nd: graph[v]){
            if(vl[nd.v]-nd.w < vl[v]){
                vl[v] = vl[nd.v]-nd.w;
            }
        }
        topo_seq.pop();
    }
    
}

// critical path solution
void critical_path(){
    for(int i=0; i<ver_n; i++){
        for(node nd: graph[i]){
            // 活动边 (i, nd.v) 最早开始时间也即是 始点事件i 的最早发生时间
            // 活动边 (i, nd.v) 最迟开始时间也即是 终点事件i 的最迟发生时间减去活动时间
            if(ve[i] == vl[nd.v]-nd.w){
                cout<<i<<" -> "<<nd.v<<" ("<<nd.w<<")"<<endl;
            }
        }
    }
}


int main(){
    init_graph();               // 数据输入
    topo();                     // 获取拓扑序列同时求解 ve[]
    fill_vl(ve[ver_n-1]);       // 求解 vl[]
    critical_path();            // 输出关键活动
    cout << "Total time is " << ve[ver_n-1] <<" at least."<< endl;
    return 0;
}

/*
5 8
0 1 6
0 2 4
0 3 3
3 1 4
1 4 5
3 2 2
2 4 7
3 4 8
*/