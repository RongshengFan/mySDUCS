//#include<iostream>
//#include<sstream>
//using namespace std;
////改变一维数组的长度
//template<class T>
//void changeLength1D(T*& a, int oldLength, int newLength)
//{
//	if (newLength < 0)
//	{
//		throw logic_error("new length must be >= 0");
//	}
//	T* temp = new T[newLength];
//	int n = min(oldLength, newLength);
//	copy(a, a + n, temp);
//	delete[]a;
//	a = temp;
//}
////异常类
//class queueEmpty
//{
//public:
//	queueEmpty(string theMessage =
//		"Invalid operation on empty queue")
//	{
//		message = theMessage;
//	}
//	void outputMessage() { cout << message << endl; }
//private:
//	string message;
//};
////最小堆
//template<class T>
//class minHeap
//{
//public:
//	minHeap(int initCapacility=10);
//	//~minHeap() { delete[]heap; }//不要析构
//	bool empty()const { return heapSize == 0; }
//	int size()const { return heapSize; }
//	const T& top()
//	{
//		if (heapSize == 0)
//			throw queueEmpty();
//		return heap[1];
//	}
//	void pop();
//	void push(const T&);
//	void initialize(T*, int);
//	void sorted(T a[], int n);
//	void deactivateArray()
//	{
//		heap = NULL; heapSize = arrayLength = 0;
//	}
//private:
//	T* heap;
//	int heapSize;
//	int arrayLength;
//};
//template<class T>
//minHeap<T>::minHeap(int initialCapacity)
//{//构造函数
//	arrayLength = initialCapacity + 1;
//	heap = new T[arrayLength];
//	heapSize = 0;
//}
////删除
//template<class T>
//void minHeap<T>::pop()
//{
//	//删除最大元素
//	heap[1].~T();
//
//	//删除最后一个元素然后重新建堆
//	T lastElement = heap[heapSize--];
//	//为元素rootElement寻找位置
//	int currentNode = 1, child = 2;
//	while (child <= heapSize)
//	{
//		//heap[child]应是兄弟中较小者
//		if (child < heapSize && heap[child] > heap[child + 1])
//			child++;
//		//可以把元素放在heap[currentNode]中
//		if (lastElement <= heap[child])
//			break;//可以
//		//不可以
//		heap[currentNode] = heap[child];//把孩子向上移
//		currentNode = child;            //移到下一层
//		child *= 2;
//	}
//	heap[currentNode] = lastElement;//插入
//}
//template<class T>
//void minHeap<T>::push(const T& theElement)
//{
//	//扩容
//	if (heapSize == arrayLength - 1)
//	{
//		changeLength1D(heap, arrayLength, 2 * arrayLength);
//		arrayLength *= 2;
//	}
//	//为元素寻找插入位置
//	//currentNode从新叶子向上移动
//	int currentNode = ++heapSize;
//	while (currentNode != 1 && heap[currentNode / 2] > theElement)
//	{
//		heap[currentNode] = heap[currentNode / 2];
//		currentNode /= 2;
//	}
//	heap[currentNode] = theElement;
//}
//template<class T>
//void minHeap<T>::initialize(T* theHeap, int theSize)
//{
//	delete[]heap;
//	heap = theHeap;
//	heapSize = theSize;
//
//	//堆化
//	for (int root = heapSize / 2; root >= 1; root--)
//	{
//		T rootElement = heap[root];
//		//为元素rootElement寻找位置
//		int child = 2 * root;//孩子的双亲是元素rootElement的位置
//		while (child <= heapSize)
//		{
//			//heap[child]应是兄弟中较小者
//			if (child < heapSize && heap[child] > heap[child + 1])
//				child++;
//			//可以把元素放在heap[child/2]中
//			if (rootElement <= heap[child])
//				break;//可以
//			//不可以
//			heap[child / 2] = heap[child];//把孩子向上移
//			child *= 2;                   //移到下一层
//		}
//		heap[child / 2] = rootElement;//插入
//	}
//}
////排序
//template<class T>
//void minHeap<T>::sorted(T a[], int n) {
//	initialize(a, n);
//	for (int i = n ; i >= 1; i--) {
//		cout << heap[1] << " ";
//		pop();
//	}
//	cout << endl;
//}
//
//int main()
//{
//	int n;
//	cin >> n;
//	int *a=new int[n+1];
//	a[0] = 0;
//	int m,k;
//	minHeap<int> heap(1);
//	for (int i = 1; i <= n; i++)
//	{
//		cin >> a[i];
//		heap.push(a[i]);
//	}
//	//heap.initialize(a, n);
//	cout << heap.top() << endl;
//	cin >> m;
//	for (int i = 0; i < m; i++)
//	{
//		cin >> k;
//		switch (k)
//		{
//		case 1://插入
//			int num;
//			cin >> num;
//			heap.push(num);
//			cout << heap.top() << endl;
//			break;
//		case 2://删除
//			heap.pop();
//			cout << heap.top() << endl;
//			break;
//		case 3://排序
//			int x;
//			cin >> x;
//			int *b=new int[x + 1];
//			b[0] = 0;
//			for (int i = 1; i <= x; i++)
//				cin >> b[i];
//			heap.sorted(b, x);
//			delete[]b;
//			break;
//		}
//		
//	}
//	delete[]a;
//	return 0;
//}
