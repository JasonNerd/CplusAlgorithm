/*
题目描述
A traveler's map gives the distances between cities along the highways, together with the cost of each highway.
Now you are supposed to write a program to help a traveler to decide the shortest path between his/her /
starting city and the destination. If such a shortest path is not unique, you aresupposed to output the one /
with the minimum cost, which is guaranteed to be unique.
输入格式
Each input file contains one test case. Each case starts with a line containing 4 positive integers N,M, S, and D, 
where N (<500) is the number of cities (and hence the cities are numbered from 0to N-1); 
M is the number of highways; S and D are the starting and the destination cities.respectively. 
Then M lines follow, each provides the information of a highway, in the format:
City1 City2 Distance Cost
where the numbers are all integers no more than 500, and are separated by a space.
输出格式
For each test case, print in one line the cities along the shortest path from the starting point tothe destination,
followed by the total distance and the total cost of the path. T
he numbers must be separated by a space and there must be no extra space at the end of output.
*/
#include <iostream>
#include <vector>

using namespace std;

int main(){
    return 0;
}

/*
input
4 5 0 3
0 1 1 20
1 3 2 30
0 3 4 10
0 2 2 20
2 3 1 20
output
0 2 3 3 40
题意
有N个城市(编号为0~N-1)、M 条道路(无向边)，并给出 M条道路的距离属性与花费属性。
现在给定起点 S 与终点 D，求从起点到终点的最短路径、最短距离及花费。
注意:如果有多条最短路径，则选择花费最小的那条。
*/
