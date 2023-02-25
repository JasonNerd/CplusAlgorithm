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