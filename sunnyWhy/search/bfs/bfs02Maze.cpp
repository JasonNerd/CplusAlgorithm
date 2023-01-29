/*
给出一个二维字符矩阵，其中S表示起点, T为终点, .表示平地, *表示墙壁
求从S到T的最短步数
*/
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
