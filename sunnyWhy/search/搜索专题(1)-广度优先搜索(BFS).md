---
title: "搜索专题(1)-广度优先搜索(BFS)"
date: 2023-04-07T14:49:02+08:00
draft: false
tags: ["算法", "搜索", "BFS"]
categories: ["学习笔记"]
twemoji: true
lightgallery: true
---

搜索, 就是在一个集合中按照一定的规则遍历访问集合的每一个元素的过程. 而广度优先搜索就是每次都把距离最近的元素访问完毕才会去访问更远的元素, 类似于一圈圈的向外扩散. 下面将以一些具体的问题进行探讨.

## 1. 求矩阵的"块数"
```git
给出一个 m x n 的矩阵，它只包含0和1，如果矩阵中若干个1相邻，
称之为一个块，求矩阵中的块数，例如
0 1 1 1 0 0 1
0 0 1 0 0 0 0
0 0 0 0 1 0 0
0 0 0 1 1 1 0
1 1 1 0 1 0 0
1 1 1 1 0 0 0
包含4个块
```
题解: 使用广度优先搜索标记每一个块, 无重复的进行计数.

```c++
#include <vector>
#include <iostream>
#include <queue>
using namespace std;
vector< vector<int> > inArr = {
    {0, 1, 0, 1, 0, 1, 0, 0}, 
    {0, 1, 1, 1, 1, 1, 0, 0}, 
    {0, 0, 0, 1, 0, 0, 0, 0}, 
    {0, 1, 0, 1, 0, 1, 0, 0}, 
    {0, 1, 1, 0, 0, 1, 0, 0}, 
    {0, 1, 1, 1, 0, 0, 0, 0}, 
    {0, 0, 0, 1, 0, 1, 0, 0}, 
    {0, 1, 0, 0, 0, 1, 0, 0}, 
    {0, 1, 0, 1, 1, 1, 0, 0}, 
    {0, 1, 0, 1, 0, 1, 0, 0}, 
};
const int m=10, n=8;
int isInQueue[m][n];
int dirX[4] = {0, 1, 0, -1};
int dirY[4] = {-1, 0, 1, 0};
int blkCnt(){
    queue<int> Q;
    int blk = 0;
    for (int i=0; i<m; i++){
        for (int j=0; j<n; j++){
            if (inArr[i][j]==1 && !isInQueue[i][j]){
                Q.push(i*n+j);  // 当前遇到1且未访问，则加入访问队列
                while(!Q.empty()){
                    int seq = Q.front();
                    Q.pop();
                    int cx = seq / n, cy = seq % n;
                    isInQueue[cx][cy] = true;   // 还原出(i, j)坐标，标记为已访问
                    for(int d=0; d<4; d++){     // 将(i, j)周围的未访问的1加入队列
                        int x = cx+dirX[d], y = cy+dirY[d];
                        if (x>=0 && x<m && y>=0 && y<n && inArr[x][y]==1 && !isInQueue[x][y])
                            Q.push(x*n+y);
                    }
                }
                blk++;
            }
        }
    }
    return blk;
}

int main(){
    cout << blkCnt() << endl;
    return 0;
}
```
## 迷宫最短路
给出一个二维字符矩阵，其中S表示起点, T为终点, .表示平地, *表示墙壁. 求从S到T的最短步数
```c++
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

const int rows=10, cols=8;
const char myMaze[rows][cols] = {
    {'*', '*', '.', '.', '*', '*', '*', '*'},
    {'.', '.', '.', '.', '.', '.', '.', '*'},
    {'.', '*', '.', '*', '*', '.', '*', '*'},
    {'.', '*', '*', '.', '*', '.', '.', '*'},
    {'.', '.', '.', '.', '*', '*', '.', '.'},
    {'S', '*', '.', '*', '*', '.', '.', '.'},
    {'.', '*', '.', '.', '*', '*', '.', '*'},
    {'.', '.', '.', '.', '.', '*', '.', '*'},
    {'*', '*', '.', '.', '*', '*', '.', 'T'},
    {'*', '*', '*', '.', '*', '.', '*', '*'},
};
int ifInQueue[rows][cols];
struct posXY{
    int x, y;
    posXY(){};
    posXY(int i, int j){
        this->x=i;
        this->y=j;
    }
    bool operator==(const posXY& oth){
        return this->x==oth.x && this->y==oth.y;
    }
    posXY operator+(const posXY& oth){
        return posXY(this->x+oth.x, this->y+oth.y);
    }
};
const posXY dirXY[4]={
    posXY(-1, 0), posXY(0, -1), posXY(1, 0), posXY(0, 1)
};
posXY S(5, 0), T(8, 7);

bool okToWalk(posXY p){
    return p.x>=0 && p.x<rows && p.y>=0 && p.y<cols && 
    (myMaze[p.x][p.y]=='.'||myMaze[p.x][p.y]=='T') && ifInQueue[p.x][p.y]==0;
}

void walkThrough(){
    queue<posXY> wlkQ;
    wlkQ.push(S);
    while(!wlkQ.empty()){
        posXY cp = wlkQ.front();
        if (myMaze[cp.x][cp.y]=='T')
            return ;
        wlkQ.pop();
        for (int i=0; i<4; i++){
            posXY atr = cp + dirXY[i];
            if (okToWalk(atr)){
                ifInQueue[atr.x][atr.y] = ifInQueue[cp.x][cp.y] + 1;
                wlkQ.push(atr);
            }
        }
    }
}

int main(){
    walkThrough();
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols; j++){
            cout << ifInQueue[i][j] << "\t";
        }
        cout << endl;
    }
    return 0;
}

```
