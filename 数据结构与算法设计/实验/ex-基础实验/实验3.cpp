//#include<iostream>
//#include <string>
//using namespace std;
////����һ��ѧ���ṹ�壬������ѧ����Ϣ
//struct student
//{
//	string name;
//	string phone;
//	int classes=0;
//	int room=0;
//};
////ʵ��һ��ͨѶ¼�����Ա�
//class adresslist
//{
//public:
//	//���캯��
//	adresslist(int capacity)
//	{
//		arraylength = capacity;
//		a = new student[arraylength];//����һ����̬����
//	}
//	~adresslist() { delete[]a; }
//	//����һ����Ϣ
//	void insert(string name, string phone, int c, int r)
//	{
//		student s = { name,phone,c,r };//Ҫ�������Ϣ
//		int n = arraylength;
//		arraylength++;
//		student* temp = new student[arraylength];//�½�һ��student���͵����飬�ҳ��Ƚ�ԭ�����һ
//		copy(a, a + n, temp);//��ԭ����Ԫ�ش�����������
//		temp[n] = s;//��Ҫ�����һ����Ϣ������ĩβ����
//		delete[]a;//�ͷ�ԭ����ռ�
//		a = temp;
//	}
//	//ɾ��һ����Ϣ
//	void erase(string name)
//	{
//		int index;
//		bool flag = false;		//�����ж��Ƿ����Ҫɾ����Ϣ
//		for (int i = 0; i < arraylength; i++)//Ѱ��Ҫɾ����Ϣ������ֵ
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
//			//������λ�ÿ�ʼ������Ԫ������ǰ�ƶ�һλ���ɴ�ɾȥҪɾ����Ϣ
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
//	//�༭��Ϣ
//	void edit(string name, int k, string m)
//	{
//		int index;
//		for (int i = 0; i < arraylength; i++)//��������
//		{
//			if (a[i].name == name)
//			{
//				index = i;//��¼����ֵ
//				switch (k)
//				{
//				case 1:
//					a[index].phone = m;//���µ绰
//					break;
//				case 2:
//					a[index].classes = stoi(m);//ǿ�ƽ�mת��Ϊint���ͣ����°༶��
//					break;
//				case 3:
//					a[index].room = stoi(m);//���¹�Ԣ��
//					break;
//				}
//				break;
//			}
//		}
//	}
//	//��ѯ��Ϣ
//	void select(string name)		
//	{;
//		bool flag = false;		//�����ж��Ƿ����Ҫ��ѯ����Ϣ
//		for (int i = 0; i < arraylength; i++)//��������
//		{
//			if (a[i].name == name)
//			{
//				flag = true;
//				break;
//			}
//		}
//		//�ж�
//		if (flag)cout << "1" << endl;
//		else cout << "0" << endl;
//	}
//	//��ȡ�༶ѧ����Ԣ�����ֵ
//	void getroomnum(int c)
//	{
//		int s=0;
//		for (int i = 0; i < arraylength; i++)
//		{
//			if (a[i].classes == c)
//			{
//				s ^= a[i].room;//���
//			}
//		}
//		cout << s << endl;
//	}
//
//private:
//	student* a;		//����һ��student���͵�ָ��a
//	int arraylength;
//};
//
//int main()
//{
//	int n, x, c, r, k;
//	string name, phone,m;
//	adresslist mylist(10);//����ͨѶ¼����
//	cin >> n;
//	for (int i = 0; i < n; i++)//���������β���
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