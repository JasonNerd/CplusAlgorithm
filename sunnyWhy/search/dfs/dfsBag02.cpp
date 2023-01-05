// 假设有n件物品，已知价格v[i]和w[i]，选取重量不超过W的物品使价格总和最大
#include <iostream>
#include <vector>

using namespace std;
const int MXN = 20;
vector<int> v={14, 30, 4, 3, 17, 7, 13, 8, 40, 22};
vector<int> w={3, 7, 1, 1, 4, 2, 3, 2, 9, 5};
int n = 10, mxv = 0, bag=12;

void DFS(int index, int cw, int cv){
    if(index >= n){
        if (cw <= bag){
            if(cv >= mxv)
                mxv = cv;
        }
        return ;
    }
    DFS(index+1, cw, cv);
    if (cw + w[index] <= bag){
        if (cw+w[index] > mxv){
            mxv = cw+w[index];
        }
        DFS(index+1, cw+w[index], cv+v[index]);
    }
}


int main(){
    DFS(0, 0, 0);
    cout << mxv << endl;
    return 0;
}