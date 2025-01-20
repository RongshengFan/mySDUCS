//#include <sstream>
//#include <string>
//#include<cstring>
//#include<iostream>
//#include<queue>
//using namespace std;
///*使用邻接数组进行数据存储*/
//
///******实现最小堆部分*******/
////改变一维数组的长度
//template<class T>
//void changelength1d(T*& a, int oldlength, int newlength)
//{
//	if (newlength < 0)
//	{
//		throw logic_error("new length must be >= 0");
//	}
//	T* temp = new T[newlength];
//	int n = min(oldlength, newlength);
//	copy(a, a + n, temp);
//	delete[]a;
//	a = temp;
//}
////异常类
//class queueEmpty
//{
//public:
//	queueEmpty(string themessage =
//		"invalid operation on empty queue")
//	{
//		message = themessage;
//	}
//	void outputmessage() { cout << message << endl; }
//private:
//	string message;
//};
////最小堆
//template<class T>
//class minHeap
//{
//public:
//	minHeap(int initcapacility = 10);
//	//~minheap() { delete[]heap; }//不要析构
//	bool empty()const { return heapsize == 0; }
//	int size()const { return heapsize; }
//	const T& top()
//	{
//		if (heapsize == 0)
//			throw queueEmpty();
//		return heap[1];
//	}
//	void pop();
//	void push(const T&);
//	void initialize(T*, int);
//private:
//	T* heap;
//	int heapsize;
//	int arraylength;
//};
//template<class T>
//minHeap<T>::minHeap(int initialcapacity)
//{//构造函数
//	arraylength = initialcapacity + 1;
//	heap = new T[arraylength];
//	heapsize = 0;
//}
////删除
//template<class T>
//void minHeap<T>::pop()
//{
//	//删除最大元素
//	heap[1].~T();
//
//	//删除最后一个元素然后重新建堆
//	T lastelement = heap[heapsize--];
//	//为元素rootelement寻找位置
//	int currentnode = 1, child = 2;
//	while (child <= heapsize)
//	{
//		//heap[child]应是兄弟中较小者
//		if (child < heapsize && heap[child] > heap[child + 1])
//			child++;
//		//可以把元素放在heap[currentnode]中
//		if (lastelement <= heap[child])
//			break;//可以
//		//不可以
//		heap[currentnode] = heap[child];//把孩子向上移
//		currentnode = child;            //移到下一层
//		child *= 2;
//	}
//	heap[currentnode] = lastelement;//插入
//}
//template<class T>
//void minHeap<T>::push(const T& theelement)
//{
//	//扩容
//	if (heapsize == arraylength - 1)
//	{
//		changelength1d(heap, arraylength, 2 * arraylength);
//		arraylength *= 2;
//	}
//	//为元素寻找插入位置
//	//currentnode从新叶子向上移动
//	int currentnode = ++heapsize;
//	while (currentnode != 1 && heap[currentnode / 2] > theelement)
//	{
//		heap[currentnode] = heap[currentnode / 2];
//		currentnode /= 2;
//	}
//	heap[currentnode] = theelement;
//}
//template<class T>
//void minHeap<T>::initialize(T* theheap, int thesize)
//{
//	delete[]heap;
//	heap = theheap;
//	heapsize = thesize;
//
//	//堆化
//	for (int root = heapsize / 2; root >= 1; root--)
//	{
//		T rootelement = heap[root];
//		//为元素rootelement寻找位置
//		int child = 2 * root;//孩子的双亲是元素rootelement的位置
//		while (child <= heapsize)
//		{
//			//heap[child]应是兄弟中较小者
//			if (child < heapsize && heap[child] > heap[child + 1])
//				child++;
//			//可以把元素放在heap[child/2]中
//			if (rootelement <= heap[child])
//				break;//可以
//			//不可以
//			heap[child / 2] = heap[child];//把孩子向上移
//			child *= 2;                   //移到下一层
//		}
//		heap[child / 2] = rootelement;//插入
//	}
//}
///**********实现边集的结构体部分**********/
//struct wEdge {//存边的结构体
//	long long v;
//	long long w;
//	wEdge() {};
//	wEdge(long long theV, long long theW) {
//		v = theV;
//		w = theW;
//	}
//	bool operator < (const wEdge& b) const
//	{
//		return w < b.w;
//	}
//	bool operator <= (const wEdge& b) const
//	{
//		return w <= b.w;
//	}
//	bool operator > (const wEdge& b) const
//	{
//		return w > b.w;
//	}
//	bool operator !=(const wEdge& b)const
//	{
//		return v != b.v;
//	}
//};
//bool reach[200002];   //访问数组用来标记所有邻接顶点
//
////实现链式无向图类
//template<class T>
//class Digraph
//{
//protected:
//	int Vnum;                          //顶点数
//	int Enum;                          //边数
//	vector<wEdge> aList[200002];       //邻接矩阵
//public:
//	Digraph(int n, int m) {
//		Vnum = n;
//		Enum = m;
//	}
//	~Digraph() {}
//
//	void insertEdge(int v1, int v2, int w) {//插入边
//		wEdge e1{ v1,w };
//		wEdge e2{ v2,w };
//		aList[v2].push_back(e1);
//		aList[v1].push_back(e2);
//	}
//	void Prim() {
//		long long sum = 0;
//		minHeap<wEdge>heap; 
//		int size = aList[1].size();//第一个数组的长度
//		reach[1] = false;//及时标记，表示已经选入 
//
//		//列出选入节点的所有边，存入最小堆
//		for (int i = 0; i < size; ++i)
//		{
//			int v, w;
//			v = aList[1][i].v;
//			w = aList[1][i].w;
//			wEdge t(v, w);//临时结构体
//			heap.push(t);
//		}
//
//		//找出上边挑出的边中权值最小的 
//		for (int i = 1; i < Vnum; i++)
//		{
//			int minW, theV;
//			while (reach[heap.top().v] == false)
//			{//检验，如果当前最小堆最小元素所指向的将插入顶点已经是false（就是已经加入了） 
//				heap.pop();//把相关数据pop掉 
//			}
//			//挑出最小权值，和它指向的顶点 
//			minW = heap.top().w;
//			theV = heap.top().v;
//			heap.pop();
//			//更新结果
//			sum += minW;
//			reach[theV] = false;//更新顶点状态 
//			size = aList[theV].size();
//			for (int j = 0; j < size; j++)
//			{//遍历新加入的顶点的邻边 
//				int v = aList[theV][j].v, w = aList[theV][j].w;
//				if (reach[v])
//				{//如果该点未被加入点集
//					wEdge t(v, w);
//					heap.push(t);
//				}
//			}
//		}
//		cout << sum << endl;
//	}
//};
//int main() {
//	int n, m;
//	cin >> n >> m;
//	Digraph<int> a(n, m);
//	for (int i = 0; i < m; i++) //接下来m行输入
//	{
//		int v1, v2, w;
//		cin >> v1 >> v2 >> w;
//		a.insertEdge(v1, v2, w);
//	}
//	for (int i = 0; i <= n; i++) {//初始化访问数组
//		reach[i] = true;
//	}
//	a.Prim();
//	return 0;
//}