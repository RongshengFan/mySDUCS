#pragma once
#include"linearList.h"
#include <sstream>
#include <iterator>
#include<iostream>
using namespace std;
//����Ľṹ�ڵ㶨��
template<class T>
struct chainNode
{
	T element;
	chainNode<T>* next;

	chainNode() {};
	chainNode(const T& element)
	{
		this->element = element;
	}
	chainNode(const T& element, chainNode<T>* next)
	{
		this->element = element;
		this->next = next;
	}
};
//����Ķ���
template <class T>
class chain : public linearList<T>
{
public: 
	chain(int initialCapacity = 10);
	chain(const chain<T>& theList);
	~chain();

	bool empty()const { return listSize == 0; }
	int size()const { return listSize; }
	T& get(int theIndex)const ;
	int indexOf(const T& theElement)const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(ostream& out)const;

	void reverse();
	int sum();
	chain<T>& meld1(const chain<T>& a, const chain<T>& b);
	chain<T>& meld2(chain<T>& a, chain<T>& b);
	chain<T>& merge1(const chain<T>& a, const chain<T>& b);
	chain<T>& merge2(chain<T>& a, chain<T>& b);
	chain<T>& split(chain<T>& a, chain<T>& b);
	chain<T>& circularShift(int index);
	chain<T>& insertionSort();
	chain<T>& selectionSort();
	chain<T>& bubbleSort();
	chain<T>& binSort(int range);

public:
	class iterator
	{
	public:
		//��ǰ����������Ҫ����typedef���
		typedef forward_iterator_tag iterator_capacity;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;

		//���캯��
		iterator(chainNode<T>* theNode = NULL)
		{
			node = theNode;
		}

		//�����ò�����
		T& operator*() const { return node->element; }
		T* operator->() const { return &node->element; }

		//�������ӷ����� ����operator--
		iterator& operator++() //ǰ��
		{
			node = node->next;
			return *this;
		}
		iterator operator++(int) //���
		{
			iterator old = *this;
			node = node->next;
			return old;
		}

		//��ȼ���
		bool operator!=(const iterator right) const
		{
			return node != right.node;
		}
		bool operator==(const iterator right) const
		{
			return node == right.node;
		}
	protected:
		chainNode<T>* node;
	};

	iterator begin() { return iterator(firstNode); }
	iterator end() { return iterator(NULL); }
protected:
	void checkIndex(int theIndex)const;

	chainNode<T>* firstNode;
	int listSize;
};

//���캯��
template<class T>
chain<T>::chain(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		ostringstream s;
		s << "initial capacity = " << initialCapacity << " must be > 0";
		throw logic_error(s.str());
	}
	firstNode = NULL;
	listSize = 0;
}
//���ƹ��캯��
template<class T>
chain<T>::chain(const chain<T>& theList)
{
	listSize = theList.listSize;

	if (listSize = 0)
	{
		firstNode = NULL;
		return;
	}
	chainNode<T>* sourceNode = theList.firstNode;
	firstNode = new chainNode<T>(sourceNode->element);
	sourceNode = sourceNode->next;
	chainNode<T>* targetNode = firstNode;

	while (sourceNode != NULL)
	{
		targetNode->next = new chainNode<T>(sourceNode->element);
		targetNode = targetNode->next;
		sourceNode = sourceNode->next;
	}
	targetNode->next = NULL;
}
//��������
template<class T>
chain<T>::~chain()
{
	while (firstNode != NULL)
	{
		chainNode<T>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}
//��������ֵ��theIndex��Ԫ��
template<class T>
T& chain<T>::get(int theIndex) const
{
	checkIndex(theIndex);

	chainNode<T>* currentNode = firstNode;
	for (int i = 0; i < theIndex; i++)
	{
		currentNode = currentNode->next;
	}
	return currentNode->element;
}
//����Ԫ����theElement�״γ��ֵ�����ֵ
template<class T>
int chain<T>::indexOf(const T& theElement) const
{
	chainNode<T>* currentNode = firstNode;
	int index = 0;
	while (currentNode != NULL && currentNode->element != theElement)
	{
		currentNode = currentNode->next;
		index++;
	}
	if (currentNode == NULL)
		return -1;
	else
		return index;
}
//ɾ������ΪtheIndex��Ԫ��
template<class T>
void chain<T>::erase(int theIndex)
{
	checkIndex(theIndex);
	chainNode<T>* deleteNode;
	if (theIndex == 0)
	{
		deleteNode = firstNode;
		firstNode = firstNode->next;
	}
	else
	{
		chainNode<T>* p = firstNode;			//ָ��Ҫɾ�ڵ��ǰ�����
		for (int i = 0; i < theIndex - 1; i++)
		{
			p = p->next;
		}
		deleteNode = p->next;
		p->next = p->next->next;
	}
	listSize--;
	delete deleteNode;
}
//������ΪtheIndex����Ԫ��theElement
template<class T>
void chain<T>::insert(int theIndex, const T& theElement)
{
	checkIndex(theIndex);
	if (theIndex == 0)
	{
		firstNode = new chainNode<T>(theElement, firstNode);
	}
	else
	{
		chainNode<T>* p = firstNode;
		for (int i = 0; i < theIndex - 1; i++)
		{
			p = p->next;
		}
		p->next = new chainNode<T>(theElement, p->next);
	}
	listSize++;
}
//������������<<
template<class T>
ostream operator<<(ostream& out, const chain<T>& x)
{
	x.output(out);
	return out;
}
//�������
template<class T>
void chain<T>::output(ostream& out) const
{
	for (chainNode<T>* currentNode = firstNode; currentNode != NULL; currentNode = currentNode->next)
	{
		out << currentNode->element << " ";
	}
}
//ԭ��ʵ�����������
template<class T>
inline void chain<T>::reverse()
{
	if (firstNode == NULL || firstNode->next == NULL)return;
	chainNode<T>* pastNode = firstNode;
	chainNode<T>* currentNode = firstNode->next;
	chainNode<T>* nextNode = firstNode->next->next;
	while (nextNode)
	{
		currentNode->next = pastNode;
		pastNode = currentNode;
		currentNode = nextNode;
		nextNode = nextNode->next;
	}
	currentNode->next = pastNode;
	firstNode = currentNode;
}
//��������ֵ��ڵ�ֵ������
template<class T>
int chain<T>::sum()
{
	int s=0,i=0;
	iterator it=begin();
	while (i < listSize)
	{
		s += i ^ (*it);
		it++;
		i++;
	}
	return s;
}

//�������ֵ�Ƿ���Ч����Ч���׳��쳣
template<class T>
void chain<T>::checkIndex(int theIndex) const
{
	if (theIndex<0 || theIndex>listSize)
	{
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw logic_error(s.str());
	}
}
//����һ����չ��������c,��a��Ԫ�ؿ�ʼ�������a,b��Ԫ�أ������ĸ��Ӷ�Ӧ������ a �� �ĳ��Ⱦ������Թ�ϵ��
template<class T>
chain<T>& chain<T>::meld1(const chain<T>& a, const chain<T>& b)
{
	// TODO: �ڴ˴����� return ���
}
//��meld1���ƣ����ϲ��������ʹ�õ������� a �� b �Ľڵ�ռ�,�ϲ�֮������a ��b �ǿձ�
template<class T>
chain<T>& chain<T>::meld2(chain<T>& a, chain<T>& b)
{
	// TODO: �ڴ˴����� return ���
}
//������һ���µ��������� c������a �� b������Ԫ��
template<class T>
chain<T>& chain<T>::merge1(const chain<T>& a, const chain<T>& b)
{
	chainNode<T>* currentNodeA = a.firstNode;
	chainNode<T>* currentNodeB = b.firstNode;
	chainNode<T>* currentNodeC = firstNode;
	while (currentNodeA || currentNodeB)
	{
		if (currentNodeA == NULL || currentNodeB != NULL && currentNodeA->element > currentNodeB->element)
		{
			if (!firstNode)
			{
				firstNode = new chanNode<T>(currentNodeB->element);
				currentNodeC = firstNode;
			}
			else
			{
				currentNodeC->next = currentNodeB;
				currentNodeC = new chainNode<T>(currentNodeB->element);
			}
			currentNodeB = currentNodeB->next;
		}
		else if (currentNodeB == NULL || currentNodeA != NULL && currentNodeA->element <= currentNodeB->element)
		{
			if (!firstNode)
			{
				firstNode = new chanNode<T>(currentNodeB->element);
				currentNodeC = firstNode;
			}
			else
			{
				currentNodeC->next = currentNodeA;
				currentNodeC = new chainNode<T>(currentNodeA->element);
			}
			currentNodeA = currentNodeA->next;
		}
	}
	listSize = a.listSize + b.listSize;
	return *this;
}
//��merge1���ƣ����鲢֮��������������a �� Ϊ��
template<class T>
chain<T>& chain<T>::merge2(chain<T>& a, chain<T>& b)
{
	chainNode<T>* currentNodeA = a.firstNode;
	chainNode<T>* currentNodeB = b.firstNode;
	chainNode<T>* currentNodeC = firstNode;
	while (currentNodeA || currentNodeB)
	{
		if (currentNodeA == NULL || currentNodeB != NULL && currentNodeA->element > currentNodeB->element)
		{
			if (!firstNode)
			{
				firstNode = new chanNode<T>(currentNodeB->element);
				currentNodeC = firstNode;
			}
			else
			{
				currentNodeC->next = currentNodeB;
				currentNodeC = new chainNode<T>(currentNodeB->element);
			}
			currentNodeB = currentNodeB->next;
		}
		else if (currentNodeB == NULL || currentNodeA != NULL && currentNodeA->element <= currentNodeB->element)
		{
			if (!firstNode)
			{
				firstNode = new chanNode<T>(currentNodeB->element);
				currentNodeC = firstNode;
			}
			else
			{
				currentNodeC->next = currentNodeA;
				currentNodeC = new chainNode<T>(currentNodeA->element);
			}
			currentNodeA = currentNodeA->next;
		}
	}
	listSize = a.listSize + b.listSize;
	a.firstNode = b.firstNode = NULL;
	a.lastNode = b.lastNode = NULL;
	a.listSize = b.listSize = 0;
	return *this;
}
//����������չ����a,b��a����c������Ϊ������Ԫ�أ�b����c�������Ԫ�أ������������������� *this �Ŀռ佨��������a��b��
template<class T>
 chain<T>& chain<T>::split(chain<T>& a, chain<T>& b)
{
	// TODO: �ڴ˴����� return ���
}
//��һ��ѭ���ƶ��Ĳ�����,���Ա��Ԫ�ظ��ݸ�����ֵ����˳ʱ�뷽���ƶ�
template<class T>
chain<T>& chain<T>::circularShift(int index)
{
	// TODO: �ڴ˴����� return ���
}
//�������򣬵�������
template<class T>
chain<T>& chain<T>::insertionSort()
{
	// TODO: �ڴ˴����� return ���
}
//ѡ������
template<class T>
chain<T>& chain<T>::selectionSort()
{
	// TODO: �ڴ˴����� return ���
}
//ð������
template<class T>
chain<T>& chain<T>::bubbleSort()
{
	//ѭ��ɨ������listSize-1�����ǰ���Ԫ�ش��ں���Ԫ�ؽ��н���
	for (int i = 0; i < listSize-1; i++)
	{
		chainNode<T>* currentPreNode = nullptr;
		chainNode<T>* currentNode = firstNode;
		chainNode<T>* currentNextNode = currentNode->next;
		while (currentNextNode)
		{
			if (currentNode->element > currentNextNode->element)
			{
				if (!currentPreNode)
					firstNode = currentNextNode;
				else
					currentPreNode->next = currentNextNode;
				currentNode->next = currentNextNode->next;
				currentNextNode->next = currentNode;
			}
			currentPreNode = currentNode;
			currentNode = currentNextNode;
			currentNextNode = currentNode->next;
		}
		lastNode = currentNode;
	}
	return *this;
}
//��������
template<class T>
inline chain<T>& chain<T>::binSort(int range)
{
	// TODO: �ڴ˴����� return ���
}
