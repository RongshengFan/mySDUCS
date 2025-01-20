#pragma once
#include<string>
#include<iostream>
using namespace std;
template<class T>
void changelength1d(T*& a, int oldlength, int newlength)
{
	if (newlength < 0)
	{
		throw logic_error("new length must be >= 0");
	}
	T* temp = new T[newlength];
	int n = min(oldlength, newlength);
	copy(a, a + n, temp);
	delete[]a;
	a = temp;
}
//异常类
class queueempty
{
public:
	queueempty(string themessage =
		"invalid operation on empty queue")
	{
		message = themessage;
	}
	void outputmessage() { cout << message << endl; }
private:
	string message;
};
//最小堆
template<class T>
class minheap
{
public:
	minheap(int initcapacility=10);
	//~minheap() { delete[]heap; }//不要析构
	bool empty()const { return heapsize == 0; }
	int size()const { return heapsize; }
	const T& top()
	{
		if (heapsize == 0)
			throw queueempty();
		return heap[1];
	}
	void pop();
	void push(const T&);
	void initialize(T*, int);
	void deactivatearray()
	{
		heap = null; heapsize = arraylength = 0;
	}
private:
	T* heap;
	int heapsize;
	int arraylength;
};
template<class T>
minheap<T>::minheap(int initialcapacity)
{//构造函数
	arraylength = initialcapacity + 1;
	heap = new T[arraylength];
	heapsize = 0;
}
//删除
template<class T>
void minheap<T>::pop()
{
	//删除最大元素
	heap[1].~T();

	//删除最后一个元素然后重新建堆
	T lastelement = heap[heapsize--];
	//为元素rootelement寻找位置
	int currentnode = 1, child = 2;
	while (child <= heapsize)
	{
		//heap[child]应是兄弟中较小者
		if (child < heapsize && heap[child] > heap[child + 1])
			child++;
		//可以把元素放在heap[currentnode]中
		if (lastelement <= heap[child])
			break;//可以
		//不可以
		heap[currentnode] = heap[child];//把孩子向上移
		currentnode = child;            //移到下一层
		child *= 2;
	}
	heap[currentnode] = lastelement;//插入
}
template<class T>
void minheap<T>::push(const T& theelement)
{
	//扩容
	if (heapsize == arraylength - 1)
	{
		changelength1d(heap, arraylength, 2 * arraylength);
		arraylength *= 2;
	}
	//为元素寻找插入位置
	//currentnode从新叶子向上移动
	int currentnode = ++heapsize;
	while (currentnode != 1 && heap[currentnode / 2] > theelement)
	{
		heap[currentnode] = heap[currentnode / 2];
		currentnode /= 2;
	}
	heap[currentnode] = theelement;
}
template<class T>
void minheap<T>::initialize(T* theheap, int thesize)
{
	delete[]heap;
	heap = theheap;
	heapsize = thesize;

	//堆化
	for (int root = heapsize / 2; root >= 1; root--)
	{
		T rootelement = heap[root];
		//为元素rootelement寻找位置
		int child = 2 * root;//孩子的双亲是元素rootelement的位置
		while (child <= heapsize)
		{
			//heap[child]应是兄弟中较小者
			if (child < heapsize && heap[child] > heap[child + 1])
				child++;
			//可以把元素放在heap[child/2]中
			if (rootelement <= heap[child])
				break;//可以
			//不可以
			heap[child / 2] = heap[child];//把孩子向上移
			child *= 2;                   //移到下一层
		}
		heap[child / 2] = rootelement;//插入
	}
}