/*
1. 基本描述
并(Union)查(Find)集(Set)
ufs描述的是集合，主要支持U集合间的合并操作和F判断元素所在的集合
2. 实现方法
也即一个数组:
    int father[N];  // 并查集，包含多个集合
father[i]表示i的父亲节点， father[i]=i表示i为根节点，
注意一个集合只有一个根节点，是该集合的标识
*/
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

/*
在查找操作中，只需找到原节点的根节点即可
因而针对链式，其查找效率会很低下
此时可以在查找过程中进行优化，也即
*/
