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