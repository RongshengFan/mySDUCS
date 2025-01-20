//#include <sstream>
//#include <string>
//#include<cstring>
//#include<iostream>
//#include<algorithm>
//using namespace std;
//
//int a[200002];   //�������鼯����
//int find(int i) {//���鼯��find����,·��ѹ��
//	if (a[i] != i)a[i] = find(a[i]);
//	return a[i];
//}
//
///**********ʵ�ֱ߼��Ľṹ�岿��**********/
//struct wEdge {//��ߵĽṹ��
//	int v1, v2, w;
//	wEdge(int i = 0, int j = 0, int weight = 0) {
//		v1 = i;
//		v2 = j;
//		w = weight;
//	}
//	bool operator<(wEdge& b) {//����Ȩֵ�������бȽ�
//	return w < b.w;
//}
//};
////ʵ��������Ȩͼ
//template<class t>
//class Digraph
//{
//protected:
//	int Vnum;
//	int Enum;
//	wEdge* edge;
//public:
//	Digraph(int n, int e) {
//		Vnum = n;
//		Enum = e;
//		edge = new wEdge[Enum];
//	}
//	~Digraph() { delete[] edge; }
//	void insert(int v1, int v2, int w, int i) {
//		edge[i] = wEdge(v1, v2, w);
//	}
//	
//	void kruskal() {//kruskal�㷨����һ����С��
//	    long long sum = 0;//��¼Ȩ��ֵ֮��
//
//		sort(edge, edge + Enum);//��Ȩֵ��������
//
//		for (int i = 1; i <= Vnum; i++) {//��ʼ�����鼯
//			a[i] = i;
//		}
//		int v1, v2, w;
//		for (int i = 0; i < Enum; i++) {//ʹ�ò��鼯������С��������Ȩֵ��
//			v1 = edge[i].v1;
//			v2 = edge[i].v2;
//			w = edge[i].w;
//			v1 = find(v1); //��ѯv1��Ӧ�ĸ��ڵ�
//			v2 = find(v2); //��ѯv2��Ӧ�ĸ��ڵ�
//			if (v1 != v2) {//������ͬһ�����ϣ����ñ߼�����С����
//				a[v1] = v2; 
//				sum += w;
//			}
//		}
//		cout << sum << endl;
//	}
//	
//};
//int main() {
//	int n, e;
//	cin >> n >> e;
//	Digraph<int> g(n,e);
//	for (int i = 0; i < e; i++){
//		int v1, v2, w;
//		cin >> v1 >> v2 >> w;
//		g.insert(v1, v2, w,i);
//	}
//	g.kruskal();
//	return 0;
//}