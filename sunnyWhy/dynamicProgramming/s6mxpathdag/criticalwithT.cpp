// @FileName:     criticalwithT.cpp
// @CreateTime:   2023/04/03 16:23:05
// @Author:       Rainbow River

#include<iostream>
#include<vector>
using namespace std;

struct node{
    int v,w;
    node(int v, int w){
        this->v = v;
        this->w = w;
    }
};
const int MAXN = 101;
vector<node> graph[MAXN];
int ver_n, edg_n, T;
int dp[MAXN], indeg[MAXN];

void init_graph(){
    cin >> ver_n >> edg_n >> T;
    for(int i=0; i<edg_n; i++){
        int ni, no, ew;
        cin >> ni >> no >> ew;
        graph[ni].push_back(node(no, ew));
        indeg[no]++;
    }
    // 注意, 将除终点 T 以外的 dp[i] 设置为 -INF, 表示目前节点 i 与 节点T 之间不可达
    for(int i=0; i<ver_n; i++)
        if(i!=T)
            dp[i] = -MAXN;
}

int DP(int i){
    if(dp[i] == -MAXN){     // 未求解, 则先求解
        for(node ch: graph[i]){
            dp[i] = max(dp[i], DP(ch.v)+ch.w);
        }
    }
    return dp[i];
}

int main(){
    init_graph();
    for(int i=0; i<ver_n; i++)
        if(indeg[i] == 0)
            DP(i);
    int res = 0;
    for(int i=0; i<ver_n; i++)
        res = max(dp[i], res);
    cout << res << endl;
    for(int i=0; i<ver_n; i++)
        cout << dp[i] << " ";
    return 0;
}

/*
9 12 7
0 1 3
0 3 2
1 2 4
1 4 1
3 5 5
2 8 3
5 7 6
4 8 5
4 6 2
4 7 4
6 8 3
6 7 1

*/