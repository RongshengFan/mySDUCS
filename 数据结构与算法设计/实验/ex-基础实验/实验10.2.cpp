//#include <iostream>
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
//// 定义哈夫曼节点，模仿二叉树节点定义
//template <class T>
//struct huffmanNode {
//	T weight;   //权重
//	huffmanNode* leftchild, * rightchild;//左孩子，右孩子
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
//	huffmanTree(int initCapacity=10); // 构造函数
//	~huffmanTree() { delete[]heap; }; // 析构函数
//	void initialize(T* theHeap, int n); // 初始化，构造霍夫曼树
//	huffmanNode<T>* top() { // 返回小根堆的堆顶元素
//		return heap[1];
//	}
//	void push(huffmanNode<T>* theElement); // 插入
//	void pop(); // 删除
//	T length(huffmanNode<T>* t, int n);// 进行计算长度
//private:
//	huffmanNode<T>** heap; // 定义一个指针小根堆
//	int arrayLength;  //容量
//	int heapSize; // 小根堆的长度
//};
//// 构造函数
//template <class T>
//huffmanTree<T>::huffmanTree(int initCapacity) {
//	arrayLength = initCapacity;// 定义长度
//	heapSize = 0; 
//	heap = new huffmanNode<T> *[27];//有26个字母，但是从heap[1]开始
//	
//}
//// 小根堆初始化
//template <class T>
//void huffmanTree<T>::initialize(T* theHeap,int n) {
//	// 为heap[i]赋值
//	for (int i = 1; i <= n; i++) { 
//		heap[i] = new huffmanNode<T>(theHeap[i - 1]);
//	}
//	heapSize = n;
//	//堆化
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
//	//造一颗霍夫曼树
//	while (heapSize != 1) {
//		//先取出最轻的两棵树
//		huffmanNode<T>* x = top();pop();
//		huffmanNode<T>* y = top();pop();
//		//合并成一棵树
//		huffmanNode<T>* z = new huffmanNode<T>(x->weight + y->weight, x, y);
//		push(z);
//	}
//}
//// 小根堆插入
//template <class T>
//void huffmanTree<T>::push(huffmanNode<T>* theElement) {
//		//扩容
//		if (heapSize == arrayLength - 1)
//		{
//			changeLength1D(heap, arrayLength, 2 * arrayLength);
//			arrayLength *= 2;
//		}
//		//为元素寻找插入位置
//		//currentNode从新叶子向上移动
//		int currentNode = ++heapSize;
//		while (currentNode != 1 && heap[currentNode / 2]->weight > theElement->weight)
//		{
//			heap[currentNode] = heap[currentNode / 2];
//			currentNode /= 2;
//		}
//		heap[currentNode] = theElement;
//}
//// 小根堆删除
//template <class T>
//void huffmanTree<T>::pop() {
//	//删除最大元素
//	//删除最后一个元素然后重新建堆
//	huffmanNode<T>* lastElement = heap[heapSize--];
//	//为元素rootElement寻找位置
//	int currentNode = 1, child = 2;
//	while (child <= heapSize)
//	{
//		//heap[child]应是兄弟中较小者
//		if (child < heapSize && heap[child]->weight > heap[child + 1]->weight)
//			child++;
//		//可以把元素放在heap[currentNode]中
//		if (lastElement->weight <= heap[child]->weight)
//			break;//可以
//		//不可以
//		heap[currentNode] = heap[child];//把孩子向上移
//		currentNode = child;            //移到下一层
//		child *= 2;
//	}
//	heap[currentNode] = lastElement;//插入
//}
//
//// 计算长度
//template <class T>
//T huffmanTree<T>::length(huffmanNode<T>* t, int n) {
//	int sum = 0;
//	if (t != NULL) {
//		if (t->rightchild == NULL && t->leftchild == NULL) { // 判断是否为外部节点，是外部节点则计算长度
//			sum += n * t->weight;  // 长度等于weight * 层数（根为0层）
//		}
//		// 使用递归计算左右孩子
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
//	int a[26] = { 0 }; // 初始化a,26个字母
//
//	for (int i = 0; i < s.length(); i++) {
//		a[s[i] - 'a']++;//存下字母出现的频率
//	}
//
//	int b[26]; // 出现的字母储存在b中
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