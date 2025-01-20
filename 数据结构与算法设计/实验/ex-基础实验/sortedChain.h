#pragma once
#include <iostream>
#include "dictionary.h"
#include "pairNode.h"

using namespace std;

template<class K, class T>
class sortedChain : public dictionary<K, T>
{
public:
    sortedChain() { firstNode = NULL; dSize = 0; }
    ~sortedChain();

    bool empty() const { return dSize == 0; }
    int size() const { return dSize; }
    pair<const K, T>* find(const K&) const;
    void erase(const K&);
    void insert(const pair<const K, T>&);
    void output(ostream& out) const;

protected:
    pairNode<K, T>* firstNode;  // pointer to first node in chain
    int dSize;                 // number of elements in dictionary
};
//实现析构函数
template<class K, class T>
sortedChain<K, T>::~sortedChain()
{// 删除链表各个节点
	while (firstNode != NULL)
	{
		pairNode<K, T>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}
//实现查找
template<class K, class T>
pair<const K, T>* sortedChain<K, T>::find(const K& theKey) const
{
	pairNode<K, T>* currentNode = firstNode;
	//搜索关键字为theKey的数对
	while (currentNode != NULL && currentNode->element.first != theKey)
	{
		currentNode = currentNode->next;
	}
	//判断数对是否匹配
	if (currentNode != NULL && currentNode->element.first == element)
	{
		return &currentNode->element;
	}
	//数对无法匹配
	return NULL;
}
//实现插入
template<class K, class T>
void sortedChain<K, T>::insert(const pair<const K, T>& thePair)
{//往字典中插入thePair，覆盖已存在的匹配数对
	pairNode<K, T>* p = firstNode, * tp = NULL:
	//搜索匹配的数对
	while (p != NULL && p->element.first != thePair.first)
	{
		tp = p;
		p = p->next;
	}
	//存在匹配的数对，则覆盖
	if (p != NULL && p->element.first == thePair.first)
	{
		p->element.secondthePair.second;
		return;
	}
	//如果不存在，则新建一个节点
	pairNode<K, E>* newNode = new pairNode < K, E>(thePair, p);
	if (tp == NULL)firstNode = newNode;//P是链首结点
	else tp->next = newNode;
	dSize++;	//链表长度+1
	return;
}
//实现删除
template<class K, class T>
void sortedChain<K, T>::erase(const K& theKey)
{
	pairNode<K, T>* p = firstNode, * tp = NULL;
	//搜索匹配的数对
	while (p != NULL && p->element.first != theKey)
	{
		tp = p;
		p = p->next;
	}
	//存在匹配的数对，则删除
	if (p != NULL && p->element.first == theKey)
	{
		if (tp == NULL)firstNode = p->next;//p是链首结点
		else tp->next = p->next;
		dSize--;
	}
}
//实现数据输出流
template<class K, class T>
void sortedChain<K, T>::output(ostream& out) const
{// Insert the chain elements into the stream out.
	for (pairNode<K, T>* currentNode = firstNode;
		currentNode != NULL;
		currentNode = currentNode->next)
		out << currentNode->element.first << " "
		<< currentNode->element.second << "  ";
}
//重载<<
template <class K, class T>
ostream& operator<<(ostream& out, const sortedChain<K, T>& x)
{
	x.output(out); return out;
}

