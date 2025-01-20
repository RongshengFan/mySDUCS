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
//�쳣��
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
//��С��
template<class T>
class minheap
{
public:
	minheap(int initcapacility=10);
	//~minheap() { delete[]heap; }//��Ҫ����
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
{//���캯��
	arraylength = initialcapacity + 1;
	heap = new T[arraylength];
	heapsize = 0;
}
//ɾ��
template<class T>
void minheap<T>::pop()
{
	//ɾ�����Ԫ��
	heap[1].~T();

	//ɾ�����һ��Ԫ��Ȼ�����½���
	T lastelement = heap[heapsize--];
	//ΪԪ��rootelementѰ��λ��
	int currentnode = 1, child = 2;
	while (child <= heapsize)
	{
		//heap[child]Ӧ���ֵ��н�С��
		if (child < heapsize && heap[child] > heap[child + 1])
			child++;
		//���԰�Ԫ�ط���heap[currentnode]��
		if (lastelement <= heap[child])
			break;//����
		//������
		heap[currentnode] = heap[child];//�Ѻ���������
		currentnode = child;            //�Ƶ���һ��
		child *= 2;
	}
	heap[currentnode] = lastelement;//����
}
template<class T>
void minheap<T>::push(const T& theelement)
{
	//����
	if (heapsize == arraylength - 1)
	{
		changelength1d(heap, arraylength, 2 * arraylength);
		arraylength *= 2;
	}
	//ΪԪ��Ѱ�Ҳ���λ��
	//currentnode����Ҷ�������ƶ�
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

	//�ѻ�
	for (int root = heapsize / 2; root >= 1; root--)
	{
		T rootelement = heap[root];
		//ΪԪ��rootelementѰ��λ��
		int child = 2 * root;//���ӵ�˫����Ԫ��rootelement��λ��
		while (child <= heapsize)
		{
			//heap[child]Ӧ���ֵ��н�С��
			if (child < heapsize && heap[child] > heap[child + 1])
				child++;
			//���԰�Ԫ�ط���heap[child/2]��
			if (rootelement <= heap[child])
				break;//����
			//������
			heap[child / 2] = heap[child];//�Ѻ���������
			child *= 2;                   //�Ƶ���һ��
		}
		heap[child / 2] = rootelement;//����
	}
}