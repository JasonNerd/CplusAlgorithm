---
title: "第02章-并查集"
date: 2023-04-03T10:11:37+08:00
draft: false
tags: ["算法", "并查集"]
categories: ["学习笔记"]
twemoji: true
lightgallery: true
---

## 1. 基本描述
**并(Union)查(Find)集(Set)**, ufs描述的是集合, 主要支持U集合间的合并操作和F判断元素所在的集合
## 2. 实现方法
也即一个数组:
```c
int father[N];  // 并查集，包含多个集合
```
father[i]表示i的父亲节点， father[i]=i表示i为根节点，注意一个集合只有一个根节点，是该集合的标识.
* 在查找过程中, 为了优化查找效率, 可以在得到集合的根节点后，再次遍历路径上的节点, 使得他们的父指针直接指向根节点.
* 其次, 合并操作必须是在根节点间进行的. 实现代码如下:
```c++
#include <iostream>
using namespace std;
const int NUM = 50;
int father[NUM];
// 不断回溯x的父节点, 随后返回元素x所在集合的根节点
int findFather(int x);
// 将a和b所在的集合合并, 首先找到 a 和 b 的 根节点
// 接着使某一根节点成为另一根节点的父亲
void Union(int a, int b);

int main(){
    return 0;
}

int findFather(int x){
    int tf = x, tx;
    // 先找根节点
    while (tf != father[tf])
        tf = father[tf];
    // 再进行调整    
    while(x != father[x]){
        tx = x; // 暂时保存原x值
        x = father[x];  // 迭代x
        father[tx] = tf;    // 使指向一个根节点
    }
    return tf;
}
void Union(int a, int b){
    int fa = findFather(a);
    int fb = findFather(b);
    if(fa != fb){
        father[fa] = fb;
    }
}

```
## 3. 找朋友问题
【好朋友】
宝贝的好朋友规则：
1. A是B的好朋友，则B是A的好朋友
2. A是B的好朋友，B是C的好朋友，则A是C的好朋友
现在给出所有好朋友的信息，试将他们分组使得组内的任意一对都是好朋友而组间任意一对均不是

* 输入说明:
两个正整数n, m(n, m<=100), 分别表示宝贝的个数和好朋友的组数，
宝贝编号为1到n，接下来是m行，每行都包含两个正整数a和b，表示宝贝a和宝贝b是好朋友
* 输出一个正整数，表示这些宝贝可以分出的组数

```c++
// 样例
7 5
1 2
3 2
1 4
3 1
5 6
```
思路: 使用并查集, 将各个朋友进行合并, 随后查看哪些节点是根节点, 统计数量即可.以下为程序示例:
```c++
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
```