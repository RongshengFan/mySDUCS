#pragma once
#include <iostream>
using namespace std;
template<class T>
class linearList
{
public:
	 virtual ~linearList() {};
	 virtual bool empty()const = 0;									//返回true，当且仅当线性表为空
	 virtual int size()const = 0;									//返回线性表的元素个数
	 virtual T& get(int theIndex)const = 0;							//返回索引为theIndex的元素
	 virtual int indexOf(const T& theElement)const = 0;				//返回theElement第一次出现时的索引
	 virtual void erase(int theIndex) = 0;							//删除索引为theIndex的元素
	 virtual void insert(int theIndex, const T& theElement) = 0;	//把theElement插入线性表中索引为theIndex的位置上
	 virtual void output(ostream& out)const = 0;					//把线性表插入输出流
};

//改变一维数组长度
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