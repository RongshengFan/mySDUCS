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
//template <class T>
//class chain 
//{
//public:
//	chain(int initialCapacity = 10);
//	chain(const chain<T>& theList);
//	~chain();
//
//	bool empty()const { return listSize == 0; }
//	int size()const { return listSize; }
//	T& get(int theIndex)const;
//	int indexOf(const T& theElement)const;
//	void erase(int theIndex);
//	void insert(int theIndex, const T& theElement);
//	void output(ostream& out)const;
//	void reverse();
//	int sum();
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
//
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
//
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
//
//	iterator begin() { return iterator(firstNode); }
//	iterator end() { return iterator(NULL); }
//protected:
//	void checkIndex(int theIndex)const;
//
//	chainNode<T>* firstNode;
//	int listSize;
//};
//
////构造函数
//template<class T>
//chain<T>::chain(int initialCapacity)
//{
//	if (initialCapacity < 1)
//	{
//		ostringstream s;
//		s << "initial capacity = " << initialCapacity << " must be > 0";
//		throw logic_error(s.str());
//	}
//	firstNode = NULL;
//	listSize = 0;
//}
////复制构造函数
//template<class T>
//chain<T>::chain(const chain<T>& theList)
//{
//	listSize = theList.listSize;
//
//	if (listSize = 0)
//	{
//		firstNode = NULL;
//		return;
//	}
//	chainNode<T>* sourceNode = theList.firstNode;
//	firstNode = new chainNode<T>(sourceNode->element);
//	sourceNode = sourceNode->next;
//	chainNode<T>* targetNode = firstNode;
//
//	while (sourceNode != NULL)
//	{
//		targetNode->next = new chainNode<T>(sourceNode->element);
//		targetNode = targetNode->next;
//		sourceNode = sourceNode->next;
//	}
//	targetNode->next = NULL;
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
////返回索引值是theIndex的元素
//template<class T>
//T& chain<T>::get(int theIndex) const
//{
//	checkIndex(theIndex);
//
//	chainNode<T>* currentNode = firstNode;
//	for (int i = 0; i < theIndex; i++)
//	{
//		currentNode = currentNode->next;
//	}
//	return currentNode->element;
//}
////返回元素是theElement首次出现的索引值
//template<class T>
//int chain<T>::indexOf(const T& theElement) const
//{
//	chainNode<T>* currentNode = firstNode;
//	int index = 0;//记录索引值
//	while (currentNode != NULL && currentNode->element != theElement)//遍历查找索引值
//	{
//		currentNode = currentNode->next;
//		index++;
//	}
//	if (currentNode == NULL)
//		return -1;
//	else
//		return index;
//}
////删除索引为theIndex的元素
//template<class T>
//void chain<T>::erase(int theIndex)
//{
//	checkIndex(theIndex);
//	chainNode<T>* deleteNode;//用以记录需删除节点
//	if (theIndex == 0)//删除头结点
//	{
//		deleteNode = firstNode;
//		firstNode = firstNode->next;
//	}
//	else
//	{
//		chainNode<T>* p = firstNode;			//指向要删节点的前驱结点
//		for (int i = 0; i < theIndex - 1; i++)
//		{
//			p = p->next;
//		}
//		deleteNode = p->next; //记下删除节点
//		p->next = p->next->next;
//	}
//	listSize--;
//	delete deleteNode;
//}
////在索引为theIndex插入元素theElement
//template<class T>
//void chain<T>::insert(int theIndex, const T& theElement)
//{
//	checkIndex(theIndex);
//	if (theIndex == 0)//插在头结点
//	{
//		firstNode = new chainNode<T>(theElement, firstNode);
//	}
//	else
//	{
//		chainNode<T>* p = firstNode; 
//		for (int i = 0; i < theIndex - 1; i++)//遍历查找需要插入节点的前驱结点
//		{
//			p = p->next;
//		}
//		p->next = new chainNode<T>(theElement, p->next);
//	}
//	listSize++;
//}
////重载流操作符<<
//template<class T>
//ostream operator<<(ostream& out, const chain<T>& x)
//{
//	x.output(out);
//	return out;
//}
////输出链表
//template<class T>
//void chain<T>::output(ostream& out) const
//{
//	for (chainNode<T>* currentNode = firstNode; currentNode != NULL; currentNode = currentNode->next)
//	{
//		out << currentNode->element << " ";
//	}
//}
////原地实现链表的逆置
//template<class T>
//inline void chain<T>::reverse()
//{
//	if (firstNode == NULL || firstNode->next == NULL)return;//如果为空链表或者单节点，那直接返回
//	chainNode<T>* pastNode = firstNode;				//记录前驱节点
//	chainNode<T>* currentNode = firstNode->next;	//记录当前节点
//	chainNode<T>* nextNode = firstNode->next->next; //记录后驱节点
//	firstNode->next = NULL;							//头结点变尾结点
//	while (nextNode)								//开始遍历，实现逆置
//	{
//		currentNode->next = pastNode;				//前驱节点变后驱节点
//		pastNode = currentNode;						//原前驱结点后移
//		currentNode = nextNode;						//原当前节点后移
//		nextNode = nextNode->next;					//原后驱节点后移
//	}
//	currentNode->next = pastNode;					//前驱节点变后驱节点
//	firstNode = currentNode;						//记下当前节点（原尾结点）为头节点
//}
////计算链表节点索引值与节点值的异或和
//template<class T>
//int chain<T>::sum()
//{
//	int s = 0, i = 0;
//	iterator it = begin();//使用迭代器
//	while (i < listSize)
//	{
//		s += i ^ (*it);
//		it++;
//		i++;
//	}
//	return s;
//}
//
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
////main函数，输入各种操作
//int main()
//{
//	int n, q, m, k;
//	cin >> n >> q;
//	chain<int>a;
//	for (int i = 0; i < n; i++)
//	{
//		cin >> m;
//		a.insert(i, m);
//	}
//	for (int i = 0; i < q; i++)
//	{
//		int idx, val, index;
//		cin >> k;
//		switch (k)
//		{
//		case 1:
//			cin >> idx >> val;
//			a.insert(idx, val);
//			break;
//		case 2:
//			cin >> val;
//			index = a.indexOf(val);
//			if (index == -1)
//				cout << "-1" << endl;
//			else 
//				a.erase(index);
//			break;
//		case 3:
//			a.reverse();
//			break;
//		case 4:
//			cin >> val;
//			cout<<a.indexOf(val)<<endl;
//			break;
//		case 5:
//			cout << a.sum() << endl;
//			break;
//		default:
//			break;
//		}
//	}
//	return 0;
//}