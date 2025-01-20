#pragma once
#include<bits/stdc++.h>
//#include"minlosertree.h"
#include"LoserTree.h"
using namespace std;
static int page_size;
static int page_num;
static int max_run = 0;
struct Page {//����������ҳ��һҳһ��˳��
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
struct StraightStringPlayer {//���ڹ���˳��
	int ID;			//���
	int element;	//Ԫ��
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
	//���캯��
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
	//���ݳ�ʼ��
	void init() {
		cout << "������Ҫ������������ļ�λ��(����������D:\CodeFile\VS\)��" << endl;
		cin >> path;

		fileName = path + "Disk.txt";
		
		cout << "������������ļ���С��";
		cin >> fileSize;

		cout << "�����뻺������С(0��1,000,000����)��";
		cin >> bufferSize;
		while(bufferSize < 0 || bufferSize>1000000){
			cout << "��������С���벻�Ϸ�,���������룺" << endl;
		}

		cout << "������鲢·����";
		cin >> ways;

		ofstream fout(fileName);
		if (!fout.is_open()) {
			cout << "�޷���ָ�������ļ�������������λ��" << endl;
			return;
		}
		//cout << "������Ԫ�����£�" << endl;
		for (int i = 1; i <= fileSize; i++) {
			int x = rand() % 1000 + 1;
			fout << x <<' ';
		//	cout << x << " ";
		}
		//cout << endl;
		fout.close();	
	}
	//����˳��
	void generate() {
		StraightStringPlayer *sPlayer = new StraightStringPlayer[fileSize+10];

		ifstream fin(fileName, ios::in);

		if (!fin.is_open()) {
			cout << "�޷���ָ�������ļ����޷�����˳��" << endl;
			return;
		}
		for (int i = 1; i <= bufferSize; i++) {
			int num = 0;
			fin >> num;
			StraightStringPlayer temp(1, num);
			sPlayer[i] = temp;
			visitTime++;
		}

		LoserTree<StraightStringPlayer>sTree(sPlayer, bufferSize);//����˳��

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
	//ѭ��ʵ�ֹ鲢
	void merge() {
		if (fileCount == 1) {//ֻ��һ��˳���ļ���ֱ���������ļ�
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

		int count = fileCount;//��¼ÿ�ι鲢��ʣ���˳���ļ�������ʼֵΪ�鲢ǰ��˳����

		for(int x = 0; count != 1; x++) {

			int runs = ceil((double)count / (double)ways);//�鲢����
			int* he = new int[ways+1];
			ifstream* infile=new ifstream[count+1];

			for (int i = 1; i <= count; i++) {
				string tempFile = path + "tempFile" + to_string(i) + ".txt";
				infile[i].open(tempFile, ios::in);
				if (!infile[i].is_open()) {
					throw logic_error("�޷�����ʱ�ļ�");
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
							{//������ļ�ĩλ�����ֵ���뵽�������У�Ȼ��������ż���
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
			count = j;					//˳���ļ�������Ϊ�鲢����
		}
	}
	//�ݹ�ʵ�ֹ鲢
	void MergeK(int k, int start, int level) {
		int count = fileCount + 1 - start;
		int end_level = fileCount;
		int times;//����ÿ��鲢����
		int nextStart = start;

		if (count <= 1) {
			cout << "�ϲ���ɣ�" << endl;
			return;
		}


		times = ceil((double)count / (double)k);//�鲢����

		if (times == 0)
			times = 1;

		while (times--)
		{//ÿ���κϲ�

			int now_k = min(end_level - nextStart + 1, k);//������治�����õ����
			nextStart += now_k;
			map<int, string> name;//���������
			ifstream* fins = new ifstream[now_k + 1];

			page_num = now_k + 1;
			page_size = bufferSize / page_num;
			Page* inBuffer = new Page[now_k + 1];
			vector<long> outBuffer(page_size, 0);

			int outpoint = 0;//���ָ��
			for (int i = 0; i <= now_k; i++)
			{
				inBuffer[i] = Page(page_size);
			}


			if (level == 0) {//����run 
				for (int i = start; i < start + now_k; i++)
				{
					string s =path + "temp" + to_string(i) + ".txt";
					name[i] = s;
					fins[i - start + 1].open(s);
				}
			}
			else
			{//����S
				for (int i = start; i < start + now_k; i++)
				{
					name[i] = path + "tempFile" + to_string(i) + ".txt";
					fins[i - start + 1].open(name[i]);
				}
			}

			//������inBuffer
			for (int i = 1; i <= now_k; i++)
			{
				int cnt = 0;
				while (cnt < page_size && !fins[i].eof())
				{
					fins[i] >> inBuffer[i].arr[cnt++];
				}
				inBuffer[i].position = 0;
				visitTime++;//��һ�� ����
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
				output_file = path + "sorted.txt";//���һ�����
			}
			ofstream fout(output_file, ios::app);

			//ÿ�ζ��ó�ʼ��
			LoserTree<int>L(ps, now_k);

			int pos = L.Winner();//�滻��λ��
			while (L.getWinner() != INT_MAX)
			{
				pos = L.Winner();//�滻��λ��
				outBuffer[outpoint++] = ps[pos];
				//T p;//�����滻��

				//fout << players[pos] << " ";//���

				//��������������������ݿ�д����� 
				if (outpoint == page_size) {
					for (outpoint = 0; outpoint < page_size; outpoint++) {
						fout << outBuffer[outpoint] << " ";
					}
					outpoint = 0;
					visitTime++;//һ�������һ��
				}
				//disk_times++;

				//���뻺�����ѿգ������������ݿ� 
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
				//������ȡ������ 
				else {
					ps[pos] = inBuffer[pos].arr[inBuffer[pos].position];
					inBuffer[pos].position++;
				}

				//players[pos] = p;//�滻
				L.rePlay(pos,ps[pos]);
				pos = L.Winner();//�滻��λ��
			}

			for (int indx = 0; indx < outpoint; indx++) {
				fout << outBuffer[indx] << " ";
			}
			visitTime++;//����ʣ���
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
			MergeK(k, nextStart, 1);//��־ ������run��
		else
			MergeK(k, nextStart, 0);

	}
	//һ��ʵ�ֹ鲢
	void combine(){
    string newfile = path + "output.txt";

    ofstream fout3(newfile);

    if (fileCount == 1) {//ֻ������һ��˳���ļ���ֱ�ӽ������Ŀ���ļ�
        string tempFile = path + "tempFile" + to_string(1) + ".txt";
        ifstream fin4(tempFile);
        int tempNum;
        while (fin4 >> tempNum) {
            fout3 << tempNum << ' ';
            visitTime += 2;
        }
        fout3.close();
        fin4.close();
     //   cout << "���������������£�" << endl;
        ifstream finy(newfile);
	//	int tempy = 0;
    //   while (finy >> tempy)
	//		cout << tempy << ' ';
	//	cout << endl;
        finy.close();
        return;
    }
	int count = fileCount;
    int *dplayer=new int[count + 10];//��ʼ������
    int *pointer = new int[count + 10];//����С�����ļ���ָ��
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
	cout << "���������������£�" << endl;*/
    ifstream finy(newfile);
    int tempy;
    /*while (finy >> tempy)
        cout << tempy << ' ';
    cout << endl;*/
    finy.close();
}
	//ʵ��������
	void externSort() {
		init();
		clock_t start1 = clock();
		generate();
		combine();
		clock_t end1 = clock();
		double time1 = (double)(1000 * (end1 - start1)) / CLOCKS_PER_SEC;
		cout << "��ʼ˳����Ϊ��" << fileCount << endl;
		cout << "���̷��ʴ���Ϊ��" << visitTime << endl;
		cout << "������ʱ��Ϊ��" << time1 << "ms" << endl;
		cout << "��������ɣ��������output.txt��" << endl;
	}
private:
	string path;					//�������ļ�λ��
	string fileName;				//�������ļ�����
	int fileSize;					//�������ļ���С
	int bufferSize;					//��������С
	int ways;						//�鲢·��
	int visitTime;					//�ô����
	int fileCount;					//˳���ļ���
	int totals;
};