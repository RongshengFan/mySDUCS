//#include<iostream>
//#include <sstream>
//#include <iterator>
//using namespace std;
////����Ľṹ�ڵ㶨��
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
////����Ķ���
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
//		//���캯��
//		iterator(chainNode<T>* theNode = NULL)
//		{
//			node = theNode;
//		}
//		//�����ò�����
//		T& operator*() const { return node->element; }
//		T* operator->() const { return &node->element; }
//
//		//�������ӷ����� ����operator--
//		iterator& operator++() //ǰ��
//		{
//			node = node->next;
//			return *this;
//		}
//		iterator operator++(int) //���
//		{
//			iterator old = *this;
//			node = node->next;
//			return old;
//		}
//
//		//��ȼ���
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
////���캯��
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
////���ƹ��캯��
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
////��������
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
////��������ֵ��theIndex��Ԫ��
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
////����Ԫ����theElement�״γ��ֵ�����ֵ
//template<class T>
//int chain<T>::indexOf(const T& theElement) const
//{
//	chainNode<T>* currentNode = firstNode;
//	int index = 0;//��¼����ֵ
//	while (currentNode != NULL && currentNode->element != theElement)//������������ֵ
//	{
//		currentNode = currentNode->next;
//		index++;
//	}
//	if (currentNode == NULL)
//		return -1;
//	else
//		return index;
//}
////ɾ������ΪtheIndex��Ԫ��
//template<class T>
//void chain<T>::erase(int theIndex)
//{
//	checkIndex(theIndex);
//	chainNode<T>* deleteNode;//���Լ�¼��ɾ���ڵ�
//	if (theIndex == 0)//ɾ��ͷ���
//	{
//		deleteNode = firstNode;
//		firstNode = firstNode->next;
//	}
//	else
//	{
//		chainNode<T>* p = firstNode;			//ָ��Ҫɾ�ڵ��ǰ�����
//		for (int i = 0; i < theIndex - 1; i++)
//		{
//			p = p->next;
//		}
//		deleteNode = p->next; //����ɾ���ڵ�
//		p->next = p->next->next;
//	}
//	listSize--;
//	delete deleteNode;
//}
////������ΪtheIndex����Ԫ��theElement
//template<class T>
//void chain<T>::insert(int theIndex, const T& theElement)
//{
//	checkIndex(theIndex);
//	if (theIndex == 0)//����ͷ���
//	{
//		firstNode = new chainNode<T>(theElement, firstNode);
//	}
//	else
//	{
//		chainNode<T>* p = firstNode; 
//		for (int i = 0; i < theIndex - 1; i++)//����������Ҫ����ڵ��ǰ�����
//		{
//			p = p->next;
//		}
//		p->next = new chainNode<T>(theElement, p->next);
//	}
//	listSize++;
//}
////������������<<
//template<class T>
//ostream operator<<(ostream& out, const chain<T>& x)
//{
//	x.output(out);
//	return out;
//}
////�������
//template<class T>
//void chain<T>::output(ostream& out) const
//{
//	for (chainNode<T>* currentNode = firstNode; currentNode != NULL; currentNode = currentNode->next)
//	{
//		out << currentNode->element << " ";
//	}
//}
////ԭ��ʵ�����������
//template<class T>
//inline void chain<T>::reverse()
//{
//	if (firstNode == NULL || firstNode->next == NULL)return;//���Ϊ��������ߵ��ڵ㣬��ֱ�ӷ���
//	chainNode<T>* pastNode = firstNode;				//��¼ǰ���ڵ�
//	chainNode<T>* currentNode = firstNode->next;	//��¼��ǰ�ڵ�
//	chainNode<T>* nextNode = firstNode->next->next; //��¼�����ڵ�
//	firstNode->next = NULL;							//ͷ����β���
//	while (nextNode)								//��ʼ������ʵ������
//	{
//		currentNode->next = pastNode;				//ǰ���ڵ������ڵ�
//		pastNode = currentNode;						//ԭǰ��������
//		currentNode = nextNode;						//ԭ��ǰ�ڵ����
//		nextNode = nextNode->next;					//ԭ�����ڵ����
//	}
//	currentNode->next = pastNode;					//ǰ���ڵ������ڵ�
//	firstNode = currentNode;						//���µ�ǰ�ڵ㣨ԭβ��㣩Ϊͷ�ڵ�
//}
////��������ڵ�����ֵ��ڵ�ֵ������
//template<class T>
//int chain<T>::sum()
//{
//	int s = 0, i = 0;
//	iterator it = begin();//ʹ�õ�����
//	while (i < listSize)
//	{
//		s += i ^ (*it);
//		it++;
//		i++;
//	}
//	return s;
//}
//
////�������ֵ�Ƿ���Ч����Ч���׳��쳣
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
////main������������ֲ���
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