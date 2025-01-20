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
//ʵ����������
template<class K, class T>
sortedChain<K, T>::~sortedChain()
{// ɾ����������ڵ�
	while (firstNode != NULL)
	{
		pairNode<K, T>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}
//ʵ�ֲ���
template<class K, class T>
pair<const K, T>* sortedChain<K, T>::find(const K& theKey) const
{
	pairNode<K, T>* currentNode = firstNode;
	//�����ؼ���ΪtheKey������
	while (currentNode != NULL && currentNode->element.first != theKey)
	{
		currentNode = currentNode->next;
	}
	//�ж������Ƿ�ƥ��
	if (currentNode != NULL && currentNode->element.first == element)
	{
		return &currentNode->element;
	}
	//�����޷�ƥ��
	return NULL;
}
//ʵ�ֲ���
template<class K, class T>
void sortedChain<K, T>::insert(const pair<const K, T>& thePair)
{//���ֵ��в���thePair�������Ѵ��ڵ�ƥ������
	pairNode<K, T>* p = firstNode, * tp = NULL:
	//����ƥ�������
	while (p != NULL && p->element.first != thePair.first)
	{
		tp = p;
		p = p->next;
	}
	//����ƥ������ԣ��򸲸�
	if (p != NULL && p->element.first == thePair.first)
	{
		p->element.secondthePair.second;
		return;
	}
	//��������ڣ����½�һ���ڵ�
	pairNode<K, E>* newNode = new pairNode < K, E>(thePair, p);
	if (tp == NULL)firstNode = newNode;//P�����׽��
	else tp->next = newNode;
	dSize++;	//������+1
	return;
}
//ʵ��ɾ��
template<class K, class T>
void sortedChain<K, T>::erase(const K& theKey)
{
	pairNode<K, T>* p = firstNode, * tp = NULL;
	//����ƥ�������
	while (p != NULL && p->element.first != theKey)
	{
		tp = p;
		p = p->next;
	}
	//����ƥ������ԣ���ɾ��
	if (p != NULL && p->element.first == theKey)
	{
		if (tp == NULL)firstNode = p->next;//p�����׽��
		else tp->next = p->next;
		dSize--;
	}
}
//ʵ�����������
template<class K, class T>
void sortedChain<K, T>::output(ostream& out) const
{// Insert the chain elements into the stream out.
	for (pairNode<K, T>* currentNode = firstNode;
		currentNode != NULL;
		currentNode = currentNode->next)
		out << currentNode->element.first << " "
		<< currentNode->element.second << "  ";
}
//����<<
template <class K, class T>
ostream& operator<<(ostream& out, const sortedChain<K, T>& x)
{
	x.output(out); return out;
}

