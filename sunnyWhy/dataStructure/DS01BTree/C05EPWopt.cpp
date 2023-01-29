/*
这一程序也是要解决相等路径权重问题，是在C05EqualPW上的改进
其一是关于最后结果的排序问题，原程序并未给出方法，但可以看出是准备事后排序，
    优化方案是：在输入时，对节点的孩子进行依据权重从大到小进行排序，这样
    每次都是先选择权重较大的节点。那么自然优先输出更大的路径序列
其二是递归出口的选择：
    原程序是一定要搜索到叶节点，然后计算路径权重，接着进行比较，那么它必定是要
    访问到每一个节点的，并且计算权重也需要额外开销
    不妨加入一个cSum变量记录当前遍历序列的权重和，判断cSum与n的大小关系
    如果相等则判断当前节点是否为叶节点，是则直接输出，否则返回上一级，
    如果已经大于n就直接返回
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Tnode{
    int weight;
    vector<int> children;
};
vector<Tnode> wTee; // 树
int m, n, k; // m节点数, n权重, k非叶节点数
vector<int> pathW;
bool cmp(int a, int b);
void construct();
void dfsPre(int root, int csum);

bool cmp(int a, int b){
    return wTee[a].weight > wTee[b].weight;
}

void construct(){
    cin >> m >> k >> n;
    for(int i=0; i<m; i++){
        Tnode nd;
        cin >> nd.weight;
        wTee.push_back(nd);
    }
    for(int i=0; i<k; i++){
        int rt, chn, chid;
        cin >> rt >> chn;
        for(int j=0; j<chn; j++){
            cin >> chid;
            wTee[rt].children.push_back(chid);
        }
        // 对孩子节点按权重从大到小进行排序, 事前排序
        sort(wTee[rt].children.begin(), wTee[rt].children.end(), cmp);
    }
}

void dfsPre(int root, int csum){
    Tnode rt = wTee[root];
    csum += rt.weight;
    pathW.push_back(rt.weight);
    if(csum > n) return ;
    if(csum == n){
        if(rt.children.size()==0){ // 叶子节点
            int pn = pathW.size();
            for(int i=0; i<pn; i++){
                cout << pathW[i];
                if (i<pn-1) cout << " ";
            }
            cout << endl;
        }
        return ;
    }
    for(int i=0; i<rt.children.size(); i++){
        dfsPre(rt.children[i], csum);
        pathW.pop_back();
    }
}

int main(){
    construct();
    cout << "+++++++++++++++" << endl;
    dfsPre(0, 0);
    return 0;
}


