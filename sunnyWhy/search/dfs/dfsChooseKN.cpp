/*
从s个数中选取k个数使其和为x，若有多个答案选取平方和最大的一组
*/
#include <iostream>
#include <vector>
using namespace std;
vector<int> seq = {12, -3, 1, 1, 4, -2, 7, 5, 2, 6, 3, -4};
int x = 12, msq = 0, k=3, n=12;
vector<int> res, rea;

int sum_(){
    int rsm = 0;
    for(int j=0; j<res.size(); j++)
        rsm += res[j];
    return rsm;
}

int sq_sum(){
    int sqm = 0;
    for (int j=0; j<res.size(); j++)
        sqm += res[j]*res[j];
    return sqm;
}

void selectK(int i, int ck){
    int rsm = sum_(), sqm = sq_sum();
    if(ck >= k){
        if(rsm == x && sqm >= msq){
            msq = sqm;
            rea = res;
        }
        return ;
    }
    if(i>=n)return ;
    res.push_back(seq[i]);
    selectK(i+1, ck+1);
    res.pop_back();
    selectK(i+1, ck);
}

int main(){
    selectK(0, 0);
    for(int i=0; i<rea.size(); i++)
        cout << rea[i] << " ";
    cout << "max square sum = " << msq << endl;
    return 0;
}
