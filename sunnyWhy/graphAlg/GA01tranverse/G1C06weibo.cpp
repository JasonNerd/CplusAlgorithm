/*
PAT A1034 Head of Gang
警方寻找一个犯罪团伙(gang)的头目(head)的一个方法是检查他们的通话时长。
假设A和B之间有通话, 则称A和B具有联系(边), 边权被定义为双方通话总时长,
gang被定义为一个相互之间具有联系的多于2人的团伙, 且该团伙的纵通话时长
超过 阈值K. 同时在每一个 gang 中, 权重最大的节点即为 头目head. 现在要求
找到所有的gang及其head

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
*/
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

/*
分析: 题目描述了一个非连通的图结构, 要求就是遍历到每一个连通分量并提取该连通分量的总体特征
例如 总边权、总节点数 以及细化特征例如各顶点的点权, 并找到其中点权最大的顶点。

这可以 基于图的遍历 来实现, 遍历时可以记录什么或者得到的信息有哪些, 遍历是基于顶点的, 因此
可以得到 连通分量包含哪些顶点、顶点总数, 接着思考使用什么数据结构实现它:
vetcor<gnode> branch;
其中每个元素都是一个节点, 节点内容含义变为:
v(顶点编号) w(对应节点的权重)
或者:
map<string, int> pweights; // 顶点编号, 点权
顶点点权与出边和入边相关, 可独立计算, 遍历连通分量后可以得到具体哪些顶点, 因此
连通分量总边权可以由点权的和的一半求得(于是不必区分是入边还是出边)
这里不妨先尝试使用深度优先遍历实现
*/
