//#include <iostream>
//#include<string>
//using namespace std;
////ʵ������̽��
////ɢ�б������쳣��Ϣ��
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
////���ؼ���ת��Ϊ�Ǹ��������ֱ�ʵ��string�桢int�桢long���
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
////ʵ��ɢ�б���
//template<class K,class E>
//class hashtable
//{
//public:
//	hashtable(int thedivisor = 11);
//	//����ture�����ҽ����ֵ�Ϊ��
//	bool empty() { return dsize == 0; }
//	//�����ֵ������Ե���Ŀ
//	int size() { return dsize; }
//	//����ƥ�����Ե�ָ��
//	pair<const K, E>* find(const K&)const;
//	//ɾ��ƥ�������
//	void erase(const K&);
//	//���ֵ��в���һ������
//	void insert(const pair<const K, E>&);
//protected:
//	int search(const K&)const;
//	pair<const K, E>** table;//ɢ�б�
//	int divisor;//ɢ�к����ĳ���
//	hash<K>hash;//������kӳ�䵽һ���Ǹ�����
//	int dsize;//�ֵ������Եĸ���
//};
////���캯��
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
////����
//template<class K, class E>
//pair<const K, E>* hashtable<K, E>::find(const K&theKey)const
//{//����theKeyƥ������Ե�ָ�룬����NULL;
//	int b = search(theKey);
//	if (table[b] == NULL || table[b]->first != theKey)
//	{
//		cout << "-1" << endl;
//		return NULL;
//	}
//	else cout << b << endl;
//	return table[b];//�ҵ�ƥ������
//}
////ɾ������
//template<class K, class E>
//void hashtable<K, E>::erase(const K& thekey)
//{
//	int num = 0;
//	int b = search(thekey);//�Ȳ��ҹؼ�����ʼͰλ��
//	if (table[b] == null || table[b]->first != thekey)
//	{
//		cout << "not found" << endl;
//	}
//	//��Ͱλ�ò�Ϊ��
//	else
//	{
//		table[b] = null;//ɾ����ֵ
//		int i = b;		//��¼��ʼͰλ��
//		int j = (b + 1) % divisor;//����ʼͰ���¸�Ͱ��ʼ
//		while (table[j] != null &&j != b )//�ص���ʼͰ���ܻ����Ļ�
//		{
//			int k = (table[j]->first) % divisor;//��¼Ͱj�ؼ��ֳ�����
//			//i,j,k��λ�������������1.k<=i<j;2.j<i,j<k;3.i<j<k
//			if ((k != j)&&((i>=k&&i<j)||(k>j&&(i>=k||i<j))))
//			{
//					table[i] = table[j];
//					table[j]=null;
//					i = j;
//					num++;		
//			}
//			j = (j + 1) % divisor;//��һ��Ͱ
//		}
//		cout<<num<<endl;
//	}
//}
//
//template<class K, class E>
//void hashtable<K, E>::insert(const pair<const K, E>&thepair)
//{//����һ������
//	int b = search(thepair.first);
//	//��ʼͰΪ��Ͱ�����
//	if (table[b] == null)
//	{
//		table[b] = new pair<const K, E>(thepair);
//		dsize++;
//		cout << b << endl;//����ĿҪ������±�
//	}
//	//��ʼͰ��Ϊ�յ����
//	else
//	{
//		//1.���ظ��ؼ��֣����������е�ֵ
//		if (table[b]->first == thepair.first)
//		{
//				table[b]->second = thepair.second;
//				cout << "existed" << endl;//����ĿҪ�����
//		}	
//		//2.Ͱ�������
//		else throw hashTableFull();
//	}
//}
//
//template<class K, class E>
//int hashtable<K, E>::search(const K& thekey) const
//{//����һ��������ַɢ�б����ҹؼ���Ϊthekey������
//	int i =(int)hash(thekey) % divisor;
//	int j = i;//����ʼͰ��ʼ
////	cout << i << endl;
//	do {
//		if (table[j] == null|| table[j]->first == thekey)
//			return j;
//		j = (j + 1 )% divisor;//��һ��Ͱ
//	} while (j != i);//������ʼͰ��
//	return j;//���Ѿ���
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