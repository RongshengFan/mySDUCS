//#include<iostream>
//#include<string>
//using namespace std;
////ʵ����ʽɢ��
////���ؼ���ת��Ϊsize_t���ͷǸ��������ֱ�ʵ��string�桢int�桢long���
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
////����һ�����Խڵ�
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
////����sortedChain��
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
//	pairNode<K, E>* firstNode; //����ͷָ�� 
//	int dSize;                 //����ڵ���
//};
//template<class K, class E>
//sortedChain<K, E>::~sortedChain()
//{// ɾ����������ڵ�
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
//	//�����ؼ���ΪtheKey������
//	while (currentNode != NULL && currentNode->element.first != theKey)
//	{
//		currentNode = currentNode->next;
//	}
//	//�ж������Ƿ�ƥ��
//	if (currentNode != NULL && currentNode->element.first == theKey)
//	{
//		return &currentNode->element;
//	}
//	//�����޷�ƥ��
//	return NULL;
//}
//
//template<class K, class E>
//void sortedChain<K, E>::insert(const pair<const K, E>& thePair)
//{//���ֵ��в���thePair�������Ѵ��ڵ�ƥ������
//	pairNode<K, E>* p = firstNode, * tp = NULL;
//	//����ƥ�������
//	while (p != NULL && p->element.first != thePair.first)
//	{
//		tp = p;
//		p = p->next;
//	}
//	//����ƥ������ԣ��򸲸�
//	if (p != NULL && p->element.first == thePair.first)
//	{
//		p->element.second=thePair.second;
//		return;
//	}
//	//��������ڣ����½�һ���ڵ�
//	pairNode<K, E>* newNode = new pairNode < K, E>(thePair, p);
//	if (tp == NULL)firstNode = newNode;//P�����׽��
//	else tp->next = newNode;
//	dSize++;	//������+1
//}
//
//template<class K, class E>
//void sortedChain<K, E>::erase(const K& theKey)
//{
//	pairNode<K, E>* p = firstNode, * tp = NULL;//��ǰ�ڵ㣬ǰ�����
//	//����ƥ�������
//	while (p != NULL && p->element.first != theKey)
//	{
//		tp = p;
//		p = p->next;
//	}
//	//����ƥ������ԣ���ɾ��
//	if (p != NULL && p->element.first == theKey)
//	{
//		if (tp == NULL)firstNode = p->next;//p�����׽��
//		else tp->next = p->next; //�ɴ�ɾ��p
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
////ʵ��ɢ�б�
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
//	sortedChain<K, E>* table; //sortedChain���͵�tableָ��
//	Hash<K>hash;
//	int dSize;
//	int divisor;
//};
////ɢ�б��캯��
//template<class K, class E>
//hashChain<K, E>::hashChain(int theDivisor)
//{
//	divisor = theDivisor;
//	dSize = 0;
//	table = new sortedChain<K, E>[divisor];
//}
////����
//template<class K, class E>
//pair<const K, E>* hashChain<K, E>::find(const K& theKey) const
//{
//	//��������find�������ɹ����ҵ�
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
//	int homeBuckt = (int)hash(thePair.first) % divisor;//��ʼͰλ��
//	int homeSize = table[homeBuckt].size();//��Ͱ������
//	table[homeBuckt].insert(thePair);	   //����������뺯��
//	if (table[homeBuckt].size() > homeSize)//Ͱ�ڲ�����thePair
//		dSize++;
//	else//Ͱ���Ѵ���
//	{
//		cout << "Existed" << endl;
//	}
//}
////ɾ��
//template<class K, class E>
//void hashChain<K, E>::erase(const K& theKey)
//{
//	int homeBuckt = (int)hash(theKey) % divisor;
//	int homeSize = table[homeBuckt].size();
//	table[homeBuckt].erase(theKey);//���������ɾ������
//	if (table[homeBuckt].size() < homeSize)//�ɹ�ɾ��
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