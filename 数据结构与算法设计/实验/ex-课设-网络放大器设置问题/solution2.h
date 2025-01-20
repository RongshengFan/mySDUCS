#pragma once
#include<bits/stdc++.h>
#include"graph.h"
using namespace std;
void solution2() {
	for (int i = 1; i <= 100; i++) {
		string fin2 = "D:/CodeFile/VS/ex-���ݽṹ���㷨��ƻ���ʵ��/ex-����Ŵ�����������/input/input";
		fin2 += to_string(i) + ".in";
		string fout2 = "D:/CodeFile/VS/ex-���ݽṹ���㷨��ƻ���ʵ��/ex-����Ŵ�����������/output/";
		fout2 += to_string(i) + ".out";
		fin.open(fin2);
		fout.open(fout2);
		if (!fin.is_open() || !fout.is_open()) {
			cout << "�ļ��޷��򿪣�\n";
			//return;
		}
		Digraph g;
		g.topoSort();
		g.branchBound();
		fout << g.bestAns << endl;
		fin.close();
		fout.close();

		cout << "�������ɿ��ӻ�ͼƬ " << i << endl;
		g.visualization2(i);
		cout << "�������.\n";
	}
	/*cout << "���ڽ��ж���...\n";
	check();*/
}
void solution2Chart() {
	clock_t start = clock();
	for (int i = 1; i <= 100; i++) {
		string fin2 = "D:/CodeFile/VS/ex-���ݽṹ���㷨��ƻ���ʵ��/ex-����Ŵ�����������/input/input";
		fin2 += to_string(i) + ".in";
		string fout2 = "D:/CodeFile/VS/ex-���ݽṹ���㷨��ƻ���ʵ��/ex-����Ŵ�����������/output/";
		fout2 += to_string(i) + ".out";
		fin.open(fin2);
		fout.open(fout2);
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
		g.branchBound();
		fout << g.bestAns << endl;
		QueryPerformanceCounter(&endTime);

		fin.close();
		fout.close();
		ofstream out("cost2.txt", ios::app);
		double time = (((static_cast<double>(endTime.QuadPart) - startTime.QuadPart) * 1000000) / cpuFreq.QuadPart);
		out << time << "us\n";
		//out << i << "  " << time << "us\n";
		out.close();

	}
	//��¼����100�����Լ���ʱ��
	clock_t end = clock();
	double time = (double)(1000 * (end - start)) / CLOCKS_PER_SEC;
	ofstream out("cost2.txt", ios::app);
	out << "\n" << time << "ms\n\n";
	out.close();
}
