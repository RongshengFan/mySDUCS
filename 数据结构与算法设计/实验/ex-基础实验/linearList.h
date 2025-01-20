#pragma once
#include <iostream>
using namespace std;
template<class T>
class linearList
{
public:
	 virtual ~linearList() {};
	 virtual bool empty()const = 0;									//����true�����ҽ������Ա�Ϊ��
	 virtual int size()const = 0;									//�������Ա��Ԫ�ظ���
	 virtual T& get(int theIndex)const = 0;							//��������ΪtheIndex��Ԫ��
	 virtual int indexOf(const T& theElement)const = 0;				//����theElement��һ�γ���ʱ������
	 virtual void erase(int theIndex) = 0;							//ɾ������ΪtheIndex��Ԫ��
	 virtual void insert(int theIndex, const T& theElement) = 0;	//��theElement�������Ա�������ΪtheIndex��λ����
	 virtual void output(ostream& out)const = 0;					//�����Ա���������
};

//�ı�һά���鳤��
template<class T>
void changeLength1D(T*& a, int oldLength, int newLength)
{
	if (newLength < 0)
	{
		throw logic_error("new length must be >= 0");
	}
	T* temp = new T[newLength];
	int n = min(oldLength, newLength);
	copy(a, a + n, temp);
	delete []a;
	a = temp;
}