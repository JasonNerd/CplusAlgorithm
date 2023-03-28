// @FileName:     GA02C04Floyd.cpp
// @CreateTime:   2023/03/27 19:36:05
// @Author:       Rainbow River

/*
Floyd算法(读者可以将其读作“弗洛伊德算法”用来解决全源最短路问题，即对给定的图G(VE)，求任意两点uv之间的最短路径长度，时间复杂度是 0(n^3)。
由于的复杂度决定了顶点数n的限制约在200以内，因此使用邻接矩阵来实现Flyd 算法是非常合适且方便的。
Floyd算法基于这样一个事实:如果存在顶点k，使得以k作为中介点时顶点i和顶点i的当前最短距离缩短，则使用顶点k作为顶点i和顶点i的中介点，
即当dis[i][k] + dis[k][j] < dis[i]li]时，令dis[i][j]= dis[i][k] + dis[k][j](其中 dis[i][j]表示从顶点i到顶点i的最短距离)。
如图10-42所示，V1 到 V4 的距离为3，而以V2为中介点时可以使V1到V4的距离缩短为2，那么就把V1到V4的距离从3优化为2,
即当dis[1][2]+dis[2][4]<dis[1][4]时，令dis[1][4]= dis[1][2] + dis[2][4]。
基于上面的事实，Floyd算法的流程如下:
枚举顶点 k in [1，n]
    以顶点k作为中介点，枚举所有顶点对i和j(i in [1，n]，j in [1，n])
        如果dis[il[k] +dis[k][j] < dis[il[j]成立
            赋值dis[i][i] = dis[i][k] +dis[k][j]
*/

#include<iostream>
using namespace std;
const int MAXN = 100;
int dis[MAXN][MAXN];
int ver_n, adj_n;

void init_graph(){
    cin >> ver_n >> adj_n;
    int ti, tj, tv;
    for(int i=0; i<ver_n; i++){
        for(int j=0; j<ver_n; j++){
            dis[i][j] = MAXN;
        }
    }
    for(int i=0; i<adj_n; i++){
        cin >> ti >> tj >> tv;
        dis[ti][tj] = dis[tj][ti] = tv;
    }
    for(int i=0; i<ver_n; i++) dis[i][i] = 0;
}

void plot(int a[MAXN][MAXN]){
    for(int i=0; i<ver_n; i++){
        for(int j=0; j<ver_n; j++){
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

void floyd(){
    for(int k=0; k<ver_n; k++){
        for(int i=0; i<ver_n; i++){
            for(int j=0; j<ver_n; j++){
                int m = dis[i][k]+dis[k][j];
                if(m < dis[i][j])
                    dis[i][j] = m;
            }
        }
        // cout << "k = " << k << endl;
        // plot(dis);
        // cout << endl;
        // cout << endl;
    }
}

int main(){
    init_graph();
    cout << endl;
    floyd();
    plot(dis);
    return 0;
}
/*
5 9
0 1 3
0 2 1
0 3 6
1 2 1
1 3 3
1 4 1
2 3 2
2 4 4
3 4 1
*/