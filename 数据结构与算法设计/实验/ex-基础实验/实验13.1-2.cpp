//#include <sstream>
//#include <string>
//#include<cstring>
//#include<iostream>
//#include<queue>
//using namespace std;
///*使用邻接链表进行数据存储*/
//
///******实现最小堆部分*******/
////改变一维数组的长度
//template<class t>
//void changelength1d(t*& a, int oldlength, int newlength)
//{
//	if (newlength < 0)
//	{
//		throw logic_error("new length must be >= 0");
//	}
//	t* temp = new t[newlength];
//	int n = min(oldlength, newlength);
//	copy(a, a + n, temp);
//	delete[]a;
//	a = temp;
//}
////异常类
//class queueempty
//{
//public:
//	queueempty(string themessage =
//		"invalid operation on empty queue")
//	{
//		message = themessage;
//	}
//	void outputmessage() { cout << message << endl; }
//private:
//	string message;
//};
////最小堆
//template<class t>
//class minheap
//{
//public:
//	minheap(int initcapacility=10);
//	//~minheap() { delete[]heap; }//不要析构
//	bool empty()const { return heapsize == 0; }
//	int size()const { return heapsize; }
//	const t& top()
//	{
//		if (heapsize == 0)
//			throw queueempty();
//		return heap[1];
//	}
//	void pop();
//	void push(const t&);
//	void initialize(t*, int);
//private:
//	t* heap;
//	int heapsize;
//	int arraylength;
//};
//template<class t>
//minheap<t>::minheap(int initialcapacity)
//{//构造函数
//	arraylength = initialcapacity + 1;
//	heap = new t[arraylength];
//	heapsize = 0;
//}
////删除
//template<class t>
//void minheap<t>::pop()
//{
//	//删除最大元素
//	heap[1].~t();
//
//	//删除最后一个元素然后重新建堆
//	t lastelement = heap[heapsize--];
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
//template<class t>
//void minheap<t>::push(const t& theelement)
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
//template<class t>
//void minheap<t>::initialize(t* theheap, int thesize)
//{
//	delete[]heap;
//	heap = theheap;
//	heapsize = thesize;
//
//	//堆化
//	for (int root = heapsize / 2; root >= 1; root--)
//	{
//		t rootelement = heap[root];
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
//struct wEdge {
//	int v;
//	int w;
//	wEdge() {};
//	wEdge(int thev, int thew) {
//		v = thev;
//		w = thew;
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
///************实现邻接链表类部分***************/
////链表的结构节点定义
//template<class t>
//struct chainnode
//{
//	t element;
//	chainnode<t>* next;
//
//	chainnode() {};
//	chainnode(const t& element)
//	{
//		this->element = element;
//	}
//	chainnode(const t& element, chainnode<t>* next)
//	{
//		this->element = element;
//		this->next = next;
//	}
//};
//template <class t>class digraph;
//
////实现扩展后的链表类graphchain
//template <class t>
//class graphchain
//{
//	friend digraph<t>;
//	friend digraph<wEdge>;
//public:
//	chainnode<t>* firstnode;
//	int listsize;
//public:
//	graphchain(int initialcapacity = 10);
//    ~graphchain();
//    void insert(int theindex, const t& theelement);
//};
////构造函数
//template<class t>
//graphchain<t>::graphchain(int initialcapacity)
//{
//	firstnode = null;
//	listsize = 0;
//}
////析构函数
//template<class t>
//graphchain<t>::~graphchain()
//{
//	while (firstnode != null)
//	{
//		chainnode<t>* nextnode = firstnode->next;
//		delete[] firstnode;
//		firstnode = nextnode;
//	}
//}
////在索引为theindex插入元素theelement
//template<class t>
//void graphchain<t>::insert(int theindex, const t& theelement)
//{
//	if (theindex == 0)
//	{
//		firstnode = new chainnode<t>(theelement, firstnode);
//	}
//	else
//	{
//		chainnode<t>* p = firstnode;
//		for (int i = 0; i < theindex - 1; i++)
//		{
//			p = p->next;
//		}
//		p->next = new chainnode<t>(theelement, p->next);
//	}
//	listsize++;
//}
////实现链式无向图类
//template<class t>
//class digraph
//{
//	friend graphchain<wEdge>;
//	friend graphchain<t>;
//	protected:
//		int vnum;                    //顶点数
//		int enum;                    //边数
//		graphchain<wEdge>* alist;    //邻接表
//	public:
//		digraph(int n,int m) {
//			vnum = n;
//			enum = m;
//			alist = new graphchain<wEdge>[vnum + 1];
//		}
//		~digraph() { delete[] alist; }
//		
//		void insertedge(int v1, int v2, int w) {//插入边
//			wEdge t1{ v1,w };
//			wEdge t2{ v2,w };
//			alist[v2].insert(0, t1);
//			alist[v1].insert(0, t2);
//		}
//		void prim() {
//			long long sum = 0;
//			minheap<wEdge>q;
//			reach[1] = false;
//			chainnode<wEdge>* p = alist[1].firstnode;
//			while (p) {
//				wEdge t { p->element.v,p->element.w };
//				q.push(t);
//				p = p->next;
//			}
//			for (int i = 1; i < vnum; i++)
//			{
//				int minweight, thev;
//				while (reach[q.top().v] == false){//检验，如果当前最小堆最小元素所指向的将插入顶点已经是false（就是已经加入了） 
//					q.pop();//把相关数据pop掉 
//				}
//				//得出最小权值，和它指向的顶点 
//				minweight = q.top().w;
//				thev = q.top().v;
//				q.pop();
//				//更新结果
//				sum += minweight;
//				reach[thev] = false;//更新顶点状态 
//				chainnode<wEdge>* p = alist[thev].firstnode;
//				while (p) {
//					if (reach[p->element.v]){//如果该点未被加入点集
//						wEdge t{ p->element.v,p->element.w };
//						q.push(t);
//					}
//					p = p->next;
//				}
//			}
//			cout << sum << endl;
//		}
//};
//int main() {
//	int n, m;
//	cin >> n >> m;
//	digraph<int> a(n,m);
//	for (int i = 0; i < m; i++) //接下来m行输入
//	{
//		int v1, v2, w;
//		cin >> v1 >> v2 >> w;
//		a.insertedge(v1, v2, w);
//	}
//	for (int i = 0; i <= n; i++) {//初始化访问数组
//		reach[i] = true;
//	}
//	a.prim();
//	return 0;
//}