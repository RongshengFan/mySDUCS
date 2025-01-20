#pragma once
template<class T>
class binaryTree
{
public:
	virtual ~binaryTree() {};
	virtual bool empty()const = 0;			 //二叉树为空时返回true
	virtual int size()const = 0;			 //返回二叉树节点数
	virtual void preOrder(void(*)T(*)) = 0;	 //前序遍历
	virtual void inOrder(void(*)T(*)) = 0;	 //中序遍历
	virtual void postOrder(void(*)T(*)) = 0; //后序遍历
	virtual void levelOrder(void(*)T(*)) = 0;//层次遍历
};