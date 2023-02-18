/*
As an emergency rescue team leader of a city, you are given a special map of your country.
The map shows several scatered cities connected by some roads. 
Amount of rescue teams in each city and the length of each road between any pair of cities are marked on the map.
When there is anemergency call to you from some other city, your job is to lead your men to the place as quickly aspossible,
and at the mean time, call up as many hands on the way as possible.
输入格式
Each input file contains one test case. For each test case, the first line contains 4 positiveintegers: 
N (<500)-the number of cities (and the cities are numbered from 0 to N-1), 
M--the number of roads, C1 and C2--the cities that you are currently in and that you must save,respectively. 
The next line contains N integers, where the i-th integer is the number of rescue teams in the i-th city
Then M lines follow, each describes a road with three integers cl, c2 and L, 
which are the pair of cities connected by a road and the length of that road, respectively. 
It is guaranteed that there exists at least one path from C1 to C2.
输出格式
For each test case, print in one line two numbers: 
the number of different shortest pathsbetween C1 and C2, and the maximum amount of rescue teams you can possibly gather.
All the numbers in a line must be separated by exactly one space, and there is no extra space allowed at the end of a line.
*/
#include<iostream>
#include<vector>

using namespace std;

int main(){
    return 0;
}

/*
input example:
5 6 0 2
1 2 1 5 3
0 1 1
0 2 2
0 3 1
1 2 1
2 4 1
3 4 1
output example:
2 4

*/