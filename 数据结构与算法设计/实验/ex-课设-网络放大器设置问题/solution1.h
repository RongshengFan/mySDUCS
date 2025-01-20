#pragma once
#include<bits/stdc++.h>
#include<windows.h>
#include<time.h>
#include"graph.h"
using namespace std;
void solution1() {
	for (int i = 1; i <= 100; i++) {
		string fin1 = "D:/CodeFile/VS/ex-���ݽṹ���㷨��ƻ���ʵ��/ex-����Ŵ�����������/input/input";
		fin1 += to_string(i) + ".in";
		string fout1 = "D:/CodeFile/VS/ex-���ݽṹ���㷨��ƻ���ʵ��/ex-����Ŵ�����������/output/";
		fout1 += to_string(i) + ".out";
		fin.open(fin1);
		fout.open(fout1);
		if (!fin.is_open() || !fout.is_open()) {
			cout << "�ļ��޷��򿪣�\n";
			//return;
		}
		Digraph g;
		g.topoSort();
		g.backTrack(1, 0);
		fout << g.bestAns << endl;
		fin.close();
		fout.close();

		cout << "�������ɿ��ӻ�ͼƬ " << i << endl;
		g.visualization1(i);
		cout << "�������.\n";
	}
	/*cout << "���ڽ��ж���...\n";
	check();*/
}
void solution1Chart() {
	clock_t start = clock();
	for (int i = 1; i <= 100; i++) {
		string fin1 = "D:/CodeFile/VS/ex-���ݽṹ���㷨��ƻ���ʵ��/ex-����Ŵ�����������/input/input";
		fin1 += to_string(i) + ".in";
		string fout1 = "D:/CodeFile/VS/ex-���ݽṹ���㷨��ƻ���ʵ��/ex-����Ŵ�����������/output/";
		fout1 += to_string(i) + ".out";
		fin.open(fin1);
		fout.open(fout1);
		if (!fin.is_open() || !fout.is_open()) {
			cout << "�ļ��޷��򿪣�\n";
			//return;
		}
		LARGE_INTEGER cpuFreq;
		LARGE_INTEGER startTime;
		LARGE_INTEGER endTime;

		QueryPerformanceFrequency(&cpuFreq);
		QueryPerformanceCounter(&startTime);

		Digraph g;
		g.topoSort();
		g.backTrack(1, 0);
		fout << g.bestAns << endl;
		QueryPerformanceCounter(&endTime);
		
		fin.close();
		fout.close();
		ofstream out("cost1.txt",ios::app);
		double time = (((static_cast<double>(endTime.QuadPart) - startTime.QuadPart) * 1000000) / cpuFreq.QuadPart);
		//out << i << "  " <<  time << "\n";//ʹ��Python����ͼ��ʱʹ��������룬��λus.
		out << time << "us\n";				//ʹ��Excel��������������������ͼ��ʱʹ���������
		out.close();

	}
	//��¼����100�����Լ���ʱ��
	clock_t end = clock();
	double time= (double)(1000 * (end - start)) / CLOCKS_PER_SEC;
	ofstream out("cost1.txt", ios::app);
	out << "\n" << time << "ms\n\n";
	out.close();
}
