#pragma once
#include<iostream>
using namespace std;
template<class T>
class Sort
{
public:
	Sort() {};
	~Sort() {};
	void rankSort(T a[], int n);
	void seletionSort(T a[], int n);
	void bubbleSort(T a[], int n);
	bool bubble(T a[], int n);
	void insertionSort(T a[], int n);
};

//名次排序
template<class T>
void Sort<T>::rankSort(T a[], int n)
{	
	int *r=new int[n];						//开辟一个动态内存数组，用来存名次
	for (int i = 0; i < n; i++)				//初始化
		r[i] = 0;
	for (int i = 0; i < n; i++)				//名次计算
	{
		for (int j = 0; j < i; j++)
		{
			if (a[j] <= a[i])r[i]++;	
			else r[j]++;
		}
	}
	for (int i = 0; i < n; i++)				//根据名次排序
	{
		while (r[i] != i)
		{
			int T = r[i];
			swap(a[i], a[T]);
			swap(r[i], r[T]);
		}
	}
	delete[]r;
}

//及时终止的选择排序
template<class T>
void Sort<T>::seletionSort(T a[],int n)
{
	bool judge = false;									//用于判断是否终止排序
	for (int i = n; !judge && (i > 0); i--)				//从最末尾开始遍历
	{
		int indexOfMax = 0;
		judge = true;
		for (int j = 1; j < i; j++)						//每次寻找最大值，放到最后位置
		{
			if (a[indexOfMax] <= a[j])indexOfMax = j;
			else judge = false;
			swap(a[indexOfMax], a[i-1]);
		}
	}
}

//及时终止的冒泡排序
template<class T>
void Sort<T>::bubbleSort(T a[], int n)
{
	int i = n;
	do {
		i--;
	} while (bubble(a, i));
}
//一次冒泡排序
template<class T>
bool Sort<T>::bubble(T a[], int n)
{
	bool judge = false;
	for (int i = 0; i < n; i++)
	{
		if (a[i] >= a[i + 1])
		{
			swap(a[i], a[i + 1]);
			judge = true;
		}
	}
	return judge;
}

//插入排序
template<class T>
void Sort<T>::insertionSort(T a[], int n)
{
	for (int i = 1; i < n; i++)
	{
		int j;
		T T = a[i];
		for (j = i - 1; j >= 0 && T < a[j]; j--)
		{
			a[j + 1] = a[j];
		}
		a[j + 1] = T;
	}
}


