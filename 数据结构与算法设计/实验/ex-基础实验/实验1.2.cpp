//#include<iostream>
////#include<bits/stdc++.h>
//using namespace std;
//void change(int d[], int i, int j)//����ֵ 
//{
//	int t = d[i];
//	d[i] = d[j];
//	d[j] = t;
//}
//void perm(int d[], int* s, int l, int n)
//{
//	if (l == n)
//	{
//		int price = 0;
//
//		for (int i = 1; i <= n; i++)price += i ^ d[i];//�������м�ֵ
//
//		(*s) |= price;//���л�����������ַs�� 
//	}
//	else
//	{
//		for (int i = l; i <= n; i++)
//		{
//			change(d, l, i);
//			perm(d, s, l + 1, n);
//			change(d, l, i);
//		}
//	}
//}
//int main()
//{
//	int n;
//	cin >> n;
//
//	int* a = new int[n + 1];
//	int* ans = new int(0);
//
//	for (int i = 1; i <= n; i++)cin >> a[i];
//
//	perm(a, ans, 1, n);
//
//	cout << *ans;
//
//	delete ans;
//	delete []a;
//
//	return 0;
//}