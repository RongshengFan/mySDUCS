//#include <sstream>
//#include <string>
//#include<cstring>
//#include<iostream>
//#include<queue>
//using namespace std;
///*ʹ���ڽ�����������ݴ洢*/
//
///******ʵ����С�Ѳ���*******/
////�ı�һά����ĳ���
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
////�쳣��
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
////��С��
//template<class T>
//class minHeap
//{
//public:
//	minHeap(int initcapacility = 10);
//	//~minheap() { delete[]heap; }//��Ҫ����
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
//{//���캯��
//	arraylength = initialcapacity + 1;
//	heap = new T[arraylength];
//	heapsize = 0;
//}
////ɾ��
//template<class T>
//void minHeap<T>::pop()
//{
//	//ɾ�����Ԫ��
//	heap[1].~T();
//
//	//ɾ�����һ��Ԫ��Ȼ�����½���
//	T lastelement = heap[heapsize--];
//	//ΪԪ��rootelementѰ��λ��
//	int currentnode = 1, child = 2;
//	while (child <= heapsize)
//	{
//		//heap[child]Ӧ���ֵ��н�С��
//		if (child < heapsize && heap[child] > heap[child + 1])
//			child++;
//		//���԰�Ԫ�ط���heap[currentnode]��
//		if (lastelement <= heap[child])
//			break;//����
//		//������
//		heap[currentnode] = heap[child];//�Ѻ���������
//		currentnode = child;            //�Ƶ���һ��
//		child *= 2;
//	}
//	heap[currentnode] = lastelement;//����
//}
//template<class T>
//void minHeap<T>::push(const T& theelement)
//{
//	//����
//	if (heapsize == arraylength - 1)
//	{
//		changelength1d(heap, arraylength, 2 * arraylength);
//		arraylength *= 2;
//	}
//	//ΪԪ��Ѱ�Ҳ���λ��
//	//currentnode����Ҷ�������ƶ�
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
//	//�ѻ�
//	for (int root = heapsize / 2; root >= 1; root--)
//	{
//		T rootelement = heap[root];
//		//ΪԪ��rootelementѰ��λ��
//		int child = 2 * root;//���ӵ�˫����Ԫ��rootelement��λ��
//		while (child <= heapsize)
//		{
//			//heap[child]Ӧ���ֵ��н�С��
//			if (child < heapsize && heap[child] > heap[child + 1])
//				child++;
//			//���԰�Ԫ�ط���heap[child/2]��
//			if (rootelement <= heap[child])
//				break;//����
//			//������
//			heap[child / 2] = heap[child];//�Ѻ���������
//			child *= 2;                   //�Ƶ���һ��
//		}
//		heap[child / 2] = rootelement;//����
//	}
//}
///**********ʵ�ֱ߼��Ľṹ�岿��**********/
//struct wEdge {//��ߵĽṹ��
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
//bool reach[200002];   //��������������������ڽӶ���
//
////ʵ����ʽ����ͼ��
//template<class T>
//class Digraph
//{
//protected:
//	int Vnum;                          //������
//	int Enum;                          //����
//	vector<wEdge> aList[200002];       //�ڽӾ���
//public:
//	Digraph(int n, int m) {
//		Vnum = n;
//		Enum = m;
//	}
//	~Digraph() {}
//
//	void insertEdge(int v1, int v2, int w) {//�����
//		wEdge e1{ v1,w };
//		wEdge e2{ v2,w };
//		aList[v2].push_back(e1);
//		aList[v1].push_back(e2);
//	}
//	void Prim() {
//		long long sum = 0;
//		minHeap<wEdge>heap; 
//		int size = aList[1].size();//��һ������ĳ���
//		reach[1] = false;//��ʱ��ǣ���ʾ�Ѿ�ѡ�� 
//
//		//�г�ѡ��ڵ�����бߣ�������С��
//		for (int i = 0; i < size; ++i)
//		{
//			int v, w;
//			v = aList[1][i].v;
//			w = aList[1][i].w;
//			wEdge t(v, w);//��ʱ�ṹ��
//			heap.push(t);
//		}
//
//		//�ҳ��ϱ������ı���Ȩֵ��С�� 
//		for (int i = 1; i < Vnum; i++)
//		{
//			int minW, theV;
//			while (reach[heap.top().v] == false)
//			{//���飬�����ǰ��С����СԪ����ָ��Ľ����붥���Ѿ���false�������Ѿ������ˣ� 
//				heap.pop();//���������pop�� 
//			}
//			//������СȨֵ������ָ��Ķ��� 
//			minW = heap.top().w;
//			theV = heap.top().v;
//			heap.pop();
//			//���½��
//			sum += minW;
//			reach[theV] = false;//���¶���״̬ 
//			size = aList[theV].size();
//			for (int j = 0; j < size; j++)
//			{//�����¼���Ķ�����ڱ� 
//				int v = aList[theV][j].v, w = aList[theV][j].w;
//				if (reach[v])
//				{//����õ�δ������㼯
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
//	for (int i = 0; i < m; i++) //������m������
//	{
//		int v1, v2, w;
//		cin >> v1 >> v2 >> w;
//		a.insertEdge(v1, v2, w);
//	}
//	for (int i = 0; i <= n; i++) {//��ʼ����������
//		reach[i] = true;
//	}
//	a.Prim();
//	return 0;
//}