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
////��Щ���ܲ���Ҫ�����ɾ��������ƪ������
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
//		//���캯��
//		iterator(chainNode<T>* theNode = NULL)
//		{
//			node = theNode;
//		}
//		//�����ò�����
//		T& operator*() const { return node->element; }
//		T* operator->() const { return &node->element; }
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
//	iterator begin() { return iterator(firstNode); }
//	iterator end() { return iterator(NULL); }
//protected:
//	void checkIndex(int theIndex)const;
//	chainNode<T>* firstNode;
//	int listSize;
//};
//
////���캯��
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
//
////������ΪtheIndex����Ԫ��theElement
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
////��������ڵ�����ֵ��ڵ�ֵ������
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
////������ֵΪ�����������������
//template<class T>
//void chain<T>::merge(chain<T>& a, chain<T>& b)
//{
//	//ʹ�õ�����
//	iterator itA = a.begin();
//	iterator itB = b.begin();
//	int len = a.listSize + b.listSize;
//	//��������Ϊ��������֮��
//	for (int i = 0; i < len;)
//	{
//		//������a������ʱ��ֻ����b����Ԫ��
//		if (itA == NULL)
//		{
//			insert(i, *itB);
//			i++;
//			itB++;
//			continue;
//		}
//		//������b������ʱ��ֻ����a����Ԫ��
//		if (itB == NULL)
//		{
//			insert(i, *itA);
//			i++;
//			itA++;
//			continue;
//		}
//		//��a�ڵ�Ԫ��ֵС��b�ڵ�Ԫ��ֵʱ
//		if ((*itA) < (*itB))
//		{
//			insert(i, *itA);
//			i++;
//			itA++;
//		}
//		//��b�ڵ�Ԫ��ֵС��a�ڵ�Ԫ��ֵʱ
//		else if ((*itA) > (*itB))
//		{
//			insert(i, *itB);
//			i++;
//			itB++;
//		}
//		//��a�ڵ�Ԫ��ֵ����b�ڵ�Ԫ��ֵʱ,���β���
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
////��������
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
//	//��������
//	chain<int>a;
//	chain<int>b;
//	chain<int>c;
//
//	int* A = new int[n];//��������洢Ԫ�أ��ź�����ڷ�������
//	for (int i = 0; i < n; i++) cin >> A[i]; //����a�Ľڵ�Ԫ��ֵ
//	insertionSort(A,n);         //���ú���������
//	for (int i = 0; i < n; i++) a.insert(i, A[i]); //������ڵ�
//
//	int* B = new int[m];//��������洢Ԫ�أ��ź�����ڷ�������
//	for (int i = 0; i < m; i++) cin >> B[i]; //����b�Ľڵ�Ԫ��ֵ
//	insertionSort(B, m);		//���ú���������
//	for (int i = 0; i < m; i++) b.insert(i, B[i]); //������ڵ�
//
//	c.merge(a, b);//�ϲ�
//
//	cout << a.sum() << endl;
//	cout << b.sum() << endl;
//	cout << c.sum() << endl;
//
//	delete[]A;
//	delete[]B;
//	return 0;
//}