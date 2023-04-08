---
title: "字符串专题(1)-字符串Hash"
date: 2023-04-07T16:14:52+08:00
draft: false
tags: ["字符串", "哈希"]
categories: ["学习笔记"]
twemoji: true
lightgallery: true
---

字符串hash 是指将一个字符串S 映射为一个整数，使得该整数可以尽可能唯一地代表字符串 S。那么在一定程度上，如果两个字符串转换成的整数相等，就可以认为这两个字符串相同。

此前, 对于一个只有大写字母的字符串, 是把它的每一个字符当作一个26进制的数位, 整个字符串形成一个26进制数, 那么Hash就是把它转为10进制数即可. 然而, 当字符串太长时, 这个数字会大到难以承受. 一个常用方法是利用模数, 也即取某个素数 mod 的模.
```c
H[i]=H[i-1]x26+index(str[i]) // (i: from 0 to H.length-1)
H[i]=(H[i-1]x26+index(str[i])) % mod // (i: from 0 to H.length-1)
```
但这又会产生另外的问题，也就是可能有多个字符串的 hash 值相同，导致冲突。不过幸运的是，在实践中发现，在 int 数据范围内，如果把进制数设置为一个 $10^7$ 级别的素数p(例如10000019)，同时把mod 设置为一个 $10^9$ 级别的素数(例如1000000007)，如下所示，那么冲突的概率将会变得非常小
`H[i] = (H[i-1] x p +index(str[i])) % mod`
来看一个问题:给出N个只有小写字母的字符串，求其中不同的字符串的个数。对这个问题，如果只用字符串 hash 来做，那么只需要将N个字符串使用字符串 hash函数转换为N个整数，然后将它们排序去重即可，代码如下(当然也可以用 set 或者 map 直接一步实现，但是速度比字符串 hash 会慢一点点):

```c++
long long hashFunc(string str){
    long long H = 0;    // in case of excessing
    for(char c: str){
        H = (H*P+(c-'a'))%MOD;
    }
    return H;
}
```

## 最长公共子串
来看一个问题:输入两个长度均不超过1000的字符串，求它们的 最长公共子串 的长度。例如字符串"ILoveYou"与"YouDontLoveMe"的最长公共子串是"Love"而不是"You"，因此输出4。(注意:子串必须连续)
### 子串Hash值
在经过上述推导后, 我们得到了一个冲突概率小的字符串哈希函数, 我们依次得到了 `H[0]`, `H[1]`, ... , `H[n-1]`. 其中 `H[n-1]` 即为最后的字符串 `str` 的哈希值, 实际工程并未使用数组存储中间值, 而是使用不断覆盖的方法. 现考虑一个问题, 如何求 `str` 的子串 `str[i ... j]` 的Hash值, 一个方法就是不考虑已经得到的 `H[]` 当作新的字符串再调用函数求解. 然而这样势必失去了Hash的时间优势. 是否可以仅凭借 `H[]` 得到 `str[i ... j]` 的 Hash 值呢？

考察 `H[i]`, 他表示了字符串 `str[0 ... i]` 的 Hash 值, 假如不考虑MOD操作, 回到原始的进制思想, 则有
$H[i]=H[i-1]\times p+index(str[i])$
而 $H[i ... j]$ 就表示 str[i ... j] 从 p进制转为10进制的结果
$ H[i, j] = str[i] \times p^{(j-i)} +...+ str[i] \times p^{(j-j)}$
又有:
$H[j] = H[j-1]*p+str[j] $
继续迭代到第i步, 就得到
$H[j]=H[i-1]*p^{(j-i+1)}+H[i, j]$
于是就有:
$H[i, j] = H[j]-H[i-1]*p^{j-i+1}$
最后再加上取模操作，同时为了保证 H[i, j] 为正数, 就得到:

$$H[i,j] = (H[j]-H[i-1]*p^{j-i+1}) \% mod$$
$$H[i,j] = H[j]\% mod-(H[i-1]*p^{j-i+1}) \% mod$$
$$H[i,j] = H[j]\% mod-(H[i-1]\% mod)*(p^{j-i+1}\% mod) \% mod$$
$$H[i,j] = H[j]-H[i-1]*(p^{j-i+1}\% mod)\% mod$$
$$H[i,j] = (H[j]-H[i-1]*(p^{j-i+1}\% mod) \% mod+mod)\% mod$$

于是, str 的 H[] 通过 hashFunc() 可以得到, 而 (p^{j-i+1}\% mod) 也可以单独计算得到, 设为 P[], 易知它独立于字符串, 在 P 和 mod 确定时是一个常数数组.
### 题解

以上讨论了计算字符串Hash值后, 利用中间值得到子串哈希值的方法. 接下来, 就是问题求解, 我们遍历两个字符串的每一个子串, 计算哈希值并存储, 然后比较它们之间是否有相同的值。
```c++
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
```
