#pragma once
#include"linearList.h"
#include <sstream>
#include <iterator>
#include<iostream>
using namespace std;
//链表的结构节点定义
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
//链表的定义
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
		//向前迭代器所需要的上typedef语句
		typedef forward_iterator_tag iterator_capacity;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;

		//构造函数
		iterator(chainNode<T>* theNode = NULL)
		{
			node = theNode;
		}

		//解引用操作符
		T& operator*() const { return node->element; }
		T* operator->() const { return &node->element; }

		//迭代器加法操作 不能operator--
		iterator& operator++() //前加
		{
			node = node->next;
			return *this;
		}
		iterator operator++(int) //后加
		{
			iterator old = *this;
			node = node->next;
			return old;
		}

		//相等检验
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

//构造函数
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
//复制构造函数
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
//析构函数
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
//返回索引值是theIndex的元素
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
//返回元素是theElement首次出现的索引值
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
//删除索引为theIndex的元素
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
		chainNode<T>* p = firstNode;			//指向要删节点的前驱结点
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
//在索引为theIndex插入元素theElement
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
//重载流操作符<<
template<class T>
ostream operator<<(ostream& out, const chain<T>& x)
{
	x.output(out);
	return out;
}
//输出链表
template<class T>
void chain<T>::output(ostream& out) const
{
	for (chainNode<T>* currentNode = firstNode; currentNode != NULL; currentNode = currentNode->next)
	{
		out << currentNode->element << " ";
	}
}
//原地实现链表的逆置
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
//计算索引值与节点值的异或和
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

//检查索引值是否有效，无效则抛出异常
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
//生成一个扩展的新链表c,从a首元素开始交替包含a,b的元素，方法的复杂度应与链表 a 和 的长度具有线性关系。
template<class T>
chain<T>& chain<T>::meld1(const chain<T>& a, const chain<T>& b)
{
	// TODO: 在此处插入 return 语句
}
//与meld1类似，但合并后的链表使用的是链表 a 和 b 的节点空间,合并之后，链表a 和b 是空表。
template<class T>
chain<T>& chain<T>::meld2(chain<T>& a, chain<T>& b)
{
	// TODO: 在此处插入 return 语句
}
//它生成一个新的有序链表 c，包含a 和 b的所有元素
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
//与merge1类似，但归并之后，两个输入链表a 和 为空
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
//生成两个扩展链表a,b，a包含c中索引为奇数的元素，b包含c中其余的元素，而且它是用输入链表 *this 的空间建立了链表a和b。
template<class T>
 chain<T>& chain<T>::split(chain<T>& a, chain<T>& b)
{
	// TODO: 在此处插入 return 语句
}
//在一个循环移动的操作中,线性表的元素根据给定的值，按顺时针方向移动
template<class T>
chain<T>& chain<T>::circularShift(int index)
{
	// TODO: 在此处插入 return 语句
}
//插入排序，递增排序
template<class T>
chain<T>& chain<T>::insertionSort()
{
	// TODO: 在此处插入 return 语句
}
//选择排序
template<class T>
chain<T>& chain<T>::selectionSort()
{
	// TODO: 在此处插入 return 语句
}
//冒泡排序
template<class T>
chain<T>& chain<T>::bubbleSort()
{
	//循环扫描链表listSize-1次如果前面的元素大于后面元素进行交换
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
//箱子排序
template<class T>
inline chain<T>& chain<T>::binSort(int range)
{
	// TODO: 在此处插入 return 语句
}
