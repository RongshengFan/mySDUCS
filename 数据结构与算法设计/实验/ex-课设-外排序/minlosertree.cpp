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
//int Count;		//待排序文件的数据个数 
//int BUF_PAGES;  //缓冲区有多少个page 
//int PAGE_SIZE; //page的大小 
//int BUF_SIZE;//BUF_PAGES*PAGE_SIZE; //缓冲区大小
//char* input_file;//输入文件名  
//
////缓冲区 
//struct Page {
//	int* arr;
//	int current; //当前顺串扫描的位置 
//	Page() {
//		current = 0;
//	}
//	Page(int bufsize) {
//		arr = new int[bufsize + 1];
//		current = 0;
//	}
//};
//
////选手 
//struct player {
//	int id;//编号 
//	int element;//元素 
//	//赢者规则 
//	friend bool operator<(const player& s1, const player& s2) {
//		if (s1.id != s2.id)
//			return s1.id < s2.id;
//
//		else
//			return s1.element < s2.element;
//	}
//	//重载运算符 = 
//	player& operator=(const player& s) {
//		id = s.id;
//		element = s.element;
//		return *this;
//	}
//};
//
////输者树 
//class LoserTree {
//public:
//	LoserTree() {}
//	~LoserTree() {}
//	//初始化 
//	void Initialize(int kk);
//	//返回赢者 
//	int Winner() { return tree[0]; }
//	//重构 
//	void Adjust(int s);
//	void Adjust(int*, player*, int, int);
//	//快排生成顺串 
//	void Generate_1();
//	//输者树生成顺串 
//	void Generate_2();
//	//K路归并 
//	void K_Merge(int start, int k);
//	//外排序
//	void ExternSort(int k);
//	//读数据块
//	int Read_Data_Block(FILE* file, int a[], int n);
//	//写数据块
//	void Write_Data_Block(FILE* file, int a[], int n);
//	//获取临时文件名称 
//	char* Get_Filename(int index);
//private:
//	int* tree;	//内部结点 
//	int* leave; //外部结点          
//	int k;      //选手个数  
//	int file_count;	//临时文件数目	 	
//};
//
////获取临时文件名称 
//char* LoserTree::Get_Filename(int index) {
//	char* tempname = new char[100];
//	sprintf(tempname, "temp%d.txt", index);
//	return tempname;
//}
//
////从外存中读数据块 
//int LoserTree::Read_Data_Block(FILE* file, int a[], int n) {
//	int i = 0;
//	while (i < n && (fscanf(file, "%d", &a[i])) != EOF)
//		i++;
//	return i;
//}
//
////往外存中写数据块 
//void LoserTree::Write_Data_Block(FILE* file, int a[], int n) {
//	for (int i = 0; i < n; i++)
//		fprintf(file, "%d ", a[i]);
//	fprintf(file, "%d", INT_MAX);
//}
//
////初始化 
//void LoserTree::Initialize(int kk) {
//	k = kk;
//	leave[k] = INT_MIN;
//	for (int i = 0; i < k; i++)
//		tree[i] = k;
//	for (int i = 0; i < k; i++)
//		Adjust(i);
//}
//
////重构输者树 
//void LoserTree::Adjust(int s) {
//	//父节点 
//	int t = (s + k) >> 1;
//	//向上调整 
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
////利用快速排序生成顺串 
//void LoserTree::Generate_1() {
//	FILE* fin = fopen(input_file, "rt");
//	int n = 0;
//	file_count = 0;
//	//内部缓冲区 
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
////重构输者树 
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
////输者树生成顺串 
//void LoserTree::Generate_2() {
//	file_count = 0;
//	int K = BUF_SIZE / 2;
//	int* Tree = new int[K];
//	player* Leave = new player[K + 1];
//	int OutputNum = Count / BUF_SIZE + 10;
//	//文件输出流 
//	ofstream* out = new ofstream[OutputNum];
//	for (int i = 0; i < OutputNum; i++) {
//		char* tmp = Get_Filename(i);
//		out[i].open(tmp, ios::app);
//	}
//	//文件输入流 
//	ifstream in;
//	in.open(input_file);
//	if (!in.is_open()) {
//		cout << "错误：当前目录下该文件不存在！" << endl;
//		exit(0);
//	}
//	for (int i = 0; i < K; i++) {
//		in >> Leave[i].element;
//		Leave[i].id = 0;
//	}
//	//初始化输者树 
//	Leave[K].element = INT_MIN;
//	Leave[K].id = -1;
//	for (int i = 0; i < K; i++)
//		Tree[i] = K;
//	for (int i = 0; i < K; i++)
//		Adjust(Tree, Leave, i, K);
//	int maxid = 0;
//	//输者树排序 
//	while (Leave[Tree[0]].element != INT_MAX) {
//		int p = Tree[0];
//		file_count = max(file_count, Leave[p].id);
//		out[Leave[p].id] << Leave[p].element << " ";
//		//读到文件尾 
//		if (in.eof()) {
//			Leave[p].element = INT_MAX;
//			Leave[p].id = INT_MAX;
//			in.close();
//		}
//		//读入新元素并确定顺串号 
//		else {
//			int element;
//			in >> element;
//			if (element < Leave[p].element) {
//				Leave[p].id++;
//			}
//			Leave[p].element = element;
//		}
//		//重构输者树 
//		Adjust(Tree, Leave, p, K);
//	}
//	file_count++;
//	//添加 ∞作为终止符 
//	for (int i = 0; i < file_count; i++) {
//		out[i] << INT_MAX;
//		out[i].close();
//	}
//}
//
////K路合并 
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
//	//执行runs次k路归并 
//	while (cnt--) {
//		k = min(K, cur - j);
//		ifstream* in = new ifstream[k];
//		//读取当前要归并的临时文件 
//		for (int i = 0; i < k; i++) {
//			char* tmp = Get_Filename(j++);
//			in[i].open(tmp);
//		}
//		//输入缓冲区 
//		Page* Buffer = new Page[k];
//		for (int i = 0; i < k; i++) {
//			Buffer[i] = Page(BUF_SIZE);
//		}
//		//从外存读入缓冲区 
//		for (int i = 0; i < k; i++) {
//			int num = 0;
//			while (num < PAGE_SIZE && !in[i].eof()) {
//				in[i] >> Buffer[i].arr[num];
//				num++;
//			}
//			Buffer[i].current = 0;
//		}
//		//读取外部节点 
//		for (int i = 0; i < k; i++) {
//			leave[i] = Buffer[i].arr[0];
//			Buffer[i].current++;
//		}
//		//初始化输者树 
//		Initialize(k);
//		int p;
//		//输出缓冲区 
//		int* res = new int[PAGE_SIZE];
//		int idx = 0;
//		char* outputfile = Get_Filename(file_count);
//		ofstream out(outputfile);
//		//输者树排序	
//		while (leave[tree[0]] != INT_MAX) {
//			p = tree[0];  //p为当前最小关键字所在的顺串 
//			res[idx++] = leave[p];
//			//输出缓冲区已满，将数据块写入外存 
//			if (idx == PAGE_SIZE) {
//				for (idx = 0; idx < PAGE_SIZE; idx++) {
//					out << res[idx] << " ";
//				}
//				idx = 0;
//			}
//			//输入缓冲区已空，从外存读入数据块 
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
//			//继续读取缓冲区 
//			else {
//				leave[p] = Buffer[p].arr[Buffer[p].current];
//				Buffer[p].current++;
//			}
//			//重构输者树 
//			Adjust(p);
//		}
//		//输出缓冲区剩余内容写入外存 
//		for (int oidx = 0; oidx < idx; oidx++) {
//			out << res[oidx] << " ";
//		}
//		//终止符 
//		out << INT_MAX;
//		//关闭文件流 
//		for (int i = 0; i < k; i++) {
//			in[i].close();
//		}
//		out.close();
//		file_count++;
//	}
//	//进行下一轮归并 
//	K_Merge(j, K);
//}
//
////外排序 
//void LoserTree::ExternSort(int K) {
//	double time = 0;
//	double counts = 0;
//	LARGE_INTEGER nFreq;
//	LARGE_INTEGER nBeginTime;
//	LARGE_INTEGER nEndTime;
//	QueryPerformanceFrequency(&nFreq);
//	QueryPerformanceCounter(&nBeginTime);//开始计时 
//	//生成初始顺串 
//	Generate_2();
//	k = K;
//	tree = new int[k];
//	leave = new int[k + 1];
//	//K路归并		
//	K_Merge(0, K);
//	cout << endl;
//	cout << "外排序成功！" << endl;
//	cout << "结果存于temp" << file_count - 1 << ".txt" << endl;
//	QueryPerformanceCounter(&nEndTime);//停止计时  
//	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位为s  
//	cout << "运行时间：" << time * 1000 << "ms" << endl;
//	//释放内存空间 
//	delete[] tree;
//	delete[] leave;
//
//}
//
////主程序 
//int main()
//{
//	//创建输者树 
//	LoserTree a;
//	//指定输入文件
//	cout << "请输入要进行外排序的文件名称：";
//	string Input_File;
//	cin >> Input_File;
//	input_file = (char*)Input_File.c_str();
//	//指定待排序的文件大小
//	cout << "请输入待排序文件的大小（数据个数）：";
//	cin >> Count;
//	cout << "请输入缓冲区大小（上限1,000,000）：";
//	cin >> BUF_SIZE;
//	if (BUF_SIZE < 0 || BUF_SIZE>1000000) {
//		cout << "错误：输入缓冲区不合法！" << endl;
//		exit(0);
//	}
//	//指定归并路数 
//	cout << "请输入归并路数：";
//	int ways;
//	cin >> ways;
//	BUF_PAGES = ways + 1;
//	PAGE_SIZE = BUF_SIZE / BUF_PAGES;
//	cout << endl;
//	//执行外排序 
//	a.ExternSort(ways);
//	return 0;
//}
//
