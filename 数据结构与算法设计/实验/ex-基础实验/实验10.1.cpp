//#include<iostream>
//#include<sstream>
//using namespace std;
////�ı�һά����ĳ���
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
////�쳣��
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
////��С��
//template<class T>
//class minHeap
//{
//public:
//	minHeap(int initCapacility=10);
//	//~minHeap() { delete[]heap; }//��Ҫ����
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
//{//���캯��
//	arrayLength = initialCapacity + 1;
//	heap = new T[arrayLength];
//	heapSize = 0;
//}
////ɾ��
//template<class T>
//void minHeap<T>::pop()
//{
//	//ɾ�����Ԫ��
//	heap[1].~T();
//
//	//ɾ�����һ��Ԫ��Ȼ�����½���
//	T lastElement = heap[heapSize--];
//	//ΪԪ��rootElementѰ��λ��
//	int currentNode = 1, child = 2;
//	while (child <= heapSize)
//	{
//		//heap[child]Ӧ���ֵ��н�С��
//		if (child < heapSize && heap[child] > heap[child + 1])
//			child++;
//		//���԰�Ԫ�ط���heap[currentNode]��
//		if (lastElement <= heap[child])
//			break;//����
//		//������
//		heap[currentNode] = heap[child];//�Ѻ���������
//		currentNode = child;            //�Ƶ���һ��
//		child *= 2;
//	}
//	heap[currentNode] = lastElement;//����
//}
//template<class T>
//void minHeap<T>::push(const T& theElement)
//{
//	//����
//	if (heapSize == arrayLength - 1)
//	{
//		changeLength1D(heap, arrayLength, 2 * arrayLength);
//		arrayLength *= 2;
//	}
//	//ΪԪ��Ѱ�Ҳ���λ��
//	//currentNode����Ҷ�������ƶ�
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
//	//�ѻ�
//	for (int root = heapSize / 2; root >= 1; root--)
//	{
//		T rootElement = heap[root];
//		//ΪԪ��rootElementѰ��λ��
//		int child = 2 * root;//���ӵ�˫����Ԫ��rootElement��λ��
//		while (child <= heapSize)
//		{
//			//heap[child]Ӧ���ֵ��н�С��
//			if (child < heapSize && heap[child] > heap[child + 1])
//				child++;
//			//���԰�Ԫ�ط���heap[child/2]��
//			if (rootElement <= heap[child])
//				break;//����
//			//������
//			heap[child / 2] = heap[child];//�Ѻ���������
//			child *= 2;                   //�Ƶ���һ��
//		}
//		heap[child / 2] = rootElement;//����
//	}
//}
////����
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
//		case 1://����
//			int num;
//			cin >> num;
//			heap.push(num);
//			cout << heap.top() << endl;
//			break;
//		case 2://ɾ��
//			heap.pop();
//			cout << heap.top() << endl;
//			break;
//		case 3://����
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
