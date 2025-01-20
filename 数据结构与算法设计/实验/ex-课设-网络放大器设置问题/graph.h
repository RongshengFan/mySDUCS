#pragma once
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
extern ifstream fin;
extern ofstream fout;
struct Node {
	Node* father;
	int level;					//�Ӽ����㼶
	int press;					//ѹ��ֵ
	bool booster;				//�Ƿ���÷Ŵ���				
	int maxCost;				//�����
	int bstNum;				    //���ȼ����Ӹ����ڵ�x·���ϵ�bst����
	Node() {
		father = NULL;
		press = 0;
		level = 0;
		bstNum = 0;
		maxCost = 0;
		booster = false;
	}
	Node(int pre, int lev, Node* fa = NULL, int bst = 0) {
		father = fa;
		press = pre;
		level = lev;
		bstNum = bst;
		maxCost = 0;
		booster = false;
	}
	bool operator<(const Node& b)const {
		return bstNum > b.bstNum;
	}
};

struct outEdge {
	int v;	//�ɴ�ĵ�
	int w;	//Ȩֵ����
	outEdge(int to, int w) :v(to), w(w) {};
};
struct inEdge {
	int u;
	int w;
	inEdge(int u, int w) :u(u), w(w) {};
};
struct Vertex {
	vector<outEdge>outEdges;	//��¼����
	vector<inEdge>inEdges;		//��¼��ߣ����ڸ���press
	int press;					//ѹ��
	bool booster;				//�Ŵ���				
	int maxCost;				//�����
	int topoNum;				//���˴���
	Vertex() {
		press = 0;
		booster = false;
		outEdges.clear();
		inEdges.clear();
		maxCost = 0;
		topoNum = 0;
	}
};

class Digraph {
public:
	int n, m;								//������������
	int bestAns;							//���Ž���Ŀ
	Digraph();								//���캯��
	~Digraph() {};							//��������
	void visualization1(int i);				//���ӻ����1
	void visualization2(int i);				//���ӻ����2
	void topoSort();						//��������ȷ���Ⱥ��ϵ
	void updatePress();						//����ѹ��ֵ
	void outputBst();						//����Ŵ���
	void backTrack(int level, int cnt);		//dfs���ݽ��
	void branchBound();						//��֧������
private:
	int Pmin, Pmax;
	vector<Vertex>vertexs;
	vector<int>inDeg;		//���
	vector<int>topology;    //��������
	vector<bool>isBst;		//�Ƿ���÷Ŵ���

	vector<Vertex>ver;
	priority_queue<Node*, vector<Node*>>q;//��С��
};
Digraph::Digraph()
{
	fin >> n >> m >> Pmax;
	Pmin = 0;				//��Сѹ������Ϊ0
	bestAns = INT_MAX;
	vertexs.clear();
	inDeg.resize(n + 1, 0);
	topology.resize(n + 1, 0);
	isBst.resize(n + 1, 0);

	for (int i = 0; i <= n; i++) {
		vertexs.push_back(Vertex());
	}
	for (int i = 0; i < m; i++) {
		int u, v, w;
		fin >> u >> v >> w;
		//��¼����
		vertexs[u].outEdges.emplace_back(v, w);
		//�������
		inDeg[v]++;
		//���������
		vertexs[u].maxCost = max(vertexs[u].maxCost, w);
		//��¼���
		vertexs[v].inEdges.emplace_back(u, w);
	}
	//����ѹ��
	vertexs[1].press = Pmax;
	isBst[1] = true;

	/*ver = vertexs;
	bfs2(1);*/
}

void Digraph::visualization1(int a)
{
	updatePress();
	string fileName =  to_string(a) + ".dot";
	ofstream out(fileName);
	out << "digraph g {\n";
	for (int i = 1; i < vertexs.size(); i++) {
		out << i;
		if (isBst[i]) {
			out << "[label=\"vertex" << i << ";pre = " << vertexs[i].press << "\",style=filled,fillcolor=red];\n";
		}
		else {
			out << "[label=\"vertex" << i << ";pre = " << vertexs[i].press << "\",style=filled,fillcolor=white];\n";
		}
	}
	for (int i = 1; i <= n; i++) {
		for (auto& ed : vertexs[i].outEdges) {
			out << i << "->" << ed.v << "[label=\"cost=" << ed.w << "\"];\n";
		}
	}
	out << 0;
	out << "[label=\"Pmax" << Pmax << ";Pmin = " << Pmin << "\",style=filled,fillcolor=yellow];\n";
	out << "}\n";
	out.close();
	string order = "dot -Tjpg " + to_string(a) + ".dot -o solve" + to_string(a) + ".jpg";
	system(order.c_str());
}

void Digraph::visualization2(int a)
{
	updatePress();
	string fileName = to_string(a) + "-2.dot";
	ofstream out(fileName);
	out << "digraph g {\n";
	for (int i = 1; i < vertexs.size(); i++) {
		out << i;
		if (isBst[i]) {
			out << "[label=\"vertex" << i << ";pre = " << vertexs[i].press << "\",style=filled,fillcolor=red];\n";
		}
		else {
			out << "[label=\"vertex" << i << ";pre = " << vertexs[i].press << "\",style=filled,fillcolor=white];\n";
		}
	}
	for (int i = 1; i <= n; i++) {
		for (auto& ed : vertexs[i].outEdges) {
			out << i << "->" << ed.v << "[label=\"cost=" << ed.w << "\"];\n";
		}
	}
	out << "}\n";
	out.close();
	string order = "dot -Tjpg " + to_string(a) + "-2.dot -o solve" + to_string(a) + "-2.jpg";
	system(order.c_str());
}

void Digraph::topoSort()
{//ʹ��bfs����ȷ����������
 //ÿ��ȷ��һ��������������к󣬸�����Ӱ��ĵ�����
	int cnt = 1;
	queue<int>q;
	for (int i = 1; i <= n; i++) {
		if (inDeg[i] == 0)q.push(i);
	}
	while (!q.empty()) {
		int u = q.front();
		q.pop();

		vertexs[u].topoNum = cnt;

		topology[cnt++] = u;		//����

		for (auto& ed : vertexs[u].outEdges) {
			if (--inDeg[ed.v] == 0)q.push(ed.v);
		}
	}
	if (cnt < n) {
		cout << "ͼ���л�������Ҫ��\n";
		return;
	}
}

void Digraph::updatePress()
{
	for (int i = 2; i <= n; i++) {
		int u = topology[i];
		if (isBst[u]) {
			vertexs[u].press = Pmax;
		}
		else {
			vertexs[u].press = 0;
			for (int j = 1; j < i; j++) {
				for (auto& ed : vertexs[topology[j]].outEdges) {
					if (ed.v == u) {
						vertexs[u].press = max(vertexs[u].press, vertexs[topology[j]].press - ed.w);
					}
				}
			}
		}
	}
}

void Digraph::outputBst()
{
	for (int i = 1; i <= n; i++) {
		if (isBst[i]) {
			cout << "vertex " << i << endl;
		}
	}
}

void Digraph::backTrack(int i, int cnt)
{//����dfs���ݣ��ʱ�临�Ӷ�O(2^n)
    //������i�� 
	int u = topology[i];//��ǰ��iҲ������������

	if (i >= n) {//�����һ���ڵ��ˣ�������Ϣ���ݳ�
		//�������Ž�
		bestAns = min(cnt, bestAns);
		//���·������
		for (int j = 1; j <= n; j++) {
			isBst[j] = false;
			isBst[j] = vertexs[j].booster;
		}
		return;
	}

	if (i == 1) {//��һ�� Դ�㲻��Ҫ����
		backTrack(2, 0);
	}
	else {//�ж�������  ������v��ѹ��ֵС��Pmin, ���ڵ�u����
		int x;
		int flag = 0;
		int tempPress = -1;//��ǰѹ��ֵ��������֦����

		for (int k = 1; k < i; k++) {//��һ�㵽��ǰ�� 
			for (auto& ed : vertexs[topology[k]].outEdges) {
				if (ed.v == u)//����ѹ��ֵ
					tempPress = max(tempPress, vertexs[topology[k]].press - ed.w);
			}
		}

		for (x = 1; x <= 2; x++)
		{//�������־���
			//��֦1����ǰѹ��ֵΪPmax���ѷ��÷Ŵ���
			if (tempPress >= Pmax || vertexs[u].booster == true) {
				backTrack(i + 1, cnt);
				break;
			}
			//��֦2����ǰѹ��ֵС��Pmin���������
			if (tempPress < Pmin)
			{
				cnt++;
				vertexs[u].booster = true;
				//��֦3���������Ѿ��ҵ����Ž���
				if (cnt >= bestAns) {
					return;
				}
				backTrack(i + 1, cnt);
			}
			if (x == 1) {//1״̬ʱ�ȶ����г��߽����ж�
				for (auto& v : vertexs[u].outEdges) {
					int nextPress = tempPress - v.w;
					if (nextPress < Pmin) {//��һ���ڵ�ѹ��ֵС��Pmin����Ҫ����
						flag = 1;
						break;
					}
				}
			}
			//����
			if (x == 2 || flag == 1) {
				cnt++;
				vertexs[u].press = Pmax;
				vertexs[u].booster = true;
				//��֦3���������Ѿ��ҵ����Ž���
				if (cnt >= bestAns)
					return;
				else {
					backTrack(i + 1, cnt);
				}
			}
			//������
			else if (x == 1 && flag != 1) {
				vertexs[u].press = tempPress;
				vertexs[u].booster = false;
				backTrack(i + 1, cnt);
			}
		}
	}
}

void Digraph::branchBound()
{//��С�ķѣ���֧����
	Node* eNode = new Node(Pmax, 2);//���û�ڵ㣬
	int level = 2;					//�ӵ�2�㿪ʼ
	while (level <= n - 1) {		//��չ��ڵ�
		int u = topology[level];//��ǰ����չ�Ļ�ڵ�
		int tempPress = -1;		//��չ�ڵ�ѹ��ֵ
		int flag = 0;

		for (int k = 1; k <= level - 1; k++) {//������չ�ڵ�ѹ��ֵ
			for (auto& e : vertexs[topology[k]].outEdges) {
				if (e.v == u) {
					Node* p = eNode;
					for (int j = level - 1; j > k; j--) {
						p = p->father;
					}
					tempPress = max(tempPress, p->press - e.w);
				}
			}
		}
		//�����޽��жϣ���ǰѹ��ֵ�����ĺ�С��Pmin,��Ҫ����
		if (tempPress - vertexs[u].maxCost < Pmin) {
			flag = 1;
		}
		if (flag == 0) {//������� ���û򲻷���
			//������
			Node* t = new Node(tempPress, level + 1, eNode, eNode->bstNum);
			q.push(t);

			//����
			Node* s = new Node(Pmax, level + 1, eNode, eNode->bstNum + 1);
			s->booster = true;
			q.push(s);
		}
		else {//�������
			Node* s = new Node(Pmax, level + 1, eNode, eNode->bstNum + 1);
			s->booster = true;
			q.push(s);
		}
		eNode = q.top();//���»�ڵ�
		q.pop();
		level = eNode->level;//��ȡ����
	}

	bestAns = eNode->bstNum;//�������Ž�

	Node* p = eNode;
	while (p) {//����isBst��״̬
		isBst[topology[p->level - 1]] = p->booster;
		p = p->father;
	}

}
//���ĺ��������ڶ��ս���Ƿ���ȷ
void check() {
	int flag = 0;
	stringstream s;
	for (int i = 1; i <= 100; i++) {
		cout << "���ڲ������ݼ���" << i << endl;
		string opStd = "D:/CodeFile/VS/ex-���ݽṹ���㷨��ƻ���ʵ��/ex-����Ŵ�����������/outputSTD/";
		string myin = "D:/CodeFile/VS/ex-���ݽṹ���㷨��ƻ���ʵ��/ex-����Ŵ�����������/output/";
		opStd += to_string(i) + ".out";
		myin += to_string(i) + ".out";
		ifstream finstd(opStd);
		if (!finstd.is_open()) {
			cout << "�ļ��޷���\n";
		}
		int ans;
		finstd >> ans;
		finstd.close();

		ifstream finmy(myin);
		if (!finmy.is_open()) {
			cout << "�ļ��޷���\n";
		}
		int me;
		finmy >> me;
		finmy.close();
		if (me != ans) {
			cout << "Wrong Answer\n";
			s << i << "WA!\n";
		}
		else {
			cout << "Accept\n";
		}
	}
	if (!flag) {
		cout << "All Accept!\n";
	}
	else {
		cout << "Wrong Answer\n";
	}
	cout << s.str();
}