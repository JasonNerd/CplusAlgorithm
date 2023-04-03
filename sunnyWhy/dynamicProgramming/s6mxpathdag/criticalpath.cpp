// @FileName:     criticalpath.cpp
// @CreateTime:   2023/04/03 11:30:57
// @Author:       Rainbow River

// 求解 DAG 最长路, 设定状态数组 dp[], dp[i]表示从节点 i 出发
// 所能得到的最长路径的长度. 思路是按照逆拓扑排序的顺序求解, 或者
// 使用递归.

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;
const int MAXN = 101;
struct node{
    int v, w;
    node(int v, int w){
        this->v = v;
        this->w = w;
    }
};
int indegree[MAXN], oudegree[MAXN];
vector<node> graph[MAXN];
int ver_n, edg_n;
int dp[MAXN]; // dp[i] 表示从节点i出发所能够得到的最长路径


void init_graph(){
    cin >> ver_n >> edg_n;
    for(int i=0; i<edg_n; i++){
        int ni, no, ew;
        cin >> ni >> no >> ew;
        graph[ni].push_back(node(no, ew));
        oudegree[ni]++;
        indegree[no]++;
    }
}

void fill_in0(queue<int>& q, bool flgs[]){
    for(int i=0; i<ver_n; i++)
        if(!flgs[i] && indegree[i]==0){
            q.push(i);
            flgs[i] = true;
        }
}
// 拓扑排序得到拓扑序列, 但使用 stack存储, 再一个个的pop, 过程中求解 dp[]
int topo_resolve(){
    stack<int> toposeq;
    queue<int> wrkQ;
    bool having_inqueue[MAXN];
    fill_in0(wrkQ, having_inqueue);
    while(!wrkQ.empty()){
        int rid = wrkQ.front();
        toposeq.push(rid);
        for(node no: graph[rid])
            indegree[no.v]--;
        wrkQ.pop();
        fill_in0(wrkQ, having_inqueue);
    }
    // 接着按照倒序遍历stack, fill the dp[]
    int res = 0;
    while(!toposeq.empty()){
        int rid = toposeq.top();
        int mxl = 0;
        for(node no: graph[rid])    // 遍历所有孩子, 寻找最大 (dp[i]+ew)
            mxl = max(dp[no.v]+no.w, mxl);
        dp[rid] = mxl;
        toposeq.pop();
        res = max(mxl, res);
    }
    return res;
}

int main(){
    init_graph();
    cout << topo_resolve() << endl;
    return 0;
}

/*
9 12
0 2 2
0 3 2
1 3 3
1 4 2
2 5 3
3 5 3
3 6 2
4 6 1
5 7 2
5 8 3
6 7 2
6 8 2

*/