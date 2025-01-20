#pragma once
template<class K,class T>
class dictionary
{
public:
	//��������
	virtual ~dictionary() {};
	//����ture�����ҽ����ֵ�Ϊ��
	virtual bool empty()const = 0;
	//�����ֵ������Ե���Ŀ
	virtual int size()const = 0;
	//����ƥ�����Ե�ָ��
	virtual pair<const K, T>* find(const K&)const = 0;
	//ɾ��ƥ�������
	virtual void erase(const K&) = 0;
	//���ֵ��в���һ������
	virtual void insert(const pair<const K, T>&) = 0;
};