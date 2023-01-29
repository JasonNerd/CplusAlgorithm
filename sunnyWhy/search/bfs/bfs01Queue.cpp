/*
给出一个 m x n 的矩阵，它只包含0和1，如果矩阵中若干个1相邻，
称之为一个块，求矩阵中的块数，例如
0 1 1 1 0 0 1
0 0 1 0 0 0 0
0 0 0 0 1 0 0
0 0 0 1 1 1 0
1 1 1 0 1 0 0
1 1 1 1 0 0 0
包含4个块
*/
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