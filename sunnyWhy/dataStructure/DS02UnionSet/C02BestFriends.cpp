/*
【好朋友】
宝贝的好朋友规则：
1. A是B的好朋友，则B是A的好朋友
2. A是B的好朋友，B是C的好朋友，则A是C的好朋友
现在给出所有好朋友的信息，试将他们分组使得组内的任意一对都是好朋友而组间任意一对均不是

输入说明:
两个正整数n, m(n, m<=100), 分别表示宝贝的个数和好朋友的组数，
宝贝编号为1到n，接下来是m行，每行都包含两个正整数a和b，表示宝贝a和宝贝b是好朋友
输出一个正整数，表示这些宝贝可以分出的组数
*/
#include<iostream>
using namespace std;

const int MXNUM = 120;
int baby[MXNUM];    // 关系数组
bool is_root[MXNUM];
int m, n;   // m边数, n顶点数

void init_baby(){
    for(int i=1; i<=n; i++){
        baby[i] = i;
        is_root[i] = false;
    }
}

int find_friend(int a){
    int f = baby[a];    
    if(f == a){ // 此即为根节点
        return a;
    }else{      // 否则向上查找父亲
        int r = find_friend(f); // 递归得到根节点
        baby[a] = r;        // 返回时一步步的把路径节点父亲设为根节点
        return r;
    }
}

void merge(int a, int b){
    int fa = find_friend(a), fb = find_friend(b);
    if(fa != fb)
        baby[fa] = fb;
}

int main(){
    cin >> n >> m;
    init_baby();
    for(int i=0; i<m; i++){
        int a, b;
        cin >> a >> b;
        merge(a, b);
    }
    for(int i=1; i<=n; i++){
        is_root[find_friend(i)] = true;
    }
    int res = 0;
    for(int i=1; i<=n; i++)
        if(is_root[i])
            res++;
    cout << res;
}
/*
思路：好朋友在一个集合，否则不在，是并查集模型
另一方面，需要记录根节点个数，或者哪些节点是根节点
*/
/*
样例
7 5
1 2
3 2
1 4
3 1
5 6

*/