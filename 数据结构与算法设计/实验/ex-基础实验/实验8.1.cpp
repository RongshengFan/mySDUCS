//#include <iostream>
//#include<string>
//using namespace std;
////实现线性探查
////散列表满的异常信息类
//class hashTableFull
//{
//public:
//	hashTableFull(string message="hash table is full")
//	{
//		*this = message;
//	}
//	void outputmessage()
//	{
//		cout << message << endl;
//	}
//private:
//	string message;
//};
////将关键字转换为非负整数，分别实现string版、int版、long版等
//template<class K>class Hash;
//template<>
//class Hash<string>
//{
//public:
//	size_t operator()(const string theKey) const
//	{
//		unsigned long hashValue = 0;
//		int length = (int)theKey.length();
//		for (int i = 0; i < length; i++)
//			hashValue = 5 * hashValue + theKey.at(i);
//
//		return size_t(hashValue);
//	}
//};
//template<>
//class Hash<int>
//{
//public:
//	size_t operator()(const int thekey)const
//	{
//		return size_t(thekey);
//	}
//};
//template<>
//class Hash<long>
//{
//public:
//	size_t operator()(const long thekey)const
//	{
//		return size_t(thekey);
//	}
//};
////实现散列表类
//template<class K,class E>
//class hashtable
//{
//public:
//	hashtable(int thedivisor = 11);
//	//返回ture，当且仅当字典为空
//	bool empty() { return dsize == 0; }
//	//返回字典中数对的数目
//	int size() { return dsize; }
//	//返回匹配数对的指针
//	pair<const K, E>* find(const K&)const;
//	//删除匹配的数对
//	void erase(const K&);
//	//往字典中插入一个数对
//	void insert(const pair<const K, E>&);
//protected:
//	int search(const K&)const;
//	pair<const K, E>** table;//散列表
//	int divisor;//散列函数的除数
//	hash<K>hash;//把类型k映射到一个非负整数
//	int dsize;//字典中数对的个数
//};
////构造函数
//template<class K, class E>
//hashtable<K, E>::hashtable(int thedivisor)
//{
//	if (thedivisor <= 0)exit(1);
//	divisor = thedivisor;
//	dsize = 0;
//	table = new pair<const K, E>*[divisor];
//	for (int i = 0; i < divisor; i++)
//		table[i] = NULL;
//}
////函数
//template<class K, class E>
//pair<const K, E>* hashtable<K, E>::find(const K&theKey)const
//{//返回theKey匹配的数对的指针，否则返NULL;
//	int b = search(theKey);
//	if (table[b] == NULL || table[b]->first != theKey)
//	{
//		cout << "-1" << endl;
//		return NULL;
//	}
//	else cout << b << endl;
//	return table[b];//找到匹配数对
//}
////删除函数
//template<class K, class E>
//void hashtable<K, E>::erase(const K& thekey)
//{
//	int num = 0;
//	int b = search(thekey);//先查找关键字起始桶位置
//	if (table[b] == null || table[b]->first != thekey)
//	{
//		cout << "not found" << endl;
//	}
//	//该桶位置不为空
//	else
//	{
//		table[b] = null;//删除其值
//		int i = b;		//记录起始桶位置
//		int j = (b + 1) % divisor;//从起始桶的下个桶开始
//		while (table[j] != null &&j != b )//回到起始桶？能回来的话
//		{
//			int k = (table[j]->first) % divisor;//记录桶j关键字除余数
//			//i,j,k的位置有三种情况：1.k<=i<j;2.j<i,j<k;3.i<j<k
//			if ((k != j)&&((i>=k&&i<j)||(k>j&&(i>=k||i<j))))
//			{
//					table[i] = table[j];
//					table[j]=null;
//					i = j;
//					num++;		
//			}
//			j = (j + 1) % divisor;//下一个桶
//		}
//		cout<<num<<endl;
//	}
//}
//
//template<class K, class E>
//void hashtable<K, E>::insert(const pair<const K, E>&thepair)
//{//插入一个数对
//	int b = search(thepair.first);
//	//起始桶为空桶的情况
//	if (table[b] == null)
//	{
//		table[b] = new pair<const K, E>(thepair);
//		dsize++;
//		cout << b << endl;//按题目要求输出下标
//	}
//	//起始桶不为空的情况
//	else
//	{
//		//1.有重复关键字，覆盖数对中的值
//		if (table[b]->first == thepair.first)
//		{
//				table[b]->second = thepair.second;
//				cout << "existed" << endl;//按题目要求输出
//		}	
//		//2.桶满的情况
//		else throw hashTableFull();
//	}
//}
//
//template<class K, class E>
//int hashtable<K, E>::search(const K& thekey) const
//{//搜索一个公开地址散列表，查找关键字为thekey的数对
//	int i =(int)hash(thekey) % divisor;
//	int j = i;//从起始桶开始
////	cout << i << endl;
//	do {
//		if (table[j] == null|| table[j]->first == thekey)
//			return j;
//		j = (j + 1 )% divisor;//下一个桶
//	} while (j != i);//返回起始桶？
//	return j;//表已经满
//}
//int main()
//{
//	int d, m;
//	int opt, x;
//	cin >> d >> m;
//	hashtable<int, int>table(d);
//	pair<int, int>p;
//	for (int i = 0; i < m; i++)
//	{
//		cin >> opt >> x;
//		switch (opt)
//		{
//		case 0:
//			p.first = x;
//			p.second = x;
//			table.insert(p);
//			break;
//		case 1:
//			table.find(x);
//			break;
//		case 2:
//			table.erase(x);
//			break;
//		default:
//			break;
//		}
//	}
//	return 0;
//}