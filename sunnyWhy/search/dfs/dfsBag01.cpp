/*
例如，以走迷宫为例，我们总是选择岔道口中的一条前进，而如果遇到了新的岔道口，
仍选择新岔道口中的一条岔路前进，直到走到死胡同，此时返回上一个岔道口，选择另一条
岔路前进。这种策略在深度上进行，不走到死胡同就不回头，称为深度优先遍历

注意到，深度优先搜素会遍历所有的路径，并且每走到一个死胡同，就代表着一个完整路径的形成。
深度优先搜索是一种枚举所有完整路径以遍历所有情况的方法
使用栈或者递归可以很好的解决递归问题
*/
// 假设有n件物品，已知价格v[i]和w[i]，选取重量不超过W的物品使价格总和最大
#include <iostream>
#include <vector>

using namespace std;
const int MXN = 20;
vector<int> v={14, 30, 4, 3, 17, 7, 13, 8, 40, 22};
vector<int> w={3, 7, 1, 1, 4, 2, 3, 2, 9, 5};
int n = 10, mxv = 0, bag=12;

void DFS(int index, int cuV, int cuW){
    if(index >= n){
        if(cuW<=bag && cuV > mxv)
            mxv = cuV;
        return ;
    }
    // cout << "index="<<index << ", current Value = " << cuV << ", current Weight = " << cuW << endl;
    DFS(index+1, cuV, cuW);
    DFS(index+1, cuV+v[index], cuW+w[index]);
}

int main(){
    DFS(0, 0, 0);
    cout << mxv << endl; 
    return 0;
}

