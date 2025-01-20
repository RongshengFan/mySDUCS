#pragma once
#include<iostream>
#include<string>
#include"arrayQueue.h"
using namespace std;
template<class T>
class emptyTree
{
public:
	emptyTree(string message = "Tree Is Empty")
	{
		*this = message;
	}
	void outputMessage()
	{
		cout << message << endl;
	}
private:
	string message;
};
//�����������ṹ��
template<class T>
struct binaryTreeNode
{
	T element;
	binaryTreeNode<T>* leftChild,  //������
		* rightChild;  //������
	binaryTreeNode() { leftChild = rightChild = NULL; }
	binaryTreeNode(const T& theElement)
	{
		element = theElement;
		leftChild = rightChild = NULL;
	}
	binaryTreeNode(const T& theElement, binaryTreeNode* theLeftChild, binaryTreeNode* theRightChild)
	{
		element(theElement);
		leftChild = theLeftChild;
		rightChild = theRightChild;
	}
};
//��ʽ������
template<class T>
class linkedBinaryTree
{
public:
	linkedBinaryTree() { root = NULL; treeSize = 0; }
	~linkedBinaryTree() { erase(); }
	bool empty()const { return treeSize == 0; }
	int size()const { return treeSize; }
	int Height()const { return height(root); }
	T* rootElement() const;
	void makeTree(const T& element, linkedBinaryTree<T>&, linkedBinaryTree<T>&);
	linkedBinaryTree<T>& removeLeftSubtree();
	linkedBinaryTree<T>& removeRightSubtree();
	void preOrder(void(*theVisit)(binaryTreeNode<T>*))
	{
		visit = theVisit; preOrder(root);
	}
	void inOrder(void(*theVisit)(binaryTreeNode<T>*))
	{
		visit = theVisit; inOrder(root);
	}
	void postOrder(void(*theVisit)(binaryTreeNode<T>*))
	{
		visit = theVisit; postOrder(root);
	}
	void levelOrder(void(*theVisit)(binaryTreeNode<T>*));
	void preOrderOutput() { preOrder(output); cout << endl; }
	void inOrderOutput() { inOrder(output); cout << endl; }
	void postOrderOutput() { postOrder(output); cout << endl; }
	void levelOrderOutput() { levelOrder(output); cout << endl; }
	void erase()
	{
		postOrder(dispose);
		root = NULL;
		treeSize = 0;
	}
private:
	binaryTreeNode<T>* root;	//���ڵ�ָ��
	int treeSize;				//����Ԫ�ظ���
	static int count;
	static void (*visit)(binaryTreeNode<T>*);
	static void preOrder(binaryTreeNode<T>* T);
	static void inOrder(binaryTreeNode<T>* T);
	static void postOrder(binaryTreeNode<T>* T);
	static void dispose(binaryTreeNode<T>* T)
	{
		delete T;
	}//ɾ��ָ���Ľڵ�
	static void output(binaryTreeNode<T>* x)
	{
		cout << x->element << " ";
	}//���ʽڵ�x�����elementֵ
	static void addToCount(binaryTreeNode<T>* T)
	{
		count++;
	}
	static int height(binaryTreeNode<T>* T);
	static void countNodes(binaryTreeNode<T>* T)
	{
		visit = addToCount;
		count = 0;
		preOrder(T);
	}
};
void (*linkedBinaryTree<int>::visit)(binaryTreeNode<int>*);
template<class T>
T* linkedBinaryTree<T>::rootElement() const
{
	if (treeSize == 0)
		return NULL;  // no root
	else
		return &root->element;
}

template<class T>
void linkedBinaryTree<T>::makeTree(const T& element, linkedBinaryTree<T>& left, linkedBinaryTree<T>& right)
{
	root = new binaryTreeNode<T>(element, left.root, right.root);
	treeSize = left.treeSize + right.treeSize + 1;
	left.root = right.root = NULL;
	left.treeSize = right.treeSize = 0;
}

template<class T>
linkedBinaryTree<T>& linkedBinaryTree<T>::removeLeftSubtree()
{
	if (treeSize == 0)
		throw emptyTree();
	linkedBinaryTree<T>leftSubTree;
	leftSubTree.root = root->leftChild;
	count = 0;
	leftSubTree.treeSize = countNodes(leftSubTree.root);
	root->leftChild = NULL;
	treeSize -= leftSubTree.treeSize;
	return leftSubTree;
}

template<class T>
linkedBinaryTree<T>& linkedBinaryTree<T>::removeRightSubtree()
{
	if (treeSize == 0)
		throw emptyTree();
	linkedBinaryTree<T>rightSubTree;
	rightSubTree.root = root->leftChild;
	count = 0;
	rightSubTree.treeSize = countNodes(rightSubTree.root);
	root->leftChild = NULL;
	treeSize -= rightSubTree.treeSize;
	return rightSubTree;
}

template<class T>
void linkedBinaryTree<T>::levelOrder(void(*theVisit)(binaryTreeNode<T>*))
{//��α���������*t
	arrayQueue<binaryTreeNode<T>*>q;
	binaryTreeNode<T>* T = root;
	while (T != NULL)
	{
		visit(T);
		//��t�ĺ��Ӳ������
		if (T->leftChild != NULL)
			q.push(T->leftChild);
		if (T->rightChild != NULL)
			q.push(T->rightChild);

		//��ȡ��һ��Ҫ���ʵĽڵ�
		try { T = q.front(); }
		catch (queueEmpty) { return; }
		q.pop();
	}
}

template<class T>
int linkedBinaryTree<T>::height(binaryTreeNode<T>* T)
{//���ض������ĸ߶�
	if (T == NULL)return 0;
	int hl = height(T->leftChild);
	int hr = height(T->rightChild);
	if (hl > hr)return hl;
	else return hr;
}

template<class T>
void linkedBinaryTree<T>::preOrder(binaryTreeNode<T>* T)
{//ǰ�����������*t
	if (T != NULL)
	{
		visit(T);					//��������
		preOrder(T->leftChild);		//ǰ�����������
		preOrder(T->rightChild);	//ǰ�����������
	}
}

template<class T>
void linkedBinaryTree<T>::inOrder(binaryTreeNode<T>* T)
{//�������������*t
	if (T != NULL)
	{
		inOrder(T->leftChild);		//ǰ�����������
		visit(T);					//��������
		inOrder(T->rightChild);		//ǰ�����������
	}
}

template<class T>
void linkedBinaryTree<T>::postOrder(binaryTreeNode<T>* T)
{//�������������*t
	if (T != NULL)
	{
		postOrder(T->leftChild);		//�������������
		postOrder(T->rightChild);		//�������������
		visit(T);						//��������
	}
}