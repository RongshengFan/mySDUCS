//#include<iostream>
//using namespace std;
//void subset(int *a,int *b,int *s,bool *j,int l,int n)
//{
//	if(l==n)
//	{
//		int x=0,price=0;
//		for(int i=0;i<n;i++)
//		{
//			if(j[i])
//			{
//				b[x]=a[i];
//				x++;
//			}
//		}
//		for(int i=0;i<x;i++)price+=(i+1)*b[i];
//		(*s)^=price;
//	}
//	else 
//	{
//		j[l]=1;subset(a,b,s,j,l+1,n);
//		j[l]=0;subset(a,b,s,j,l+1,n);
//	}
// } 
//int main()
//{
//	int n;
//	cin>>n;
//	
//	int *a=new int[n];
//	int *b=new int[n];
//	int *ans=new int(0);
//	bool *judge=new bool[n];
//
//	for(int i=0;i<n;i++)cin>>a[i];
//	subset(a,b,ans,judge,0,n);
//	cout<<*ans;
//	
//	delete []a;
//	delete []b;
//	delete ans;
//	delete []judge;
//	return 0;
// } 