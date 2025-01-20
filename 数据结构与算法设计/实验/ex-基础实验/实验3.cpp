//#include<iostream>
//#include <string>
//using namespace std;
////定义一个学生结构体，包含该学生信息
//struct student
//{
//	string name;
//	string phone;
//	int classes=0;
//	int room=0;
//};
////实现一个通讯录的线性表
//class adresslist
//{
//public:
//	//构造函数
//	adresslist(int capacity)
//	{
//		arraylength = capacity;
//		a = new student[arraylength];//开辟一个动态数组
//	}
//	~adresslist() { delete[]a; }
//	//插入一组信息
//	void insert(string name, string phone, int c, int r)
//	{
//		student s = { name,phone,c,r };//要插入的信息
//		int n = arraylength;
//		arraylength++;
//		student* temp = new student[arraylength];//新建一个student类型的数组，且长度较原数组加一
//		copy(a, a + n, temp);//将原数组元素存入新数组中
//		temp[n] = s;//将要插入的一组信息插入最末尾处；
//		delete[]a;//释放原数组空间
//		a = temp;
//	}
//	//删除一条信息
//	void erase(string name)
//	{
//		int index;
//		bool flag = false;		//用以判断是否存在要删的信息
//		for (int i = 0; i < arraylength; i++)//寻找要删除信息的索引值
//		{
//			if (a[i].name == name)
//			{
//				index = i;
//				flag = true;
//				break;
//			}
//		}
//		if (flag)
//		{
//			//从索引位置开始，后续元素逐步向前移动一位，由此删去要删除信息
//			for (int i = index; i < arraylength-1; i++)
//			{
//				a[i] = a[i + 1];
//			}
//			student* temp = new student[--arraylength];
//			int n = arraylength;
//			copy(a, a + n, temp);
//			delete[]a;
//			a = temp;
//		}
//	}
//	//编辑信息
//	void edit(string name, int k, string m)
//	{
//		int index;
//		for (int i = 0; i < arraylength; i++)//遍历数组
//		{
//			if (a[i].name == name)
//			{
//				index = i;//记录索引值
//				switch (k)
//				{
//				case 1:
//					a[index].phone = m;//记下电话
//					break;
//				case 2:
//					a[index].classes = stoi(m);//强制将m转换为int类型，记下班级号
//					break;
//				case 3:
//					a[index].room = stoi(m);//记下公寓号
//					break;
//				}
//				break;
//			}
//		}
//	}
//	//查询信息
//	void select(string name)		
//	{;
//		bool flag = false;		//用以判断是否存在要查询的信息
//		for (int i = 0; i < arraylength; i++)//遍历搜索
//		{
//			if (a[i].name == name)
//			{
//				flag = true;
//				break;
//			}
//		}
//		//判断
//		if (flag)cout << "1" << endl;
//		else cout << "0" << endl;
//	}
//	//获取班级学生公寓号异或值
//	void getroomnum(int c)
//	{
//		int s=0;
//		for (int i = 0; i < arraylength; i++)
//		{
//			if (a[i].classes == c)
//			{
//				s ^= a[i].room;//异或
//			}
//		}
//		cout << s << endl;
//	}
//
//private:
//	student* a;		//定义一个student类型的指针a
//	int arraylength;
//};
//
//int main()
//{
//	int n, x, c, r, k;
//	string name, phone,m;
//	adresslist mylist(10);//声明通讯录对象
//	cin >> n;
//	for (int i = 0; i < n; i++)//遍历，依次操作
//	{
//		cin >> x;
//		switch (x)
//			{
//			case 0:
//				cin >> name >> phone >> c >> r;
//				mylist.insert(name, phone, c, r);
//				break;
//			case 1:
//				cin >> name;
//				mylist.erase(name);
//				break;
//			case 2:
//				cin >> name >> k >> m;
//				mylist.edit(name, k, m);
//				break;
//			case 3:
//				cin >> name;
//				mylist.select(name);
//				break;
//			case 4:
//				cin >> c;
//				mylist.getroomnum(c);
//				break;
//			}
//	}
//	return 0;
//}