#include<bits/stdc++.h>
#include"graph.h"
#include"solution1.h"
#include"solution2.h"
using namespace std;
ifstream fin;
ofstream fout;
//���ܷ���
void test() {
	cout << "�����������ܶԱ�����...\n";
	solution1Chart();
	solution2Chart();
	cout << "���ݽ�������ɣ������ͼ����з���.\n";
	//system("testTime.py");//������û�����������Լ���
}
//test1:����100���������
void test1() {
	cout << "���ڲ��Է���1:dfs����...\n";
	solution1();
	cout<< "���ڲ��Է���2:��֧����...\n";
	solution2();
}
//test2:����ָ�����ݼ���
void test2() {
	cout << "�������ļ�·�����ƣ�\n";
	string path;
	cin >> path;
	fin.open(path);
	if (!fin.is_open()) {
		cout << "�ļ��޷��򿪣����������룡\n";
		return;
	}
	Digraph g;
	g.topoSort();
	//g.backTrack(1,0);
	g.branchBound();
	cout << g.bestAns << endl;
	g.outputBst();
}
int main() {
	while (1) {
		cout << "------�Ŵ�������------\n";
		cout << "0:�������ܶԱȷ���\n";
		cout << "1:����100����������\n";
		cout << "2:����ָ�����ݼ���\n";
		string op;
		cin >> op;
		if (op == "0") {
			test();
		}
		else if (op == "1") {
			test1();
		}
		else if (op == "2") {
			test2();
		}
		else {
			cout << "����������������룡\n";
		}
	}
	return 0;
}