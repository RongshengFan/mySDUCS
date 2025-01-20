#pragma once
#include"linearList.h"
#include <sstream>
#include <algorithm>
#include <iterator>
using namespace std;
template<class T>
class linearList;

template<class T>
class arrayList : public linearList<T>
{
public:
	arrayList(int initialCapacity = 10);
	arrayList(const arrayList<T>& theList);
	~arrayList(){ delete  []element; }

	//��������
	bool empty()const { return listSize == 0; }
	int size()const { return listSize; }
	T& get(int theIndex)const override;
	int indexOf(const T& theElement)const override;
	void erase(int theIndex)override;
	void insert(int theIndex,const T& theElement)override;
	void output(ostream& out)const override;

	//��������
	int capacity()const { return arrayLength; }	
	arrayList<T>& trimToSize();									
	arrayList<T>& setSize(int length);							
	T& operator[](int i);
	bool operator==(const arrayList<T>& right)const;
	bool operator!=(const arrayList<T>& right)const;
	bool operator< (const arrayList<T>& right)const;
	void push_back(const T& theElement);
	T& pop_back();
	arrayList<T>& swap(arrayList thelist)const;
	arrayList<T>& reserve(int theCapacity)const;
	T set(int intIndex, const T& theElement);
	arrayList<T>& clear();
	arrayList<T>& removeRange(int startIndex, int endIndex);
	int lastIndexOf(const T& theElement)const;

	arrayList<T>& decreaseArray(int capacity);
	arrayList<T>& reverse();
	arrayList<T>& leftShift(int shift);
	arrayList<T>& circularShift(int shift);
	arrayList<T>& half();
	arrayList<T>& meld(arrayList<T>& a, arrayList<T>& b);
	arrayList<T>& split(arrayList<T>& a, arrayList<T>& b);

	void input()
	{
		int len;
		cin >> len;
		arrayLength = len;
	}

public:
	class iterator
	{
	public:
		typedef bidirectional_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;

		//���캯��
		iterator(T* thePosition = 0) { position = thePosition; }

		//�����ò�����
		T& operator*()const { return *position; }
		T* operator->()const { return &*position; }

		//��������ֵ����
		iterator& operator++()//ǰ��
		{
			++position;
			return *this;
		}
		iterator operator++(int)//���
		{
			iterator old = *this;
			--position;
			return old;
		}
		//��������ֵ����
		iterator& operator--()//ǰ��
		{
			++position;
			return *this;
		}
		iterator operator--(int)//���
		{
			iterator old = *this;
			--position;
			return old;
		}

		//�����Ƿ����
		bool operator!=(const iterator right)const
		{
			return position != right.position;
		}
		bool operator==(const iterator right)const
		{
			return position == right.position;
		}

		////��չ��ʹ֮��Ϊ������ʵ�����
		//T& operator[](int i)
		//{
		//	return *(position + i);
		//}
		//ptrdiff_t operator-(const arrayList<T>::iterator& right)const
		//{
		//	return position-right.position;
		//}
		//T& operator-(const ptrdiff_t& diff)const
		//{
		//	return *(position - diff);
		//}
		//T& operator+(const ptrdiff_t& diff)const
		//{
		//	return *(position + diff);
		//}

	protected:
		T* position;		//ָ���Ԫ�ص�ָ��
	};

	iterator begin() { return iterator(element); }
	iterator end() { return iterator(element + listSize); }

private:
	void checkIndex(int thIndex)const; 	 
	void increaseArray(int capacity);	
	
	T* element;                          //�洢���Ա�Ԫ�ص�һά����
	int arrayLength;					 //һά���������
	int listSize;						 //���Ա��Ԫ�ظ���
};

//���캯��
template<class T>
arrayList<T>::arrayList(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		ostringstream s;
		s << "Initial capacity = " << initialCapacity << "must be > 0";
		throw logic_error(s.str());
	}
	arrayLength = initialCapacity;
	element = new T[arrayLength];
	listSize = 0;
}
//���ƹ��캯��
template<class T>
arrayList<T>::arrayList(const arrayList<T>& theList)
{
	arrayLength = theList.arrayLength;
	listSize = theList.listSize;
	element = new T[arrayLength];
	copy(theList.element, theList.element + listSize, element);

	/*for (int i = 0; i < theList.listSize; i++)
	{
		element[i] = theList.element[i];
	}*/
}

//���� theIndex ��Ч���׳��쳣
template<class T>
void arrayList<T>::checkIndex(int theIndex) const
{
	if (theIndex<0 || theIndex>listSize)
	{
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw logic_error(s.str());
	}
}
//����
template<class T>
void arrayList<T>::increaseArray(int capacity)
{
	if (capacity <= arrayLength)
	{
		cout << " input capacity <= arrayLength";
		return;
	}
	changeLength1D(element, arrayLength, capacity);
	arrayLength = capacity;
}
//��������theIndex��Ԫ�أ��������ھ��׳��쳣
template<class T>
T& arrayList<T>::get(int theIndex) const
{
	checkIndex(theIndex);
	return element[theIndex];
}
//����Ԫ��theElement��һ�γ���ʱ�����������򷵻�-1
template<class T>
int arrayList<T>::indexOf(const T& theElement) const
{
	int theIndex = (int)(find(element, element + listSize, theElement) - element);
	if (theIndex == listSize)
		return -1;
	else
		return theIndex;
}
//ɾ������ΪtheIndex��Ԫ��
template<class T>
void arrayList<T>::erase(int theIndex)
{
	checkIndex(theIndex);
	copy(element + theIndex + 1, element + listSize, element + theIndex);
	element[--listSize].~T();
}
//������ΪtheIndex��λ���ϲ���һ��Ԫ��
template<class T>
void arrayList<T>::insert(int theIndex, const T& theElement)
{
	checkIndex(theIndex);
	if (listSize == arrayLength)
	{
		changeLength1D(element, arrayLength, 2 * arrayLength);
	}
	copy_backward(element + theIndex, element + listSize, element + listSize + 1);
	element[theIndex] = theElement;
}
template<class T>
void arrayList<T>::output(ostream& out) const
{
	copy(element, element + listSize, ostream_iterator<T>(out, " "));
}
template <class T>
ostream& operator<<(ostream& out, const arrayList<T>& a)
{
	a.output(out);
	return out;
}
//ʹ���鳤�ȵ���max{listSize,1}
template<class T>
arrayList<T>& arrayList<T>::trimToSize()
{
	// TODO: �ڴ˴����� return ���
}
//ʹ���Ա�Ĵ�С����ָ����С����ʼ��С��С��ָ������������Ԫ�أ���֮ɾ��Ԫ��
template<class T>
arrayList<T>& arrayList<T>::setSize(int length)
{
	// TODO: �ڴ˴����� return ���
}

template<class T>
T& arrayList<T>::operator[](int i)
{
	// TODO: �ڴ˴����� return ���
}

template<class T>
bool arrayList<T>::operator==(const arrayList<T>& right) const
{
	return false;
}

template<class T>
bool arrayList<T>::operator!=(const arrayList<T>& right) const
{
	return false;
}

template<class T>
bool arrayList<T>::operator<(const arrayList<T>& right) const
{
	return false;
}

template<class T>
void arrayList<T>::push_back(const T& theElement)
{
	if (listSize == arrayLength)
	{
		arrayLength *= 2;
	}
	listSize++;
	element[listSize] = theElement;
}
template<class T>
T& arrayList<T>::pop_back()
{
	if (listSize == 0)
	{
		ostringstream s;
		s << "arrayList is empty";
		throw logic_error(s.str());
	}
	T& theElement = element[--listSize];
	if (listSize < arrayLength / 4)
	{
		arrayLength /= 2;
	}
	return theElement;
}
template<class T>
arrayList<T>& arrayList<T>::swap(arrayList thelist)const
{
	T& temp = element;
	element = thelist.element;
	thelist.element = temp;

	int l = listSize;
	listSize = thelist.listSize;
	thelist.listSize = l;

	int capacity = arrayLength;
	arrayLength = thelist.arrayLength;
	thelist.arrayLength = capacity;

	return *this;
}
template<class T>
arrayList<T>& arrayList<T>::reserve(int theCapacity)const
{
	if (theCapacity <= arrayLength) return *this;
	changeLength1D(element, arrayLength, theCapacity);
	arrayLength = theCapacity;
	return *this;
}
template<class T>
T arrayList<T>::set(int intIndex, const T& theElement)
{
	return T();
}
template<class T>
arrayList<T>& arrayList<T>::clear()
{
	// TODO: �ڴ˴����� return ���
}
template<class T>
arrayList<T>& arrayList<T>::removeRange(int startIndex, int endIndex)
{
	// TODO: �ڴ˴����� return ���
}
template<class T>
int arrayList<T>::lastIndexOf(const T& theElement) const
{
	return 0;
}
template<class T>
arrayList<T>& arrayList<T>::decreaseArray(int capacity)
{
	// TODO: �ڴ˴����� return ���
}
template<class T>
arrayList<T>& arrayList<T>::reverse()
{
	// TODO: �ڴ˴����� return ���
}
template<class T>
arrayList<T>& arrayList<T>::leftShift(int shift)
{
	// TODO: �ڴ˴����� return ���
}
template<class T>
arrayList<T>& arrayList<T>::circularShift(int shift)
{
	// TODO: �ڴ˴����� return ���
}
template<class T>
arrayList<T>& arrayList<T>::half()
{
	// TODO: �ڴ˴����� return ���
}
template<class T>
arrayList<T>& arrayList<T>::meld(arrayList<T>& a, arrayList<T>& b)
{
	// TODO: �ڴ˴����� return ���
}
template<class T>
arrayList<T>& arrayList<T>::split(arrayList<T>& a, arrayList<T>& b)
{
	// TODO: �ڴ˴����� return ���
}
