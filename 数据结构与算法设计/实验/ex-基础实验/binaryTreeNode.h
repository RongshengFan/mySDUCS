#pragma once
template<class T>
struct binaryTreeNode
{
	T element;
	binaryTreeNode<T>* leftChild,  //×ó×ÓÊ÷
					* rightChild;  //ÓÒ×ÓÊ÷
	binaryTreeNode() { leftChild = rightChild = NULL; }
	binaryTreeNode(const T& theElement)
	{
		element(theElement);
		leftChild = rightChild = NULL;
	}
	binaryTreeNode(const T& theElement, binaryTreeNode* theLeftChild, binaryTreeNode* theRightChild)
	{
		element(theElement);
		leftChild = theLeftChild;
		rightChild = theRightChild;
	}
};