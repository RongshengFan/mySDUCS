//#include<iostream>
//#include <sstream>
//#include <iterator>
//using namespace std;
////链表的结构节点定义
//template<class T>
//struct chainNode
//{
//	T element;
//	chainNode<T>* next;
//
//	chainNode() {};
//	chainNode(const T& element)
//	{
//		this->element = element;
//	}
//	chainNode(const T& element, chainNode<T>* next)
//	{
//		this->element = element;
//		this->next = next;
//	}
//};
////链表的定义
////有些功能不需要，因此删除，否则篇幅过长
//template <class T>
//class chain
//{
//public:
//	chain(int initialCapacity = 10);
//	~chain();
//	void insert(int theIndex, const T& theElement);
//	int sum();
//	void merge(chain<T>& a, chain<T>& b);
//
//public:
//	class iterator
//	{
//	public:
//		//构造函数
//		iterator(chainNode<T>* theNode = NULL)
//		{
//			node = theNode;
//		}
//		//解引用操作符
//		T& operator*() const { return node->element; }
//		T* operator->() const { return &node->element; }
//		//迭代器加法操作 不能operator--
//		iterator& operator++() //前加
//		{
//			node = node->next;
//			return *this;
//		}
//		iterator operator++(int) //后加
//		{
//			iterator old = *this;
//			node = node->next;
//			return old;
//		}
//		//相等检验
//		bool operator!=(const iterator right) const
//		{
//			return node != right.node;
//		}
//		bool operator==(const iterator right) const
//		{
//			return node == right.node;
//		}
//	protected:
//		chainNode<T>* node;
//	};
//	iterator begin() { return iterator(firstNode); }
//	iterator end() { return iterator(NULL); }
//protected:
//	void checkIndex(int theIndex)const;
//	chainNode<T>* firstNode;
//	int listSize;
//};
//
////构造函数
//template<class T>
//chain<T>::chain(int initialCapacity)
//{
//	/*if (initialCapacity < 1)
//	{
//		ostringstream s;
//		s << "initial capacity = " << initialCapacity << " must be > 0";
//		throw logic_error(s.str());
//	}*/
//	firstNode = NULL;
//	listSize = 0;
//}
////析构函数
//template<class T>
//chain<T>::~chain()
//{
//	while (firstNode != NULL)
//	{
//		chainNode<T>* nextNode = firstNode->next;
//		delete firstNode;
//		firstNode = nextNode;
//	}
//}
//
////在索引为theIndex插入元素theElement
//template<class T>
//void chain<T>::insert(int theIndex, const T& theElement)
//{
//	checkIndex(theIndex);
//	if (theIndex == 0)
//	{
//		firstNode = new chainNode<T>(theElement, firstNode);
//	}
//	else
//	{
//		chainNode<T>* p = firstNode;
//		for (int i = 0; i < theIndex - 1; i++)
//		{
//			p = p->next;
//		}
//		p->next = new chainNode<T>(theElement, p->next);
//	}
//	listSize++;
//}
////计算链表节点索引值与节点值的异或和
//template<class T>
//int chain<T>::sum()
//{
//	int s = 0, i = 0;
//	iterator it = begin();
//	while (i < listSize)
//	{
//		s += i ^ (*it);
//		it++;
//		i++;
//	}
//	return s;
//}
////检查索引值是否有效，无效则抛出异常
//template<class T>
//void chain<T>::checkIndex(int theIndex) const
//{
//	if (theIndex<0 || theIndex>listSize)
//	{
//		ostringstream s;
//		s << "index = " << theIndex << " size = " << listSize;
//		throw logic_error(s.str());
//	}
//}
////将链表赋值为两个链表的有序连接
//template<class T>
//void chain<T>::merge(chain<T>& a, chain<T>& b)
//{
//	//使用迭代器
//	iterator itA = a.begin();
//	iterator itB = b.begin();
//	int len = a.listSize + b.listSize;
//	//遍历长度为两链表长度之和
//	for (int i = 0; i < len;)
//	{
//		//当链表a遍历完时，只插入b链表元素
//		if (itA == NULL)
//		{
//			insert(i, *itB);
//			i++;
//			itB++;
//			continue;
//		}
//		//当链表b遍历完时，只插入a链表元素
//		if (itB == NULL)
//		{
//			insert(i, *itA);
//			i++;
//			itA++;
//			continue;
//		}
//		//当a节点元素值小于b节点元素值时
//		if ((*itA) < (*itB))
//		{
//			insert(i, *itA);
//			i++;
//			itA++;
//		}
//		//当b节点元素值小于a节点元素值时
//		else if ((*itA) > (*itB))
//		{
//			insert(i, *itB);
//			i++;
//			itB++;
//		}
//		//当a节点元素值等于b节点元素值时,依次插入
//		else
//		{
//			insert(i, *itA);
//			i++;
//			insert(i, *itB);
//			i++;
//			itA++;
//			itB++;
//		}
//	}
//}
////插入排序
//template<class T>
//void insertionSort(T a[], int n)
//{
//	for (int i = 1; i < n; i++)
//	{
//		int j;
//		T t = a[i];
//		for (j = i - 1; j >= 0 && t < a[j]; j--)
//		{
//			a[j + 1] = a[j];
//		}
//		a[j + 1] = t;
//	}
//}
//
//int main()
//{
//	int  n, m;
//	cin >> n >> m;
//	//创建链表
//	chain<int>a;
//	chain<int>b;
//	chain<int>c;
//
//	int* A = new int[n];//创建数组存储元素，排好序后在放入链表
//	for (int i = 0; i < n; i++) cin >> A[i]; //输入a的节点元素值
//	insertionSort(A,n);         //调用函数，排序
//	for (int i = 0; i < n; i++) a.insert(i, A[i]); //插入各节点
//
//	int* B = new int[m];//创建数组存储元素，排好序后在放入链表
//	for (int i = 0; i < m; i++) cin >> B[i]; //输入b的节点元素值
//	insertionSort(B, m);		//调用函数，排序
//	for (int i = 0; i < m; i++) b.insert(i, B[i]); //插入各节点
//
//	c.merge(a, b);//合并
//
//	cout << a.sum() << endl;
//	cout << b.sum() << endl;
//	cout << c.sum() << endl;
//
//	delete[]A;
//	delete[]B;
//	return 0;
//}