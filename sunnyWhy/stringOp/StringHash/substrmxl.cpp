// @FileName:     substrmxl.cpp
// @CreateTime:   2023/04/08 14:01:16
// @Author:       Rainbow River

#include <iostream>
#include <string>
#include <vector>

using namespace std;
const int MOD = 1e9+7;
const int P = 1e7+19;
const int MAXLEN = 1010;    // 字符串最大长度
typedef long long LL;
LL powerP[MAXLEN];         // 计算P^[i]%MOD的值
struct hashnode{
    LL hashval;     // 子串哈希值
    int i, j;       // 子串下标值
    hashnode(int i, int j, int v){
        this->i = i;
        this->j = j;
        this->hashval = v;
    }
};

void hashFunc(LL H[], string str){
    H[0] = str[0];  // 自定义一个值
    for(int i=1; i<str.length(); i++){
        H[i] = (H[i-1]*P+str[i]) % MOD;
    }
}

void fillPowerP(){
    powerP[0] = 1;
    for(int i=1; i<MAXLEN; i++)
        powerP[i] = (powerP[i-1]*P)%MOD;
}

// 计算 H[i, j]
LL substrHash(LL H[], int i, int j){
    if(i == 0) return H[j];
    else return (H[j]-(H[i-1]*powerP[j-i+1])%MOD+MOD)%MOD;
}

// 计算所有子串的的 Hash 值, 并保存 hash-value, i, j
void hashStrCal(LL H[], int n, vector<hashnode>& res){
    for(int i=0; i<n; i++){
        for(int j=i; j<n; j++){
            res.push_back(hashnode(i, j, substrHash(H, i, j)));
        }
    }
}

int main(){
    // 1. 输入两个字符串
    string str1, str2;
    cin >> str1 >> str2;
    // 2. 计算 str1 和 str2 的 Hash 值数组
    int n1 = str1.length(), n2 = str2.length();
    LL *H1 = new LL[n1], *H2 = new LL[n2];
    fillPowerP();
    hashFunc(H1, str1);
    hashFunc(H2, str2);
    // 3. 计算 str1 和 str2 的 所有子串的Hash
    vector<hashnode> res1, res2;
    hashStrCal(H1, n1, res1);
    hashStrCal(H2, n2, res2);
    // 4. 比较 hash 值, 迭代得到最长的公共字符串
    int mxl=0;
    string mxsubstr;
    for(int i=0; i<res1.size(); i++){
        for(int j=0; j<res2.size(); j++){
            int l1 = res1[i].j - res1[i].i + 1;
            int l2 = res2[j].j - res2[j].i + 1;
            if(res1[i].hashval == res2[j].hashval && l1==l2 && l1 > mxl){
                mxl = l1;
                mxsubstr = str1.substr(res1[i].i, l1);
            }
        }
    }
    cout << mxl << endl;
    cout << mxsubstr << endl;
}

/*
a a
a ba
a b
aa ba
icanhearyou iamearyel
*/