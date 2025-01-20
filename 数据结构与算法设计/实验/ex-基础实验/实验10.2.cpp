//#include <iostream>
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
//// ����������ڵ㣬ģ�¶������ڵ㶨��
//template <class T>
//struct huffmanNode {
//	T weight;   //Ȩ��
//	huffmanNode* leftchild, * rightchild;//���ӣ��Һ���
//	huffmanNode() {}
//	huffmanNode(T w) {
//		weight = w;
//		rightchild = leftchild = NULL;
//	}
//	huffmanNode(T w, huffmanNode* r, huffmanNode* l) {
//		weight = w;
//		rightchild = r;
//		leftchild = l;
//	}
//};
//template <class T>
//class huffmanTree {
//public:
//	huffmanTree(int initCapacity=10); // ���캯��
//	~huffmanTree() { delete[]heap; }; // ��������
//	void initialize(T* theHeap, int n); // ��ʼ���������������
//	huffmanNode<T>* top() { // ����С���ѵĶѶ�Ԫ��
//		return heap[1];
//	}
//	void push(huffmanNode<T>* theElement); // ����
//	void pop(); // ɾ��
//	T length(huffmanNode<T>* t, int n);// ���м��㳤��
//private:
//	huffmanNode<T>** heap; // ����һ��ָ��С����
//	int arrayLength;  //����
//	int heapSize; // С���ѵĳ���
//};
//// ���캯��
//template <class T>
//huffmanTree<T>::huffmanTree(int initCapacity) {
//	arrayLength = initCapacity;// ���峤��
//	heapSize = 0; 
//	heap = new huffmanNode<T> *[27];//��26����ĸ�����Ǵ�heap[1]��ʼ
//	
//}
//// С���ѳ�ʼ��
//template <class T>
//void huffmanTree<T>::initialize(T* theHeap,int n) {
//	// Ϊheap[i]��ֵ
//	for (int i = 1; i <= n; i++) { 
//		heap[i] = new huffmanNode<T>(theHeap[i - 1]);
//	}
//	heapSize = n;
//	//�ѻ�
//	for (int root = heapSize / 2; root >= 1; root--) {
//		huffmanNode<T>* theElement = heap[root];
//		int child = root * 2;
//		while (child <= heapSize) {
//			if (child < heapSize && heap[child]->weight > heap[child + 1]->weight) {
//				child++;
//			}
//			if (theElement->weight <= heap[child]->weight) {
//				break;
//			}
//			heap[child / 2] = heap[child];
//			child *= 2;
//		}
//		heap[child / 2] = theElement;
//	}
//	//��һ�Ż�������
//	while (heapSize != 1) {
//		//��ȡ�������������
//		huffmanNode<T>* x = top();pop();
//		huffmanNode<T>* y = top();pop();
//		//�ϲ���һ����
//		huffmanNode<T>* z = new huffmanNode<T>(x->weight + y->weight, x, y);
//		push(z);
//	}
//}
//// С���Ѳ���
//template <class T>
//void huffmanTree<T>::push(huffmanNode<T>* theElement) {
//		//����
//		if (heapSize == arrayLength - 1)
//		{
//			changeLength1D(heap, arrayLength, 2 * arrayLength);
//			arrayLength *= 2;
//		}
//		//ΪԪ��Ѱ�Ҳ���λ��
//		//currentNode����Ҷ�������ƶ�
//		int currentNode = ++heapSize;
//		while (currentNode != 1 && heap[currentNode / 2]->weight > theElement->weight)
//		{
//			heap[currentNode] = heap[currentNode / 2];
//			currentNode /= 2;
//		}
//		heap[currentNode] = theElement;
//}
//// С����ɾ��
//template <class T>
//void huffmanTree<T>::pop() {
//	//ɾ�����Ԫ��
//	//ɾ�����һ��Ԫ��Ȼ�����½���
//	huffmanNode<T>* lastElement = heap[heapSize--];
//	//ΪԪ��rootElementѰ��λ��
//	int currentNode = 1, child = 2;
//	while (child <= heapSize)
//	{
//		//heap[child]Ӧ���ֵ��н�С��
//		if (child < heapSize && heap[child]->weight > heap[child + 1]->weight)
//			child++;
//		//���԰�Ԫ�ط���heap[currentNode]��
//		if (lastElement->weight <= heap[child]->weight)
//			break;//����
//		//������
//		heap[currentNode] = heap[child];//�Ѻ���������
//		currentNode = child;            //�Ƶ���һ��
//		child *= 2;
//	}
//	heap[currentNode] = lastElement;//����
//}
//
//// ���㳤��
//template <class T>
//T huffmanTree<T>::length(huffmanNode<T>* t, int n) {
//	int sum = 0;
//	if (t != NULL) {
//		if (t->rightchild == NULL && t->leftchild == NULL) { // �ж��Ƿ�Ϊ�ⲿ�ڵ㣬���ⲿ�ڵ�����㳤��
//			sum += n * t->weight;  // ���ȵ���weight * ��������Ϊ0�㣩
//		}
//		// ʹ�õݹ�������Һ���
//		sum += length(t->leftchild, n + 1);
//		sum += length(t->rightchild, n + 1);
//	}
//	return sum;
//
//}
//int main() {
//
//	string s;
//	cin >> s;
//	int n = 0;
//
//	int a[26] = { 0 }; // ��ʼ��a,26����ĸ
//
//	for (int i = 0; i < s.length(); i++) {
//		a[s[i] - 'a']++;//������ĸ���ֵ�Ƶ��
//	}
//
//	int b[26]; // ���ֵ���ĸ������b��
//	for (int i = 0; i < 26; i++) {
//		if (a[i] != 0) {
//			b[n] = a[i];
//			n++;
//		}
//	}
//
//	huffmanTree<int> h(10);
//	h.initialize(b,n);
//
//	cout << h.length(h.top(), 0) << endl;
//	return 0;
//}