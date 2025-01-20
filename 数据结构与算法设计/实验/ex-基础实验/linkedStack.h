#pragma once
#include"stack.h"
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
template<class T>
class linkedStack
{
public:
	linkedStack(int initialCapacity = 10)
	{
		stackTop = NULL;
		stackSize = 0;
	}
	~linkedStack()
	{
		while (stackTop != NULL)
		{
			chainNode<T>* deleteNode = stackTop;
			stackTop = stackTop->next;
			delete deleteNode；
		}
	}
	bool empty()const { return stackSize == 0; }
	int size()const { return stackSize; }
	T& top()
	{
		if (stackSize == 0)
			throw logic_error();
		return stackTop->element;
	}
	void pop();
	void push(const T& theElement);
	chainNode<T>& popNode();
	void pushNode(chainNode<T>* theNode);
private:
	chainNode<T>* stackTop;
	int stackSize;
};
template<class T>
void linkedStack<T>::pop()
{
	if (stackSize == 0)
		throw logic_error();
	chainNode<T>* nextNode = stackTop->next;
	delete stackTop;
	stackTop = nextNode;
	stackSize--;
}
template<class T>
void linkedStack<T>::push(const T& theElement)
{
	stackTop = new chainNode<T>(theElement, stackTop);
	stackSize++;
}
template<class T>
chainNode<T>& linkedStack<T>::popNode()
{
	if (stackSize == 0)return NULL;
	chainNode<T>* Node = stackTop;
	chainNode<T>* nextNode = stackTop->next;
	delete stackTop;
	stackTop = nextNode;
	stackSize--;
	return Node;
}
template<class T>
void linkedStack<T>::pushNode(chainNode<T>* theNode)
{
	theNode->next = stackTop;
	stackTop = theNode;
}
