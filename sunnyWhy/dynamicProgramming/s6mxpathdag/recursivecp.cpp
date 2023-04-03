// @FileName:     recursivecp.cpp
// @CreateTime:   2023/04/03 15:45:29
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
int ver_n, edg_n;
int dp[MAXN], indeg[MAXN];

void init_graph(){
    cin >> ver_n >> edg_n;
    for(int i=0; i<edg_n; i++){
        int ni, no, ew;
        cin >> ni >> no >> ew;
        graph[ni].push_back(node(no, ew));
        indeg[no]++;
    }
}

int DP(int i){
    if(dp[i] == 0){     // 未求解, 则先求解
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
    return 0;
}