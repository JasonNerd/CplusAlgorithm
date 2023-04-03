---
title: "第04章-哈夫曼树"
date: 2023-04-03T10:49:39+08:00
draft: false
tags: ["算法", "哈夫曼树"]
categories: ["学习笔记"]
twemoji: true
lightgallery: true
---

## 哈夫曼编码和哈夫曼树
考虑这个问题：现有若干堆石子需要合并为一堆, 合并两堆石子的费用即为两堆石子的质量总和, 问合并费用的最小值

这里将石子视为节点, 石子质量视为节点权重, 合并视为父节点, 父节点权重为孩子节点的权重之和。合并的过程就是生成一棵具有一个根节点的二叉树，那么此时原始各石子堆形成了叶节点，而合并费用即为非叶节点的权重之和。另一方面，也可以看作【树的带权路径长度之和】，此处权重即为叶节点权重。

因此，可以每次选取两个最小的石子堆进行合并直到最后只有一个石子堆，可以使用小顶堆实现，每次做两次删除堆顶操作，然后将他们的和插入到堆中，小顶堆可以方便的使用优先队列实现

## 代码实现
```c++
#include <iostream>
#include <queue>
using namespace std;
priority_queue<int, vector<int>, greater<int> > minHeap;    // 小顶堆
int n=10, a[10] = {85, 55, 82, 57, 68, 92, 99, 98, 66, 56};

int main(){
    for(int i=0; i<10; i++)
        minHeap.push(a[i]);
    while (minHeap.size() > 1){
        int lf1 = minHeap.top();
        minHeap.pop();
        int lf2 = minHeap.top();
        minHeap.pop();
        minHeap.push(lf1+lf2);
    }
    cout << minHeap.top() << endl;
    return 0;
}

/*
           55
      56       82
  57     68   92 99
98 66  85
*/

/*
关于优先队列的基本使用方法
priority_queue<Type, Container, Functional>
Type 就是数据类型, Container 就是容器类型, Functional 就是比较的方式，当需要用自定义的数据类型时
才需要传入这三个参数，使用基本数据类型时，只需要传入数据类型，默认是大顶堆
    priority_queue<int> a; 
    //等同于 priority_queue<int, vector<int>, less<int> > a;
    priority_queue<int, vector<int>, greater<int> > c;  //这样就是小顶堆

和队列基本操作相同:

top 访问队头元素
empty 队列是否为空
size 返回队列内元素个数
push 插入元素到队尾 (并排序)
emplace 原地构造一个元素并插入队列
pop 弹出队头元素
swap 交换内容
*/
```