#include<iostream>
using namespace std;
const int maxn = 101;
struct heap{
    int data[maxn];     // 节点数据存放, 从1开始
    int n;              // 节点数
};
int n=10, a[10] = {85, 55, 82, 57, 68, 92, 99, 98, 66, 56};
// 初始化（返回）一个特定堆
heap init_heap(int n, int a[]);
// 向下调整, rid是待调整节点的编号
void downAdjust(int rid);
// 建堆, 从最后一个非叶节点开始向下调整得到符合定义的堆
void adjustHeap();
// 删除堆顶元素, 具体做法是把堆顶元素与堆尾元素交换, 再对堆顶元素进行向下调整
void deleteTop();
// 向上调整，只与父节点比较即可, 相对于向下调整情况更简单
void upAdjust(int rid);
// 插入元素时总是附在末尾，再向上调整
void insert(int val);
// 堆排序, 也即不断的删除堆顶元素(不断使最大的元素调到末尾)
void heapSort();

heap dyheap = init_heap(10, a);
/*功能辅助函数*/
void swapVal(int &x, int &y){
    int tmp = x;
    x = y;
    y = tmp;
}

void info(){
    for(int i=1; i<=dyheap.n; i++)
        cout << dyheap.data[i] << " ";
    cout << endl;
}

int main(){
    adjustHeap();
    info();
    insert(60);
    info();
    insert(32);
    info();
    insert(100);
    info();
    insert(95);
    info();
    insert(80);
    info();
    return 0;
}

heap init_heap(int n, int a[]){
    heap h;
    h.n = n;
    for(int i=0; i<h.n; i++)
        h.data[i+1] = a[i];
    return h;
}

void downAdjust(int rid){
    // rid是待调整节点编号, 向下调整意味着向下看，也即与左右孩子作比较, 因此若为叶节点就跳过
    int lastNotLeaf = dyheap.n / 2;     // 最后一个非叶节点编号
    if (rid > lastNotLeaf) return ;     // 叶节点不需要调整
    while(rid <= lastNotLeaf){  // 注意这是一个调整路径, 路径上的节点必有左孩子但不一定有右孩子
        // 因此需要在考虑是否有右孩子的情况下比较出最大者，决定是否调整以及调整的节点
        int lch = 2*rid, rch = 2*rid+1, nxtrid;
        if(rch <= dyheap.n){    // 节点有两个孩子
            if (dyheap.data[rid] > dyheap.data[lch] && dyheap.data[rid] > dyheap.data[rch])
                return ;  // 根节点最大无需调整
            if (dyheap.data[lch] > dyheap.data[rid] && dyheap.data[lch] > dyheap.data[rch])
                nxtrid = lch;   // 左孩子最大
            if (dyheap.data[rch] > dyheap.data[rid] && dyheap.data[rch] > dyheap.data[lch])
                nxtrid = rch;   // 右孩子最大
            swapVal(dyheap.data[rid], dyheap.data[nxtrid]); // 交换之
            rid = nxtrid;   // 进行下一步调整
        }else{  // 只有一个左孩子
            if (dyheap.data[lch] > dyheap.data[rid])
                swapVal(dyheap.data[rid], dyheap.data[lch]);
            return ;
        }

    }
}

void adjustHeap(){
    int lastNotLeaf = dyheap.n / 2;     // 最后一个非叶节点编号
    for (int i=lastNotLeaf; i>=1; i--)
        downAdjust(i);
}

void deleteTop(){
    swapVal(dyheap.data[1], dyheap.data[dyheap.n]);
    dyheap.n -= 1;
    downAdjust(1);
}

void upAdjust(int rid){
    // 先排除基本情况: 堆包含不超过1个节点, 被调整节点为根节点, rid不合法
    if (dyheap.n <= 1 || rid <= 1 || rid > dyheap.n) return;
    while(rid > 1){
        // 无论rid是左孩子还是右孩子, rid/2 必为父节点, 是原最大节点, 若发生交换, 换下去后成为所在子树新的最大节点
        int parent = rid/2;
        if (dyheap.data[rid] > dyheap.data[parent])
            swapVal(dyheap.data[rid], dyheap.data[parent]);
        else return;
        rid = parent;
    }
}

void insert(int val){
    dyheap.n++;
    dyheap.data[dyheap.n] = val;
    upAdjust(dyheap.n);
}

void heapSort(){
    for(int i=1; i<n; i++)
        deleteTop();
}

/*
n = 10, n/2=5, data[5]=68
           85
      55        82
  57     68   92 99
98 66  56

85 55 82 57 68 92 99 98 68 56
85 55 82 57 68 92 99 98 68 56
85 55 99 98 68 82 92 57 68 56
85 55 82 57 68 92 99 98 68 56

*/