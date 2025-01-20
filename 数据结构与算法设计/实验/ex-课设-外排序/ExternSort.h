#pragma once
#include<bits/stdc++.h>
//#include"minlosertree.h"
#include"LoserTree.h"
using namespace std;
static int page_size;
static int page_num;
static int max_run = 0;
struct Page {//将缓冲区分页，一页一个顺串
	int* arr;
	int position;
	Page() {
		arr = nullptr;
		position = 0;
	}
	Page(int page_size) {
		position = 0;
		arr = new int[page_size + 1];
	}
};
struct StraightStringPlayer {//用于构建顺串
	int ID;			//编号
	int element;	//元素
	StraightStringPlayer() {
		ID = 0;
		element = 0;
	}
	StraightStringPlayer(int id, int theElement) {
		ID = id;
		element = theElement;
	}
	bool operator<=(const StraightStringPlayer& b)const {
		return (ID != b.ID) ? ID < b.ID : element < b.element;
	}
};

class ExternSort {
public:
	//构造函数
	ExternSort() {
		fileName = "";
		fileSize = 0;
		bufferSize = 0;
		ways = 0;
		visitTime = 0;
		fileCount = 1;
	}
	void get_total() {
		totals = 0;
		if (max_run % ways == 0) {
			int temp = max_run / ways; totals += temp;
			cout <<max_run<<" "<<fileCount<<" " << temp << endl;
			while (temp != 1)
			{
				temp /= ways;
				totals += temp;
			}
		}
		else
		{
			int temp = max_run / ways; totals += temp; totals++;
			while (temp != 0)
			{
				temp /= ways;
				totals += temp;
				totals++;
			}
		}
	};
	//数据初始化
	void init() {
		cout << "请输入要进行外排序的文件位置(输入样例：D:\CodeFile\VS\)：" << endl;
		cin >> path;

		fileName = path + "Disk.txt";
		
		cout << "请输入待排序文件大小：";
		cin >> fileSize;

		cout << "请输入缓冲区大小(0到1,000,000以内)：";
		cin >> bufferSize;
		while(bufferSize < 0 || bufferSize>1000000){
			cout << "缓冲区大小输入不合法,请重新输入：" << endl;
		}

		cout << "请输入归并路数：";
		cin >> ways;

		ofstream fout(fileName);
		if (!fout.is_open()) {
			cout << "无法打开指定磁盘文件，请重新输入位置" << endl;
			return;
		}
		//cout << "待排序元素如下：" << endl;
		for (int i = 1; i <= fileSize; i++) {
			int x = rand() % 1000 + 1;
			fout << x <<' ';
		//	cout << x << " ";
		}
		//cout << endl;
		fout.close();	
	}
	//生成顺串
	void generate() {
		StraightStringPlayer *sPlayer = new StraightStringPlayer[fileSize+10];

		ifstream fin(fileName, ios::in);

		if (!fin.is_open()) {
			cout << "无法打开指定磁盘文件，无法生成顺串" << endl;
			return;
		}
		for (int i = 1; i <= bufferSize; i++) {
			int num = 0;
			fin >> num;
			StraightStringPlayer temp(1, num);
			sPlayer[i] = temp;
			visitTime++;
		}

		LoserTree<StraightStringPlayer>sTree(sPlayer, bufferSize);//构造顺串

		for (int i = 1; i <= fileSize; i++) {
			int num = 0;

			if (!(fin >> num))num=INT_MIN;
			else visitTime++;

			StraightStringPlayer Winner = sPlayer[sTree.Winner()];
			StraightStringPlayer temp(0, num);

			if (num >= Winner.element) {
				temp.ID = Winner.ID;
			}
			else {
				temp.ID = (num == INT_MIN) ? INT_MAX : Winner.ID + 1;
				
			}
			fileCount = max(fileCount, Winner.ID);
			sTree.rePlay(sTree.Winner(), temp);

			string tempFile = path + "tempFile" + to_string(Winner.ID) + ".txt";

			ofstream fout1(tempFile,ios::app);
			fout1 << Winner.element << " ";
			fout1.close();

			visitTime++;
		}
		max_run = fileCount;

		//get_total();

		fin.close();
	}
	//循环实现归并
	void merge() {
		if (fileCount == 1) {//只有一个顺串文件，直接输入结果文件
			string resultFile = path + "output.txt";
			string tempFile = path + "tempFile" + to_string(1) + ".txt";
			ofstream fout(resultFile);
			ifstream fin(tempFile);
			int temp;
			while (fin >> temp) {
				fout << temp << " ";
				visitTime += 2;
			}
			fout.close();
			fin.close();
			return;
		}

		int count = fileCount;//记录每次归并后剩余的顺串文件数，初始值为归并前的顺串数

		for(int x = 0; count != 1; x++) {

			int runs = ceil((double)count / (double)ways);//归并段数
			int* he = new int[ways+1];
			ifstream* infile=new ifstream[count+1];

			for (int i = 1; i <= count; i++) {
				string tempFile = path + "tempFile" + to_string(i) + ".txt";
				infile[i].open(tempFile, ios::in);
				if (!infile[i].is_open()) {
					throw logic_error("无法打开临时文件");
				}
				visitTime++;
			}
			int j = 0;
			for (; j < runs; j++) {
				string out;
				if (count <= ways) {
					out = path + "output.txt";
				}
				else {
					out = path + "tempFile" + to_string(x + 1) + ".txt";
				}
				ofstream outfile(out, ios::out);
				visitTime++;

				he[0] = INT_MAX;
				for (int i = 1; i <= ways; i++) {
					if (j * ways + i >= count + 1) {
						he[i] = INT_MAX;
					}
					else {
						infile[j * ways + i] >> he[i];
					}
				}
				LoserTree<int>L(he, ways);
				while (he[L.Winner()] != INT_MAX) {
					outfile << he[L.Winner()] << " ";

					for (int y = 0; y < ways; y++) {
						if (L.Winner() == y + ways && j * ways + y < count) {
							int u = 0;
							infile[j * ways + y + 1] >> u;

							if (infile[j * ways + 1 + y].eof())
							{//如果到文件末位则将最大值输入到输者树中，然后进行重排即可
								u = INT_MAX;
							}

							L.rePlay(L.Winner(),u);
							break;
						}
					}
				}
				outfile.close();
			}
			for (int i = 1; i <= count; i++) {
				infile[i].close();
			}
			count = j;					//顺串文件数更新为归并段数
		}
	}
	//递归实现归并
	void MergeK(int k, int start, int level) {
		int count = fileCount + 1 - start;
		int end_level = fileCount;
		int times;//计算每层归并次数
		int nextStart = start;

		if (count <= 1) {
			cout << "合并完成！" << endl;
			return;
		}


		times = ceil((double)count / (double)k);//归并段数

		if (times == 0)
			times = 1;

		while (times--)
		{//每层多次合并

			int now_k = min(end_level - nextStart + 1, k);//处理后面不是正好的情况
			nextStart += now_k;
			map<int, string> name;//读入的名字
			ifstream* fins = new ifstream[now_k + 1];

			page_num = now_k + 1;
			page_size = bufferSize / page_num;
			Page* inBuffer = new Page[now_k + 1];
			vector<long> outBuffer(page_size, 0);

			int outpoint = 0;//输出指针
			for (int i = 0; i <= now_k; i++)
			{
				inBuffer[i] = Page(page_size);
			}


			if (level == 0) {//读入run 
				for (int i = start; i < start + now_k; i++)
				{
					string s =path + "temp" + to_string(i) + ".txt";
					name[i] = s;
					fins[i - start + 1].open(s);
				}
			}
			else
			{//读入S
				for (int i = start; i < start + now_k; i++)
				{
					name[i] = path + "tempFile" + to_string(i) + ".txt";
					fins[i - start + 1].open(name[i]);
				}
			}

			//外存读入inBuffer
			for (int i = 1; i <= now_k; i++)
			{
				int cnt = 0;
				while (cnt < page_size && !fins[i].eof())
				{
					fins[i] >> inBuffer[i].arr[cnt++];
				}
				inBuffer[i].position = 0;
				visitTime++;//读一次 读满
			}

			int* ps = new int[now_k + 1];
			ps[0] = INT_MAX;
			for (int i = 1; i <= now_k; i++)
			{
				ps[i] = inBuffer[i].arr[0];
				inBuffer[i].position++;
			}

			string output_file = path + "tempFile" + to_string(++fileCount) + ".txt";
			if (fileCount - max_run == totals) {
				output_file = path + "sorted.txt";//最后一次输出
			}
			ofstream fout(output_file, ios::app);

			//每次都得初始化
			LoserTree<int>L(ps, now_k);

			int pos = L.Winner();//替换的位置
			while (L.getWinner() != INT_MAX)
			{
				pos = L.Winner();//替换的位置
				outBuffer[outpoint++] = ps[pos];
				//T p;//用来替换的

				//fout << players[pos] << " ";//输出

				//输出缓冲区已满，将数据块写入外存 
				if (outpoint == page_size) {
					for (outpoint = 0; outpoint < page_size; outpoint++) {
						fout << outBuffer[outpoint] << " ";
					}
					outpoint = 0;
					visitTime++;//一次性输出一堆
				}
				//disk_times++;

				//输入缓冲区已空，从外存读入数据块 
				if (inBuffer[pos].position >= page_size) {
					int cnt = 0;
					while (cnt < page_size && !fins[pos].eof()) {
						fins[pos] >> inBuffer[pos].arr[cnt++];
					}
					inBuffer[pos].position = 0;
					ps[pos] = inBuffer[pos].arr[inBuffer[pos].position];
					inBuffer[pos].position++;
					visitTime++;
				}
				//继续读取缓冲区 
				else {
					ps[pos] = inBuffer[pos].arr[inBuffer[pos].position];
					inBuffer[pos].position++;
				}

				//players[pos] = p;//替换
				L.rePlay(pos,ps[pos]);
				pos = L.Winner();//替换的位置
			}

			for (int indx = 0; indx < outpoint; indx++) {
				fout << outBuffer[indx] << " ";
			}
			visitTime++;//处理剩余的
			if (fileCount - max_run != totals) {
				fout << INT_MAX;
			}


			for (int i = start; i < start + now_k; i++)
			{
				fins[i - start + 1].close();
			}
			fout.close();
			start = nextStart;
		}
		if (nextStart > max_run)
			MergeK(k, nextStart, 1);//标志 不读入run了
		else
			MergeK(k, nextStart, 0);

	}
	//一趟实现归并
	void combine(){
    string newfile = path + "output.txt";

    ofstream fout3(newfile);

    if (fileCount == 1) {//只生成了一个顺串文件，直接将其加入目标文件
        string tempFile = path + "tempFile" + to_string(1) + ".txt";
        ifstream fin4(tempFile);
        int tempNum;
        while (fin4 >> tempNum) {
            fout3 << tempNum << ' ';
            visitTime += 2;
        }
        fout3.close();
        fin4.close();
     //   cout << "最终外排序结果如下：" << endl;
        ifstream finy(newfile);
	//	int tempy = 0;
    //   while (finy >> tempy)
	//		cout << tempy << ' ';
	//	cout << endl;
        finy.close();
        return;
    }
	int count = fileCount;
    int *dplayer=new int[count + 10];//初始化队列
    int *pointer = new int[count + 10];//各个小磁盘文件的指针
    for (int i = 1; i <= count; i++) {
        string tempFile = path + "tempFile" + to_string(i) + ".txt";
        ifstream fin2(tempFile);
        fin2 >> dplayer[i];
        pointer[i] = fin2.tellg();
        fin2.close();
    }
    LoserTree<int> dtree(dplayer, count);
    int cnt = 0;
    while (cnt < fileSize) {
        cnt++;
        int temp = dtree.Winner();
        int tempWinner = dplayer[temp];
        fout3 << tempWinner << ' ';
        visitTime++;
        string tempFile =path + "tempFile" + to_string(temp) + ".txt";
        ifstream fin3(tempFile);
        fin3.clear(); fin3.seekg(pointer[temp] + 1);

        int tempNum;
        if (pointer[temp] + 1 == 0) tempNum = INT_MAX;
        else {
            fin3 >> tempNum;
            pointer[temp] = fin3.tellg();
            if (pointer[temp] + 1 == 0) tempNum = INT_MAX;
        }
        visitTime++;
        dtree.rePlay(temp, tempNum);
        fin3.close();
    }
    fout3.close();
    /*cout << endl;
	cout << "最终外排序结果如下：" << endl;*/
    ifstream finy(newfile);
    int tempy;
    /*while (finy >> tempy)
        cout << tempy << ' ';
    cout << endl;*/
    finy.close();
}
	//实现外排序
	void externSort() {
		init();
		clock_t start1 = clock();
		generate();
		combine();
		clock_t end1 = clock();
		double time1 = (double)(1000 * (end1 - start1)) / CLOCKS_PER_SEC;
		cout << "初始顺串数为：" << fileCount << endl;
		cout << "磁盘访问次数为：" << visitTime << endl;
		cout << "外排序时间为：" << time1 << "ms" << endl;
		cout << "外排序完成，结果存于output.txt中" << endl;
	}
private:
	string path;					//待排序文件位置
	string fileName;				//待排序文件名称
	int fileSize;					//待排序文件大小
	int bufferSize;					//缓冲区大小
	int ways;						//归并路数
	int visitTime;					//访存次数
	int fileCount;					//顺串文件数
	int totals;
};