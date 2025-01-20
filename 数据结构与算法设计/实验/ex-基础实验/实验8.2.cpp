//#include<iostream>
//#include<string>
//using namespace std;
////实现链式散列
////将关键字转换为size_t类型非负整数，分别实现string版、int版、long版等
//template<class K>class Hash;
//template<>
//class Hash<string>
//{
//public:
//	size_t operator()(const string theKey) const
//	{
//		unsigned long hashValue = 0;
//		int length = (int)theKey.length();
//		for (int i = 0; i < length; i++)
//			hashValue = 5 * hashValue + theKey.at(i);
//
//		return size_t(hashValue);
//	}
//};
//template<>
//class Hash<int>
//{
//public:
//	size_t operator()(const int theKey)const
//	{
//		return size_t(theKey);
//	}
//};
//template<>
//class Hash<long>
//{
//public:
//	size_t operator()(const long theKey)const
//	{
//		return size_t(theKey);
//	}
//};
////定义一个数对节点
//template <class K, class E>
//struct pairNode
//{
//	typedef pair<const K, E> pairType;
//	pairType element;
//	pairNode<K, E>* next;
//
//	pairNode(const pairType& thePair) :element(thePair) {}
//	pairNode(const pairType& thePair, pairNode<K, E>* theNext)
//		:element(thePair) {
//		next = theNext;
//	}
//};
////定义sortedChain类
//template<class K, class E>
//class sortedChain
//{
//public:
//	sortedChain() { firstNode = NULL; dSize = 0; }
//	~sortedChain();
//
//	bool empty() const { return dSize == 0; }
//	int size() const { return dSize; }
//	pair<const K, E>* find(const K&) const;
//	void erase(const K&);
//	void insert(const pair<const K, E>&);
//	void output(ostream& out) const;
//
//protected:
//	pairNode<K, E>* firstNode; //链表头指针 
//	int dSize;                 //链表节点数
//};
//template<class K, class E>
//sortedChain<K, E>::~sortedChain()
//{// 删除链表各个节点
//	while (firstNode != NULL)
//	{
//		pairNode<K, E>* nextNode = firstNode->next;
//		delete firstNode;
//		firstNode = nextNode;
//	}
//}
//
//template<class K, class E>
//pair<const K, E>* sortedChain<K, E>::find(const K& theKey) const
//{
//	pairNode<K, E>* currentNode = firstNode;
//	//搜索关键字为theKey的数对
//	while (currentNode != NULL && currentNode->element.first != theKey)
//	{
//		currentNode = currentNode->next;
//	}
//	//判断数对是否匹配
//	if (currentNode != NULL && currentNode->element.first == theKey)
//	{
//		return &currentNode->element;
//	}
//	//数对无法匹配
//	return NULL;
//}
//
//template<class K, class E>
//void sortedChain<K, E>::insert(const pair<const K, E>& thePair)
//{//往字典中插入thePair，覆盖已存在的匹配数对
//	pairNode<K, E>* p = firstNode, * tp = NULL;
//	//搜索匹配的数对
//	while (p != NULL && p->element.first != thePair.first)
//	{
//		tp = p;
//		p = p->next;
//	}
//	//存在匹配的数对，则覆盖
//	if (p != NULL && p->element.first == thePair.first)
//	{
//		p->element.second=thePair.second;
//		return;
//	}
//	//如果不存在，则新建一个节点
//	pairNode<K, E>* newNode = new pairNode < K, E>(thePair, p);
//	if (tp == NULL)firstNode = newNode;//P是链首结点
//	else tp->next = newNode;
//	dSize++;	//链表长度+1
//}
//
//template<class K, class E>
//void sortedChain<K, E>::erase(const K& theKey)
//{
//	pairNode<K, E>* p = firstNode, * tp = NULL;//当前节点，前驱结点
//	//搜索匹配的数对
//	while (p != NULL && p->element.first != theKey)
//	{
//		tp = p;
//		p = p->next;
//	}
//	//存在匹配的数对，则删除
//	if (p != NULL && p->element.first == theKey)
//	{
//		if (tp == NULL)firstNode = p->next;//p是链首结点
//		else tp->next = p->next; //由此删除p
//		dSize--;
//	}
//}
//
//template<class K, class E>
//void sortedChain<K, E>::output(ostream& out) const
//{// Insert the chain elements into the stream out.
//	for (pairNode<K, E>* currentNode = firstNode;
//		currentNode != NULL;
//		currentNode = currentNode->next)
//		out << currentNode->element.first << " "
//		<< currentNode->element.second << "  ";
//}
//
//template <class K, class E>
//ostream& operator<<(ostream& out, const sortedChain<K, E>& x)
//{
//	x.output(out); return out;
//}
////实现散列表
//template<class K,class E>
//class hashChain
//{
//public:
//	hashChain(int theDivisor=11);
//	~hashChain() { delete[] table; }
//	bool empty() const { return dSize == 0; }
//	int size() const { return dSize; }
//	pair<const K, E>* find(const K& theKey) const;
//	void insert(const pair<const K, E>& thePair);
//	void erase(const K& theKey);
//private:
//	sortedChain<K, E>* table; //sortedChain类型的table指针
//	Hash<K>hash;
//	int dSize;
//	int divisor;
//};
////散列表构造函数
//template<class K, class E>
//hashChain<K, E>::hashChain(int theDivisor)
//{
//	divisor = theDivisor;
//	dSize = 0;
//	table = new sortedChain<K, E>[divisor];
//}
////查找
//template<class K, class E>
//pair<const K, E>* hashChain<K, E>::find(const K& theKey) const
//{
//	//调用链表find函数，成功查找到
//	if (table[theKey % divisor].find(theKey) != NULL)
//	{
//		cout << table[theKey % divisor].size() << endl;
//		return table[theKey % divisor].find(theKey);
//	}
//	else cout << "Not Found" << endl;
//	return nullptr;
//}
//
//template<class K, class E>
//void hashChain<K, E>::insert(const pair<const K, E>& thePair)
//{
//	int homeBuckt = (int)hash(thePair.first) % divisor;//起始桶位置
//	int homeSize = table[homeBuckt].size();//该桶链表长度
//	table[homeBuckt].insert(thePair);	   //调用链表插入函数
//	if (table[homeBuckt].size() > homeSize)//桶内不存在thePair
//		dSize++;
//	else//桶内已存在
//	{
//		cout << "Existed" << endl;
//	}
//}
////删除
//template<class K, class E>
//void hashChain<K, E>::erase(const K& theKey)
//{
//	int homeBuckt = (int)hash(theKey) % divisor;
//	int homeSize = table[homeBuckt].size();
//	table[homeBuckt].erase(theKey);//调用链表的删除函数
//	if (table[homeBuckt].size() < homeSize)//成功删除
//	{
//		cout << table[homeBuckt].size() << endl;
//		dSize--;
//	}
//	else
//		cout << "Delete Failed" << endl;
//}
//int main()
//{
//	int d, m;
//	cin >> d >> m;
//	int opt, x;
//	hashChain<int, int>S(d);
//	pair<int, int>P;
//	for (int i = 0; i < m; i++)
//	{
//		cin >> opt >> x;
//		switch (opt)
//		{
//		case 0:
//			P.first = x;
//			P.second = x;
//			S.insert(P);
//			break;
//		case 1:
//			S.find(x);
//			break;
//		case 2:
//			S.erase(x);
//			break;
//		default:
//			break;
//		}
//	}
//}