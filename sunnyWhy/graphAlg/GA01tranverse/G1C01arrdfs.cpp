/*
使用邻接矩阵实现图的存储, 用深度优先遍历方法遍历图
*/


#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int MXN = 100;   // N为最大节点数
int graph[MXN][MXN], n;     // n为实际节点数 ( 编号 0 到 n-1 ), s为遍历起始节点
bool having_accessed[MXN];      // 记录各个顶点是否 已加入队列
vector<int> tranverse_seq;
// 使用 递归 实现深度优先
void dfsTranverse(int start){
    tranverse_seq.push_back(start);
    having_accessed[start] = true;
    for (int i=0; i<n; i++){
        if (graph[start][i] > 0 && !having_accessed[i]){
            // 未被访问的邻居
            dfsTranverse(i);
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
    init_grah();
    dfsTranverse(start);
    for(auto i: tranverse_seq){
        cout << i << " ";
    }
    cout << endl;
}

int main(){
    prt_res(1); // 1 0 4 3 2
    // prt_res(0); // 0 1 2 3 4
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