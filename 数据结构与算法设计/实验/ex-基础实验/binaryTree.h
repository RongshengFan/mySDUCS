#pragma once
template<class T>
class binaryTree
{
public:
	virtual ~binaryTree() {};
	virtual bool empty()const = 0;			 //������Ϊ��ʱ����true
	virtual int size()const = 0;			 //���ض������ڵ���
	virtual void preOrder(void(*)T(*)) = 0;	 //ǰ�����
	virtual void inOrder(void(*)T(*)) = 0;	 //�������
	virtual void postOrder(void(*)T(*)) = 0; //�������
	virtual void levelOrder(void(*)T(*)) = 0;//��α���
};