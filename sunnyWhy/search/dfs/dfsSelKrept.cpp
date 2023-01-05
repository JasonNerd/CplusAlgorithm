// 从n个数中选k个数使其和为x，每个数可重复选，可包含负数，若有多个结果，取平方和最大的
#include <iostream>
#include <vector>

using namespace std;
vector<int> tmp, ans, seq = {5, -2, 3, 1};
int n = 4, x = 27, k = 9, mxSqsum = 0;

void selectK(int index, int curK, int curSum, int curSq){
    if (curK == k && curSum==x){
        if (curSq >= mxSqsum){
            ans = tmp;
            mxSqsum = curSq;
        }
        return ;
    }
    if(index >= n || curK > k) return ;
    tmp.push_back(seq[index]);
    selectK(index, curK+1, curSum+seq[index], curSq+seq[index]*seq[index]);
    tmp.pop_back();
    selectK(index+1, curK+1, curSum, curSq);
}

int main(){
    selectK(0, 0, 0, 0);
    for(int i=0; i<ans.size(); i++)
        cout << ans[i] << " ";
    cout << "max square sum = " << mxSqsum << endl;
    return 0;
}
