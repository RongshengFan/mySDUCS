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
//二叉树树结点结构体
template<class T>
struct binaryTreeNode
{
	T element;
	binaryTreeNode<T>* leftChild,  //左子树
		* rightChild;  //右子树
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
//链式二叉树
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
	binaryTreeNode<T>* root;	//根节点指针
	int treeSize;				//树的元素个数
	static int count;
	static void (*visit)(binaryTreeNode<T>*);
	static void preOrder(binaryTreeNode<T>* T);
	static void inOrder(binaryTreeNode<T>* T);
	static void postOrder(binaryTreeNode<T>* T);
	static void dispose(binaryTreeNode<T>* T)
	{
		delete T;
	}//删除指定的节点
	static void output(binaryTreeNode<T>* x)
	{
		cout << x->element << " ";
	}//访问节点x，输出element值
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
{//层次遍历二叉树*t
	arrayQueue<binaryTreeNode<T>*>q;
	binaryTreeNode<T>* T = root;
	while (T != NULL)
	{
		visit(T);
		//将t的孩子插入队列
		if (T->leftChild != NULL)
			q.push(T->leftChild);
		if (T->rightChild != NULL)
			q.push(T->rightChild);

		//提取下一个要访问的节点
		try { T = q.front(); }
		catch (queueEmpty) { return; }
		q.pop();
	}
}

template<class T>
int linkedBinaryTree<T>::height(binaryTreeNode<T>* T)
{//返回二叉树的高度
	if (T == NULL)return 0;
	int hl = height(T->leftChild);
	int hr = height(T->rightChild);
	if (hl > hr)return hl;
	else return hr;
}

template<class T>
void linkedBinaryTree<T>::preOrder(binaryTreeNode<T>* T)
{//前序遍历二叉树*t
	if (T != NULL)
	{
		visit(T);					//访问树根
		preOrder(T->leftChild);		//前序遍历左子树
		preOrder(T->rightChild);	//前序遍历右子树
	}
}

template<class T>
void linkedBinaryTree<T>::inOrder(binaryTreeNode<T>* T)
{//中序遍历二叉树*t
	if (T != NULL)
	{
		inOrder(T->leftChild);		//前序遍历左子树
		visit(T);					//访问树根
		inOrder(T->rightChild);		//前序遍历右子树
	}
}

template<class T>
void linkedBinaryTree<T>::postOrder(binaryTreeNode<T>* T)
{//后序遍历二叉树*t
	if (T != NULL)
	{
		postOrder(T->leftChild);		//后序遍历左子树
		postOrder(T->rightChild);		//后序遍历右子树
		visit(T);						//访问树根
	}
}