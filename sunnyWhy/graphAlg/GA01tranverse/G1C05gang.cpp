/*
PAT A1076 Forwards on Weibo
在微博上一个用户(root)可能拥有很多粉丝(follower), 同时也会关注许多用户
这就构成了一个社交网络. 假设 root 发表了一条微博, 那么他的 follower 就可以看到
并转发, 同时也可以继续被 follower 的粉丝继续转发.  现在给出一个社交网络, 你需要
计算指定用户的微博可能的最大转发数(每个用户只转发一次), 并且限制 间接粉丝的层级至多为L

输入格式:
N, L    // N是用户数(<=1000), L为间接粉丝最大层数(<=6)
n, f[n] // 接下来的N行, 每行第一个数表示用户粉丝数n, 后面跟着n个数表示 关注的用户id列表
...
...
query_n, query_list // 最后一行是查询列表, 第一个数是要查询的用户数量, 后面跟着用户ID
*/

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

/*
问题分析：
一是，输入是某用户关注的用户编号, 在输入时应该这样构建邻接表，也即
G[i] 后的用户列表表示 G[i]转发微博后 可以继续转发的用户列表, 也即粉丝列表
二是, 如何记录遍历层数, 这可以通过设置节点，增加冗余信息做到
其次可以设定一个指针指向上一层的最后一个节点, 当遍历完这个节点就表示进入了下一层
1<- 4 
2<- 1
3<- 1 4 5
4<- 1 5 6
6<- 3
7<-
*/