//#include <iostream>
//#include <cstdio>
//#include <cstdlib> 
//#include <algorithm>
//#include <cstring>
//#include <string>
//#include <climits>
//#include <fstream>
//#include <WTypesbase.h>
//#include<bits/stdc++.h>
//using namespace std;
//
//int Count;		//�������ļ������ݸ��� 
//int BUF_PAGES;  //�������ж��ٸ�page 
//int PAGE_SIZE; //page�Ĵ�С 
//int BUF_SIZE;//BUF_PAGES*PAGE_SIZE; //��������С
//char* input_file;//�����ļ���  
//
////������ 
//struct Page {
//	int* arr;
//	int current; //��ǰ˳��ɨ���λ�� 
//	Page() {
//		current = 0;
//	}
//	Page(int bufsize) {
//		arr = new int[bufsize + 1];
//		current = 0;
//	}
//};
//
////ѡ�� 
//struct player {
//	int id;//��� 
//	int element;//Ԫ�� 
//	//Ӯ�߹��� 
//	friend bool operator<(const player& s1, const player& s2) {
//		if (s1.id != s2.id)
//			return s1.id < s2.id;
//
//		else
//			return s1.element < s2.element;
//	}
//	//��������� = 
//	player& operator=(const player& s) {
//		id = s.id;
//		element = s.element;
//		return *this;
//	}
//};
//
////������ 
//class LoserTree {
//public:
//	LoserTree() {}
//	~LoserTree() {}
//	//��ʼ�� 
//	void Initialize(int kk);
//	//����Ӯ�� 
//	int Winner() { return tree[0]; }
//	//�ع� 
//	void Adjust(int s);
//	void Adjust(int*, player*, int, int);
//	//��������˳�� 
//	void Generate_1();
//	//����������˳�� 
//	void Generate_2();
//	//K·�鲢 
//	void K_Merge(int start, int k);
//	//������
//	void ExternSort(int k);
//	//�����ݿ�
//	int Read_Data_Block(FILE* file, int a[], int n);
//	//д���ݿ�
//	void Write_Data_Block(FILE* file, int a[], int n);
//	//��ȡ��ʱ�ļ����� 
//	char* Get_Filename(int index);
//private:
//	int* tree;	//�ڲ���� 
//	int* leave; //�ⲿ���          
//	int k;      //ѡ�ָ���  
//	int file_count;	//��ʱ�ļ���Ŀ	 	
//};
//
////��ȡ��ʱ�ļ����� 
//char* LoserTree::Get_Filename(int index) {
//	char* tempname = new char[100];
//	sprintf(tempname, "temp%d.txt", index);
//	return tempname;
//}
//
////������ж����ݿ� 
//int LoserTree::Read_Data_Block(FILE* file, int a[], int n) {
//	int i = 0;
//	while (i < n && (fscanf(file, "%d", &a[i])) != EOF)
//		i++;
//	return i;
//}
//
////�������д���ݿ� 
//void LoserTree::Write_Data_Block(FILE* file, int a[], int n) {
//	for (int i = 0; i < n; i++)
//		fprintf(file, "%d ", a[i]);
//	fprintf(file, "%d", INT_MAX);
//}
//
////��ʼ�� 
//void LoserTree::Initialize(int kk) {
//	k = kk;
//	leave[k] = INT_MIN;
//	for (int i = 0; i < k; i++)
//		tree[i] = k;
//	for (int i = 0; i < k; i++)
//		Adjust(i);
//}
//
////�ع������� 
//void LoserTree::Adjust(int s) {
//	//���ڵ� 
//	int t = (s + k) >> 1;
//	//���ϵ��� 
//	while (t > 0) {
//		if (leave[s] > leave[tree[t]]) {
//			s ^= tree[t];
//			tree[t] ^= s;
//			s ^= tree[t];
//		}
//		t >>= 1;
//	}
//	tree[0] = s;
//}
//
////���ÿ�����������˳�� 
//void LoserTree::Generate_1() {
//	FILE* fin = fopen(input_file, "rt");
//	int n = 0;
//	file_count = 0;
//	//�ڲ������� 
//	int* array = new int[BUF_SIZE / 2];
//	while ((n = Read_Data_Block(fin, array, BUF_SIZE / 2)) > 0) {
//		sort(array, array + BUF_SIZE / 2);
//		char* filename = Get_Filename(file_count++);
//		FILE* tempfile = fopen(filename, "w");
//		free(filename);
//		Write_Data_Block(tempfile, array, n);
//		fclose(tempfile);
//	}
//	delete[] array;
//	fclose(fin);
//	cout << file_count << endl;
//}
//
////�ع������� 
//void LoserTree::Adjust(int* tree, player* leave, int s, int k) {
//	int t = (s + k) >> 1;
//	while (t > 0) {
//		if (leave[tree[t]] < leave[s]) {
//			s ^= tree[t];
//			tree[t] ^= s;
//			s ^= tree[t];
//		}
//		t >>= 1;
//	}
//	tree[0] = s;
//}
//
////����������˳�� 
//void LoserTree::Generate_2() {
//	file_count = 0;
//	int K = BUF_SIZE / 2;
//	int* Tree = new int[K];
//	player* Leave = new player[K + 1];
//	int OutputNum = Count / BUF_SIZE + 10;
//	//�ļ������ 
//	ofstream* out = new ofstream[OutputNum];
//	for (int i = 0; i < OutputNum; i++) {
//		char* tmp = Get_Filename(i);
//		out[i].open(tmp, ios::app);
//	}
//	//�ļ������� 
//	ifstream in;
//	in.open(input_file);
//	if (!in.is_open()) {
//		cout << "���󣺵�ǰĿ¼�¸��ļ������ڣ�" << endl;
//		exit(0);
//	}
//	for (int i = 0; i < K; i++) {
//		in >> Leave[i].element;
//		Leave[i].id = 0;
//	}
//	//��ʼ�������� 
//	Leave[K].element = INT_MIN;
//	Leave[K].id = -1;
//	for (int i = 0; i < K; i++)
//		Tree[i] = K;
//	for (int i = 0; i < K; i++)
//		Adjust(Tree, Leave, i, K);
//	int maxid = 0;
//	//���������� 
//	while (Leave[Tree[0]].element != INT_MAX) {
//		int p = Tree[0];
//		file_count = max(file_count, Leave[p].id);
//		out[Leave[p].id] << Leave[p].element << " ";
//		//�����ļ�β 
//		if (in.eof()) {
//			Leave[p].element = INT_MAX;
//			Leave[p].id = INT_MAX;
//			in.close();
//		}
//		//������Ԫ�ز�ȷ��˳���� 
//		else {
//			int element;
//			in >> element;
//			if (element < Leave[p].element) {
//				Leave[p].id++;
//			}
//			Leave[p].element = element;
//		}
//		//�ع������� 
//		Adjust(Tree, Leave, p, K);
//	}
//	file_count++;
//	//��� ����Ϊ��ֹ�� 
//	for (int i = 0; i < file_count; i++) {
//		out[i] << INT_MAX;
//		out[i].close();
//	}
//}
//
////K·�ϲ� 
//void LoserTree::K_Merge(int start, int k) {
//	int count = file_count - start;
//	if (count <= 1)
//		return;
//	int runs = count / k;
//	int cur = file_count;
//	if (count % k != 0)
//		runs++;
//	int cnt = runs;
//	int j = start;
//	int K = k;
//	//ִ��runs��k·�鲢 
//	while (cnt--) {
//		k = min(K, cur - j);
//		ifstream* in = new ifstream[k];
//		//��ȡ��ǰҪ�鲢����ʱ�ļ� 
//		for (int i = 0; i < k; i++) {
//			char* tmp = Get_Filename(j++);
//			in[i].open(tmp);
//		}
//		//���뻺���� 
//		Page* Buffer = new Page[k];
//		for (int i = 0; i < k; i++) {
//			Buffer[i] = Page(BUF_SIZE);
//		}
//		//�������뻺���� 
//		for (int i = 0; i < k; i++) {
//			int num = 0;
//			while (num < PAGE_SIZE && !in[i].eof()) {
//				in[i] >> Buffer[i].arr[num];
//				num++;
//			}
//			Buffer[i].current = 0;
//		}
//		//��ȡ�ⲿ�ڵ� 
//		for (int i = 0; i < k; i++) {
//			leave[i] = Buffer[i].arr[0];
//			Buffer[i].current++;
//		}
//		//��ʼ�������� 
//		Initialize(k);
//		int p;
//		//��������� 
//		int* res = new int[PAGE_SIZE];
//		int idx = 0;
//		char* outputfile = Get_Filename(file_count);
//		ofstream out(outputfile);
//		//����������	
//		while (leave[tree[0]] != INT_MAX) {
//			p = tree[0];  //pΪ��ǰ��С�ؼ������ڵ�˳�� 
//			res[idx++] = leave[p];
//			//��������������������ݿ�д����� 
//			if (idx == PAGE_SIZE) {
//				for (idx = 0; idx < PAGE_SIZE; idx++) {
//					out << res[idx] << " ";
//				}
//				idx = 0;
//			}
//			//���뻺�����ѿգ������������ݿ� 
//			if (Buffer[p].current >= PAGE_SIZE) {
//				int num = 0;
//				while (num < PAGE_SIZE && !in[p].eof()) {
//					in[p] >> Buffer[p].arr[num];
//					num++;
//				}
//				Buffer[p].current = 0;
//				leave[p] = Buffer[p].arr[Buffer[p].current];
//				Buffer[p].current++;
//			}
//			//������ȡ������ 
//			else {
//				leave[p] = Buffer[p].arr[Buffer[p].current];
//				Buffer[p].current++;
//			}
//			//�ع������� 
//			Adjust(p);
//		}
//		//���������ʣ������д����� 
//		for (int oidx = 0; oidx < idx; oidx++) {
//			out << res[oidx] << " ";
//		}
//		//��ֹ�� 
//		out << INT_MAX;
//		//�ر��ļ��� 
//		for (int i = 0; i < k; i++) {
//			in[i].close();
//		}
//		out.close();
//		file_count++;
//	}
//	//������һ�ֹ鲢 
//	K_Merge(j, K);
//}
//
////������ 
//void LoserTree::ExternSort(int K) {
//	double time = 0;
//	double counts = 0;
//	LARGE_INTEGER nFreq;
//	LARGE_INTEGER nBeginTime;
//	LARGE_INTEGER nEndTime;
//	QueryPerformanceFrequency(&nFreq);
//	QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ 
//	//���ɳ�ʼ˳�� 
//	Generate_2();
//	k = K;
//	tree = new int[k];
//	leave = new int[k + 1];
//	//K·�鲢		
//	K_Merge(0, K);
//	cout << endl;
//	cout << "������ɹ���" << endl;
//	cout << "�������temp" << file_count - 1 << ".txt" << endl;
//	QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
//	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs  
//	cout << "����ʱ�䣺" << time * 1000 << "ms" << endl;
//	//�ͷ��ڴ�ռ� 
//	delete[] tree;
//	delete[] leave;
//
//}
//
////������ 
//int main()
//{
//	//���������� 
//	LoserTree a;
//	//ָ�������ļ�
//	cout << "������Ҫ������������ļ����ƣ�";
//	string Input_File;
//	cin >> Input_File;
//	input_file = (char*)Input_File.c_str();
//	//ָ����������ļ���С
//	cout << "������������ļ��Ĵ�С�����ݸ�������";
//	cin >> Count;
//	cout << "�����뻺������С������1,000,000����";
//	cin >> BUF_SIZE;
//	if (BUF_SIZE < 0 || BUF_SIZE>1000000) {
//		cout << "�������뻺�������Ϸ���" << endl;
//		exit(0);
//	}
//	//ָ���鲢·�� 
//	cout << "������鲢·����";
//	int ways;
//	cin >> ways;
//	BUF_PAGES = ways + 1;
//	PAGE_SIZE = BUF_SIZE / BUF_PAGES;
//	cout << endl;
//	//ִ�������� 
//	a.ExternSort(ways);
//	return 0;
//}
//
