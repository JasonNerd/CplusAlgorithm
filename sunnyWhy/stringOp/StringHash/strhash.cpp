// @FileName:     strhash.cpp
// @CreateTime:   2023/04/08 11:52:09
// @Author:       Rainbow River

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
const int MOD = 1e9+7;
const int P = 1e7+19;

// string hash: assume only xiao xie letter
long long hashFunc(string str){
    long long H = 0;    // in case of excessing
    for(char c: str){
        H = (H*P+(c-'a'))%MOD;
    }
    return H;
}

int main(){
    string input;
    vector<int> ans;
    while(getline(cin, input), input != "#"){
        long long strid = hashFunc(input);
        ans.push_back(strid);
    }
    sort(ans.begin(), ans.end());
    int cnt = 0;
    for (int i=0; i<ans.size(); i++) {
        if(i==0 || ans[i] != ans[i-1])
            cnt++;
    }
    cout << cnt << endl;
}